#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"
#include "Sampler.h"

// ComboBoxes ===========================
#define SAMPLE_PACK_ID "sample Pack"
#define SAMPLE_PACK_NAME "Sample Pack"
#define CURVE_MENU_ID "velocity Curve"
#define CURVE_MENU_NAME "Velocity Curve"

// MIDI notes ===========================
#define KICK_MIDI_NOTE_ID "MIDI note kick"
#define KICK_MIDI_NOTE_NAME "MIDI note Kick"

#define SNARE_MIDI_NOTE_ID "MIDI note snare"
#define SNARE_MIDI_NOTE_NAME "MIDI note Snare"
#define SNARE_SWIRL_MIDI_NOTE_ID "MIDI note snare Swirl"
#define SNARE_SWIRL_MIDI_NOTE_NAME "MIDI note Snare Swirl"
#define SNARE_FLAM_MIDI_NOTE_ID "MIDI note snare Flam"
#define SNARE_FLAM_MIDI_NOTE_NAME "MIDI note Snare Flam"
#define SNARE_ROUND_MIDI_NOTE_ID "MIDI note snare Round"
#define SNARE_ROUND_MIDI_NOTE_NAME "MIDI note Snare Round"
#define SNARE_WIRELESS_MIDI_NOTE_ID "MIDI note snare Wireless"
#define SNARE_WIRELESS_MIDI_NOTE_NAME "MIDI note Snare Wireless"
#define SNARE_WIRELESS_ROUND_MIDI_NOTE_ID "MIDI note snare Wireless Round"
#define SNARE_WIRELESS_ROUND_MIDI_NOTE_NAME "MIDI note Snare Wireless Round"

#define SNARE_PICCOLO_MIDI_NOTE_ID "MIDI note snare Piccolo"
#define SNARE_PICCOLO_MIDI_NOTE_NAME "MIDI note Snare Piccolo"
#define SNARE_PICCOLO_SWIRL_MIDI_NOTE_ID "MIDI note snare Piccolo Swirl"
#define SNARE_PICCOLO_SWIRL_MIDI_NOTE_NAME "MIDI note Snare Piccolo Swirl"

#define TOM_MIDI_NOTE_ID "MIDI note tom"
#define TOM_MIDI_NOTE_NAME "MIDI note Tom"
#define TOM_FLAM_MIDI_NOTE_ID "MIDI note tom Flam"
#define TOM_FLAM_MIDI_NOTE_NAME "MIDI note Tom Flam"
#define FTOM_MIDI_NOTE_ID "MIDI note ftom"
#define FTOM_MIDI_NOTE_NAME "MIDI note FTom"
#define FTOM_FLAM_MIDI_NOTE_ID "MIDI note ftom Flam"
#define FTOM_FLAM_MIDI_NOTE_NAME "MIDI note FTom Flam"

#define HH_FOOT_MIDI_NOTE_ID "MIDI note hh Foot"
#define HH_FOOT_MIDI_NOTE_NAME "MIDI note HH Foot"
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

#define STACK_CLOSED_MIDI_NOTE_ID "MIDI note stack Closed"
#define STACK_CLOSED_MIDI_NOTE_NAME "MIDI note Stack Closed"
#define STACK_OPEN_MIDI_NOTE_ID "MIDI note stack Open"
#define STACK_OPEN_MIDI_NOTE_NAME "MIDI note Stack Open"

#define STICKS_MIDI_NOTE_ID "MIDI note sticks"
#define STICKS_MIDI_NOTE_NAME "MIDI note Sticks"

// Slider Values ========================================
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
#define CYMBALS_OH_GAIN_ID "cymbals OH"
#define CYMBALS_OH_GAIN_NAME "Cymbals OH"
#define CYMBALS_ROOM_GAIN_ID "cymbals Room"
#define CYMBALS_ROOM_GAIN_NAME "Cymbals Room"
#define CYMBALS_BLEED_GAIN_ID "cymbals Bleed"
#define CYMBALS_BLEED_GAIN_NAME "Cymbals Bleed"

