#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    osc.setWaveFrequency(midiNoteNumber);
    lastMidiNote = midiNoteNumber;
    fullStepUp = lastMidiNote + 4;
    fullStepDown = lastMidiNote - 4;

    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::setPitchBend(float pitchWheelPos) {
    juce::NormalisableRange<float> sourceRange {-1.0f, 1.0f};
    sourceRange.setSkewForCentre(0.0f);
    if (lastMidiNote != 0) {
        juce::NormalisableRange<float> targetRange {float(juce::MidiMessage::getMidiNoteInHertz(fullStepDown)), float(juce::MidiMessage::getMidiNoteInHertz(fullStepUp))};
        targetRange.setSkewForCentre(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote));

        float freqChange = targetRange.convertFrom0to1(sourceRange.convertTo0to1(pitchWheelPos));
        osc.setFrequency(freqChange, true);
        lastPitchWheelVal = pitchWheelPos;
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
    if (lastRecievedPitchWheelValue != newPitchWheelValue) {
        lastRecievedPitchWheelValue = newPitchWheelValue;

        if (lastRecievedPitchWheelValue > 8192) {
            pitchBend = float(lastRecievedPitchWheelValue - 8192) / (16383 - 8192);
        }   else {
            pitchBend = float(8192 - lastRecievedPitchWheelValue) / - 8192;
        }
    }

    if (pitchBend > 1.0f) {
        pitchBend = 1.0f;
    } else if (pitchBend < -1.0f) {
        pitchBend = -1.0f;
    }

    lastPitchWheelVal = pitchBend;
    setPitchBend(pitchBend);
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    adsr.gain.prepare(spec);

    adsr.adsrParameters.attack = 0.1f;
    adsr.adsrParameters.decay = 0.1f;
    adsr.adsrParameters.sustain = 0.4f;
    adsr.adsrParameters.release = 1.0f;
    
    adsr.setParameters(adsr.adsrParameters);

    isPrepared = true;
}

void SynthVoice::updateASDR(const float gain_param, const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(gain_param, attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    adsr.gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }
}
