#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"
#include "Sampler.h"
#define SAMPLE_PACK_ID "samplePack"
#define SAMPLE_PACK "SamplePack"

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"
#define OH_GAIN_ID "OHgain"
#define OH_GAIN_NAME "OHGain"
#define ROOM_GAIN_ID "roomGain"
#define ROOM_GAIN_NAME "RoomGain"
#define BLEED_GAIN_ID "bleedGain"
#define BLEED_GAIN_NAME "BleedGain"

#define KICK_CLOSE_GAIN_ID "kickCloseGain"
#define KICK_CLOSE_GAIN_NAME "KickCloseGain"
#define KICK_OH_GAIN_ID "kickOHGain"
#define KICK_OH_GAIN_NAME "KickOHGain"
#define KICK_ROOM_GAIN_ID "kickRoomGain"
#define KICK_ROOM_GAIN_NAME "KickRoomGain"
#define KICK_BLEED_GAIN_ID "kickBleedGain"
#define KICK_BLEED_GAIN_NAME "KickBleedGain"

#define SNARE_TOP_CLOSE_GAIN_ID "snareTopCloseGain"
#define SNARE_TOP_CLOSE_GAIN_NAME "SnareTopCloseGain"
#define SNARE_BOT_CLOSE_GAIN_ID "snareBotCloseGain"
#define SNARE_BOT_CLOSE_GAIN_NAME "SnareBotCloseGain"
#define SNARE_OH_GAIN_ID "snareOHGain"
#define SNARE_OH_GAIN_NAME "SnareOHGain"
#define SNARE_ROOM_GAIN_ID "snareRoomGain"
#define SNARE_ROOM_GAIN_NAME "SnareRoomGain"
#define SNARE_BLEED_GAIN_ID "snareBleedGain"
#define SNARE_BLEED_GAIN_NAME "SnareBleedGain"

#define TOM_CLOSE_GAIN_ID "tomCloseGain"
#define TOM_CLOSE_GAIN_NAME "TomCloseGain"
#define FTOM_CLOSE_GAIN_ID "ftomCloseGain"
#define FTOM_CLOSE_GAIN_NAME "FTomCloseGain"
#define TOMS_OH_GAIN_ID "tomsOHGain"
#define TOMS_OH_GAIN_NAME "TomsOHGain"
#define TOMS_ROOM_GAIN_ID "tomsRoomGain"
#define TOMS_ROOM_GAIN_NAME "TomsRoomGain"
#define TOMS_BLEED_GAIN_ID "tomsBleedGain"
#define TOMS_BLEED_GAIN_NAME "TomsBleedGain"

#define HH_CLOSE_GAIN_ID "hhCloseGain"
#define HH_CLOSE_GAIN_NAME "HHCloseGain"
#define TAMB_CLOSE_GAIN_ID "tambCloseGain"
#define TAMB_CLOSE_GAIN_NAME "TambCloseGain"
#define HH_OH_GAIN_ID "hhOHGain"
#define HH_OH_GAIN_NAME "HHOHGain"
#define HH_ROOM_GAIN_ID "hhRoomGain"
#define HH_ROOM_GAIN_NAME "HHRoomGain"
#define HH_BLEED_GAIN_ID "hhBleedGain"
#define HH_BLEED_GAIN_NAME "HHBleedGain"

#define CRASH_CLOSE_GAIN_ID "crashCloseGain"
#define CRASH_CLOSE_GAIN_NAME "CrashCloseGain"
#define RIDE_CLOSE_GAIN_ID "rideCloseGain"
#define RIDE_CLOSE_GAIN_NAME "RideCloseGain"
#define CYMBALS_OH_GAIN_ID "cymbalsOHGain"
#define CYMBALS_OH_GAIN_NAME "CymbalsOHGain"
#define CYMBALS_ROOM_GAIN_ID "cymbalsRoomGain"
#define CYMBALS_ROOM_GAIN_NAME "CymbalsRoomGain"
#define CYMBALS_BLEED_GAIN_ID "cymbalsBleedGain"
#define CYMBALS_BLEED_GAIN_NAME "CymbalsBleedGain"

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
    void loadSamples(int samplePackID, int curveMenuID, int kickNoteID, int snareNoteID, int snareFlamNoteID);

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

    Sampler samplerKickClose;
    Sampler samplerKickOH;
    Sampler samplerKickRoom;
    Sampler samplerKickBleed;

    Sampler samplerSnareTop;
    Sampler samplerSnareBot;
    Sampler samplerSnareOH;
    Sampler samplerSnareRoom;
    Sampler samplerSnareBleed;

    Sampler samplerTomClose;
    Sampler samplerFTomClose;
    Sampler samplerTomsOH;
    Sampler samplerTomsRoom;
    Sampler samplerTomsBleed;

    Sampler samplerHHClose;
    Sampler samplerTambClose;
    Sampler samplerHHOH;
    Sampler samplerHHRoom;
    Sampler samplerHHBleed;

    Sampler samplerCrashClose;
    Sampler samplerRideClose;
    Sampler samplerCymbalsOH;
    Sampler samplerCymbalsRoom;
    Sampler samplerCymbalsBleed;

    juce::AudioFormatManager formatManager;

    float linCurveFor3[4] = { 1, 40, 60, 128 };
    float linCurveFor4[5] = { 1, 40, 60, 80, 128 };
    float linCurveFor5[6] = { 1, 40, 60, 80, 110, 128 };
    float linCurveFor6[7] = { 1, 40, 60, 80, 110, 124, 128 };

    float logCurveFor3[4] = { 1, 80, 100, 128 };
    float logCurveFor4[5] = { 1, 80, 100, 115, 128 };
    float logCurveFor5[6] = { 1, 80, 100, 115, 122, 128 };
    float logCurveFor6[7] = { 1, 80, 100, 115, 122, 126, 128 };

    void loadDirectory();
    void clearSoundsFromAllSamplers();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessor)
};
