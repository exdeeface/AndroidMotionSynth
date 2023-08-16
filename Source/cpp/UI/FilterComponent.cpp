#include <JuceHeader.h>
#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts) {
    juce::StringArray choices {"Lowpass", "Bandpass", "Highpass"};
    filterTypeSelector.addItemList(choices, 1);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTER", filterTypeSelector);
    addAndMakeVisible(&filterTypeSelector);

    cutoffSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERCUTOFF", cutoffSlider);
    resonanceSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERRES", resonanceSlider);

    setSliderParams(cutoffSlider);
    setSliderParams(resonanceSlider);
}

FilterComponent::~FilterComponent() {
}

void FilterComponent::paint (juce::Graphics& g) {

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void FilterComponent::resized() {
    auto padding = 5;
    auto leftSide = getLocalBounds();
    leftSide.setWidth(getWidth() / 2 - 5);
    leftSide.setX(5);
    auto rightSide = getLocalBounds();
    rightSide.setWidth(getWidth() / 2 - 5);
    rightSide.setX(leftSide.getRight() + 5);
    cutoffSlider.setBounds(leftSide);
    resonanceSlider.setBounds(rightSide);
}

void FilterComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 100);
    addAndMakeVisible(slider);
}
