
#include <JuceHeader.h>
#include "PlayComponent.h"

PlayComponent::PlayComponent(TestSynthAudioProcessor &ap) : audioProcessor(ap) {

}

PlayComponent::~PlayComponent() {

}

void PlayComponent::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    g.setColour (juce::Colours::white);
    g.setFont (18.0f);
    g.drawText ("press me!", getLocalBounds(), juce::Justification::centred, true);
}

void PlayComponent::resized() {

}

void PlayComponent::mouseDown(const juce::MouseEvent& event) {
    audioProcessor.startNote = true;
}

void PlayComponent::mouseUp(const juce::MouseEvent& event) {
    audioProcessor.startNote = false;
}
