#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginEditor.cpp"
#include <JuceHeader.h>
#include "SamplerSoundLayer.h"
#include "LoadingSamples.h"

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

    for (auto i = 0; i < 16; i++)    // i < x+1 defines how many sounds can play at the same time (x)
        samplerBinaural.addVoice(new juce::SamplerVoice());

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

    auto KickCloseGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_CLOSE_GAIN_ID, KICK_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto KickOHGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_OH_GAIN_ID, KICK_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, -3.0f);
    auto KickRoomGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_ROOM_GAIN_ID, KICK_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto KickBleedGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_BLEED_GAIN_ID, KICK_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -18.0f);
    params.push_back(std::move(KickCloseGainParam));
    params.push_back(std::move(KickOHGainParam));
    params.push_back(std::move(KickRoomGainParam));
    params.push_back(std::move(KickBleedGainParam));

    auto SnareTopCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_TOP_CLOSE_GAIN_ID, SNARE_TOP_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto SnareBotCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BOT_CLOSE_GAIN_ID, SNARE_BOT_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, -9.0f);
    auto SnareOHGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_OH_GAIN_ID, SNARE_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto SnareRoomGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_ROOM_GAIN_ID, SNARE_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto SnareBleedGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BLEED_GAIN_ID, SNARE_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -9.0f);
    params.push_back(std::move(SnareTopCloseGainParam));
    params.push_back(std::move(SnareBotCloseGainParam));
    params.push_back(std::move(SnareOHGainParam));
    params.push_back(std::move(SnareRoomGainParam));
    params.push_back(std::move(SnareBleedGainParam));

    auto TomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(TOM_CLOSE_GAIN_ID, TOM_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto FTomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(FTOM_CLOSE_GAIN_ID, FTOM_CLOSE_GAIN_NAME, sliderMinValue, sliderMaxValue, 0.0f);
    auto TomsOHGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_OH_GAIN_ID, TOMS_OH_GAIN_NAME, sliderMinValue, sliderMaxValue, -6.0f);
    auto TomsRoomGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_ROOM_GAIN_ID, TOMS_ROOM_GAIN_NAME, sliderMinValue, sliderMaxValue, -16.0f);
    auto TomsBleedGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_BLEED_GAIN_ID, TOMS_BLEED_GAIN_NAME, sliderMinValue, sliderMaxValue, -12.0f);
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
    auto CurveMenuParam = std::make_unique<juce::AudioParameterChoice>(CURVE_MENU_ID, CURVE_MENU_NAME, juce::StringArray("Linear", "Natural"), 1);
    params.push_back(std::move(SamplePackParam));
    params.push_back(std::move(CurveMenuParam));
    // ==================================================================

    // Solo parameters ==================================================
    auto binauralParam = std::make_unique<juce::AudioParameterBool>(BINAURAL_ID, BINAURAL_NAME, false);
    params.push_back(std::move(binauralParam));

    auto closeSoloParam = std::make_unique<juce::AudioParameterBool>(CLOSE_SOLO_ID, CLOSE_SOLO_NAME, false);
    auto OHSoloParam = std::make_unique<juce::AudioParameterBool>(OH_SOLO_ID, OH_SOLO_NAME, false);
    auto roomSoloParam = std::make_unique<juce::AudioParameterBool>(ROOM_SOLO_ID, ROOM_SOLO_NAME, false);
    auto bleedSoloParam = std::make_unique<juce::AudioParameterBool>(BLEED_SOLO_ID, BLEED_SOLO_NAME, false);
    params.push_back(std::move(closeSoloParam));
    params.push_back(std::move(OHSoloParam));
    params.push_back(std::move(roomSoloParam));
    params.push_back(std::move(bleedSoloParam));

    auto kickCloseSoloParam = std::make_unique<juce::AudioParameterBool>(KICK_CLOSE_SOLO_ID, KICK_CLOSE_SOLO_NAME, false);
    auto kickOHSoloParam = std::make_unique<juce::AudioParameterBool>(KICK_OH_SOLO_ID, KICK_OH_SOLO_NAME, false);
    auto kickRoomSoloParam = std::make_unique<juce::AudioParameterBool>(KICK_ROOM_SOLO_ID, KICK_ROOM_SOLO_NAME, false);
    auto kickBleedSoloParam = std::make_unique<juce::AudioParameterBool>(KICK_BLEED_SOLO_ID, KICK_BLEED_SOLO_NAME, false);
    params.push_back(std::move(kickCloseSoloParam));
    params.push_back(std::move(kickOHSoloParam));
    params.push_back(std::move(kickRoomSoloParam));
    params.push_back(std::move(kickBleedSoloParam));

    auto snareTopSoloParam = std::make_unique<juce::AudioParameterBool>(SNARE_TOP_SOLO_ID, SNARE_TOP_SOLO_NAME, false);
    auto snareBotSoloParam = std::make_unique<juce::AudioParameterBool>(SNARE_BOT_SOLO_ID, SNARE_BOT_SOLO_NAME, false);
    auto snareOHSoloParam = std::make_unique<juce::AudioParameterBool>(SNARE_OH_SOLO_ID, SNARE_OH_SOLO_NAME, false);
    auto snareRoomSoloParam = std::make_unique<juce::AudioParameterBool>(SNARE_ROOM_SOLO_ID, SNARE_ROOM_SOLO_NAME, false);
    auto snareBleedSoloParam = std::make_unique<juce::AudioParameterBool>(SNARE_BLEED_SOLO_ID, SNARE_BLEED_SOLO_NAME, false);
    params.push_back(std::move(snareTopSoloParam));
    params.push_back(std::move(snareBotSoloParam));
    params.push_back(std::move(snareOHSoloParam));
    params.push_back(std::move(snareRoomSoloParam));
    params.push_back(std::move(snareBleedSoloParam));

    auto tomCloseSoloParam = std::make_unique<juce::AudioParameterBool>(TOM_CLOSE_SOLO_ID, TOM_CLOSE_SOLO_NAME, false);
    auto ftomCloseSoloParam = std::make_unique<juce::AudioParameterBool>(FTOM_CLOSE_SOLO_ID, FTOM_CLOSE_SOLO_NAME, false);
    auto tomsOHSoloParam = std::make_unique<juce::AudioParameterBool>(TOMS_OH_SOLO_ID, TOMS_OH_SOLO_NAME, false);
    auto tomsRoomSoloParam = std::make_unique<juce::AudioParameterBool>(TOMS_ROOM_SOLO_ID, TOMS_ROOM_SOLO_NAME, false);
    auto tomsBleedSoloParam = std::make_unique<juce::AudioParameterBool>(TOMS_BLEED_SOLO_ID, TOMS_BLEED_SOLO_NAME, false);
    params.push_back(std::move(tomCloseSoloParam));
    params.push_back(std::move(ftomCloseSoloParam));
    params.push_back(std::move(tomsOHSoloParam));
    params.push_back(std::move(tomsRoomSoloParam));
    params.push_back(std::move(tomsBleedSoloParam));

    auto hhCloseSoloParam = std::make_unique<juce::AudioParameterBool>(HH_CLOSE_SOLO_ID, HH_CLOSE_SOLO_NAME, false);
    auto cymbalsOHSoloParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_OH_SOLO_ID, CYMBALS_OH_SOLO_NAME, false);
    auto cymbalsRoomSoloParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_ROOM_SOLO_ID, CYMBALS_ROOM_SOLO_NAME, false);
    auto cymbalsBleedSoloParam = std::make_unique<juce::AudioParameterBool>(CYMBALS_BLEED_SOLO_ID, CYMBALS_BLEED_SOLO_NAME, false);
    params.push_back(std::move(hhCloseSoloParam));
    params.push_back(std::move(cymbalsOHSoloParam));
    params.push_back(std::move(cymbalsRoomSoloParam));
    params.push_back(std::move(cymbalsBleedSoloParam));

    // Mute parameters ==================================================
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

    auto kickNoteParam = std::make_unique<juce::AudioParameterChoice>(KICK_MIDI_NOTE_ID, KICK_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[1]);
    auto snareNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_MIDI_NOTE_ID, SNARE_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[2]);
    auto snareSwirlNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_SWIRL_MIDI_NOTE_ID, SNARE_SWIRL_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[3]);
    auto snareFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_FLAM_MIDI_NOTE_ID, SNARE_FLAM_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[4]);
    auto snareRoundNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_ROUND_MIDI_NOTE_ID, SNARE_ROUND_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[5]);
    auto snareWirelessNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_WIRELESS_MIDI_NOTE_ID, SNARE_WIRELESS_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[6]);
    auto snareWirelessRoundNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_WIRELESS_ROUND_MIDI_NOTE_ID, SNARE_WIRELESS_ROUND_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[7]);
    auto snarePiccoloNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_PICCOLO_MIDI_NOTE_ID, SNARE_PICCOLO_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[8]);
    auto snarePiccoloSwirlNoteParam = std::make_unique<juce::AudioParameterChoice>(SNARE_PICCOLO_SWIRL_MIDI_NOTE_ID, SNARE_PICCOLO_SWIRL_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[9]);
    auto tomNoteParam = std::make_unique<juce::AudioParameterChoice>(TOM_MIDI_NOTE_ID, TOM_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[10]);
    auto tomFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(TOM_FLAM_MIDI_NOTE_ID, TOM_FLAM_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[11]);
    auto ftomNoteParam = std::make_unique<juce::AudioParameterChoice>(FTOM_MIDI_NOTE_ID, FTOM_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[12]);
    auto ftomFlamNoteParam = std::make_unique<juce::AudioParameterChoice>(FTOM_FLAM_MIDI_NOTE_ID, FTOM_FLAM_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[13]);
    auto hhFootNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_FOOT_MIDI_NOTE_ID, HH_FOOT_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[14]);
    auto hhClosedNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_CLOSED_MIDI_NOTE_ID, HH_CLOSED_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[15]);
    auto hhHalfNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_HALF_MIDI_NOTE_ID, HH_HALF_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[16]);
    auto hhOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(HH_OPEN_MIDI_NOTE_ID, HH_OPEN_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[17]);
    auto tambNoteParam = std::make_unique<juce::AudioParameterChoice>(TAMB_MIDI_NOTE_ID, TAMB_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[18]);
    auto ridePointNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_POINT_MIDI_NOTE_ID, RIDE_POINT_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[19]);
    auto rideBellNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_BELL_MIDI_NOTE_ID, RIDE_BELL_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[20]);
    auto rideOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(RIDE_OPEN_MIDI_NOTE_ID, RIDE_OPEN_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[21]);
    auto crashPointNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_POINT_MIDI_NOTE_ID, CRASH_POINT_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[22]);
    auto crashBellNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_BELL_MIDI_NOTE_ID, CRASH_BELL_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[23]);
    auto crashOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(CRASH_OPEN_MIDI_NOTE_ID, CRASH_OPEN_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[24]);
    auto stackClosedNoteParam = std::make_unique<juce::AudioParameterChoice>(STACK_CLOSED_MIDI_NOTE_ID, STACK_CLOSED_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[25]);
    auto stackOpenNoteParam = std::make_unique<juce::AudioParameterChoice>(STACK_OPEN_MIDI_NOTE_ID, STACK_OPEN_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[26]);
    auto sticksNoteParam = std::make_unique<juce::AudioParameterChoice>(STICKS_MIDI_NOTE_ID, STICKS_MIDI_NOTE_NAME, processorMidiNotes, midiProcessor.newMidiNotes[27]);
    params.push_back(std::move(kickNoteParam));
    params.push_back(std::move(snareNoteParam));
    params.push_back(std::move(snareSwirlNoteParam));
    params.push_back(std::move(snareFlamNoteParam));
    params.push_back(std::move(snareRoundNoteParam));
    params.push_back(std::move(snareWirelessNoteParam));
    params.push_back(std::move(snareWirelessRoundNoteParam));
    params.push_back(std::move(snarePiccoloNoteParam));
    params.push_back(std::move(snarePiccoloSwirlNoteParam));
    params.push_back(std::move(tomNoteParam));
    params.push_back(std::move(tomFlamNoteParam));
    params.push_back(std::move(ftomNoteParam));
    params.push_back(std::move(ftomFlamNoteParam));
    params.push_back(std::move(hhFootNoteParam));
    params.push_back(std::move(hhClosedNoteParam));
    params.push_back(std::move(hhHalfNoteParam));
    params.push_back(std::move(hhOpenNoteParam));
    params.push_back(std::move(tambNoteParam));
    params.push_back(std::move(ridePointNoteParam));
    params.push_back(std::move(rideBellNoteParam));
    params.push_back(std::move(rideOpenNoteParam));
    params.push_back(std::move(crashPointNoteParam));
    params.push_back(std::move(crashBellNoteParam));
    params.push_back(std::move(crashOpenNoteParam));
    params.push_back(std::move(stackClosedNoteParam));
    params.push_back(std::move(stackOpenNoteParam));
    params.push_back(std::move(sticksNoteParam));

    return { params.begin(), params.end() };
}
//==============================================================================

