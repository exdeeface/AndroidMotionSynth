#include <JuceHeader.h>
#include "MainComponent.h"

MainComponent::MainComponent(TestSynthAudioProcessor &ap) : audioProcessor(ap),
                                                            adsrComponent(audioProcessor.apvts),
                                                            oscComponent(audioProcessor.apvts, "OSC"),
                                                            playComponent(ap) {
    addAndMakeVisible(&adsrComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&playComponent);

#if defined(JUCE_ANDROID)
    //motionManager.start();
    startTimerHz(200);
#endif

}

MainComponent::~MainComponent() {
#if defined(JUCE_ANDROID)
    //motionManager.stop();
#endif
}

void MainComponent::paint (juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    auto adsrBounds = getLocalBounds();
    adsrBounds.setHeight(getHeight() / 10 * 6);
    adsrBounds.setY(100);
    adsrComponent.setBounds(adsrBounds);
    auto oscBounds = getLocalBounds();
    oscBounds.setHeight(100);
    oscComponent.setBounds(oscBounds);
    auto playBounds = getLocalBounds().reduced(10);
    playBounds.setHeight(getHeight() / 10 * 2.5);
    playBounds.setY(getHeight() / 10 * 7);
    playComponent.setBounds(playBounds);
}

#if defined(JUCE_ANDROID)
    extern "C" JNIEXPORT jfloat JNICALL Java_com_rmsl_juce_JuceApp_getPitch(JNIEnv *env, jclass clazz) {
        jmethodID get_pitch_id = env->GetStaticMethodID(clazz, "getPitch", "()F");
        return env->CallStaticFloatMethod(clazz, get_pitch_id);
    }

    extern "C" JNIEXPORT jfloat JNICALL Java_com_rmsl_juce_JuceApp_getRoll(JNIEnv *env, jclass clazz) {
        jmethodID get_roll_id = env->GetStaticMethodID(clazz, "getRoll", "()F");
        return env->CallStaticFloatMethod(clazz, get_roll_id);
    }
    extern "C" JNIEXPORT jfloat JNICALL Java_com_rmsl_juce_JuceApp_getYaw(JNIEnv *env, jclass clazz) {
        jmethodID get_yaw_id = env->GetStaticMethodID(clazz, "getYaw", "()F");
        return env->CallStaticFloatMethod(clazz, get_yaw_id);
    }
#endif

void MainComponent::timerCallback() {
#if defined(JUCE_ANDROID)

    JNIEnv* jvm = juce::getEnv();
    jclass juce_app = jvm->FindClass("com/rmsl/juce/JuceApp");

    rotX = Java_com_rmsl_juce_JuceApp_getPitch(jvm, juce_app) * -1.0f;
    rotY = Java_com_rmsl_juce_JuceApp_getRoll(jvm, juce_app);
    rotZ = Java_com_rmsl_juce_JuceApp_getYaw(jvm, juce_app);

    const juce::NormalisableRange<float> sourceX {-juce::MathConstants<float>::halfPi, juce::MathConstants<float>::halfPi};
    float pitchToGain = sourceX.convertTo0to1(rotX);
    adsrComponent.gainSlider.setValue(pitchToGain - 0.10f);

    const juce::NormalisableRange<float> sourceY {-juce::MathConstants<float>::pi, juce::MathConstants<float>::pi};
    const juce::NormalisableRange<float> targetY {-1.0f, 1.0f};
    const juce::NormalisableRange<float> targetYToWhatever {0, 16383};
    float yh = targetY.convertFrom0to1(sourceY.convertTo0to1(rotY));
    adsrComponent.pitchSlider.setValue(yh);
#endif
}