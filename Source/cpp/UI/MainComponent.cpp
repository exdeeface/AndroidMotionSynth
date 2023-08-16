#include <JuceHeader.h>
#include "MainComponent.h"

MainComponent::MainComponent(TestSynthAudioProcessor &ap) : audioProcessor(ap),
                                                            adsrComponent(audioProcessor.apvts),
                                                            oscComponent(audioProcessor.apvts),
                                                            playComponent(ap),
                                                            calibrateComponent(*this) {
    addAndMakeVisible(&adsrComponent);
    addAndMakeVisible(&oscComponent);
    addAndMakeVisible(&calibrateComponent);
    addAndMakeVisible(&playComponent);

#if defined(JUCE_ANDROID)
    startTimerHz(200);
#endif

}

MainComponent::~MainComponent() {

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
    oscBounds.setWidth(getWidth()/2);
    oscComponent.setBounds(oscBounds);
    auto calibrateBounds = oscBounds;
    calibrateBounds.setX(oscBounds.getRight());
    calibrateComponent.setBounds(calibrateBounds);
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
    jclass juce_app = jvm->FindClass("com/me/NativeAndroid/NativeApp");

    rotX = Java_com_rmsl_juce_JuceApp_getPitch(jvm, juce_app) * -1.0f;
    rotY = Java_com_rmsl_juce_JuceApp_getRoll(jvm, juce_app);
    rotZ = Java_com_rmsl_juce_JuceApp_getYaw(jvm, juce_app);

    const juce::NormalisableRange<float> sourceX {-juce::MathConstants<float>::halfPi, juce::MathConstants<float>::halfPi};
    const juce::NormalisableRange<float> sourceY {-juce::MathConstants<float>::pi, juce::MathConstants<float>::pi};
    const juce::NormalisableRange<float> sourceZ {-juce::MathConstants<float>::pi, juce::MathConstants<float>::pi};

    const juce::NormalisableRange<float> targetX {20.0f, 20000.0f, 0.1f, 0.6f};
    const juce::NormalisableRange<float> targetY {-1.0f, 1.0f};
    const juce::NormalisableRange<float> targetZ {0.0f, 10.0f};

    adsrComponent.filterComponent.cutoffSlider.setValue(targetX.convertFrom0to1(sourceX.convertTo0to1(rotX)));
    adsrComponent.pitchSlider.setValue(targetY.convertFrom0to1(sourceY.convertTo0to1(rotY)));

    float modRotZ = rotZ - zOffset;

    if (modRotZ > juce::MathConstants<float>::pi) {
        float delta = modRotZ - juce::MathConstants<float>::pi;
        modRotZ = -juce::MathConstants<float>::pi + delta;
    } else if (modRotZ < -juce::MathConstants<float>::pi) {
        float delta = modRotZ + juce::MathConstants<float>::pi;
        modRotZ = juce::MathConstants<float>::pi + delta;
    }

    adsrComponent.filterComponent.resonanceSlider.setValue(targetZ.convertFrom0to1(sourceZ.convertTo0to1(modRotZ)));
#endif
}

void MainComponent::resetOrientation() {
    zOffset = rotZ;
}
