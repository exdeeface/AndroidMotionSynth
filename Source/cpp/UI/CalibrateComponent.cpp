#include <JuceHeader.h>
#include "CalibrateComponent.h"
#include "MainComponent.h"

CalibrateComponent::CalibrateComponent(juce::Component &parent) {
    calibrateButton.setClickingTogglesState(true);
    calibrateButton.onClick = [&]() {
        if (typeid(parent) == typeid(MainComponent)) {
            dynamic_cast<MainComponent&>(parent).resetOrientation();
        }
    };
    addAndMakeVisible(&calibrateButton);
}

CalibrateComponent::~CalibrateComponent() {

}

void CalibrateComponent::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void CalibrateComponent::resized() {
    calibrateButton.setBounds(getWidth() / 2 - 50, getHeight() / 2, 100, 20);
}