// Solo buttons =====================
#define CLOSE_SOLO_ID "close Solo"
#define CLOSE_SOLO_NAME "Close Solo"
#define OH_SOLO_ID "oh Solo"
#define OH_SOLO_NAME "OH Solo"
#define ROOM_SOLO_ID "room Solo"
#define ROOM_SOLO_NAME "Room Solo"
#define BLEED_SOLO_ID "bleed Solo"
#define BLEED_SOLO_NAME "Bleed Solo"

#define KICK_CLOSE_SOLO_ID "kick Close Solo"
#define KICK_CLOSE_SOLO_NAME "Kick Close Solo"
#define KICK_OH_SOLO_ID "kick OH Solo"
#define KICK_OH_SOLO_NAME "Kick OH Solo"
#define KICK_ROOM_SOLO_ID "kick Room Solo"
#define KICK_ROOM_SOLO_NAME "Kick Room Solo"
#define KICK_BLEED_SOLO_ID "kick Bleed Solo"
#define KICK_BLEED_SOLO_NAME "Kick Bleed Solo"

#define SNARE_TOP_SOLO_ID "snare Top Close Solo"
#define SNARE_TOP_SOLO_NAME "Snare Top Close Solo"
#define SNARE_BOT_SOLO_ID "snare Bottom Close Solo"
#define SNARE_BOT_SOLO_NAME "Snare Bottom Close Solo"
#define SNARE_OH_SOLO_ID "snare OH Solo"
#define SNARE_OH_SOLO_NAME "Snare OH Solo"
#define SNARE_ROOM_SOLO_ID "snare Room Solo"
#define SNARE_ROOM_SOLO_NAME "Snare Room Solo"
#define SNARE_BLEED_SOLO_ID "snare Bleed Solo"
#define SNARE_BLEED_SOLO_NAME "Snare Bleed Solo"

#define TOM_CLOSE_SOLO_ID "tom Close Solo"
#define TOM_CLOSE_SOLO_NAME "Tom Close Solo"
#define FTOM_CLOSE_SOLO_ID "ftom Close Solo"
#define FTOM_CLOSE_SOLO_NAME "FTom Close Solo"
#define TOMS_OH_SOLO_ID "toms OH Solo"
#define TOMS_OH_SOLO_NAME "Toms OH Solo"
#define TOMS_ROOM_SOLO_ID "Toms Room Solo"
#define TOMS_ROOM_SOLO_NAME "Toms Room Solo"
#define TOMS_BLEED_SOLO_ID "Toms Bleed Solo"
#define TOMS_BLEED_SOLO_NAME "Toms Bleed Solo"

#define HH_CLOSE_SOLO_ID "hh Close Solo"
#define HH_CLOSE_SOLO_NAME "HH Close Solo"
#define CYMBALS_OH_SOLO_ID "cymbals OH Solo"
#define CYMBALS_OH_SOLO_NAME "Cymbals OH Solo"
#define CYMBALS_ROOM_SOLO_ID "cymbals Room Solo"
#define CYMBALS_ROOM_SOLO_NAME "Cymbals Room Solo"
#define CYMBALS_BLEED_SOLO_ID "cymbals Bleed Solo"
#define CYMBALS_BLEED_SOLO_NAME "Cymbals Bleed Solo"

// Mute buttons =====================
#define CLOSE_MUTE_ID "close Mute"
#define CLOSE_MUTE_NAME "Close Mute"
#define OH_MUTE_ID "oh Mute"
#define OH_MUTE_NAME "OH Mute"
#define ROOM_MUTE_ID "room Mute"
#define ROOM_MUTE_NAME "Room Mute"
#define BLEED_MUTE_ID "bleed Mute"
#define BLEED_MUTE_NAME "Bleed Mute"