void HDrumsAudioProcessor::loadSamples(int samplePackID)
{
    loadingSamples.samplePack = samplePackID;
    if (samplePackID == 1)  // Electronic Drum Kit
    {
        clearSoundsFromAllSamplers();
        loadingSamples.loadElectronicSamples(samplers, formatManager);
    }
    else if (samplePackID == 2) // Acoustic Drum Kit
    {
        clearSoundsFromAllSamplers();
        loadingSamples.loadAcousticSamples(samplers, formatManager);
    }
    else if (samplePackID == 3) // Dry Drum Kit
    {
        clearSoundsFromAllSamplers();
        loadingSamples.loadDrySamples(samplers, formatManager);
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

    samplerBinaural.clearSounds();
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

    samplerBinaural.setCurrentPlaybackSampleRate(sampleRate);
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

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

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

    // =================================================================
    auto binauralState = treeState.getRawParameterValue(BINAURAL_ID);
    auto samplePackId = treeState.getRawParameterValue(SAMPLE_PACK_ID);
    
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

    juce::AudioBuffer<float> bufferBinaural;

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

    bufferBinaural.makeCopyOf(buffer);
    
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

    if (*binauralState > 0.5f && *samplePackId == 1)
    {
        samplerBinaural.renderNextBlock(bufferBinaural, midiMessages, 0, bufferBinaural.getNumSamples());
        buffer.addFrom(0, 0, bufferBinaural, 0, 0, bufferBinaural.getNumSamples(), 1.5f * juce::Decibels::decibelsToGain<float>(*sliderValue));
        buffer.addFrom(1, 0, bufferBinaural, 1, 0, bufferBinaural.getNumSamples(), 1.5f * juce::Decibels::decibelsToGain<float>(*sliderValue));
    }
    else
    {
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
    auto snareSwirlNote = treeState.getRawParameterValue(SNARE_SWIRL_MIDI_NOTE_ID);
    auto snareFlamNote = treeState.getRawParameterValue(SNARE_FLAM_MIDI_NOTE_ID);
    auto snareRoundNote = treeState.getRawParameterValue(SNARE_ROUND_MIDI_NOTE_ID);
    auto snareWirelessNote = treeState.getRawParameterValue(SNARE_WIRELESS_MIDI_NOTE_ID);
    auto snareWirelessRoundNote = treeState.getRawParameterValue(SNARE_WIRELESS_ROUND_MIDI_NOTE_ID);
    auto snarePiccoloNote = treeState.getRawParameterValue(SNARE_PICCOLO_MIDI_NOTE_ID);
    auto snarePiccoloSwirlNote = treeState.getRawParameterValue(SNARE_PICCOLO_SWIRL_MIDI_NOTE_ID);
    auto tomNote = treeState.getRawParameterValue(TOM_MIDI_NOTE_ID);
    auto tomFlamNote = treeState.getRawParameterValue(TOM_FLAM_MIDI_NOTE_ID);
    auto ftomNote = treeState.getRawParameterValue(FTOM_MIDI_NOTE_ID);
    auto ftomFlamNote = treeState.getRawParameterValue(FTOM_FLAM_MIDI_NOTE_ID);
    auto hhFootNote = treeState.getRawParameterValue(HH_FOOT_MIDI_NOTE_ID);
    auto hhClosedNote = treeState.getRawParameterValue(HH_CLOSED_MIDI_NOTE_ID);
    auto hhHalfNote = treeState.getRawParameterValue(HH_HALF_MIDI_NOTE_ID);
    auto hhOpenNote = treeState.getRawParameterValue(HH_OPEN_MIDI_NOTE_ID);
    auto tambNote = treeState.getRawParameterValue(TAMB_MIDI_NOTE_ID);
    auto ridePointNote = treeState.getRawParameterValue(RIDE_POINT_MIDI_NOTE_ID);
    auto rideBellNote = treeState.getRawParameterValue(RIDE_BELL_MIDI_NOTE_ID);
    auto rideOpenNote = treeState.getRawParameterValue(RIDE_OPEN_MIDI_NOTE_ID);
    auto crashPointNote = treeState.getRawParameterValue(CRASH_POINT_MIDI_NOTE_ID);
    auto crashBellNote = treeState.getRawParameterValue(CRASH_BELL_MIDI_NOTE_ID);
    auto crashOpenNote = treeState.getRawParameterValue(CRASH_OPEN_MIDI_NOTE_ID);
    auto stackClosedNote = treeState.getRawParameterValue(STACK_CLOSED_MIDI_NOTE_ID);
    auto stackOpenNote = treeState.getRawParameterValue(STACK_OPEN_MIDI_NOTE_ID);
    auto sticksNote = treeState.getRawParameterValue(STICKS_MIDI_NOTE_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareSwirlNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoundNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareWirelessNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareWirelessRoundNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snarePiccoloNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*snarePiccoloSwirlNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomFlamNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhFootNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhClosedNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhHalfNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*tambNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*ridePointNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*rideBellNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*rideOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashPointNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashBellNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*stackClosedNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*stackOpenNote);
    juce::MemoryOutputStream(destData, true).writeFloat(*sticksNote);

    // Solo buttons
    auto binauralState = treeState.getRawParameterValue(BINAURAL_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*binauralState);

    auto closeSolo = treeState.getRawParameterValue(CLOSE_SOLO_ID);
    auto OHSolo = treeState.getRawParameterValue(OH_SOLO_ID);
    auto roomSolo = treeState.getRawParameterValue(ROOM_SOLO_ID);
    auto bleedSolo = treeState.getRawParameterValue(BLEED_SOLO_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*closeSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*OHSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*roomSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*bleedSolo);

    auto kickCloseSolo = treeState.getRawParameterValue(KICK_CLOSE_SOLO_ID);
    auto kickOHSolo = treeState.getRawParameterValue(KICK_OH_SOLO_ID);
    auto kickRoomSolo = treeState.getRawParameterValue(KICK_ROOM_SOLO_ID);
    auto kickBleedSolo = treeState.getRawParameterValue(KICK_BLEED_SOLO_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickCloseSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickOHSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickRoomSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickBleedSolo);

    auto snareTopSolo = treeState.getRawParameterValue(SNARE_TOP_SOLO_ID);
    auto snareBotSolo = treeState.getRawParameterValue(SNARE_BOT_SOLO_ID);
    auto snareOHSolo = treeState.getRawParameterValue(SNARE_OH_SOLO_ID);
    auto snareRoomSolo = treeState.getRawParameterValue(SNARE_ROOM_SOLO_ID);
    auto snareBleedSolo = treeState.getRawParameterValue(SNARE_BLEED_SOLO_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareTopSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBotSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareOHSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoomSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBleedSolo);

    auto tomCloseSolo = treeState.getRawParameterValue(TOM_CLOSE_SOLO_ID);
    auto ftomCloseSolo = treeState.getRawParameterValue(FTOM_CLOSE_SOLO_ID);
    auto tomsOHSolo = treeState.getRawParameterValue(TOMS_OH_SOLO_ID);
    auto tomsRoomSolo = treeState.getRawParameterValue(TOMS_ROOM_SOLO_ID);
    auto tomsBleedSolo = treeState.getRawParameterValue(TOMS_BLEED_SOLO_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomCloseSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*ftomCloseSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsOHSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsRoomSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*tomsBleedSolo);

    auto hhCloseSolo = treeState.getRawParameterValue(HH_CLOSE_SOLO_ID);
    auto cymbalsOHSolo = treeState.getRawParameterValue(CYMBALS_OH_SOLO_ID);
    auto cymbalsRoomSolo = treeState.getRawParameterValue(CYMBALS_ROOM_SOLO_ID);
    auto cymbalsBleedSolo = treeState.getRawParameterValue(CYMBALS_BLEED_SOLO_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhCloseSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsOHSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsRoomSolo);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsBleedSolo);

    // Mute buttons
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
