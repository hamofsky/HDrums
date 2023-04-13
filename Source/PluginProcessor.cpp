#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEditor.cpp"
#include <JuceHeader.h>
#include "SamplerSoundLayer.h"

HDrumsAudioProcessor::HDrumsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
    #if ! JucePlugin_IsMidiEffect
    #if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
    #endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    #endif
    ),
    treeState(*this, nullptr, "PARAMETER", { createParameterLayout()})
#endif
{

    formatManager.registerBasicFormats();
    for (auto i = 0; i < 5; i++)    // i < x+1 defines how many sounds can play at the same time (x)
    {
        sampler.addVoice(new juce::SamplerVoice());
        samplerOH.addVoice(new juce::SamplerVoice());
        samplerRoom.addVoice(new juce::SamplerVoice());
        samplerBleed.addVoice(new juce::SamplerVoice());

        samplerKickClose.addVoice(new juce::SamplerVoice());
        samplerKickOH.addVoice(new juce::SamplerVoice());
        samplerKickRoom.addVoice(new juce::SamplerVoice());
        samplerKickBleed.addVoice(new juce::SamplerVoice());

        samplerSnareTop.addVoice(new juce::SamplerVoice());
        samplerSnareBot.addVoice(new juce::SamplerVoice());
        samplerSnareOH.addVoice(new juce::SamplerVoice());
        samplerSnareRoom.addVoice(new juce::SamplerVoice());
        samplerSnareBleed.addVoice(new juce::SamplerVoice());

        samplerTomClose.addVoice(new juce::SamplerVoice());
        samplerFTomClose.addVoice(new juce::SamplerVoice());
        samplerTomsOH.addVoice(new juce::SamplerVoice());
        samplerTomsRoom.addVoice(new juce::SamplerVoice());
        samplerTomsBleed.addVoice(new juce::SamplerVoice());

        samplerHHClose.addVoice(new juce::SamplerVoice());
        samplerCymbalsOH.addVoice(new juce::SamplerVoice());
        samplerCymbalsRoom.addVoice(new juce::SamplerVoice());
        samplerCymbalsBleed.addVoice(new juce::SamplerVoice());
    }

    loadSamples(1); // default settings for samples (samplePackMenuId)

}

HDrumsAudioProcessor::~HDrumsAudioProcessor()
{
}

//==============================================================================
// here you add parameters that need to be transported from the Editor to the Processor (slider values, etc.). These will also be available to be automated in a DAW
juce::AudioProcessorValueTreeState::ParameterLayout HDrumsAudioProcessor::createParameterLayout()
{
    float sliderMinValue = -36.0f;
    float sliderMaxValue = 12.0f;
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    auto gainParam = std::make_unique<juce::AudioParameterFloat>(GAIN_ID, GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto OHgainParam = std::make_unique<juce::AudioParameterFloat>(OH_GAIN_ID, OH_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto RoomGainParam = std::make_unique<juce::AudioParameterFloat>(ROOM_GAIN_ID, ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -3.0f);
    auto BleedGainParam = std::make_unique<juce::AudioParameterFloat>(BLEED_GAIN_ID, BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -3.0f);
    params.push_back(std::move(gainParam));
    params.push_back(std::move(OHgainParam));
    params.push_back(std::move(RoomGainParam));
    params.push_back(std::move(BleedGainParam));

    auto KickCloseGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_CLOSE_GAIN_ID, KICK_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 3.0f);
    auto KickOHGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_OH_GAIN_ID, KICK_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto KickRoomGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_ROOM_GAIN_ID, KICK_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto KickBleedGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_BLEED_GAIN_ID, KICK_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -18.0f);
    params.push_back(std::move(KickCloseGainParam));
    params.push_back(std::move(KickOHGainParam));
    params.push_back(std::move(KickRoomGainParam));
    params.push_back(std::move(KickBleedGainParam));

    auto SnareTopCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_TOP_CLOSE_GAIN_ID, SNARE_TOP_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto SnareBotCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BOT_CLOSE_GAIN_ID, SNARE_BOT_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto SnareOHGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_OH_GAIN_ID, SNARE_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto SnareRoomGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_ROOM_GAIN_ID, SNARE_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -3.0f);
    auto SnareBleedGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BLEED_GAIN_ID, SNARE_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -9.0f);
    params.push_back(std::move(SnareTopCloseGainParam));
    params.push_back(std::move(SnareBotCloseGainParam));
    params.push_back(std::move(SnareOHGainParam));
    params.push_back(std::move(SnareRoomGainParam));
    params.push_back(std::move(SnareBleedGainParam));

    auto TomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(TOM_CLOSE_GAIN_ID, TOM_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto FTomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(FTOM_CLOSE_GAIN_ID, FTOM_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 2.0f);
    auto TomsOHGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_OH_GAIN_ID, TOMS_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto TomsRoomGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_ROOM_GAIN_ID, TOMS_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -12.0f);
    auto TomsBleedGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_BLEED_GAIN_ID, TOMS_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -9.0f);
    params.push_back(std::move(TomCloseGainParam));
    params.push_back(std::move(FTomCloseGainParam));
    params.push_back(std::move(TomsOHGainParam));
    params.push_back(std::move(TomsRoomGainParam));
    params.push_back(std::move(TomsBleedGainParam));

    auto HHCloseGainParam = std::make_unique<juce::AudioParameterFloat>(HH_CLOSE_GAIN_ID, HH_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, -3.0f);
    auto CymbalsOHGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_OH_GAIN_ID, CYMBALS_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto CymbalsRoomGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_ROOM_GAIN_ID, CYMBALS_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto CymbalsBleedGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_BLEED_GAIN_ID, CYMBALS_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -9.0f);
    params.push_back(std::move(HHCloseGainParam));
    params.push_back(std::move(CymbalsOHGainParam));
    params.push_back(std::move(CymbalsRoomGainParam));
    params.push_back(std::move(CymbalsBleedGainParam));

    // ==================================================================
    auto SamplePackParam = std::make_unique<juce::AudioParameterChoice>(SAMPLE_PACK_ID, SAMPLE_PACK_NAME, juce::StringArray("Electronic", "Acoustic", "Dry"), 1);
    auto CurveMenuParam = std::make_unique<juce::AudioParameterChoice>(CURVE_MENU_ID, CURVE_MENU_NAME, juce::StringArray("Linear", "Logarhytmic"), 1);
    params.push_back(std::move(SamplePackParam));
    params.push_back(std::move(CurveMenuParam));
    // ==================================================================

    auto closeSoloParam = std::make_unique<juce::AudioParameterBool>(CLOSE_SOLO_ID, CLOSE_SOLO_NAME, false);
    auto OHSoloParam = std::make_unique<juce::AudioParameterBool>(OH_SOLO_ID, OH_SOLO_NAME, false);
    auto roomSoloParam = std::make_unique<juce::AudioParameterBool>(ROOM_SOLO_ID, ROOM_SOLO_NAME, false);
    auto bleedSoloParam = std::make_unique<juce::AudioParameterBool>(BLEED_SOLO_ID, BLEED_SOLO_NAME, false);
    params.push_back(std::move(closeSoloParam));
    params.push_back(std::move(OHSoloParam));
    params.push_back(std::move(roomSoloParam));
    params.push_back(std::move(bleedSoloParam));

    auto closeMuteParam = std::make_unique<juce::AudioParameterBool>(CLOSE_MUTE_ID, CLOSE_MUTE_NAME, false);
    auto OHMuteParam = std::make_unique<juce::AudioParameterBool>(OH_MUTE_ID, OH_MUTE_NAME, false);
    auto roomMuteParam = std::make_unique<juce::AudioParameterBool>(ROOM_MUTE_ID, ROOM_MUTE_NAME, false);
    auto bleedMuteParam = std::make_unique<juce::AudioParameterBool>(BLEED_MUTE_ID, BLEED_MUTE_NAME, false);
    params.push_back(std::move(closeMuteParam));
    params.push_back(std::move(OHMuteParam));
    params.push_back(std::move(roomMuteParam));
    params.push_back(std::move(bleedMuteParam));

    auto kickCloseMuteParam = std::make_unique<juce::AudioParameterBool>(KICK_CLOSE_MUTE_ID, KICK_CLOSE_MUTE_NAME, false);
    auto kickOHMuteParam = std::make_unique<juce::AudioParameterBool>(KICK_OH_MUTE_ID, KICK_OH_MUTE_NAME, false);
    auto kickRoomMuteParam = std::make_unique<juce::AudioParameterBool>(KICK_ROOM_MUTE_ID, KICK_ROOM_MUTE_NAME, false);
    auto kickBleedMuteParam = std::make_unique<juce::AudioParameterBool>(KICK_BLEED_MUTE_ID, KICK_BLEED_MUTE_NAME, false);
    params.push_back(std::move(kickCloseMuteParam));
    params.push_back(std::move(kickOHMuteParam));
    params.push_back(std::move(kickRoomMuteParam));
    params.push_back(std::move(kickBleedMuteParam));

    auto snareTopMuteParam = std::make_unique<juce::AudioParameterBool>(SNARE_TOP_MUTE_ID, SNARE_TOP_MUTE_NAME, false);
    auto snareBotMuteParam = std::make_unique<juce::AudioParameterBool>(SNARE_BOT_MUTE_ID, SNARE_BOT_MUTE_NAME, false);
    auto snareOHMuteParam = std::make_unique<juce::AudioParameterBool>(SNARE_OH_MUTE_ID, SNARE_OH_MUTE_NAME, false);
    auto snareRoomMuteParam = std::make_unique<juce::AudioParameterBool>(SNARE_ROOM_MUTE_ID, SNARE_ROOM_MUTE_NAME, false);
    auto snareBleedMuteParam = std::make_unique<juce::AudioParameterBool>(SNARE_BLEED_MUTE_ID, SNARE_BLEED_MUTE_NAME, false);
    params.push_back(std::move(snareTopMuteParam));
    params.push_back(std::move(snareBotMuteParam));
    params.push_back(std::move(snareOHMuteParam));
    params.push_back(std::move(snareRoomMuteParam));
    params.push_back(std::move(snareBleedMuteParam));

    auto tomCloseMuteParam = std::make_unique<juce::AudioParameterBool>(TOM_CLOSE_MUTE_ID, TOM_CLOSE_MUTE_NAME, false);
    auto ftomCloseMuteParam = std::make_unique<juce::AudioParameterBool>(FTOM_CLOSE_MUTE_ID, FTOM_CLOSE_MUTE_NAME, false);
    auto tomsOHMuteParam = std::make_unique<juce::AudioParameterBool>(TOMS_OH_MUTE_ID, TOMS_OH_MUTE_NAME, false);
    auto tomsRoomMuteParam = std::make_unique<juce::AudioParameterBool>(TOMS_ROOM_MUTE_ID, TOMS_ROOM_MUTE_NAME, false);
    auto tomsBleedMuteParam = std::make_unique<juce::AudioParameterBool>(TOMS_BLEED_MUTE_ID, TOMS_BLEED_MUTE_NAME, false);
    params.push_back(std::move(tomCloseMuteParam));
    params.push_back(std::move(ftomCloseMuteParam));
    params.push_back(std::move(tomsOHMuteParam));
    params.push_back(std::move(tomsRoomMuteParam));
    params.push_back(std::move(tomsBleedMuteParam));

    auto hhCloseMuteParam = std::make_unique<juce::AudioParameterBool>(HH_CLOSE_MUTE_ID, HH_CLOSE_MUTE_NAME, false);
    auto cymbalsOHMuteParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_OH_MUTE_ID, CYMBALS_OH_MUTE_NAME, false);
    auto cymbalsRoomMuteParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_ROOM_MUTE_ID, CYMBALS_ROOM_MUTE_NAME, false);
    auto cymbalsBleedMuteParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_BLEED_MUTE_ID, CYMBALS_BLEED_MUTE_NAME, false);
    params.push_back(std::move(hhCloseMuteParam));
    params.push_back(std::move(cymbalsOHMuteParam));
    params.push_back(std::move(cymbalsRoomMuteParam));
    params.push_back(std::move(cymbalsBleedMuteParam));

    juce::StringArray processorMidiNotes = juce::StringArray("0 C-2", "1 C#-2", "2 D-2", "3 D#-2", "4 E-2", "5 F-2", "6 F#-2", "7 G-2", "8 G#-2", "9 A-2", "10 A#-2", "11 B-2",
                                                             "12 C-1", "13 C#-1", "14 D-1", "15 D#-1", "16 E-1", "17 F-1", "18 F#-1", "19 G-1", "20 G#-1", "21 A-1", "22 A#-1", "23 B-1",
                                                             "24 C0", "25 C#0", "26 D0", "27 D#0", " 28 E0", "29 F0", "30 F#0", " 31 G0", "32 G#0", "33 A0", "34 A#0", "35 B0",
                                                             "36 C1", "37 C#1", "38 D1", "39 D#1", "40 E1", "41 F1", "42 F#1", "43 G1", "44 G#1", "45 A1", "46 A#1", "47 B1",
                                                             "48 C2", "49 C#2", "50 D2", "51 D#2", "52 E2", "53 F2", "54 F#2", "55 G2", "56 G#2", "57 A2", "58 A#2", "59 B2",
                                                             "60 C3", "61 C#3", "62 D3", "63 D#3", "64 E3", "65 F3", "66 F#3", "67 G3", "68 G#3", "69 A3", "70 A#3", "71 B3",
                                                             "72 C4", "73 C#4", "74 D4", "75 D#4", "76 E4", "77 F4", "78 F#4", "79 G4", "80 G#4", "81 A4", "82 A#4", "83 B4",
                                                             "84 C5", "85 C#5", "86 D5", "87 D#5", "88 E5", "89 F5", "90 F#5", "91 G5", "92 G#5", "93 A5", "94 A#5", "95 B5",
                                                             "96 C6", "97 C#6", "98 D6", "99 D#6", "100 E6", "101 F6", "102 F#6", "103 G6", "104 G#6", "105 A6", "106 A#6", "107 B6",
                                                             "108 C7", "109 C#7", "110 D7", "111 D#7", "112 E7", "113 F7", "114 F#7", "115 G7", "116 G#7", "117 A7", "118 A#7", "119 B7",
                                                             "120 C8", "121 C#8", "122 D8", "123 D#8", "124 E8", "125 F8", "126 F#8", "127 G8");

    auto kickNoteParam = std::make_unique<juce::AudioParameterChoice>(KICK_MIDI_NOTE_ID, KICK_MIDI_NOTE_NAME, processorMidiNotes, 71);
    auto snareNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_MIDI_NOTE_ID, SNARE_MIDI_NOTE_NAME, processorMidiNotes, 72);
    auto snareFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_FLAM_MIDI_NOTE_ID, SNARE_FLAM_MIDI_NOTE_NAME, processorMidiNotes, 73);
    auto snareRoundNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_ROUND_MIDI_NOTE_ID, SNARE_ROUND_MIDI_NOTE_NAME, processorMidiNotes, 74);
    auto snareWirelessNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_WIRELESS_MIDI_NOTE_ID, SNARE_WIRELESS_MIDI_NOTE_NAME, processorMidiNotes, 75);
    auto snareWirelessRoundNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_WIRELESS_ROUND_MIDI_NOTE_ID, SNARE_WIRELESS_ROUND_MIDI_NOTE_NAME, processorMidiNotes, 76);
    auto tomNoteParam = std::make_unique<juce::AudioParameterChoice>(TOM_MIDI_NOTE_ID, TOM_MIDI_NOTE_NAME, processorMidiNotes, 78);
    auto tomFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(TOM_FLAM_MIDI_NOTE_ID, TOM_FLAM_MIDI_NOTE_NAME, processorMidiNotes, 79);
    auto ftomNoteParam = std::make_unique<juce::AudioParameterChoice>(FTOM_MIDI_NOTE_ID, FTOM_MIDI_NOTE_NAME, processorMidiNotes, 80);
    auto ftomFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(FTOM_FLAM_MIDI_NOTE_ID, FTOM_FLAM_MIDI_NOTE_NAME, processorMidiNotes, 81);
    auto tambNoteParam = std::make_unique<juce::AudioParameterChoice>(TAMB_MIDI_NOTE_ID, TAMB_MIDI_NOTE_NAME, processorMidiNotes, 83);
    auto hhClosedNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_CLOSED_MIDI_NOTE_ID, HH_CLOSED_MIDI_NOTE_NAME, processorMidiNotes, 85);
    auto hhHalfNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_HALF_MIDI_NOTE_ID, HH_HALF_MIDI_NOTE_NAME, processorMidiNotes, 86);
    auto hhOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_OPEN_MIDI_NOTE_ID, HH_OPEN_MIDI_NOTE_NAME, processorMidiNotes, 87);
    auto ridePointNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_POINT_MIDI_NOTE_ID, RIDE_POINT_MIDI_NOTE_NAME, processorMidiNotes, 89);
    auto rideBellNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_BELL_MIDI_NOTE_ID, RIDE_BELL_MIDI_NOTE_NAME, processorMidiNotes, 90);
    auto rideOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_OPEN_MIDI_NOTE_ID, RIDE_OPEN_MIDI_NOTE_NAME, processorMidiNotes, 91);
    auto crashPointNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_POINT_MIDI_NOTE_ID, CRASH_POINT_MIDI_NOTE_NAME, processorMidiNotes, 93);
    auto crashBellNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_BELL_MIDI_NOTE_ID, CRASH_BELL_MIDI_NOTE_NAME, processorMidiNotes, 94);
    auto crashOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_OPEN_MIDI_NOTE_ID, CRASH_OPEN_MIDI_NOTE_NAME, processorMidiNotes, 95);
    params.push_back(std::move(kickNoteParam));
    params.push_back(std::move(snareNoteParam));
    params.push_back(std::move(snareFlamNoteParam));
    params.push_back(std::move(snareRoundNoteParam));
    params.push_back(std::move(snareWirelessNoteParam));
    params.push_back(std::move(snareWirelessRoundNoteParam));
    params.push_back(std::move(tomNoteParam));
    params.push_back(std::move(tomFlamNoteParam));
    params.push_back(std::move(ftomNoteParam));
    params.push_back(std::move(ftomFlamNoteParam));
    params.push_back(std::move(tambNoteParam));
    params.push_back(std::move(hhClosedNoteParam));
    params.push_back(std::move(hhHalfNoteParam));
    params.push_back(std::move(hhOpenNoteParam));
    params.push_back(std::move(ridePointNoteParam));
    params.push_back(std::move(rideBellNoteParam));
    params.push_back(std::move(rideOpenNoteParam));
    params.push_back(std::move(crashPointNoteParam));
    params.push_back(std::move(crashBellNoteParam));
    params.push_back(std::move(crashOpenNoteParam));

    return { params.begin(), params.end() };
}
//==============================================================================

