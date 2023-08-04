#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR {
public:
	void updateADSR(const float gain, const float attack, const float decay, const float sustain, const float release);

	juce::ADSR::Parameters adsrParameters;
	juce::dsp::Gain<float> gain;
private:
	
};

