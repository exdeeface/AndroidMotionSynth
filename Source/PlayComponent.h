#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class PlayComponent  : public juce::Component {
public:
    PlayComponent(TestSynthAudioProcessor &ap);
    ~PlayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

private:
    TestSynthAudioProcessor &audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayComponent)
};
