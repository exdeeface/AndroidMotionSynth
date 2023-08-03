#include <JuceHeader.h>
#include "ADSRComponent.h"

#if defined(JUCE_ANDROID)
    #include "jni.h"
    #include <android/log.h>

    #define TAG "STUPORVILLAIN"
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)
    #define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#endif

ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts) {
    setSliderParams(gainSlider);
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

    setSliderParams(pitchSlider);

    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "GAIN", gainSlider);
    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "ATTACK", attackSlider);
    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", releaseSlider);

    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "PITCH", pitchSlider);
}

ADSRComponent::~ADSRComponent() {

}

void ADSRComponent::paint (juce::Graphics& g) {

}

void ADSRComponent::resized() {
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(padding * 4);

    const auto sliderWidth = bounds.getWidth() / 2;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = padding;
    const auto sliderStartY = padding * 4;

    gainSlider.setBounds(sliderStartX + padding * 2, sliderStartY, sliderWidth, sliderHeight);
    pitchSlider.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

/*
void ADSRComponent::resized() {
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(padding*4);
    
    const auto sliderWidth = bounds.getWidth() / 5;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = padding;
    const auto sliderStartY = padding*4;

    gainSlider.setBounds(sliderStartX + padding, sliderStartY, sliderWidth, sliderHeight);
    attackSlider.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}
*/

void ADSRComponent::setSliderParams(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 100);
    addAndMakeVisible(slider);
}