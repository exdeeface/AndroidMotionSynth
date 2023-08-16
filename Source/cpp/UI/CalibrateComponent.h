#pragma once
#include <JuceHeader.h>

class CalibrateComponent  : public juce::Component {
public:
    CalibrateComponent(juce::Component &parent);
    ~CalibrateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton calibrateButton { "Calibrate Z" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CalibrateComponent)


};
