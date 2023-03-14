#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"
#include "Sampler.h"
#define GAIN_ID "gain"
#define GAIN_NAME "Gain"
#define OH_GAIN_ID "OHgain"
#define OH_GAIN_NAME "OHGain"
#define ROOM_GAIN_ID "roomGain"
#define ROOM_GAIN_NAME "RoomGain"
#define BLEED_GAIN_ID "bleedGain"
#define BLEED_GAIN_NAME "BleedGain"
#define SAMPLE_PACK_ID "samplePack"
#define SAMPLE_PACK "SamplePack"
#define KICK_CLOSE_GAIN_ID "kickCloseGain"
#define KICK_CLOSE_GAIN_NAME "KickCloseGain"
#define SNARE_TOP_CLOSE_GAIN_ID "snareTopCloseGain"
#define SNARE_TOP_CLOSE_GAIN_NAME "SnareTopCloseGain"

using namespace std;

class HDrumsAudioProcessor  : public juce::AudioProcessor
{
public:
    HDrumsAudioProcessor();
    ~HDrumsAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
   #endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void addSample(string sampleName, string destination, int midiNote, int lowestVelocity, int highestVelocity, double release, double maxLength, string bus);
    void loadSamples(int samplePackID, int curveMenuID, int kickNoteID, int snareNoteID);

    juce::MidiMessageCollector& getMidiMessageCollector() noexcept { return midiMessageCollector; }

    juce::MidiBuffer processedBuffer;

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    MidiProcessor midiProcessor;

private:
    
    juce::MidiMessageCollector midiMessageCollector;
    
    Sampler sampler;
    Sampler samplerOH;
    Sampler samplerRoom;
    Sampler samplerBleed;
    juce::AudioFormatManager formatManager;

    float linCurve[5] = {40, 60, 80, 110, 124};
    float logCurve[5] = {80, 100, 115, 122, 126};

    void loadDirectory();
    void clearSoundsFromAllSamplers();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessor)
};
