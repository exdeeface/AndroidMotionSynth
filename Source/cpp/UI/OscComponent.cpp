#include <JuceHeader.h>
#include "OscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts) {
    juce::StringArray choices {"Sin", "Saw", "Sqr"};
    oscWaveSelector.addItemList(choices, 1);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC", oscWaveSelector);
    addAndMakeVisible(&oscWaveSelector);
}

OscComponent::~OscComponent() {

}

void OscComponent::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void OscComponent::resized() {
    oscWaveSelector.setBounds(getWidth() / 2 - 50, getHeight() / 2, 100, 20);
}
