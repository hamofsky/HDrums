#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"
#include "Sampler.h"
#define SAMPLE_PACK_ID "sample Pack"
#define SAMPLE_PACK_NAME "Sample Pack"
#define CURVE_MENU_ID "velocity Curve"
#define CURVE_MENU_NAME "Velocity Curve"

#define KICK_MIDI_NOTE_ID "MIDI note kick"
#define KICK_MIDI_NOTE_NAME "MIDI note Kick"

#define SNARE_MIDI_NOTE_ID "MIDI note snare"
#define SNARE_MIDI_NOTE_NAME "MIDI note Snare"
#define SNARE_FLAM_MIDI_NOTE_ID "MIDI note snare Flam"
#define SNARE_FLAM_MIDI_NOTE_NAME "MIDI note Snare Flam"
#define SNARE_ROUND_MIDI_NOTE_ID "MIDI note snare Round"
#define SNARE_ROUND_MIDI_NOTE_NAME "MIDI note Snare Round"
#define SNARE_WIRELESS_MIDI_NOTE_ID "MIDI note snare Wireless"
#define SNARE_WIRELESS_MIDI_NOTE_NAME "MIDI note Snare Wireless"
#define SNARE_WIRELESS_ROUND_MIDI_NOTE_ID "MIDI note snare Wireless Round"
#define SNARE_WIRELESS_ROUND_MIDI_NOTE_NAME "MIDI note Snare Wireless Round"

#define TOM_MIDI_NOTE_ID "MIDI note tom"
#define TOM_MIDI_NOTE_NAME "MIDI note Tom"
#define TOM_FLAM_MIDI_NOTE_ID "MIDI note tom Flam"
#define TOM_FLAM_MIDI_NOTE_NAME "MIDI note Tom Flam"
#define FTOM_MIDI_NOTE_ID "MIDI note ftom"
#define FTOM_MIDI_NOTE_NAME "MIDI note FTom"
#define FTOM_FLAM_MIDI_NOTE_ID "MIDI note ftom Flam"
#define FTOM_FLAM_MIDI_NOTE_NAME "MIDI note FTom Flam"

#define HH_BELL_MIDI_NOTE_ID "MIDI note hh Bell"
#define HH_BELL_MIDI_NOTE_NAME "MIDI note HH Bell"
#define HH_CLOSED_MIDI_NOTE_ID "MIDI note hh Closed"
#define HH_CLOSED_MIDI_NOTE_NAME "MIDI note HH Closed"
#define HH_HALF_MIDI_NOTE_ID "MIDI note hh Half"
#define HH_HALF_MIDI_NOTE_NAME "MIDI note HH Half"
#define HH_OPEN_MIDI_NOTE_ID "MIDI note hh Open"
#define HH_OPEN_MIDI_NOTE_NAME "MIDI note HH Open"
#define TAMB_MIDI_NOTE_ID "MIDI note tambourine"
#define TAMB_MIDI_NOTE_NAME "MIDI note Tambourine"

#define RIDE_POINT_MIDI_NOTE_ID "MIDI note ride Point"
#define RIDE_POINT_MIDI_NOTE_NAME "MIDI note Ride Point"
#define RIDE_HALF_MIDI_NOTE_ID "MIDI note ride Half"
#define RIDE_HALF_MIDI_NOTE_NAME "MIDI note Ride Half"
#define RIDE_BELL_MIDI_NOTE_ID "MIDI note ride Bell"
#define RIDE_BELL_MIDI_NOTE_NAME "MIDI note Ride Bell"
#define RIDE_OPEN_MIDI_NOTE_ID "MIDI note ride Open"
#define RIDE_OPEN_MIDI_NOTE_NAME "MIDI note Ride Open"

#define CRASH_POINT_MIDI_NOTE_ID "MIDI note crash Point"
#define CRASH_POINT_MIDI_NOTE_NAME "MIDI note Crash Point"
#define CRASH_BELL_MIDI_NOTE_ID "MIDI note crash Bell"
#define CRASH_BELL_MIDI_NOTE_NAME "MIDI note Crash Bell"
#define CRASH_OPEN_MIDI_NOTE_ID "MIDI note crash Open"
#define CRASH_OPEN_MIDI_NOTE_NAME "MIDI note Crash Open"

#define GAIN_ID "close"
#define GAIN_NAME "Close"
#define OH_GAIN_ID "OH"
#define OH_GAIN_NAME "OH"
#define ROOM_GAIN_ID "room"
#define ROOM_GAIN_NAME "Room"
#define BLEED_GAIN_ID "bleed"
#define BLEED_GAIN_NAME "Bleed"

