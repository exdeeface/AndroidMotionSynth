#include "PluginProcessor.h"
#include "PluginEditor.h"

TestSynthAudioProcessorEditor::TestSynthAudioProcessorEditor (TestSynthAudioProcessor& p) : AudioProcessorEditor(&p), audioProcessor(p), mainComponent(audioProcessor) {
    addAndMakeVisible(mainComponent);
    setSize (1280, 720);
}

TestSynthAudioProcessorEditor::~TestSynthAudioProcessorEditor() {

}

void TestSynthAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void TestSynthAudioProcessorEditor::resized() {
    mainComponent.setBounds(getLocalBounds());
}

void TestSynthAudioProcessorEditor::mouseDown(const juce::MouseEvent& event) {
    audioProcessor.startNote = true;
}

void TestSynthAudioProcessorEditor::mouseUp(const juce::MouseEvent& event) {
    audioProcessor.startNote = false;
}

