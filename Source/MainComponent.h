#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSRComponent.h"
#include "OscComponent.h"
#include "PlayComponent.h"

#if defined(JUCE_ANDROID)
    #include <jni.h>
    #include "android/log.h"
    #include "juce_core/native/juce_JNIHelpers_android.h"
#endif

class MainComponent : public juce::Component, public juce::Timer {
public:
    MainComponent(TestSynthAudioProcessor& ap);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    bool isReady = false;

#if defined(JUCE_ANDROID)
    //MotionManager motionManager;
#endif

    float rotX{ 0.0f };
    float rotY{ 0.0f };
    float rotZ{ 0.0f };

    TestSynthAudioProcessor& audioProcessor;
    ADSRComponent adsrComponent;
    OscComponent oscComponent;
    PlayComponent playComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
