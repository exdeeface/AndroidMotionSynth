#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType(const int choice) {
    switch (choice) {
    case 0:
        //sin
        initialise([](float x) { return std::sin(x); });
        break;

    case 1:
        //saw
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        break;

    case 2:
        //square
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;

    default:
        jassertfalse;
        break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber) {
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)); // + fmMod);
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock) {
#ifndef JUCE_ANDROID
    for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel) {
        for (int sample = 0; sample < audioBlock.getNumSamples(); ++sample) {
            fmMod = fmOsc.processSample(audioBlock.getSample(channel, sample)); // * fmDepth;
        }
    }
#endif
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::setFmParams(const float freq, const float depth) {
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote)); // + fmMod);
}
