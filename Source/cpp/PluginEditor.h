#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/MainComponent.h"

class TestSynthAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    TestSynthAudioProcessorEditor (TestSynthAudioProcessor&);
    ~TestSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
private:

    TestSynthAudioProcessor& audioProcessor;
    MainComponent mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestSynthAudioProcessorEditor)
};
