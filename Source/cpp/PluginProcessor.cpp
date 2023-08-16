#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Data/SynthSound.h"
#include "Data/SynthVoice.h"

TestSynthAudioProcessor::TestSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    for (int i = 0; i < 3; ++i) { synth.addVoice(new SynthVoice()); }
    synth.addSound(new SynthSound());
#if defined(JUCE_ANDROID)
    jab = juce::JUCEApplicationBase::getInstance();
#endif
}

TestSynthAudioProcessor::~TestSynthAudioProcessor() {

}

const juce::String TestSynthAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool TestSynthAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestSynthAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestSynthAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int TestSynthAudioProcessor::getNumPrograms() {
    return 1;
}

int TestSynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void TestSynthAudioProcessor::setCurrentProgram (int index) {

}

const juce::String TestSynthAudioProcessor::getProgramName (int index) {
    return {};
}

void TestSynthAudioProcessor::changeProgramName (int index, const juce::String& newName) {

}

void TestSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    synth.setCurrentPlaybackSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void TestSynthAudioProcessor::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

bool hasSentFirstNote = false;
bool noteStarted = false;

void TestSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {

    if (startNote && !noteStarted) {
        midiMessages.addEvent(juce::MidiMessage::noteOn(1, 45, 1.0f), 0);
        midiMessages.addEvent(juce::MidiMessage::noteOn(2, 52, 1.0f), 0);
        midiMessages.addEvent(juce::MidiMessage::noteOn(3, 55, 1.0f), 0);
        noteStarted = true;
    } else if (!startNote && noteStarted) {
        midiMessages.addEvent(juce::MidiMessage::noteOff(1, 45, 1.0f), 0);
        midiMessages.addEvent(juce::MidiMessage::noteOff(2, 52, 1.0f), 0);
        midiMessages.addEvent(juce::MidiMessage::noteOff(3, 55, 1.0f), 0);
        noteStarted = false;
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            auto &oscWave = *apvts.getRawParameterValue("OSC");

            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");

            auto &gain = *apvts.getRawParameterValue("GAIN");
            auto &attack = *apvts.getRawParameterValue("ATTACK");
            auto &decay = *apvts.getRawParameterValue("DECAY");
            auto &sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto &release = *apvts.getRawParameterValue("RELEASE");
            auto &pitch = *apvts.getRawParameterValue("PITCH");
            
            voice->getOscillator().setWaveType(oscWave);

            #if defined(JUCE_ANDROID) 
                voice->setPitchBend(pitch.load());
            #endif

            voice->updateASDR(gain.load(), attack.load(), decay.load(), sustain.load(), release.load()); 
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    auto &filterType = *apvts.getRawParameterValue("FILTER");
    auto &cutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto &resonance = *apvts.getRawParameterValue("FILTERRES");

    filter.updateParameters(filterType.load(), cutoff.load(), resonance.load());
    filter.processBlock(buffer);

#if defined(JUCE_ANDROID) //find a better place to put this
    if (jab->backButtonPressed()) {
        jab->quit();
    }
#endif
}

bool TestSynthAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* TestSynthAudioProcessor::createEditor() {
    return new TestSynthAudioProcessorEditor (*this);
}

void TestSynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {

}

void TestSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {

}

juce::AudioProcessorValueTreeState::ParameterLayout TestSynthAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray({"Sin", "Saw", "Sqr"}), 1));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.25f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 2.0f, 1.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("PITCH", "Pitch", -1.0f, 1.0f, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER", "Filter", juce::StringArray {"Lowpass", "Bandpass", "Highpass"}, 2));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.6f}, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float> {1.0f, 10.0f, 0.1f}, 1.0f));

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new TestSynthAudioProcessor();
}
