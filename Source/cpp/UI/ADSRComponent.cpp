#include <JuceHeader.h>
#include "ADSRComponent.h"

ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts) : filterComponent(apvts) {
    setSliderParams(gainSlider);
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    setSliderParams(pitchSlider);

    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "GAIN", gainSlider);
    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "ATTACK", attackSlider);
    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", releaseSlider);

    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PITCH", pitchSlider);

    addAndMakeVisible(&filterComponent);
}

ADSRComponent::~ADSRComponent() {

}

void ADSRComponent::paint (juce::Graphics& g) {

}

void ADSRComponent::resized() {
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(padding * 4);

    const auto sliderWidth = bounds.getWidth() / 4;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = padding;
    const auto sliderStartY = padding * 4;

    gainSlider.setBounds(sliderStartX + padding * 2, sliderStartY, sliderWidth, sliderHeight);
    pitchSlider.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    filterComponent.setBounds(pitchSlider.getRight() + padding, sliderStartY, sliderWidth * 2, sliderHeight);
}

/*
void ADSRComponent::resized() {
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(padding*4);
    
    const auto sliderWidth = bounds.getWidth() / 5;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = padding;
    const auto sliderStartY = padding*4;

    gainSlider.setBounds(sliderStartX + padding, sliderStartY, sliderWidth, sliderHeight);
    attackSlider.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}
*/

void ADSRComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 100);
    addAndMakeVisible(slider);
}