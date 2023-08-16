#pragma once
#include <JuceHeader.h>
#include "FilterComponent.h"

class ADSRComponent : public juce::Component {
public:
    ADSRComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderParams(juce::Slider& slider);

    juce::Slider gainSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Slider pitchSlider;

    FilterComponent filterComponent;

private:
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