#define KICK_CLOSE_GAIN_ID "kick Close"
#define KICK_CLOSE_GAIN_NAME "Kick Close"
#define KICK_OH_GAIN_ID "kick OH"
#define KICK_OH_GAIN_NAME "Kick OH"
#define KICK_ROOM_GAIN_ID "kick Room"
#define KICK_ROOM_GAIN_NAME "Kick Room"
#define KICK_BLEED_GAIN_ID "kick Bleed"
#define KICK_BLEED_GAIN_NAME "Kick Bleed"

#define SNARE_TOP_CLOSE_GAIN_ID "snare Top"
#define SNARE_TOP_CLOSE_GAIN_NAME "Snare Top"
#define SNARE_BOT_CLOSE_GAIN_ID "snare Bottom"
#define SNARE_BOT_CLOSE_GAIN_NAME "Snare Bottom"
#define SNARE_OH_GAIN_ID "snare OH"
#define SNARE_OH_GAIN_NAME "Snare OH"
#define SNARE_ROOM_GAIN_ID "snare Room"
#define SNARE_ROOM_GAIN_NAME "Snare Room"
#define SNARE_BLEED_GAIN_ID "snare Bleed"
#define SNARE_BLEED_GAIN_NAME "Snare Bleed"

#define TOM_CLOSE_GAIN_ID "tom Close"
#define TOM_CLOSE_GAIN_NAME "Tom Close"
#define FTOM_CLOSE_GAIN_ID "ftom Close"
#define FTOM_CLOSE_GAIN_NAME "FTom Close"
#define TOMS_OH_GAIN_ID "toms OH"
#define TOMS_OH_GAIN_NAME "Toms OH"
#define TOMS_ROOM_GAIN_ID "toms Room"
#define TOMS_ROOM_GAIN_NAME "Toms Room"
#define TOMS_BLEED_GAIN_ID "toms Bleed"
#define TOMS_BLEED_GAIN_NAME "Toms Bleed"

#define HH_CLOSE_GAIN_ID "hh Close"
#define HH_CLOSE_GAIN_NAME "HH Close"
//#define TAMB_CLOSE_GAIN_ID "tamb Close"
//#define TAMB_CLOSE_GAIN_NAME "Tamb Close"
//#define HH_OH_GAIN_ID "hh OH"
//#define HH_OH_GAIN_NAME "HH OH"
//#define HH_ROOM_GAIN_ID "hh Room"
//#define HH_ROOM_GAIN_NAME "HH Room"
//#define HH_BLEED_GAIN_ID "hh Bleed"
//#define HH_BLEED_GAIN_NAME "HH Bleed"
//
//#define CRASH_CLOSE_GAIN_ID "crash Close"
//#define CRASH_CLOSE_GAIN_NAME "Crash Close"
//#define RIDE_CLOSE_GAIN_ID "ride Close"
//#define RIDE_CLOSE_GAIN_NAME "Ride Close"
#define CYMBALS_OH_GAIN_ID "cymbals OH"
#define CYMBALS_OH_GAIN_NAME "Cymbals OH"
#define CYMBALS_ROOM_GAIN_ID "cymbals Room"
#define CYMBALS_ROOM_GAIN_NAME "Cymbals Room"
#define CYMBALS_BLEED_GAIN_ID "cymbals Bleed"
#define CYMBALS_BLEED_GAIN_NAME "Cymbals Bleed"

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
    void loadSamples(int samplePackID, int kickNoteID, int snareNoteID, int snareFlamNoteID, int snareRoundNoteID,
                    int snareWirelessNoteID, int snareWirelessRoundNoteID, int tomNoteID, int tomFlamNoteID, int ftomNoteID, int ftomFlamNoteID,
                    int tambourineNoteID, int hhBellNoteID, int hhClosedNoteID, int hhHalfNoteID, int hhOpenNoteID,  int ridePointNoteID,
                    int rideHalfNoteID, int rideBellNoteID, int rideOpenNoteID, int crashPointNoteID, int crashBellNoteID, int crashOpenNoteID);

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
    /*Sampler samplerTambClose;
    Sampler samplerHHOH;
    Sampler samplerHHRoom;
    Sampler samplerHHBleed;

    Sampler samplerCrashClose;
    Sampler samplerRideClose;*/
    Sampler samplerCymbalsOH;
    Sampler samplerCymbalsRoom;
    Sampler samplerCymbalsBleed;

    juce::AudioFormatManager formatManager;

    float linCurveFor3[4] = { 0, 43, 85, 129 };
    float linCurveFor4[5] = { 0, 32, 64, 96, 129 };
    float linCurveFor5[6] = { 0, 26, 51, 77, 102, 129 };
    float linCurveFor6[7] = { 0, 21, 43, 64, 85, 107, 129 };

    void loadDirectory();
    void clearSoundsFromAllSamplers();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessor)
};
