#pragma once
#include <JuceHeader.h>
#include "ADSRData.h"
#include "OscData.h"

#if defined(JUCE_ANDROID)
    #include <android/log.h>

    #define TAG "STUPORVILLAIN"
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)
    #define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#endif

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void setPitchBend(float pitchWheelPos);
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void updateASDR(const float gain, const float attack, const float decay, const float sustain, const float release);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;    
    OscData& getOscillator() { return osc; }


private:
    float lastPitchWheelVal {0.0f};
    int lastRecievedPitchWheelValue;
    int lastMidiNote;
    int fullStepUp;
    int fullStepDown;
    float pitchBend { 0.0f };

    OscData osc;
    ADSRData adsr;
    bool isPrepared{ false };
    juce::AudioBuffer<float> synthBuffer;
};