void HDrumsAudioProcessor::addSample(string sampleName, string destination, int midiNote, float lowestVelocity, float highestVelocity, double release, double maxLength, string bus)
{
    juce::File file(destination);
    unique_ptr<juce::AudioFormatReader>audioReader(formatManager.createReaderFor(file));
    if (audioReader != nullptr) {
        juce::BigInteger midiNotes;
        midiNotes.setRange(midiNote, 1, true);
        juce::Range<float> velocities(1.f / 127 * lowestVelocity, 1.f / 127 * highestVelocity);

        if (bus == "Close")
            sampler.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "OH")
            samplerOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "Room")
            samplerRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "Bleed")
            samplerBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "KickClose")
            samplerKickClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickOH")
            samplerKickOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickRoom")
            samplerKickRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickBleed")
            samplerKickBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "SnareTop")
            samplerSnareTop.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareBot")
            samplerSnareBot.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareOH")
            samplerSnareOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareRoom")
            samplerSnareRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareBleed")
            samplerSnareBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "TomClose")
            samplerTomClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "FTomClose")
            samplerFTomClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsOH")
            samplerTomsOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsRoom")
            samplerTomsRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsBleed")
            samplerTomsBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "HHClose")
            samplerHHClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsOH")
            samplerCymbalsOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsRoom")
            samplerCymbalsRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsBleed")
            samplerCymbalsBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

    }
    else {
        loadDirectory();
    }
    
}

void HDrumsAudioProcessor::loadDirectory()
{
    DBG("Source was a nullptr, so you will have to choose a correct directory");
}

