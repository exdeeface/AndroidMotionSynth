#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public:
	void prepareToPlay(juce::dsp::ProcessSpec& spec);
	void setWaveType(const int choice);
	void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);
	void setWaveFrequency(const int midiNoteNumber);
	void setFmParams(const float frequency, const float depth);

private:
	juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin(x); }};
	float fmMod { 0.0f };
	float fmDepth { 0.0f };
	int lastMidiNote;
};