#pragma once
#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "ADSRComponent.h"
#include "OscComponent.h"
#include "PlayComponent.h"
#include "FilterComponent.h"
#include "CalibrateComponent.h"

#if defined(JUCE_ANDROID)
    #include <jni.h>
    #include "android/log.h"
    #include "juce_core/native/juce_JNIHelpers_android.h"

    #define TAG "STUPORVILLAIN"
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)
    #define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#endif

class MainComponent : public juce::Component, public juce::Timer {
public:
    MainComponent(TestSynthAudioProcessor& ap);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void resetOrientation();

private:
    float zOffset { 0.0f };
    bool isReady = false;

    float rotX { 0.0f };
    float rotY { 0.0f };
    float rotZ { 0.0f };

    TestSynthAudioProcessor& audioProcessor;

    ADSRComponent adsrComponent;
    OscComponent oscComponent;
    CalibrateComponent calibrateComponent;
    PlayComponent playComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
