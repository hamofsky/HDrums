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
#define TAMB_CLOSE_GAIN_ID "tamb Close"
#define TAMB_CLOSE_GAIN_NAME "Tamb Close"
#define HH_OH_GAIN_ID "hh OH"
#define HH_OH_GAIN_NAME "HH OH"
#define HH_ROOM_GAIN_ID "hh Room"
#define HH_ROOM_GAIN_NAME "HH Room"
#define HH_BLEED_GAIN_ID "hh Bleed"
#define HH_BLEED_GAIN_NAME "HH Bleed"

#define CRASH_CLOSE_GAIN_ID "crash Close"
#define CRASH_CLOSE_GAIN_NAME "Crash Close"
#define RIDE_CLOSE_GAIN_ID "ride Close"
#define RIDE_CLOSE_GAIN_NAME "Ride Close"
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
    void loadSamples(int samplePackID, int curveMenuID, int kickNoteID, int snareNoteID, int snareFlamNoteID, int snareRoundNoteID,
                    int snareWirelessNoteID, int snareWirelessRoundNoteID, int tomNoteID, int tomFlamNoteID, int ftomNoteID, int ftomFlamNoteID,
                    int hhBellNoteID, int hhClosedNoteID, int hhHalfNoteID, int hhOpenNoteID, int tambourineNoteID, int ridePointNoteID,
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

    juce::StringArray processorMidiNotes = { "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
                                    "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
                                    "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
                                    "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
                                    "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A4", "B4",
                                    "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
                                    "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
                                    "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
                                    "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "A#8", "B8",
                                    "C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "A#9", "B9",
                                    "C10", "C#10", "D10", "D#10", "E10", "F10", "F#10", "G10" };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessor)
};