#define KICK_CLOSE_MUTE_ID "kick Close Mute"
#define KICK_CLOSE_MUTE_NAME "Kick Close Mute"
#define KICK_OH_MUTE_ID "kick OH Mute"
#define KICK_OH_MUTE_NAME "Kick OH Mute"
#define KICK_ROOM_MUTE_ID "kick Room Mute"
#define KICK_ROOM_MUTE_NAME "Kick Room Mute"
#define KICK_BLEED_MUTE_ID "kick Bleed Mute"
#define KICK_BLEED_MUTE_NAME "Kick Bleed Mute"

#define SNARE_TOP_MUTE_ID "snare Top Close Mute"
#define SNARE_TOP_MUTE_NAME "Snare Top Close Mute"
#define SNARE_BOT_MUTE_ID "snare Bottom Close Mute"
#define SNARE_BOT_MUTE_NAME "Snare Bottom Close Mute"
#define SNARE_OH_MUTE_ID "snare OH Mute"
#define SNARE_OH_MUTE_NAME "Snare OH Mute"
#define SNARE_ROOM_MUTE_ID "snare Room Mute"
#define SNARE_ROOM_MUTE_NAME "Snare Room Mute"
#define SNARE_BLEED_MUTE_ID "snare Bleed Mute"
#define SNARE_BLEED_MUTE_NAME "Snare Bleed Mute"

#define TOM_CLOSE_MUTE_ID "tom Close Mute"
#define TOM_CLOSE_MUTE_NAME "Tom Close Mute"
#define FTOM_CLOSE_MUTE_ID "ftom Close Mute"
#define FTOM_CLOSE_MUTE_NAME "FTom Close Mute"
#define TOMS_OH_MUTE_ID "toms OH Mute"
#define TOMS_OH_MUTE_NAME "Toms OH Mute"
#define TOMS_ROOM_MUTE_ID "Toms Room Mute"
#define TOMS_ROOM_MUTE_NAME "Toms Room Mute"
#define TOMS_BLEED_MUTE_ID "Toms Bleed Mute"
#define TOMS_BLEED_MUTE_NAME "Toms Bleed Mute"

#define HH_CLOSE_MUTE_ID "hh Close Mute"
#define HH_CLOSE_MUTE_NAME "HH Close Mute"
#define CYMBALS_OH_MUTE_ID "cymbals OH Mute"
#define CYMBALS_OH_MUTE_NAME "Cymbals OH Mute"
#define CYMBALS_ROOM_MUTE_ID "cymbals Room Mute"
#define CYMBALS_ROOM_MUTE_NAME "Cymbals Room Mute"
#define CYMBALS_BLEED_MUTE_ID "cymbals Bleed Mute"
#define CYMBALS_BLEED_MUTE_NAME "Cymbals Bleed Mute"

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

    void addSample(string sampleName, string destination, int midiNote, float lowestVelocity, float highestVelocity, double release, double maxLength, string bus);
    void loadSamples(int samplePackID);

    juce::MidiMessageCollector& getMidiMessageCollector() noexcept { return midiMessageCollector; }

    juce::MidiBuffer processedBuffer;

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    MidiProcessor midiProcessor;

private:
    
    juce::AudioProcessorValueTreeState::Listener *samplePackListener;

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
    Sampler samplerCymbalsOH;
    Sampler samplerCymbalsRoom;
    Sampler samplerCymbalsBleed;

    juce::AudioFormatManager formatManager;

    float linCurveFor3[4] = { 0.0, 43.0, 85.0, 129.0 };
    float linCurveFor4[5] = { 0.0, 32.0, 64.0, 96.0, 129.0 };
    float linCurveFor5[6] = { 0.0, 26.0, 51.0, 77.0, 102.0, 129.0 };
    float linCurveFor6[7] = { 0.0, 21.0, 43.0, 64.0, 85.0, 107.0, 129.0 };

    int defaultMidiNotes[27] = { 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };

    void loadDirectory();
    void clearSoundsFromAllSamplers();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessor)
};