void HDrumsAudioProcessor::loadSamples(int samplePackID)
{
    string destinationAll = "C:/Users/damia/Desktop/Sampelki/";

    auto curveFor3 = linCurveFor3;
    auto curveFor4 = linCurveFor4;
    auto curveFor5 = linCurveFor5;
    auto curveFor6 = linCurveFor6;

    if (samplePackID == 1)  // Electronic Drum Kit
    {
        clearSoundsFromAllSamplers();

        string electronicDestination = destinationAll + "electronicSamples/";
        string kickDestination = electronicDestination + "kick/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        addSample("Electronic Kick Close", kickDestination + "kick_close.wav", defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickClose");
        addSample("Electronic Kick OH", kickDestination + "kick_OH.wav", defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickOH");
        addSample("Electronic Kick Room", kickDestination + "kick_room.wav", defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickRoom");
        addSample("Electronic Kick Bleed", kickDestination + "kick_bleed.wav", defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickBleed");
        string snareDestination = electronicDestination + "snare/";
        addSample("Electronic Snare Close", snareDestination + "snare_close.wav", defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareTop");
        addSample("Electronic Snare OH", snareDestination + "snare_OH.wav", defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareOH");
        addSample("Electronic Snare Room", snareDestination + "snare_room.wav", defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareRoom");
        addSample("Electronic Snare Bleed", snareDestination + "snare_bleed.wav", defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareBleed");
        string tomDestination = electronicDestination + "tom/";
        addSample("Electronic Tom Close", tomDestination + "tom_close.wav", defaultMidiNotes[6], 1, 127, 0.5, 1.0, "TomClose");
        addSample("Electronic Tom OH", tomDestination + "tom_OH.wav", defaultMidiNotes[6], 1, 127, 0.5, 1.0, "TomsOH");
        addSample("Electronic Tom Room", tomDestination + "tom_room.wav", defaultMidiNotes[6], 1, 127, 0.5, 1.0, "TomsRoom");
        addSample("Electronic Tom Bleed", tomDestination + "tom_bleed.wav", defaultMidiNotes[6], 1, 127, 0.5, 1.0, "TomsBleed");
        string ftomDestination = electronicDestination + "ftom/";
        addSample("Electronic FTom Close", ftomDestination + "ftom_close.wav", defaultMidiNotes[8], 1, 127, 0.5, 1.0, "FTomClose");
        addSample("Electronic FTom OH", ftomDestination + "ftom_OH.wav", defaultMidiNotes[8], 1, 127, 0.5, 1.0, "TomsOH");
        addSample("Electronic FTom Room", ftomDestination + "ftom_room.wav", defaultMidiNotes[8], 1, 127, 0.5, 1.0, "TomsRoom");
        addSample("Electronic FTom Bleed", ftomDestination + "ftom_bleed.wav", defaultMidiNotes[8], 1, 127, 0.5, 1.0, "TomsBleed");
        string hhDestination = electronicDestination + "hh/";
        addSample("Electronic HH Closed Close", hhDestination + "hhClosed_close.wav", defaultMidiNotes[11], 1, 127, 0.5, 1.0, "HHClose");
        addSample("Electronic HH Closed OH", hhDestination + "hhClosed_OH.wav", defaultMidiNotes[11], 1, 127, 0.5, 1.0, "CymbalsOH");
        addSample("Electronic HH Closed Room", hhDestination + "hhClosed_room.wav", defaultMidiNotes[11], 1, 127, 0.5, 1.0, "CymbalsRoom");
        addSample("Electronic HH Closed Bleed", hhDestination + "hhClosed_bleed.wav", defaultMidiNotes[11], 1, 127, 0.5, 1.0, "CymbalsBleed");
        addSample("Electronic HH Open Close", hhDestination + "hhOpen_close.wav", defaultMidiNotes[13], 1, 127, 0.5, 1.0, "HHClose");
        addSample("Electronic HH Open OH", hhDestination + "hhOpen_OH.wav", defaultMidiNotes[13], 1, 127, 0.5, 1.0, "CymbalsOH");
        addSample("Electronic HH Open Room", hhDestination + "hhOpen_room.wav", defaultMidiNotes[13], 1, 127, 0.5, 1.0, "CymbalsRoom");
        addSample("Electronic HH Open Bleed", hhDestination + "hhOpen_bleed.wav", defaultMidiNotes[13], 1, 127, 0.5, 1.0, "CymbalsBleed");
        string rideDestination = electronicDestination + "ride/";
        addSample("Electronic Ride OH", rideDestination + "ride_OH.wav", defaultMidiNotes[14], 1, 127, 0.8, 2.2, "CymbalsOH");
        addSample("Electronic Ride Room", rideDestination + "ride_room.wav", defaultMidiNotes[14], 1, 127, 0.8, 2.2, "CymbalsRoom");
        addSample("Electronic Ride Bleed", rideDestination + "ride_bleed.wav", defaultMidiNotes[14], 1, 127, 0.8, 2.2, "CymbalsBleed");
        string crashDestination = electronicDestination + "crash/";
        addSample("Electronic Crash OH", crashDestination + "crash_OH.wav", defaultMidiNotes[19], 1, 127, 0.8, 2.2, "CymbalsOH");
        addSample("Electronic Crash Room", crashDestination + "crash_room.wav", defaultMidiNotes[19], 1, 127, 0.8, 2.2, "CymbalsRoom");
        addSample("Electronic Crash Bleed", crashDestination + "crash_bleed.wav", defaultMidiNotes[19], 1, 127, 0.8, 2.2, "CymbalsBleed");

    }
    else if (samplePackID == 2) // Acoustic Drum Kit
    {
        clearSoundsFromAllSamplers();
        double snareRelease = 0.5;
        double snareMaxLen = 2.0;

        string destinationP = destinationAll + "Perkusja/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select
        addSample("Ride Hard", destinationP + "Ride Hard.wav", defaultMidiNotes[16], curveFor6[0], 127, 5.0, 8.0, "Close");
        addSample("Ride Smooth", destinationP + "Ride Smooth.wav", defaultMidiNotes[14], 1, curveFor6[0] - 1, 0.5, 8.0, "Close");
        string GGDdestination = destinationP + "GGD/";
        addSample("HH open", GGDdestination + "HH open.wav", defaultMidiNotes[13], 1, 127, 0.12, 6.5, "Close");
        addSample("HH closed", GGDdestination + "HH closed.wav", defaultMidiNotes[11], 1, 127, 0.1, 2.0, "Close");

        string snareDestination = destinationP + "Konrad1/Snare/";
        addSample("Snare 1_1", snareDestination + "Snare 1_1.wav", defaultMidiNotes[1], curveFor6[4], 128, snareRelease, snareMaxLen, "Close");
        addSample("Snare 2_1", snareDestination + "Snare 2_1.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 3_1", snareDestination + "Snare 3_1.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 4_1", snareDestination + "Snare 4_1.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 5_1", snareDestination + "Snare 5_1.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 6_1", snareDestination + "Snare 6_1.wav", defaultMidiNotes[1], 1, curveFor6[0] - 1, snareRelease, snareMaxLen, "Close");
        string kickDestination = destinationP + "Konrad1/Kick/";
        addSample("Kick 0_1", kickDestination + "Kick 0_1.wav", defaultMidiNotes[0], 126, 127, 0.6, 2.0, "Close");
        addSample("Kick 1_1", kickDestination + "Kick 1_1.wav", defaultMidiNotes[0], 114, 125, 0.6, 2.0, "Close");
        addSample("Kick 2_1", kickDestination + "Kick 2_1.wav", defaultMidiNotes[0], 100, 113, 0.6, 2.0, "Close");
        addSample("Kick 3_1", kickDestination + "Kick 3_1.wav", defaultMidiNotes[0], 85, 99, 0.6, 2.0, "Close");
        addSample("Kick 4_1", kickDestination + "Kick 4_1.wav", defaultMidiNotes[0], 75, 84, 0.6, 2.0, "Close");
        addSample("Kick 5_1", kickDestination + "Kick 5_1.wav", defaultMidiNotes[0], 66, 74, 0.6, 2.0, "Close");
        addSample("Kick 6_1", kickDestination + "Kick 6_1.wav", defaultMidiNotes[0], 40, 65, 0.6, 2.0, "Close");
        addSample("Kick 7_1", kickDestination + "Kick 7_1.wav", defaultMidiNotes[0], 1, 39, 0.6, 2.0, "Close");
        string FTCloseDestination = destinationP + "Konrad1/FT/Close/";
        addSample("FT Close 1_1", FTCloseDestination + "FT Close 1_1.wav", defaultMidiNotes[8], 1, 127, 0.7, 1.5, "Close");
        string FTOHDestination = destinationP + "Konrad1/FT/OH/";
        addSample("FT OH 1_1", FTOHDestination + "FT OH 1_1.wav", defaultMidiNotes[8], 1, 127, 0.7, 1.5, "OH");

    }
    else if (samplePackID == 3) // Dry Drum Kit
    {
        clearSoundsFromAllSamplers();

        double kickRelease = 0.5;
        double kickMaxLen = 2.0;
        string dryDestination = destinationAll + "drySamples2/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        string kickDestination = dryDestination + "kick/";
        addSample("Dry Kick 1 Close", kickDestination + "kick_1_close.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Dry Kick 2 Close", kickDestination + "kick_2_close.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Dry Kick 3 Close", kickDestination + "kick_3_close.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Dry Kick 4 Close", kickDestination + "kick_4_close.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Dry Kick 5 Close", kickDestination + "kick_5_close.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Dry Kick 1 OH", kickDestination + "kick_1_OH.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Dry Kick 2 OH", kickDestination + "kick_2_OH.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Dry Kick 3 OH", kickDestination + "kick_3_OH.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Dry Kick 4 OH", kickDestination + "kick_4_OH.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Dry Kick 5 OH", kickDestination + "kick_5_OH.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Dry Kick 1 Room", kickDestination + "kick_1_room.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Dry Kick 2 Room", kickDestination + "kick_2_room.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Dry Kick 3 Room", kickDestination + "kick_3_room.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Dry Kick 4 Room", kickDestination + "kick_4_room.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Dry Kick 5 Room", kickDestination + "kick_5_room.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Dry Kick 1 Bleed", kickDestination + "kick_1_bleed.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Dry Kick 2 Bleed", kickDestination + "kick_2_bleed.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Dry Kick 3 Bleed", kickDestination + "kick_3_bleed.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Dry Kick 4 Bleed", kickDestination + "kick_4_bleed.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Dry Kick 5 Bleed", kickDestination + "kick_5_bleed.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickBleed");


        double snareRelease = 0.5;
        double snareMaxLen = 2.0;
        string snareAllDestination = dryDestination + "snareAll/";
        string snareDestination = snareAllDestination + "snare/";
        addSample("Dry Snare 1 Top", snareDestination + "snare_1_top.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareTop");
        addSample("Dry Snare 2 Top", snareDestination + "snare_2_top.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareTop");
        addSample("Dry Snare 3 Top", snareDestination + "snare_3_top.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareTop");
        addSample("Dry Snare 4 Top", snareDestination + "snare_4_top.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareTop");
        addSample("Dry Snare 5 Top", snareDestination + "snare_5_top.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareTop");
        addSample("Dry Snare 6 Top", snareDestination + "snare_6_top.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareTop");
        addSample("Dry Snare 1 Bot", snareDestination + "snare_1_bot.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareBot");
        addSample("Dry Snare 2 Bot", snareDestination + "snare_2_bot.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareBot");
        addSample("Dry Snare 3 Bot", snareDestination + "snare_3_bot.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareBot");
        addSample("Dry Snare 4 Bot", snareDestination + "snare_4_bot.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareBot");
        addSample("Dry Snare 5 Bot", snareDestination + "snare_5_bot.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareBot");
        addSample("Dry Snare 6 Bot", snareDestination + "snare_6_bot.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareBot");
        addSample("Dry Snare 1 OH", snareDestination + "snare_1_OH.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareOH");
        addSample("Dry Snare 2 OH", snareDestination + "snare_2_OH.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareOH");
        addSample("Dry Snare 3 OH", snareDestination + "snare_3_OH.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareOH");
        addSample("Dry Snare 4 OH", snareDestination + "snare_4_OH.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareOH");
        addSample("Dry Snare 5 OH", snareDestination + "snare_5_OH.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareOH");
        addSample("Dry Snare 6 OH", snareDestination + "snare_6_OH.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareOH");
        addSample("Dry Snare 1 Room", snareDestination + "snare_1_room.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareRoom");
        addSample("Dry Snare 2 Room", snareDestination + "snare_2_room.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareRoom");
        addSample("Dry Snare 3 Room", snareDestination + "snare_3_room.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareRoom");
        addSample("Dry Snare 4 Room", snareDestination + "snare_4_room.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareRoom");
        addSample("Dry Snare 5 Room", snareDestination + "snare_5_room.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareRoom");
        addSample("Dry Snare 6 Room", snareDestination + "snare_6_room.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareRoom");
        addSample("Dry Snare 1 Bleed", snareDestination + "snare_1_bleed.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareBleed");
        addSample("Dry Snare 2 Bleed", snareDestination + "snare_2_bleed.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareBleed");
        addSample("Dry Snare 3 Bleed", snareDestination + "snare_3_bleed.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareBleed");
        addSample("Dry Snare 4 Bleed", snareDestination + "snare_4_bleed.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareBleed");
        addSample("Dry Snare 5 Bleed", snareDestination + "snare_5_bleed.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareBleed");
        addSample("Dry Snare 6 Bleed", snareDestination + "snare_6_bleed.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareBleed");

        string snareFlamDestination = snareAllDestination + "snareFlam/";
        addSample("Dry SnareFlam 1 Top", snareFlamDestination + "snareFlam_1_top.wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareTop");
        addSample("Dry SnareFlam 2 Top", snareFlamDestination + "snareFlam_2_top.wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareTop");
        addSample("Dry SnareFlam 3 Top", snareFlamDestination + "snareFlam_3_top.wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareTop");
        addSample("Dry SnareFlam 4 Top", snareFlamDestination + "snareFlam_4_top.wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareTop");
        addSample("Dry SnareFlam 1 Bot", snareFlamDestination + "snareFlam_1_bot.wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareBot");
        addSample("Dry SnareFlam 2 Bot", snareFlamDestination + "snareFlam_2_bot.wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareBot");
        addSample("Dry SnareFlam 3 Bot", snareFlamDestination + "snareFlam_3_bot.wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareBot");
        addSample("Dry SnareFlam 4 Bot", snareFlamDestination + "snareFlam_4_bot.wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareBot");
        addSample("Dry SnareFlam 1 OH", snareFlamDestination + "snareFlam_1_OH.wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareOH");
        addSample("Dry SnareFlam 2 OH", snareFlamDestination + "snareFlam_2_OH.wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareOH");
        addSample("Dry SnareFlam 3 OH", snareFlamDestination + "snareFlam_3_OH.wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareOH");
        addSample("Dry SnareFlam 4 OH", snareFlamDestination + "snareFlam_4_OH.wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareOH");
        addSample("Dry SnareFlam 1 Room", snareFlamDestination + "snareFlam_1_room.wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareRoom");
        addSample("Dry SnareFlam 2 Room", snareFlamDestination + "snareFlam_2_room.wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareRoom");
        addSample("Dry SnareFlam 3 Room", snareFlamDestination + "snareFlam_3_room.wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareRoom");
        addSample("Dry SnareFlam 4 Room", snareFlamDestination + "snareFlam_4_room.wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareRoom");
        addSample("Dry SnareFlam 1 Bleed", snareFlamDestination + "snareFlam_1_bleed.wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareBleed");
        addSample("Dry SnareFlam 2 Bleed", snareFlamDestination + "snareFlam_2_bleed.wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareBleed");
        addSample("Dry SnareFlam 3 Bleed", snareFlamDestination + "snareFlam_3_bleed.wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareBleed");
        addSample("Dry SnareFlam 4 Bleed", snareFlamDestination + "snareFlam_4_bleed.wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareBleed");

        double snareMaxLen2 = 1.1;
        string snareRoundDestination = snareAllDestination + "snareRound/";
        addSample("Dry SnareRound 1 Top", snareRoundDestination + "snareRound_1_top.wav", defaultMidiNotes[3], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareTop");
        addSample("Dry SnareRound 2 Top", snareRoundDestination + "snareRound_2_top.wav", defaultMidiNotes[3], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareTop");
        addSample("Dry SnareRound 3 Top", snareRoundDestination + "snareRound_3_top.wav", defaultMidiNotes[3], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareTop");
        addSample("Dry SnareRound 1 Bot", snareRoundDestination + "snareRound_1_bot.wav", defaultMidiNotes[3], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareBot");
        addSample("Dry SnareRound 2 Bot", snareRoundDestination + "snareRound_2_bot.wav", defaultMidiNotes[3], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareBot");
        addSample("Dry SnareRound 3 Bot", snareRoundDestination + "snareRound_3_bot.wav", defaultMidiNotes[3], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareBot");
        addSample("Dry SnareRound 1 OH", snareRoundDestination + "snareRound_1_OH.wav", defaultMidiNotes[3], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareOH");
        addSample("Dry SnareRound 2 OH", snareRoundDestination + "snareRound_2_OH.wav", defaultMidiNotes[3], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareOH");
        addSample("Dry SnareRound 3 OH", snareRoundDestination + "snareRound_3_OH.wav", defaultMidiNotes[3], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareOH");
        addSample("Dry SnareRound 1 Room", snareRoundDestination + "snareRound_1_room.wav", defaultMidiNotes[3], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareRoom");
        addSample("Dry SnareRound 2 Room", snareRoundDestination + "snareRound_2_room.wav", defaultMidiNotes[3], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareRoom");
        addSample("Dry SnareRound 3 Room", snareRoundDestination + "snareRound_3_room.wav", defaultMidiNotes[3], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareRoom");
        addSample("Dry SnareRound 1 Bleed", snareRoundDestination + "snareRound_1_bleed.wav", defaultMidiNotes[3], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareBleed");
        addSample("Dry SnareRound 2 Bleed", snareRoundDestination + "snareRound_2_bleed.wav", defaultMidiNotes[3], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareBleed");
        addSample("Dry SnareRound 3 Bleed", snareRoundDestination + "snareRound_3_bleed.wav", defaultMidiNotes[3], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareBleed");

        string snareWirelessDestination = snareAllDestination + "snareWireless/";
        addSample("Dry SnareWireless 1 Top", snareWirelessDestination + "snareWireless_1_top.wav", defaultMidiNotes[4], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareTop");
        addSample("Dry SnareWireless 2 Top", snareWirelessDestination + "snareWireless_2_top.wav", defaultMidiNotes[4], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareTop");
        addSample("Dry SnareWireless 3 Top", snareWirelessDestination + "snareWireless_3_top.wav", defaultMidiNotes[4], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareTop");
        addSample("Dry SnareWireless 4 Top", snareWirelessDestination + "snareWireless_4_top.wav", defaultMidiNotes[4], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareTop");
        addSample("Dry SnareWireless 1 Bot", snareWirelessDestination + "snareWireless_1_bot.wav", defaultMidiNotes[4], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareBot");
        addSample("Dry SnareWireless 2 Bot", snareWirelessDestination + "snareWireless_2_bot.wav", defaultMidiNotes[4], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareBot");
        addSample("Dry SnareWireless 3 Bot", snareWirelessDestination + "snareWireless_3_bot.wav", defaultMidiNotes[4], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareBot");
        addSample("Dry SnareWireless 4 Bot", snareWirelessDestination + "snareWireless_4_bot.wav", defaultMidiNotes[4], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareBot");
        addSample("Dry SnareWireless 1 OH", snareWirelessDestination + "snareWireless_1_OH.wav", defaultMidiNotes[4], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareOH");
        addSample("Dry SnareWireless 2 OH", snareWirelessDestination + "snareWireless_2_OH.wav", defaultMidiNotes[4], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareOH");
        addSample("Dry SnareWireless 3 OH", snareWirelessDestination + "snareWireless_3_OH.wav", defaultMidiNotes[4], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareOH");
        addSample("Dry SnareWireless 4 OH", snareWirelessDestination + "snareWireless_4_OH.wav", defaultMidiNotes[4], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareOH");
        addSample("Dry SnareWireless 1 Room", snareWirelessDestination + "snareWireless_1_room.wav", defaultMidiNotes[4], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareRoom");
        addSample("Dry SnareWireless 2 Room", snareWirelessDestination + "snareWireless_2_room.wav", defaultMidiNotes[4], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareRoom");
        addSample("Dry SnareWireless 3 Room", snareWirelessDestination + "snareWireless_3_room.wav", defaultMidiNotes[4], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareRoom");
        addSample("Dry SnareWireless 4 Room", snareWirelessDestination + "snareWireless_4_room.wav", defaultMidiNotes[4], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareRoom");
        addSample("Dry SnareWireless 1 Bleed", snareWirelessDestination + "snareWireless_1_bleed.wav", defaultMidiNotes[4], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareBleed");
        addSample("Dry SnareWireless 2 Bleed", snareWirelessDestination + "snareWireless_2_bleed.wav", defaultMidiNotes[4], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareBleed");
        addSample("Dry SnareWireless 3 Bleed", snareWirelessDestination + "snareWireless_3_bleed.wav", defaultMidiNotes[4], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareBleed");
        addSample("Dry SnareWireless 4 Bleed", snareWirelessDestination + "snareWireless_4_bleed.wav", defaultMidiNotes[4], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareBleed");

        string snareWirelessRoundDestination = snareAllDestination + "snareWirelessRound/";
        addSample("Dry SnareWirelessRound 1 Top", snareWirelessRoundDestination + "snareWirelessRound_1_top.wav", defaultMidiNotes[5], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareTop");
        addSample("Dry SnareWirelessRound 2 Top", snareWirelessRoundDestination + "snareWirelessRound_2_top.wav", defaultMidiNotes[5], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareTop");
        addSample("Dry SnareWirelessRound 3 Top", snareWirelessRoundDestination + "snareWirelessRound_3_top.wav", defaultMidiNotes[5], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareTop");
        addSample("Dry SnareWirelessRound 1 Bot", snareWirelessRoundDestination + "snareWirelessRound_1_bot.wav", defaultMidiNotes[5], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareBot");
        addSample("Dry SnareWirelessRound 2 Bot", snareWirelessRoundDestination + "snareWirelessRound_2_bot.wav", defaultMidiNotes[5], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareBot");
        addSample("Dry SnareWirelessRound 3 Bot", snareWirelessRoundDestination + "snareWirelessRound_3_bot.wav", defaultMidiNotes[5], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareBot");
        addSample("Dry SnareWirelessRound 1 OH", snareWirelessRoundDestination + "snareWirelessRound_1_OH.wav", defaultMidiNotes[5], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareOH");
        addSample("Dry SnareWirelessRound 2 OH", snareWirelessRoundDestination + "snareWirelessRound_2_OH.wav", defaultMidiNotes[5], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareOH");
        addSample("Dry SnareWirelessRound 3 OH", snareWirelessRoundDestination + "snareWirelessRound_3_OH.wav", defaultMidiNotes[5], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareOH");
        addSample("Dry SnareWirelessRound 1 Room", snareWirelessRoundDestination + "snareWirelessRound_1_room.wav", defaultMidiNotes[5], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareRoom");
        addSample("Dry SnareWirelessRound 2 Room", snareWirelessRoundDestination + "snareWirelessRound_2_room.wav", defaultMidiNotes[5], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareRoom");
        addSample("Dry SnareWirelessRound 3 Room", snareWirelessRoundDestination + "snareWirelessRound_3_room.wav", defaultMidiNotes[5], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareRoom");
        addSample("Dry SnareWirelessRound 1 Bleed", snareWirelessRoundDestination + "snareWirelessRound_1_bleed.wav", defaultMidiNotes[5], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareBleed");
        addSample("Dry SnareWirelessRound 2 Bleed", snareWirelessRoundDestination + "snareWirelessRound_2_bleed.wav", defaultMidiNotes[5], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareBleed");
        addSample("Dry SnareWirelessRound 3 Bleed", snareWirelessRoundDestination + "snareWirelessRound_3_bleed.wav", defaultMidiNotes[5], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareBleed");

        double tomRelease = 0.6;
        double tomMaxLen = 2.2;
        string tomAllDestination = dryDestination + "tomAll/";
        string tomDestination = tomAllDestination + "tom/";
        addSample("Dry Tom 1 Close", tomDestination + "tom_1_close.wav", defaultMidiNotes[6], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomClose");
        addSample("Dry Tom 2 Close", tomDestination + "tom_2_close.wav", defaultMidiNotes[6], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomClose");
        addSample("Dry Tom 3 Close", tomDestination + "tom_3_close.wav", defaultMidiNotes[6], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomClose");
        addSample("Dry Tom 4 Close", tomDestination + "tom_4_close.wav", defaultMidiNotes[6], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomClose");
        addSample("Dry Tom 1 OH", tomDestination + "tom_1_OH.wav", defaultMidiNotes[6], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsOH");
        addSample("Dry Tom 2 OH", tomDestination + "tom_2_OH.wav", defaultMidiNotes[6], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsOH");
        addSample("Dry Tom 3 OH", tomDestination + "tom_3_OH.wav", defaultMidiNotes[6], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsOH");
        addSample("Dry Tom 4 OH", tomDestination + "tom_4_OH.wav", defaultMidiNotes[6], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsOH");
        addSample("Dry Tom 1 Room", tomDestination + "tom_1_room.wav", defaultMidiNotes[6], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsRoom");
        addSample("Dry Tom 2 Room", tomDestination + "tom_2_room.wav", defaultMidiNotes[6], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsRoom");
        addSample("Dry Tom 3 Room", tomDestination + "tom_3_room.wav", defaultMidiNotes[6], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsRoom");
        addSample("Dry Tom 4 Room", tomDestination + "tom_4_room.wav", defaultMidiNotes[6], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsRoom");
        addSample("Dry Tom 1 Bleed", tomDestination + "tom_1_bleed.wav", defaultMidiNotes[6], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsBleed");
        addSample("Dry Tom 2 Bleed", tomDestination + "tom_2_bleed.wav", defaultMidiNotes[6], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsBleed");
        addSample("Dry Tom 3 Bleed", tomDestination + "tom_3_bleed.wav", defaultMidiNotes[6], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsBleed");
        addSample("Dry Tom 4 Bleed", tomDestination + "tom_4_bleed.wav", defaultMidiNotes[6], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsBleed");

        string tomFlamDestination = tomAllDestination + "tomFlam/";
        addSample("Dry TomFlam 1 Close", tomFlamDestination + "tomFlam_1_close.wav", defaultMidiNotes[7], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomClose");
        addSample("Dry TomFlam 2 Close", tomFlamDestination + "tomFlam_2_close.wav", defaultMidiNotes[7], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomClose");
        addSample("Dry TomFlam 3 Close", tomFlamDestination + "tomFlam_3_close.wav", defaultMidiNotes[7], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomClose");
        addSample("Dry TomFlam 1 OH", tomFlamDestination + "tomFlam_1_OH.wav", defaultMidiNotes[7], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsOH");
        addSample("Dry TomFlam 2 OH", tomFlamDestination + "tomFlam_2_OH.wav", defaultMidiNotes[7], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsOH");
        addSample("Dry TomFlam 3 OH", tomFlamDestination + "tomFlam_3_OH.wav", defaultMidiNotes[7], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsOH");
        addSample("Dry TomFlam 1 Room", tomFlamDestination + "tomFlam_1_room.wav", defaultMidiNotes[7], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsRoom");
        addSample("Dry TomFlam 2 Room", tomFlamDestination + "tomFlam_2_room.wav", defaultMidiNotes[7], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsRoom");
        addSample("Dry TomFlam 3 Room", tomFlamDestination + "tomFlam_3_room.wav", defaultMidiNotes[7], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsRoom");
        addSample("Dry TomFlam 1 Bleed", tomFlamDestination + "tomFlam_1_bleed.wav", defaultMidiNotes[7], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsBleed");
        addSample("Dry TomFlam 2 Bleed", tomFlamDestination + "tomFlam_2_bleed.wav", defaultMidiNotes[7], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsBleed");
        addSample("Dry TomFlam 3 Bleed", tomFlamDestination + "tomFlam_3_bleed.wav", defaultMidiNotes[7], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsBleed");

        double ftomRelease = 0.7;
        double ftomMaxLen = 2.5;
        string ftomAllDestination = dryDestination + "ftomAll/";
        string ftomDestination = ftomAllDestination + "ftom/";
        addSample("Dry FTom 1 Close", ftomDestination + "ftom_1_close.wav", defaultMidiNotes[8], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "FTomClose");
        addSample("Dry FTom 2 Close", ftomDestination + "ftom_2_close.wav", defaultMidiNotes[8], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "FTomClose");
        addSample("Dry FTom 3 Close", ftomDestination + "ftom_3_close.wav", defaultMidiNotes[8], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "FTomClose");
        addSample("Dry FTom 4 Close", ftomDestination + "ftom_4_close.wav", defaultMidiNotes[8], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "FTomClose");
        addSample("Dry FTom 1 OH", ftomDestination + "ftom_1_OH.wav", defaultMidiNotes[8], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "TomsOH");
        addSample("Dry FTom 2 OH", ftomDestination + "ftom_2_OH.wav", defaultMidiNotes[8], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "TomsOH");
        addSample("Dry FTom 3 OH", ftomDestination + "ftom_3_OH.wav", defaultMidiNotes[8], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "TomsOH");
        addSample("Dry FTom 4 OH", ftomDestination + "ftom_4_OH.wav", defaultMidiNotes[8], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "TomsOH");
        addSample("Dry FTom 1 Room", ftomDestination + "ftom_1_room.wav", defaultMidiNotes[8], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "TomsRoom");
        addSample("Dry FTom 2 Room", ftomDestination + "ftom_2_room.wav", defaultMidiNotes[8], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "TomsRoom");
        addSample("Dry FTom 3 Room", ftomDestination + "ftom_3_room.wav", defaultMidiNotes[8], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "TomsRoom");
        addSample("Dry FTom 4 Room", ftomDestination + "ftom_4_room.wav", defaultMidiNotes[8], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "TomsRoom");
        addSample("Dry FTom 1 Bleed", ftomDestination + "ftom_1_bleed.wav", defaultMidiNotes[8], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.4, "TomsBleed");
        addSample("Dry FTom 2 Bleed", ftomDestination + "ftom_2_bleed.wav", defaultMidiNotes[8], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.9, "TomsBleed");
        addSample("Dry FTom 3 Bleed", ftomDestination + "ftom_3_bleed.wav", defaultMidiNotes[8], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsBleed");
        addSample("Dry FTom 4 Bleed", ftomDestination + "ftom_4_bleed.wav", defaultMidiNotes[8], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsBleed");

        string ftomFlamDestination = ftomAllDestination + "ftomFlam/";
        addSample("Dry FTomFlam 1 Close", ftomFlamDestination + "ftomFlam_1_close.wav", defaultMidiNotes[9], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "FTomClose");
        addSample("Dry FTomFlam 2 Close", ftomFlamDestination + "ftomFlam_2_close.wav", defaultMidiNotes[9], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "FTomClose");
        addSample("Dry FTomFlam 3 Close", ftomFlamDestination + "ftomFlam_3_close.wav", defaultMidiNotes[9], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "FTomClose");
        addSample("Dry FTomFlam 1 OH", ftomFlamDestination + "ftomFlam_1_OH.wav", defaultMidiNotes[9], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsOH");
        addSample("Dry FTomFlam 2 OH", ftomFlamDestination + "ftomFlam_2_OH.wav", defaultMidiNotes[9], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsOH");
        addSample("Dry FTomFlam 3 OH", ftomFlamDestination + "ftomFlam_3_OH.wav", defaultMidiNotes[9], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsOH");
        addSample("Dry FTomFlam 1 Room", ftomFlamDestination + "ftomFlam_1_room.wav", defaultMidiNotes[9], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsRoom");
        addSample("Dry FTomFlam 2 Room", ftomFlamDestination + "ftomFlam_2_room.wav", defaultMidiNotes[9], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsRoom");
        addSample("Dry FTomFlam 3 Room", ftomFlamDestination + "ftomFlam_3_room.wav", defaultMidiNotes[9], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsRoom");
        addSample("Dry FTomFlam 1 Bleed", ftomFlamDestination + "ftomFlam_1_bleed.wav", defaultMidiNotes[9], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsBleed");
        addSample("Dry FTomFlam 2 Bleed", ftomFlamDestination + "ftomFlam_2_bleed.wav", defaultMidiNotes[9], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsBleed");
        addSample("Dry FTomFlam 3 Bleed", ftomFlamDestination + "ftomFlam_3_bleed.wav", defaultMidiNotes[9], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsBleed");

        double hhRelease = 0.12;
        string tambDestination = dryDestination + "tambourine/";
        addSample("Dry Tambourine 1 OH", tambDestination + "tambourine_1_OH.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsOH");
        addSample("Dry Tambourine 2 OH", tambDestination + "tambourine_2_OH.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsOH");
        addSample("Dry Tambourine 3 OH", tambDestination + "tambourine_3_OH.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsOH");
        addSample("Dry Tambourine 1 Room", tambDestination + "tambourine_1_room.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsRoom");
        addSample("Dry Tambourine 2 Room", tambDestination + "tambourine_2_room.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsRoom");
        addSample("Dry Tambourine 3 Room", tambDestination + "tambourine_3_room.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsRoom");
        addSample("Dry Tambourine 1 Bleed", tambDestination + "tambourine_1_bleed.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsBleed");
        addSample("Dry Tambourine 2 Bleed", tambDestination + "tambourine_2_bleed.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsBleed");
        addSample("Dry Tambourine 3 Bleed", tambDestination + "tambourine_3_bleed.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsBleed");

        double hhMaxLen = 1.0;
        string HHAllDestination = dryDestination + "HHAll/";
        string HHClosedDestination = HHAllDestination + "HHClosed/";
        addSample("Dry HHClosed 1 Close", HHClosedDestination + "HHClosed_1_close.wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "HHClose");
        addSample("Dry HHClosed 2 Close", HHClosedDestination + "HHClosed_2_close.wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "HHClose");
        addSample("Dry HHClosed 3 Close", HHClosedDestination + "HHClosed_3_close.wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "HHClose");
        addSample("Dry HHClosed 4 Close", HHClosedDestination + "HHClosed_4_close.wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "HHClose");
        addSample("Dry HHClosed 5 Close", HHClosedDestination + "HHClosed_5_close.wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "HHClose");
        addSample("Dry HHClosed 1 OH", HHClosedDestination + "HHClosed_1_OH.wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsOH");
        addSample("Dry HHClosed 2 OH", HHClosedDestination + "HHClosed_2_OH.wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsOH");
        addSample("Dry HHClosed 3 OH", HHClosedDestination + "HHClosed_3_OH.wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsOH");
        addSample("Dry HHClosed 4 OH", HHClosedDestination + "HHClosed_4_OH.wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsOH");
        addSample("Dry HHClosed 5 OH", HHClosedDestination + "HHClosed_5_OH.wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsOH");
        addSample("Dry HHClosed 1 Room", HHClosedDestination + "HHClosed_1_room.wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsRoom");
        addSample("Dry HHClosed 2 Room", HHClosedDestination + "HHClosed_2_room.wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsRoom");
        addSample("Dry HHClosed 3 Room", HHClosedDestination + "HHClosed_3_room.wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsRoom");
        addSample("Dry HHClosed 4 Room", HHClosedDestination + "HHClosed_4_room.wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsRoom");
        addSample("Dry HHClosed 5 Room", HHClosedDestination + "HHClosed_5_room.wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsRoom");
        addSample("Dry HHClosed 1 Bleed", HHClosedDestination + "HHClosed_1_bleed.wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsBleed");
        addSample("Dry HHClosed 2 Bleed", HHClosedDestination + "HHClosed_2_bleed.wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsBleed");
        addSample("Dry HHClosed 3 Bleed", HHClosedDestination + "HHClosed_3_bleed.wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsBleed");
        addSample("Dry HHClosed 4 Bleed", HHClosedDestination + "HHClosed_4_bleed.wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsBleed");
        addSample("Dry HHClosed 5 Bleed", HHClosedDestination + "HHClosed_5_bleed.wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsBleed");

        double hhHalfMaxLen = 1.4;
        string HHHalfDestination = HHAllDestination + "HHHalf/";
        addSample("Dry HHHalf 1 Close", HHHalfDestination + "HHHalf_1_close.wav", defaultMidiNotes[12], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "HHClose");
        addSample("Dry HHHalf 2 Close", HHHalfDestination + "HHHalf_2_close.wav", defaultMidiNotes[12], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "HHClose");
        addSample("Dry HHHalf 3 Close", HHHalfDestination + "HHHalf_3_close.wav", defaultMidiNotes[12], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "HHClose");
        addSample("Dry HHHalf 4 Close", HHHalfDestination + "HHHalf_4_close.wav", defaultMidiNotes[12], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "HHClose");
        addSample("Dry HHHalf 1 OH", HHHalfDestination + "HHHalf_1_OH.wav", defaultMidiNotes[12], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH");
        addSample("Dry HHHalf 2 OH", HHHalfDestination + "HHHalf_2_OH.wav", defaultMidiNotes[12], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH");
        addSample("Dry HHHalf 3 OH", HHHalfDestination + "HHHalf_3_OH.wav", defaultMidiNotes[12], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH");
        addSample("Dry HHHalf 4 OH", HHHalfDestination + "HHHalf_4_OH.wav", defaultMidiNotes[12], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH");
        addSample("Dry HHHalf 1 Room", HHHalfDestination + "HHHalf_1_room.wav", defaultMidiNotes[12], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom");
        addSample("Dry HHHalf 2 Room", HHHalfDestination + "HHHalf_2_room.wav", defaultMidiNotes[12], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom");
        addSample("Dry HHHalf 3 Room", HHHalfDestination + "HHHalf_3_room.wav", defaultMidiNotes[12], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom");
        addSample("Dry HHHalf 4 Room", HHHalfDestination + "HHHalf_4_room.wav", defaultMidiNotes[12], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom");
        addSample("Dry HHHalf 1 Bleed", HHHalfDestination + "HHHalf_1_bleed.wav", defaultMidiNotes[12], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed");
        addSample("Dry HHHalf 2 Bleed", HHHalfDestination + "HHHalf_2_bleed.wav", defaultMidiNotes[12], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed");
        addSample("Dry HHHalf 3 Bleed", HHHalfDestination + "HHHalf_3_bleed.wav", defaultMidiNotes[12], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed");
        addSample("Dry HHHalf 4 Bleed", HHHalfDestination + "HHHalf_4_bleed.wav", defaultMidiNotes[12], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed");

        double hhOpenMaxLen = 5.0;
        string HHOpenDestination = HHAllDestination + "HHOpen/";
        addSample("Dry HHOpen 1 Close", HHOpenDestination + "HHOpen_1_close.wav", defaultMidiNotes[13], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "HHClose");
        addSample("Dry HHOpen 2 Close", HHOpenDestination + "HHOpen_2_close.wav", defaultMidiNotes[13], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "HHClose");
        addSample("Dry HHOpen 3 Close", HHOpenDestination + "HHOpen_3_close.wav", defaultMidiNotes[13], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "HHClose");
        addSample("Dry HHOpen 4 Close", HHOpenDestination + "HHOpen_4_close.wav", defaultMidiNotes[13], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "HHClose");
        addSample("Dry HHOpen 1 OH", HHOpenDestination + "HHOpen_1_OH.wav", defaultMidiNotes[13], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsOH");
        addSample("Dry HHOpen 2 OH", HHOpenDestination + "HHOpen_2_OH.wav", defaultMidiNotes[13], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsOH");
        addSample("Dry HHOpen 3 OH", HHOpenDestination + "HHOpen_3_OH.wav", defaultMidiNotes[13], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsOH");
        addSample("Dry HHOpen 4 OH", HHOpenDestination + "HHOpen_4_OH.wav", defaultMidiNotes[13], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsOH");
        addSample("Dry HHOpen 1 Room", HHOpenDestination + "HHOpen_1_room.wav", defaultMidiNotes[13], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsRoom");
        addSample("Dry HHOpen 2 Room", HHOpenDestination + "HHOpen_2_room.wav", defaultMidiNotes[13], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsRoom");
        addSample("Dry HHOpen 3 Room", HHOpenDestination + "HHOpen_3_room.wav", defaultMidiNotes[13], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsRoom");
        addSample("Dry HHOpen 4 Room", HHOpenDestination + "HHOpen_4_room.wav", defaultMidiNotes[13], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsRoom");
        addSample("Dry HHOpen 1 Bleed", HHOpenDestination + "HHOpen_1_bleed.wav", defaultMidiNotes[13], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsBleed");
        addSample("Dry HHOpen 2 Bleed", HHOpenDestination + "HHOpen_2_bleed.wav", defaultMidiNotes[13], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsBleed");
        addSample("Dry HHOpen 3 Bleed", HHOpenDestination + "HHOpen_3_bleed.wav", defaultMidiNotes[13], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsBleed");
        addSample("Dry HHOpen 4 Bleed", HHOpenDestination + "HHOpen_4_bleed.wav", defaultMidiNotes[13], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsBleed");

        double RideRelease = 0.7;
        string RideAllDestination = dryDestination + "rideAll/";
        string RidePointDestination = RideAllDestination + "ridePoint/";
        addSample("Dry RidePoint 1 OH", RidePointDestination + "ridePoint_1_OH.wav", defaultMidiNotes[14], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsOH");
        addSample("Dry RidePoint 2 OH", RidePointDestination + "ridePoint_2_OH.wav", defaultMidiNotes[14], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsOH");
        addSample("Dry RidePoint 3 OH", RidePointDestination + "ridePoint_3_OH.wav", defaultMidiNotes[14], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsOH");
        addSample("Dry RidePoint 4 OH", RidePointDestination + "ridePoint_4_OH.wav", defaultMidiNotes[14], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsOH");
        addSample("Dry RidePoint 1 Room", RidePointDestination + "ridePoint_1_room.wav", defaultMidiNotes[14], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsRoom");
        addSample("Dry RidePoint 2 Room", RidePointDestination + "ridePoint_2_room.wav", defaultMidiNotes[14], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsRoom");
        addSample("Dry RidePoint 3 Room", RidePointDestination + "ridePoint_3_room.wav", defaultMidiNotes[14], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsRoom");
        addSample("Dry RidePoint 4 Room", RidePointDestination + "ridePoint_4_room.wav", defaultMidiNotes[14], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsRoom");
        addSample("Dry RidePoint 1 Bleed", RidePointDestination + "ridePoint_1_bleed.wav", defaultMidiNotes[14], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsBleed");
        addSample("Dry RidePoint 2 Bleed", RidePointDestination + "ridePoint_2_bleed.wav", defaultMidiNotes[14], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsBleed");
        addSample("Dry RidePoint 3 Bleed", RidePointDestination + "ridePoint_3_bleed.wav", defaultMidiNotes[14], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsBleed");
        addSample("Dry RidePoint 4 Bleed", RidePointDestination + "ridePoint_4_bleed.wav", defaultMidiNotes[14], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsBleed");

        string RideBellDestination = RideAllDestination + "rideBell/";
        addSample("Dry RideBell 1 OH", RideBellDestination + "rideBell_1_OH.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsOH");
        addSample("Dry RideBell 2 OH", RideBellDestination + "rideBell_2_OH.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsOH");
        addSample("Dry RideBell 3 OH", RideBellDestination + "rideBell_3_OH.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsOH");
        addSample("Dry RideBell 4 OH", RideBellDestination + "rideBell_4_OH.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsOH");
        addSample("Dry RideBell 1 Room", RideBellDestination + "rideBell_1_room.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsRoom");
        addSample("Dry RideBell 2 Room", RideBellDestination + "rideBell_2_room.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsRoom");
        addSample("Dry RideBell 3 Room", RideBellDestination + "rideBell_3_room.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsRoom");
        addSample("Dry RideBell 4 Room", RideBellDestination + "rideBell_4_room.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsRoom");
        addSample("Dry RideBell 1 Bleed", RideBellDestination + "rideBell_1_bleed.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsBleed");
        addSample("Dry RideBell 2 Bleed", RideBellDestination + "rideBell_2_bleed.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsBleed");
        addSample("Dry RideBell 3 Bleed", RideBellDestination + "rideBell_3_bleed.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsBleed");
        addSample("Dry RideBell 4 Bleed", RideBellDestination + "rideBell_4_bleed.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsBleed");

        double RideOpenRelease = 4.5;
        string RideOpenDestination = RideAllDestination + "rideOpen/";
        addSample("Dry RideOpen 1 OH", RideOpenDestination + "rideOpen_1_OH.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsOH");
        addSample("Dry RideOpen 2 OH", RideOpenDestination + "rideOpen_2_OH.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsOH");
        addSample("Dry RideOpen 3 OH", RideOpenDestination + "rideOpen_3_OH.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsOH");
        addSample("Dry RideOpen 4 OH", RideOpenDestination + "rideOpen_4_OH.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsOH");
        addSample("Dry RideOpen 1 Room", RideOpenDestination + "rideOpen_1_room.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsRoom");
        addSample("Dry RideOpen 2 Room", RideOpenDestination + "rideOpen_2_room.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsRoom");
        addSample("Dry RideOpen 3 Room", RideOpenDestination + "rideOpen_3_room.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsRoom");
        addSample("Dry RideOpen 4 Room", RideOpenDestination + "rideOpen_4_room.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsRoom");
        addSample("Dry RideOpen 1 Bleed", RideOpenDestination + "rideOpen_1_bleed.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsBleed");
        addSample("Dry RideOpen 2 Bleed", RideOpenDestination + "rideOpen_2_bleed.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsBleed");
        addSample("Dry RideOpen 3 Bleed", RideOpenDestination + "rideOpen_3_bleed.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsBleed");
        addSample("Dry RideOpen 4 Bleed", RideOpenDestination + "rideOpen_4_bleed.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsBleed");


        double CrashRelease = 0.12;
        string CrashAllDestination = dryDestination + "crashAll/";
        string CrashPointDestination = CrashAllDestination + "crashPoint/";
        addSample("Dry CrashPoint 1 OH", CrashPointDestination + "crashPoint_1_OH.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsOH");
        addSample("Dry CrashPoint 2 OH", CrashPointDestination + "crashPoint_2_OH.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsOH");
        addSample("Dry CrashPoint 3 OH", CrashPointDestination + "crashPoint_3_OH.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsOH");
        addSample("Dry CrashPoint 1 Room", CrashPointDestination + "crashPoint_1_room.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsRoom");
        addSample("Dry CrashPoint 2 Room", CrashPointDestination + "crashPoint_2_room.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsRoom");
        addSample("Dry CrashPoint 3 Room", CrashPointDestination + "crashPoint_3_room.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsRoom");
        addSample("Dry CrashPoint 1 Bleed", CrashPointDestination + "crashPoint_1_bleed.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsBleed");
        addSample("Dry CrashPoint 2 Bleed", CrashPointDestination + "crashPoint_2_bleed.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsBleed");
        addSample("Dry CrashPoint 3 Bleed", CrashPointDestination + "crashPoint_3_bleed.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsBleed");

        string CrashBellDestination = CrashAllDestination + "crashBell/";
        addSample("Dry CrashBell 1 OH", CrashBellDestination + "crashBell_1_OH.wav", defaultMidiNotes[18], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsOH");
        addSample("Dry CrashBell 2 OH", CrashBellDestination + "crashBell_2_OH.wav", defaultMidiNotes[18], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsOH");
        addSample("Dry CrashBell 3 OH", CrashBellDestination + "crashBell_3_OH.wav", defaultMidiNotes[18], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsOH");
        addSample("Dry CrashBell 1 Room", CrashBellDestination + "crashBell_1_room.wav", defaultMidiNotes[18], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsRoom");
        addSample("Dry CrashBell 2 Room", CrashBellDestination + "crashBell_2_room.wav", defaultMidiNotes[18], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsRoom");
        addSample("Dry CrashBell 3 Room", CrashBellDestination + "crashBell_3_room.wav", defaultMidiNotes[18], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsRoom");
        addSample("Dry CrashBell 1 Bleed", CrashBellDestination + "crashBell_1_bleed.wav", defaultMidiNotes[18], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsBleed");
        addSample("Dry CrashBell 2 Bleed", CrashBellDestination + "crashBell_2_bleed.wav", defaultMidiNotes[18], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsBleed");
        addSample("Dry CrashBell 3 Bleed", CrashBellDestination + "crashBell_3_bleed.wav", defaultMidiNotes[18], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsBleed");

        double CrashOpenRelease = 0.14;
        double CrashOpenMaxLen = 6.0;
        string CrashOpenDestination = CrashAllDestination + "crashOpen/";
        addSample("Dry CrashOpen 1 OH", CrashOpenDestination + "crashOpen_1_OH.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsOH");
        addSample("Dry CrashOpen 2 OH", CrashOpenDestination + "crashOpen_2_OH.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsOH");
        addSample("Dry CrashOpen 3 OH", CrashOpenDestination + "crashOpen_3_OH.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsOH");
        addSample("Dry CrashOpen 4 OH", CrashOpenDestination + "crashOpen_4_OH.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsOH");
        addSample("Dry CrashOpen 1 Room", CrashOpenDestination + "crashOpen_1_room.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsRoom");
        addSample("Dry CrashOpen 2 Room", CrashOpenDestination + "crashOpen_2_room.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsRoom");
        addSample("Dry CrashOpen 3 Room", CrashOpenDestination + "crashOpen_3_room.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsRoom");
        addSample("Dry CrashOpen 4 Room", CrashOpenDestination + "crashOpen_4_room.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsRoom");
        addSample("Dry CrashOpen 1 Bleed", CrashOpenDestination + "crashOpen_1_bleed.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsBleed");
        addSample("Dry CrashOpen 2 Bleed", CrashOpenDestination + "crashOpen_2_bleed.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsBleed");
        addSample("Dry CrashOpen 3 Bleed", CrashOpenDestination + "crashOpen_3_bleed.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsBleed");
        addSample("Dry CrashOpen 4 Bleed", CrashOpenDestination + "crashOpen_4_bleed.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsBleed");

    }
}

void HDrumsAudioProcessor::clearSoundsFromAllSamplers()
{
    sampler.clearSounds();
    samplerOH.clearSounds();
    samplerRoom.clearSounds();
    samplerBleed.clearSounds();

    samplerKickClose.clearSounds();
    samplerKickOH.clearSounds();
    samplerKickRoom.clearSounds();
    samplerKickBleed.clearSounds();

    samplerSnareTop.clearSounds();
    samplerSnareBot.clearSounds();
    samplerSnareOH.clearSounds();
    samplerSnareRoom.clearSounds();
    samplerSnareBleed.clearSounds();

    samplerTomClose.clearSounds();
    samplerFTomClose.clearSounds();
    samplerTomsOH.clearSounds();
    samplerTomsRoom.clearSounds();
    samplerTomsBleed.clearSounds();

    samplerHHClose.clearSounds();
    samplerCymbalsOH.clearSounds();
    samplerCymbalsRoom.clearSounds();
    samplerCymbalsBleed.clearSounds();

}

const juce::String HDrumsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HDrumsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HDrumsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HDrumsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HDrumsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HDrumsAudioProcessor::getNumPrograms()
{
    return 1;
}

int HDrumsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HDrumsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HDrumsAudioProcessor::getProgramName (int index)
{
    return {};
}

void HDrumsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


//==============================================================================
void HDrumsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    midiMessageCollector.reset(sampleRate);

    sampler.setCurrentPlaybackSampleRate(sampleRate);
    samplerOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerBleed.setCurrentPlaybackSampleRate(sampleRate);

    samplerKickClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerKickOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerKickRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerKickBleed.setCurrentPlaybackSampleRate(sampleRate);

    samplerSnareTop.setCurrentPlaybackSampleRate(sampleRate);
    samplerSnareBot.setCurrentPlaybackSampleRate(sampleRate);
    samplerSnareOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerSnareRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerSnareBleed.setCurrentPlaybackSampleRate(sampleRate);

    samplerTomClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerFTomClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerTomsOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerTomsRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerTomsBleed.setCurrentPlaybackSampleRate(sampleRate);
    
    samplerHHClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerCymbalsOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerCymbalsRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerCymbalsBleed.setCurrentPlaybackSampleRate(sampleRate);

}

void HDrumsAudioProcessor::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
}


void HDrumsAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HDrumsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HDrumsAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

    midiProcessor.process(midiMessages);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    auto sliderValue = treeState.getRawParameterValue(GAIN_ID);
    auto OHsliderValue = treeState.getRawParameterValue(OH_GAIN_ID);
    auto RoomSliderValue = treeState.getRawParameterValue(ROOM_GAIN_ID);
    auto BleedSliderValue = treeState.getRawParameterValue(BLEED_GAIN_ID);

    auto kickCloseSliderValue = treeState.getRawParameterValue(KICK_CLOSE_GAIN_ID);
    auto kickOHSliderValue = treeState.getRawParameterValue(KICK_OH_GAIN_ID);
    auto kickRoomSliderValue = treeState.getRawParameterValue(KICK_ROOM_GAIN_ID);
    auto kickBleedSliderValue = treeState.getRawParameterValue(KICK_BLEED_GAIN_ID);

    auto snareTopSliderValue = treeState.getRawParameterValue(SNARE_TOP_CLOSE_GAIN_ID);
    auto snareBotSliderValue = treeState.getRawParameterValue(SNARE_BOT_CLOSE_GAIN_ID);
    auto snareOHSliderValue = treeState.getRawParameterValue(SNARE_OH_GAIN_ID);
    auto snareRoomSliderValue = treeState.getRawParameterValue(SNARE_ROOM_GAIN_ID);
    auto snareBleedSliderValue = treeState.getRawParameterValue(SNARE_BLEED_GAIN_ID);

    auto tomCloseSliderValue = treeState.getRawParameterValue(TOM_CLOSE_GAIN_ID);
    auto ftomCloseSliderValue = treeState.getRawParameterValue(FTOM_CLOSE_GAIN_ID);
    auto tomsOHSliderValue = treeState.getRawParameterValue(TOMS_OH_GAIN_ID);
    auto tomsRoomSliderValue = treeState.getRawParameterValue(TOMS_ROOM_GAIN_ID);
    auto tomsBleedSliderValue = treeState.getRawParameterValue(TOMS_BLEED_GAIN_ID);

    auto hhCloseSliderValue = treeState.getRawParameterValue(HH_CLOSE_GAIN_ID);
    auto cymbalsOHSliderValue = treeState.getRawParameterValue(CYMBALS_OH_GAIN_ID);
    auto cymbalsRoomSliderValue = treeState.getRawParameterValue(CYMBALS_ROOM_GAIN_ID);
    auto cymbalsBleedSliderValue = treeState.getRawParameterValue(CYMBALS_BLEED_GAIN_ID);

    auto closeSoloState = treeState.getRawParameterValue(CLOSE_SOLO_ID);
    auto OHSoloState = treeState.getRawParameterValue(OH_SOLO_ID);
    auto roomSoloState = treeState.getRawParameterValue(ROOM_SOLO_ID);
    auto bleedSoloState = treeState.getRawParameterValue(BLEED_SOLO_ID);
    // =================================================================
    auto closeMuteState = treeState.getRawParameterValue(CLOSE_MUTE_ID);
    auto OHMuteState = treeState.getRawParameterValue(OH_MUTE_ID);
    auto roomMuteState = treeState.getRawParameterValue(ROOM_MUTE_ID);
    auto bleedMuteState = treeState.getRawParameterValue(BLEED_MUTE_ID);

    auto kickCloseMuteState = treeState.getRawParameterValue(KICK_CLOSE_MUTE_ID);
    auto kickOHMuteState = treeState.getRawParameterValue(KICK_OH_MUTE_ID);
    auto kickRoomMuteState = treeState.getRawParameterValue(KICK_ROOM_MUTE_ID);
    auto kickBleedMuteState = treeState.getRawParameterValue(KICK_BLEED_MUTE_ID);

    auto snareTopMuteState = treeState.getRawParameterValue(SNARE_TOP_MUTE_ID);
    auto snareBotMuteState = treeState.getRawParameterValue(SNARE_BOT_MUTE_ID);
    auto snareOHMuteState = treeState.getRawParameterValue(SNARE_OH_MUTE_ID);
    auto snareRoomMuteState = treeState.getRawParameterValue(SNARE_ROOM_MUTE_ID);
    auto snareBleedMuteState = treeState.getRawParameterValue(SNARE_BLEED_MUTE_ID);

    auto tomCloseMuteState = treeState.getRawParameterValue(TOM_CLOSE_MUTE_ID);
    auto ftomCloseMuteState = treeState.getRawParameterValue(FTOM_CLOSE_MUTE_ID);
    auto tomsOHMuteState = treeState.getRawParameterValue(TOMS_OH_MUTE_ID);
    auto tomsRoomMuteState = treeState.getRawParameterValue(TOMS_ROOM_MUTE_ID);
    auto tomsBleedMuteState = treeState.getRawParameterValue(TOMS_BLEED_MUTE_ID);

    auto hhCloseMuteState = treeState.getRawParameterValue(HH_CLOSE_MUTE_ID);
    auto cymbalsOHMuteState = treeState.getRawParameterValue(CYMBALS_OH_MUTE_ID);
    auto cymbalsRoomMuteState = treeState.getRawParameterValue(CYMBALS_ROOM_MUTE_ID);
    auto cymbalsBleedMuteState = treeState.getRawParameterValue(CYMBALS_BLEED_MUTE_ID);

    juce::AudioBuffer<float> bufferClose;
    juce::AudioBuffer<float> bufferOH;
    juce::AudioBuffer<float> bufferRoom;
    juce::AudioBuffer<float> bufferBleed;

    juce::AudioBuffer<float> bufferKickClose;
    juce::AudioBuffer<float> bufferKickOH;
    juce::AudioBuffer<float> bufferKickRoom;
    juce::AudioBuffer<float> bufferKickBleed;

    juce::AudioBuffer<float> bufferSnareTop;
    juce::AudioBuffer<float> bufferSnareBot;
    juce::AudioBuffer<float> bufferSnareOH;
    juce::AudioBuffer<float> bufferSnareRoom;
    juce::AudioBuffer<float> bufferSnareBleed;

    juce::AudioBuffer<float> bufferTomClose;
    juce::AudioBuffer<float> bufferFTomClose;
    juce::AudioBuffer<float> bufferTomsOH;
    juce::AudioBuffer<float> bufferTomsRoom;
    juce::AudioBuffer<float> bufferTomsBleed;

    juce::AudioBuffer<float> bufferHHClose;
    juce::AudioBuffer<float> bufferCymbalsOH;
    juce::AudioBuffer<float> bufferCymbalsRoom;
    juce::AudioBuffer<float> bufferCymbalsBleed;

    bufferClose.makeCopyOf(buffer);
    bufferOH.makeCopyOf(buffer);
    bufferRoom.makeCopyOf(buffer);
    bufferBleed.makeCopyOf(buffer);

    bufferKickClose.makeCopyOf(buffer);
    bufferKickOH.makeCopyOf(buffer);
    bufferKickRoom.makeCopyOf(buffer);
    bufferKickBleed.makeCopyOf(buffer);

    bufferSnareTop.makeCopyOf(buffer);
    bufferSnareBot.makeCopyOf(buffer);
    bufferSnareOH.makeCopyOf(buffer);
    bufferSnareRoom.makeCopyOf(buffer);
    bufferSnareBleed.makeCopyOf(buffer);

    bufferTomClose.makeCopyOf(buffer);
    bufferFTomClose.makeCopyOf(buffer);
    bufferTomsOH.makeCopyOf(buffer);
    bufferTomsRoom.makeCopyOf(buffer);
    bufferTomsBleed.makeCopyOf(buffer);

    bufferHHClose.makeCopyOf(buffer);
    bufferCymbalsOH.makeCopyOf(buffer);
    bufferCymbalsRoom.makeCopyOf(buffer);
    bufferCymbalsBleed.makeCopyOf(buffer);

    sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    buffer.applyGain(juce::Decibels::decibelsToGain<float>(*sliderValue));

    // Close individual microphones ========================================================================
    if (*kickCloseMuteState < 0.5f)
    {
        samplerKickClose.renderNextBlock(bufferKickClose, midiMessages, 0, bufferKickClose.getNumSamples());
        bufferClose.addFrom(0, 0, bufferKickClose, 0, 0, bufferKickClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickCloseSliderValue));
        bufferClose.addFrom(1, 0, bufferKickClose, 1, 0, bufferKickClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickCloseSliderValue));
    }
    if (*snareTopMuteState < 0.5f)
    {
        samplerSnareTop.renderNextBlock(bufferSnareTop, midiMessages, 0, bufferSnareTop.getNumSamples());
        bufferClose.addFrom(0, 0, bufferSnareTop, 0, 0, bufferSnareTop.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareTopSliderValue));
        bufferClose.addFrom(1, 0, bufferSnareTop, 1, 0, bufferSnareTop.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareTopSliderValue));
    }
    if (*snareBotMuteState < 0.5f)
    {
        samplerSnareBot.renderNextBlock(bufferSnareBot, midiMessages, 0, bufferSnareBot.getNumSamples());
        bufferClose.addFrom(0, 0, bufferSnareBot, 0, 0, bufferSnareBot.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBotSliderValue));
        bufferClose.addFrom(1, 0, bufferSnareBot, 1, 0, bufferSnareBot.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBotSliderValue));
    }
    if (*tomCloseMuteState < 0.5f)
    {
        samplerTomClose.renderNextBlock(bufferTomClose, midiMessages, 0, bufferTomClose.getNumSamples());
        bufferClose.addFrom(0, 0, bufferTomClose, 0, 0, bufferTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomCloseSliderValue));
        bufferClose.addFrom(1, 0, bufferTomClose, 1, 0, bufferTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomCloseSliderValue - 3.0));     // manual panning (the samples are mono)
    }
    if (*ftomCloseMuteState < 0.5f)
    {
        samplerFTomClose.renderNextBlock(bufferFTomClose, midiMessages, 0, bufferFTomClose.getNumSamples());
        bufferClose.addFrom(0, 0, bufferFTomClose, 0, 0, bufferFTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*ftomCloseSliderValue - 10.0));
        bufferClose.addFrom(1, 0, bufferFTomClose, 1, 0, bufferFTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*ftomCloseSliderValue));
    }
    if (*hhCloseMuteState < 0.5f)
    {
        samplerHHClose.renderNextBlock(bufferHHClose, midiMessages, 0, bufferHHClose.getNumSamples());
        bufferClose.addFrom(0, 0, bufferHHClose, 0, 0, bufferHHClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhCloseSliderValue));
        bufferClose.addFrom(1, 0, bufferHHClose, 1, 0, bufferHHClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhCloseSliderValue - 6.0));
    }

    // OH individual microphones ========================================================================
    if (*kickOHMuteState < 0.5f)
    {
        samplerKickOH.renderNextBlock(bufferKickOH, midiMessages, 0, bufferKickOH.getNumSamples());
        bufferOH.addFrom(1, 0, bufferKickOH, 1, 0, bufferKickOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickOHSliderValue));
        bufferOH.addFrom(0, 0, bufferKickOH, 0, 0, bufferKickOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickOHSliderValue));
    }
    if (*snareOHMuteState < 0.5f)
    {
        samplerSnareOH.renderNextBlock(bufferSnareOH, midiMessages, 0, bufferSnareOH.getNumSamples());
        bufferOH.addFrom(0, 0, bufferSnareOH, 0, 0, bufferSnareOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareOHSliderValue));
        bufferOH.addFrom(1, 0, bufferSnareOH, 1, 0, bufferSnareOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareOHSliderValue));
    }
    if (*tomsOHMuteState < 0.5f)
    {
        samplerTomsOH.renderNextBlock(bufferTomsOH, midiMessages, 0, bufferTomsOH.getNumSamples());
        bufferOH.addFrom(0, 0, bufferTomsOH, 0, 0, bufferTomsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsOHSliderValue));
        bufferOH.addFrom(1, 0, bufferTomsOH, 1, 0, bufferTomsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsOHSliderValue));
    }
    if (*cymbalsOHMuteState < 0.5f)
    {
        samplerCymbalsOH.renderNextBlock(bufferCymbalsOH, midiMessages, 0, bufferCymbalsOH.getNumSamples());
        bufferOH.addFrom(0, 0, bufferCymbalsOH, 0, 0, bufferCymbalsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsOHSliderValue));
        bufferOH.addFrom(1, 0, bufferCymbalsOH, 1, 0, bufferCymbalsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsOHSliderValue));
    }

    // Room individual microphones ========================================================================
    if (*kickRoomMuteState < 0.5f)
    {
        samplerKickRoom.renderNextBlock(bufferKickRoom, midiMessages, 0, bufferKickRoom.getNumSamples());
        bufferRoom.addFrom(0, 0, bufferKickRoom, 0, 0, bufferKickRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickRoomSliderValue));
        bufferRoom.addFrom(1, 0, bufferKickRoom, 1, 0, bufferKickRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickRoomSliderValue));
    }
    if (*snareRoomMuteState < 0.5f)
    {
        samplerSnareRoom.renderNextBlock(bufferSnareRoom, midiMessages, 0, bufferSnareRoom.getNumSamples());
        bufferRoom.addFrom(0, 0, bufferSnareRoom, 0, 0, bufferSnareRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareRoomSliderValue));
        bufferRoom.addFrom(1, 0, bufferSnareRoom, 1, 0, bufferSnareRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareRoomSliderValue));
    }
    if (*tomsRoomMuteState < 0.5f)
    {
        samplerTomsRoom.renderNextBlock(bufferTomsRoom, midiMessages, 0, bufferTomsRoom.getNumSamples());
        bufferRoom.addFrom(0, 0, bufferTomsRoom, 0, 0, bufferTomsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsRoomSliderValue));
        bufferRoom.addFrom(1, 0, bufferTomsRoom, 1, 0, bufferTomsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsRoomSliderValue));
    }
    if (*cymbalsRoomMuteState < 0.5f)
    {
        samplerCymbalsRoom.renderNextBlock(bufferCymbalsRoom, midiMessages, 0, bufferCymbalsRoom.getNumSamples());
        bufferRoom.addFrom(0, 0, bufferCymbalsRoom, 0, 0, bufferCymbalsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsRoomSliderValue));
        bufferRoom.addFrom(1, 0, bufferCymbalsRoom, 1, 0, bufferCymbalsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsRoomSliderValue));
    }

    // Bleed individual microphones ========================================================================
    if (*kickBleedMuteState < 0.5f)
    {
        samplerKickBleed.renderNextBlock(bufferKickBleed, midiMessages, 0, bufferKickBleed.getNumSamples());
        bufferBleed.addFrom(0, 0, bufferKickBleed, 0, 0, bufferKickBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickBleedSliderValue));
        bufferBleed.addFrom(1, 0, bufferKickBleed, 1, 0, bufferKickBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickBleedSliderValue));
    }
    if (*snareBleedMuteState < 0.5f)
    {
        samplerSnareBleed.renderNextBlock(bufferSnareBleed, midiMessages, 0, bufferSnareBleed.getNumSamples());
        bufferBleed.addFrom(0, 0, bufferSnareBleed, 0, 0, bufferSnareBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBleedSliderValue));
        bufferBleed.addFrom(1, 0, bufferSnareBleed, 1, 0, bufferSnareBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBleedSliderValue));
    }
    if (*tomsBleedMuteState < 0.5f)
    {
        samplerTomsBleed.renderNextBlock(bufferTomsBleed, midiMessages, 0, bufferTomsBleed.getNumSamples());
        bufferBleed.addFrom(0, 0, bufferTomsBleed, 0, 0, bufferTomsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsBleedSliderValue));
        bufferBleed.addFrom(1, 0, bufferTomsBleed, 1, 0, bufferTomsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsBleedSliderValue));
    }
    if (*cymbalsBleedMuteState < 0.5f)
    {
        samplerCymbalsBleed.renderNextBlock(bufferCymbalsBleed, midiMessages, 0, bufferCymbalsBleed.getNumSamples());
        bufferBleed.addFrom(0, 0, bufferCymbalsBleed, 0, 0, bufferCymbalsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsBleedSliderValue));
        bufferBleed.addFrom(1, 0, bufferCymbalsBleed, 1, 0, bufferCymbalsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsBleedSliderValue));
    }
    
    // Main mute ============================================================
    if (*closeMuteState < 0.5f)
    {
        buffer.addFrom(0, 0, bufferClose, 0, 0, bufferClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*sliderValue));
        buffer.addFrom(1, 0, bufferClose, 1, 0, bufferClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*sliderValue));
    }

    if (*OHMuteState < 0.5f)
    {
        samplerOH.renderNextBlock(bufferOH, midiMessages, 0, bufferOH.getNumSamples());
        buffer.addFrom(0, 0, bufferOH, 0, 0, bufferOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*OHsliderValue));
        buffer.addFrom(1, 0, bufferOH, 1, 0, bufferOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*OHsliderValue));
    }

    if (*roomMuteState < 0.5f)
    {
        samplerRoom.renderNextBlock(bufferRoom, midiMessages, 0, bufferRoom.getNumSamples());
        buffer.addFrom(0, 0, bufferRoom, 0, 0, bufferRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*RoomSliderValue));
        buffer.addFrom(1, 0, bufferRoom, 1, 0, bufferRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*RoomSliderValue));
    }

    if (*bleedMuteState < 0.5f)
    {
        samplerBleed.renderNextBlock(bufferBleed, midiMessages, 0, bufferBleed.getNumSamples());
        buffer.addFrom(0, 0, bufferBleed, 0, 0, bufferBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*BleedSliderValue));
        buffer.addFrom(1, 0, bufferBleed, 1, 0, bufferBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*BleedSliderValue));
    }

}

//==============================================================================
bool HDrumsAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* HDrumsAudioProcessor::createEditor()
{
    return new HDrumsAudioProcessorEditor (*this);
}

//==============================================================================
void HDrumsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

    auto sliderValue = treeState.getRawParameterValue(GAIN_ID);
    auto OHsliderValue = treeState.getRawParameterValue(OH_GAIN_ID);
    auto RoomSliderValue = treeState.getRawParameterValue(ROOM_GAIN_ID);
    auto BleedSliderValue = treeState.getRawParameterValue(BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*sliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*OHsliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*RoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*BleedSliderValue);

    auto kickCloseSliderValue = treeState.getRawParameterValue(KICK_CLOSE_GAIN_ID);
    auto kickOHSliderValue = treeState.getRawParameterValue(KICK_OH_GAIN_ID);
    auto kickRoomSliderValue = treeState.getRawParameterValue(KICK_ROOM_GAIN_ID);
    auto kickBleedSliderValue = treeState.getRawParameterValue(KICK_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickBleedSliderValue);

    auto snareTopCloseSliderValue = treeState.getRawParameterValue(SNARE_TOP_CLOSE_GAIN_ID);
    auto snareBotCloseSliderValue = treeState.getRawParameterValue(SNARE_BOT_CLOSE_GAIN_ID);
    auto snareOHSliderValue = treeState.getRawParameterValue(SNARE_OH_GAIN_ID);
    auto snareRoomSliderValue = treeState.getRawParameterValue(SNARE_ROOM_GAIN_ID);
    auto snareBleedSliderValue = treeState.getRawParameterValue(SNARE_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareTopCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBotCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBleedSliderValue);

    auto tomCloseSliderValue = treeState.getRawParameterValue(TOM_CLOSE_GAIN_ID);
    auto ftomCloseSliderValue = treeState.getRawParameterValue(FTOM_CLOSE_GAIN_ID);
    auto tomsOHSliderValue = treeState.getRawParameterValue(TOMS_OH_GAIN_ID);
    auto tomsRoomSliderValue = treeState.getRawParameterValue(TOMS_ROOM_GAIN_ID);
    auto tomsBleedSliderValue = treeState.getRawParameterValue(TOMS_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsBleedSliderValue);

    auto hhCloseSliderValue = treeState.getRawParameterValue(HH_CLOSE_GAIN_ID);
    auto cymbalsOHSliderValue = treeState.getRawParameterValue(CYMBALS_OH_GAIN_ID);
    auto cymbalsRoomSliderValue = treeState.getRawParameterValue(CYMBALS_ROOM_GAIN_ID);
    auto cymbalsBleedSliderValue = treeState.getRawParameterValue(CYMBALS_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsBleedSliderValue);

    auto samplePackMenu = treeState.getRawParameterValue(SAMPLE_PACK_ID);
    auto curveMenu = treeState.getRawParameterValue(CURVE_MENU_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*samplePackMenu);
    juce::MemoryOutputStream(destData, true).writeFloat(*curveMenu);

    auto kickNote = treeState.getRawParameterValue(KICK_MIDI_NOTE_ID);
    auto snareNote = treeState.getRawParameterValue(SNARE_MIDI_NOTE_ID);
    auto snareFlamNote = treeState.getRawParameterValue(SNARE_FLAM_MIDI_NOTE_ID);
    auto snareRoundNote = treeState.getRawParameterValue(SNARE_ROUND_MIDI_NOTE_ID);
    auto snareWirelessNote = treeState.getRawParameterValue(SNARE_WIRELESS_MIDI_NOTE_ID);
    auto snareWirelessRoundNote = treeState.getRawParameterValue(SNARE_WIRELESS_ROUND_MIDI_NOTE_ID);
    auto tomNote = treeState.getRawParameterValue(TOM_MIDI_NOTE_ID);
    auto tomFlamNote = treeState.getRawParameterValue(TOM_FLAM_MIDI_NOTE_ID);
    auto ftomNote = treeState.getRawParameterValue(FTOM_MIDI_NOTE_ID);
    auto ftomFlamNote = treeState.getRawParameterValue(FTOM_FLAM_MIDI_NOTE_ID);
    auto tambNote = treeState.getRawParameterValue(TAMB_MIDI_NOTE_ID);
    auto hhClosedNote = treeState.getRawParameterValue(HH_CLOSED_MIDI_NOTE_ID);
    auto hhHalfNote = treeState.getRawParameterValue(HH_HALF_MIDI_NOTE_ID);
    auto hhOpenNote = treeState.getRawParameterValue(HH_OPEN_MIDI_NOTE_ID);
    auto ridePointNote = treeState.getRawParameterValue(RIDE_POINT_MIDI_NOTE_ID);
    auto rideBellNote = treeState.getRawParameterValue(RIDE_BELL_MIDI_NOTE_ID);
    auto rideOpenNote = treeState.getRawParameterValue(RIDE_OPEN_MIDI_NOTE_ID);
    auto crashPointNote = treeState.getRawParameterValue(CRASH_POINT_MIDI_NOTE_ID);
    auto crashBellNote = treeState.getRawParameterValue(CRASH_BELL_MIDI_NOTE_ID);
    auto crashOpenNote = treeState.getRawParameterValue(CRASH_OPEN_MIDI_NOTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoundNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareWirelessNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareWirelessRoundNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tambNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhClosedNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhHalfNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ridePointNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*rideBellNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*rideOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashPointNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashBellNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashOpenNote);

    auto closeMute = treeState.getRawParameterValue(CLOSE_MUTE_ID);
    auto OHMute = treeState.getRawParameterValue(OH_MUTE_ID);
    auto roomMute = treeState.getRawParameterValue(ROOM_MUTE_ID);
    auto bleedMute = treeState.getRawParameterValue(BLEED_MUTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*closeMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*OHMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*roomMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*bleedMute);

    auto kickCloseMute = treeState.getRawParameterValue(KICK_CLOSE_MUTE_ID);
    auto kickOHMute = treeState.getRawParameterValue(KICK_OH_MUTE_ID);
    auto kickRoomMute = treeState.getRawParameterValue(KICK_ROOM_MUTE_ID);
    auto kickBleedMute = treeState.getRawParameterValue(KICK_BLEED_MUTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickCloseMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickOHMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickRoomMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickBleedMute);

    auto snareTopMute = treeState.getRawParameterValue(SNARE_TOP_MUTE_ID);
    auto snareBotMute = treeState.getRawParameterValue(SNARE_BOT_MUTE_ID);
    auto snareOHMute = treeState.getRawParameterValue(SNARE_OH_MUTE_ID);
    auto snareRoomMute = treeState.getRawParameterValue(SNARE_ROOM_MUTE_ID);
    auto snareBleedMute = treeState.getRawParameterValue(SNARE_BLEED_MUTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareTopMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBotMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareOHMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoomMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBleedMute);

    auto tomCloseMute = treeState.getRawParameterValue(TOM_CLOSE_MUTE_ID);
    auto ftomCloseMute = treeState.getRawParameterValue(FTOM_CLOSE_MUTE_ID);
    auto tomsOHMute = treeState.getRawParameterValue(TOMS_OH_MUTE_ID);
    auto tomsRoomMute = treeState.getRawParameterValue(TOMS_ROOM_MUTE_ID);
    auto tomsBleedMute = treeState.getRawParameterValue(TOMS_BLEED_MUTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomCloseMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomCloseMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsOHMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsRoomMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsBleedMute);

    auto hhCloseMute = treeState.getRawParameterValue(HH_CLOSE_MUTE_ID);
    auto cymbalsOHMute = treeState.getRawParameterValue(CYMBALS_OH_MUTE_ID);
    auto cymbalsRoomMute = treeState.getRawParameterValue(CYMBALS_ROOM_MUTE_ID);
    auto cymbalsBleedMute = treeState.getRawParameterValue(CYMBALS_BLEED_MUTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhCloseMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsOHMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsRoomMute);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsBleedMute);
}

void HDrumsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(treeState.state.getType()))
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HDrumsAudioProcessor();
}
