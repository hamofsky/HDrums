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
    for (auto i = 0; i < 10; i++)    // i < x+1 defines how many sounds can play at the same time
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
        samplerTambClose.addVoice(new juce::SamplerVoice());
        samplerHHOH.addVoice(new juce::SamplerVoice());
        samplerHHRoom.addVoice(new juce::SamplerVoice());
        samplerHHBleed.addVoice(new juce::SamplerVoice());

        samplerCrashClose.addVoice(new juce::SamplerVoice());
        samplerRideClose.addVoice(new juce::SamplerVoice());
        samplerCymbalsOH.addVoice(new juce::SamplerVoice());
        samplerCymbalsRoom.addVoice(new juce::SamplerVoice());
        samplerCymbalsBleed.addVoice(new juce::SamplerVoice());
    }

    loadSamples(1, 1, 57, 60);  // default settings for samples

}

HDrumsAudioProcessor::~HDrumsAudioProcessor()
{
}

//==============================================================================
// here you add parameters that need to be transported from the Editor to the Processor (slider values, etc.). These will also be available to be automated in a DAW
juce::AudioProcessorValueTreeState::ParameterLayout HDrumsAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    auto gainParam = std::make_unique<juce::AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto OHgainParam = std::make_unique<juce::AudioParameterFloat>(OH_GAIN_ID, OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto RoomGainParam = std::make_unique<juce::AudioParameterFloat>(ROOM_GAIN_ID, ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto BleedGainParam = std::make_unique<juce::AudioParameterFloat>(BLEED_GAIN_ID, BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(gainParam));
    params.push_back(std::move(OHgainParam));
    params.push_back(std::move(RoomGainParam));
    params.push_back(std::move(BleedGainParam));

    auto KickCloseGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_CLOSE_GAIN_ID, KICK_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto KickOHGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_OH_GAIN_ID, KICK_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto KickRoomGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_ROOM_GAIN_ID, KICK_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto KickBleedGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_BLEED_GAIN_ID, KICK_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(KickCloseGainParam));
    params.push_back(std::move(KickOHGainParam));
    params.push_back(std::move(KickRoomGainParam));
    params.push_back(std::move(KickBleedGainParam));

    auto SnareTopCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_TOP_CLOSE_GAIN_ID, SNARE_TOP_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto SnareBotCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BOT_CLOSE_GAIN_ID, SNARE_BOT_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto SnareOHGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_OH_GAIN_ID, SNARE_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto SnareRoomGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_ROOM_GAIN_ID, SNARE_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto SnareBleedGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BLEED_GAIN_ID, SNARE_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareTopCloseGainParam));
    params.push_back(std::move(SnareBotCloseGainParam));
    params.push_back(std::move(SnareOHGainParam));
    params.push_back(std::move(SnareRoomGainParam));
    params.push_back(std::move(SnareBleedGainParam));

    auto TomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(TOM_CLOSE_GAIN_ID, TOM_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto FTomCloseGainParam = std::make_unique<juce::AudioParameterFloat>(FTOM_CLOSE_GAIN_ID, FTOM_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto TomsOHGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_OH_GAIN_ID, TOMS_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto TomsRoomGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_ROOM_GAIN_ID, TOMS_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto TomsBleedGainParam = std::make_unique<juce::AudioParameterFloat>(TOMS_BLEED_GAIN_ID, TOMS_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(TomCloseGainParam));
    params.push_back(std::move(FTomCloseGainParam));
    params.push_back(std::move(TomsOHGainParam));
    params.push_back(std::move(TomsRoomGainParam));
    params.push_back(std::move(TomsBleedGainParam));

    auto HHCloseGainParam = std::make_unique<juce::AudioParameterFloat>(HH_CLOSE_GAIN_ID, HH_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto HHOHGainParam = std::make_unique<juce::AudioParameterFloat>(HH_OH_GAIN_ID, HH_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto HHRoomGainParam = std::make_unique<juce::AudioParameterFloat>(HH_ROOM_GAIN_ID, HH_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto HHBleedGainParam = std::make_unique<juce::AudioParameterFloat>(HH_BLEED_GAIN_ID, HH_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(HHCloseGainParam));
    params.push_back(std::move(HHOHGainParam));
    params.push_back(std::move(HHRoomGainParam));
    params.push_back(std::move(HHBleedGainParam));

    auto CrashCloseGainParam = std::make_unique<juce::AudioParameterFloat>(CRASH_CLOSE_GAIN_ID, CRASH_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto RideCloseGainParam = std::make_unique<juce::AudioParameterFloat>(RIDE_CLOSE_GAIN_ID, RIDE_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto TambCloseGainParam = std::make_unique<juce::AudioParameterFloat>(TAMB_CLOSE_GAIN_ID, TAMB_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto CymbalsOHGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_OH_GAIN_ID, CYMBALS_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto CymbalsRoomGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_ROOM_GAIN_ID, CYMBALS_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    auto CymbalsBleedGainParam = std::make_unique<juce::AudioParameterFloat>(CYMBALS_BLEED_GAIN_ID, CYMBALS_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(CrashCloseGainParam));
    params.push_back(std::move(RideCloseGainParam));
    params.push_back(std::move(TambCloseGainParam));
    params.push_back(std::move(CymbalsOHGainParam));
    params.push_back(std::move(CymbalsRoomGainParam));
    params.push_back(std::move(CymbalsBleedGainParam));

    //auto samplePack = std::make_unique<juce::ComboBoxParameterAttachment>(SAMPLE_PACK_ID, SAMPLE_PACK, 0, 1, 1);
    //params.push_back(std::move(samplePack));
    return { params.begin(), params.end() };
}
//==============================================================================

void HDrumsAudioProcessor::addSample(string sampleName, string destination, int midiNote, int lowestVelocity, int highestVelocity, double release, double maxLength, string bus)
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

    }
    else {
        loadDirectory();
    }
    
}

void HDrumsAudioProcessor::loadDirectory()
{
    DBG("Source was a nullptr, so you will have to choose a correct directory");
}

void HDrumsAudioProcessor::loadSamples(int samplePackID, int curveMenuID, int kickNoteID, int snareNoteID)
{
    string destinationAll = "C:/Users/damia/Desktop/Sampelki/";

    auto curveFor3 = linCurveFor3;
    auto curveFor4 = linCurveFor4;
    auto curveFor5 = linCurveFor5;
    auto curveFor6 = linCurveFor6;
    if (curveMenuID == 1) {
        curveFor3 = linCurveFor3;
        curveFor4 = linCurveFor4;
        curveFor5 = linCurveFor5;
        curveFor6 = linCurveFor6;
    }
    else if (curveMenuID == 2) {
        curveFor3 = logCurveFor3;
        curveFor4 = logCurveFor4;
        curveFor5 = logCurveFor5;
        curveFor6 = logCurveFor6;
    }

    if (samplePackID == 1) {
        clearSoundsFromAllSamplers();
        float snareRelease = 0.5;
        float snareMaxLen = 2.0;

        string destinationP = destinationAll + "Perkusja/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        addSample("Ride Hard", destinationP + "Ride Hard.wav", 65, curveFor6[0], 127, 5.0, 8.0, "Close");
        addSample("Ride Smooth", destinationP + "Ride Smooth.wav", 65, 1, curveFor6[0] - 1, 0.5, 8.0, "Close");
        string GGDdestination = destinationP + "GGD/";
        addSample("HH open", GGDdestination + "HH open.wav", 64, 1, 127, 0.12, 6.5, "Close");
        addSample("HH closed", GGDdestination + "HH closed.wav", 62, 1, 127, 0.1, 2.0, "Close");

        string snareDestination = destinationP + "Konrad1/Snare/";
        addSample("Snare 1_1", snareDestination + "Snare 1_1.wav", snareNoteID, curveFor6[4], 127, snareRelease, snareMaxLen, "Close");
        addSample("Snare 2_1", snareDestination + "Snare 2_1.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 3_1", snareDestination + "Snare 3_1.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 4_1", snareDestination + "Snare 4_1.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 5_1", snareDestination + "Snare 5_1.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 6_1", snareDestination + "Snare 6_1.wav", snareNoteID, 1, curveFor6[0] - 1, snareRelease, snareMaxLen, "Close");
        string kickDestination = destinationP + "Konrad1/Kick/";
        addSample("Kick 0_1", kickDestination + "Kick 0_1.wav", kickNoteID, 126, 127, 0.6, 2.0, "Close");
        addSample("Kick 1_1", kickDestination + "Kick 1_1.wav", kickNoteID, 114, 125, 0.6, 2.0, "Close");
        addSample("Kick 2_1", kickDestination + "Kick 2_1.wav", kickNoteID, 100, 113, 0.6, 2.0, "Close");
        addSample("Kick 3_1", kickDestination + "Kick 3_1.wav", kickNoteID, 85, 99, 0.6, 2.0, "Close");
        addSample("Kick 4_1", kickDestination + "Kick 4_1.wav", kickNoteID, 75, 84, 0.6, 2.0, "Close");
        addSample("Kick 5_1", kickDestination + "Kick 5_1.wav", kickNoteID, 66, 74, 0.6, 2.0, "Close");
        addSample("Kick 6_1", kickDestination + "Kick 6_1.wav", kickNoteID, curveFor6[0], curveFor6[1] - 1, 0.6, 2.0, "Close");
        addSample("Kick 7_1", kickDestination + "Kick 7_1.wav", kickNoteID, 1, curveFor6[0] - 1, 0.6, 2.0, "Close");
        string FTCloseDestination = destinationP + "Konrad1/FT/Close/";
        addSample("FT Close 1_1", FTCloseDestination + "FT Close 1_1.wav", 67, 1, 127, 0.7, 1.5, "Close");
        string FTOHDestination = destinationP + "Konrad1/FT/OH/";
        addSample("FT OH 1_1", FTOHDestination + "FT OH 1_1.wav", 67, 1, 127, 0.7, 1.5, "OH");
    }
    else if (samplePackID == 2) {
        clearSoundsFromAllSamplers();
        
        string LeafDestination = destinationAll + "Fall of the Leaf/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        addSample("Leaf Kick + Crash", LeafDestination + "Leaf Kick + Crash.wav", 65, 1, 127, 5.0, 8.0, "Close");
        addSample("Leaf Kick", LeafDestination + "Leaf Kick.wav", kickNoteID, 1, 127, 0.6, 2.0, "Close");
        addSample("Leaf Snare", LeafDestination + "Leaf Snare.wav", snareNoteID, 1, 127, 0.5, 2.0, "Close");
        addSample("Leaf Trap Hat", LeafDestination + "Leaf Trap Hat.wav", 64, 1, 127, 0.12, 6.5, "Close");
        addSample("Leaf Hat", LeafDestination + "Leaf Hat.wav", 62, 1, 127, 0.1, 2.0, "Close");
    }
    else if (samplePackID == 3) {
        clearSoundsFromAllSamplers();

        float kickRelease = 0.6;
        float kickMaxLen = 2.0;
        string dryDestination = destinationAll + "drySamples/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        string kickDestination = dryDestination + "kick/";
        addSample("Kick 1 Close", kickDestination + "kick_1_close.wav", kickNoteID, curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 2 Close", kickDestination + "kick_2_close.wav", kickNoteID, curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 3 Close", kickDestination + "kick_3_close.wav", kickNoteID, curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 4 Close", kickDestination + "kick_4_close.wav", kickNoteID, curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 5 Close", kickDestination + "kick_5_close.wav", kickNoteID, curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 6 Close", kickDestination + "kick_6_close.wav", kickNoteID, curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickClose");
        addSample("Kick 1 OH", kickDestination + "kick_1_OH.wav", kickNoteID, curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 2 OH", kickDestination + "kick_2_OH.wav", kickNoteID, curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 3 OH", kickDestination + "kick_3_OH.wav", kickNoteID, curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 4 OH", kickDestination + "kick_4_OH.wav", kickNoteID, curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 5 OH", kickDestination + "kick_5_OH.wav", kickNoteID, curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 6 OH", kickDestination + "kick_6_OH.wav", kickNoteID, curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickOH");
        addSample("Kick 1 Room", kickDestination + "kick_1_room.wav", kickNoteID, curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 2 Room", kickDestination + "kick_2_room.wav", kickNoteID, curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 3 Room", kickDestination + "kick_3_room.wav", kickNoteID, curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 4 Room", kickDestination + "kick_4_room.wav", kickNoteID, curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 5 Room", kickDestination + "kick_5_room.wav", kickNoteID, curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 6 Room", kickDestination + "kick_6_room.wav", kickNoteID, curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickRoom");
        addSample("Kick 1 Bleed", kickDestination + "kick_1_bleed.wav", kickNoteID, curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Kick 2 Bleed", kickDestination + "kick_2_bleed.wav", kickNoteID, curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Kick 3 Bleed", kickDestination + "kick_3_bleed.wav", kickNoteID, curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Kick 4 Bleed", kickDestination + "kick_4_bleed.wav", kickNoteID, curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Kick 5 Bleed", kickDestination + "kick_5_bleed.wav", kickNoteID, curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickBleed");
        addSample("Kick 6 Bleed", kickDestination + "kick_6_bleed.wav", kickNoteID, curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickBleed");


        float snareRelease = 0.5;
        float snareMaxLen = 2.0;
        string snareAllDestination = dryDestination + "snareAll/";
        string snareDestination = snareAllDestination + "snare/";
        addSample("Snare 1 Top", snareDestination + "snare_1_top.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 2 Top", snareDestination + "snare_2_top.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 3 Top", snareDestination + "snare_3_top.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 4 Top", snareDestination + "snare_4_top.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 5 Top", snareDestination + "snare_5_top.wav", snareNoteID, curveFor6[4], curveFor6[5] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 6 Top", snareDestination + "snare_6_top.wav", snareNoteID, curveFor6[5], curveFor6[6] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("Snare 1 Bot", snareDestination + "snare_1_bot.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 2 Bot", snareDestination + "snare_2_bot.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 3 Bot", snareDestination + "snare_3_bot.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 4 Bot", snareDestination + "snare_4_bot.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 5 Bot", snareDestination + "snare_5_bot.wav", snareNoteID, curveFor6[4], curveFor6[5] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 6 Bot", snareDestination + "snare_6_bot.wav", snareNoteID, curveFor6[5], curveFor6[6] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("Snare 1 OH", snareDestination + "snare_1_OH.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 2 OH", snareDestination + "snare_2_OH.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 3 OH", snareDestination + "snare_3_OH.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 4 OH", snareDestination + "snare_4_OH.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 5 OH", snareDestination + "snare_5_OH.wav", snareNoteID, curveFor6[4], curveFor6[5] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 6 OH", snareDestination + "snare_6_OH.wav", snareNoteID, curveFor6[5], curveFor6[6] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("Snare 1 Room", snareDestination + "snare_1_room.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 2 Room", snareDestination + "snare_2_room.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 3 Room", snareDestination + "snare_3_room.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 4 Room", snareDestination + "snare_4_room.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 5 Room", snareDestination + "snare_5_room.wav", snareNoteID, curveFor6[4], curveFor6[5] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 6 Room", snareDestination + "snare_6_room.wav", snareNoteID, curveFor6[5], curveFor6[6] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("Snare 1 Bleed", snareDestination + "snare_1_bleed.wav", snareNoteID, curveFor6[0], curveFor6[1] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("Snare 2 Bleed", snareDestination + "snare_2_bleed.wav", snareNoteID, curveFor6[1], curveFor6[2] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("Snare 3 Bleed", snareDestination + "snare_3_bleed.wav", snareNoteID, curveFor6[2], curveFor6[3] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("Snare 4 Bleed", snareDestination + "snare_4_bleed.wav", snareNoteID, curveFor6[3], curveFor6[4] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("Snare 5 Bleed", snareDestination + "snare_5_bleed.wav", snareNoteID, curveFor6[4], curveFor6[5] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("Snare 6 Bleed", snareDestination + "snare_6_bleed.wav", snareNoteID, curveFor6[5], curveFor6[6] - 1, snareRelease, snareMaxLen, "SnareBleed");


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
    samplerTambClose.clearSounds();
    samplerHHOH.clearSounds();
    samplerHHRoom.clearSounds();
    samplerHHBleed.clearSounds();

    samplerCrashClose.clearSounds();
    samplerRideClose.clearSounds();
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
    samplerTambClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerHHOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerHHRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerHHBleed.setCurrentPlaybackSampleRate(sampleRate);
    
    samplerCrashClose.setCurrentPlaybackSampleRate(sampleRate);
    samplerRideClose.setCurrentPlaybackSampleRate(sampleRate);
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

void HDrumsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

    midiProcessor.process(midiMessages);    //narazie nic sie tam nie dzieje
    
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
    auto tambCloseSliderValue = treeState.getRawParameterValue(TAMB_CLOSE_GAIN_ID);
    auto hhOHSliderValue = treeState.getRawParameterValue(HH_OH_GAIN_ID);
    auto hhRoomSliderValue = treeState.getRawParameterValue(HH_ROOM_GAIN_ID);
    auto hhBleedSliderValue = treeState.getRawParameterValue(HH_BLEED_GAIN_ID);

    auto crashCloseSliderValue = treeState.getRawParameterValue(CRASH_CLOSE_GAIN_ID);
    auto rideCloseSliderValue = treeState.getRawParameterValue(RIDE_CLOSE_GAIN_ID);
    auto cymbalsOHSliderValue = treeState.getRawParameterValue(CYMBALS_OH_GAIN_ID);
    auto cymbalsRoomSliderValue = treeState.getRawParameterValue(CYMBALS_ROOM_GAIN_ID);
    auto cymbalsBleedSliderValue = treeState.getRawParameterValue(CYMBALS_BLEED_GAIN_ID);

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
    juce::AudioBuffer<float> bufferTambClose;
    juce::AudioBuffer<float> bufferHHOH;
    juce::AudioBuffer<float> bufferHHRoom;
    juce::AudioBuffer<float> bufferHHBleed;
    
    juce::AudioBuffer<float> bufferCrashClose;
    juce::AudioBuffer<float> bufferRideClose;
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
    bufferTambClose.makeCopyOf(buffer);
    bufferHHOH.makeCopyOf(buffer);
    bufferHHRoom.makeCopyOf(buffer);
    bufferHHBleed.makeCopyOf(buffer);
    
    bufferCrashClose.makeCopyOf(buffer);
    bufferRideClose.makeCopyOf(buffer);
    bufferCymbalsOH.makeCopyOf(buffer);
    bufferCymbalsRoom.makeCopyOf(buffer);
    bufferCymbalsBleed.makeCopyOf(buffer);

    sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    buffer.applyGain(juce::Decibels::decibelsToGain<float>(*sliderValue));

    samplerKickClose.renderNextBlock(bufferKickClose, midiMessages, 0, bufferKickClose.getNumSamples());
    samplerSnareTop.renderNextBlock(bufferSnareTop, midiMessages, 0, bufferSnareTop.getNumSamples());
    samplerSnareBot.renderNextBlock(bufferSnareBot, midiMessages, 0, bufferSnareBot.getNumSamples());
    samplerTomClose.renderNextBlock(bufferTomClose, midiMessages, 0, bufferTomClose.getNumSamples());
    samplerFTomClose.renderNextBlock(bufferFTomClose, midiMessages, 0, bufferFTomClose.getNumSamples());
    samplerHHClose.renderNextBlock(bufferHHClose, midiMessages, 0, bufferHHClose.getNumSamples());
    samplerTambClose.renderNextBlock(bufferTambClose, midiMessages, 0, bufferTambClose.getNumSamples());
    samplerCrashClose.renderNextBlock(bufferCrashClose, midiMessages, 0, bufferCrashClose.getNumSamples());
    samplerRideClose.renderNextBlock(bufferRideClose, midiMessages, 0, bufferRideClose.getNumSamples());

    bufferClose.addFrom(0, 0, bufferKickClose, 0, 0, bufferKickClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferKickClose, 1, 0, bufferKickClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferSnareTop, 0, 0, bufferSnareTop.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareTopSliderValue));
    bufferClose.addFrom(1, 0, bufferSnareTop, 1, 0, bufferSnareTop.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareTopSliderValue));
    bufferClose.addFrom(0, 0, bufferSnareBot, 0, 0, bufferSnareBot.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBotSliderValue));
    bufferClose.addFrom(1, 0, bufferSnareBot, 1, 0, bufferSnareBot.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBotSliderValue));
    bufferClose.addFrom(0, 0, bufferTomClose, 0, 0, bufferTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferTomClose, 1, 0, bufferTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferFTomClose, 0, 0, bufferFTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*ftomCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferFTomClose, 1, 0, bufferFTomClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*ftomCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferHHClose, 0, 0, bufferHHClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferHHClose, 1, 0, bufferHHClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferTambClose, 0, 0, bufferTambClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tambCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferTambClose, 1, 0, bufferTambClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tambCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferCrashClose, 0, 0, bufferCrashClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*crashCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferCrashClose, 1, 0, bufferCrashClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*crashCloseSliderValue));
    bufferClose.addFrom(0, 0, bufferRideClose, 0, 0, bufferRideClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*rideCloseSliderValue));
    bufferClose.addFrom(1, 0, bufferRideClose, 1, 0, bufferRideClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*rideCloseSliderValue));
    
    samplerKickOH.renderNextBlock(bufferKickOH, midiMessages, 0, bufferKickOH.getNumSamples());
    samplerSnareOH.renderNextBlock(bufferSnareOH, midiMessages, 0, bufferSnareOH.getNumSamples());
    samplerTomsOH.renderNextBlock(bufferTomsOH, midiMessages, 0, bufferTomsOH.getNumSamples());
    samplerHHOH.renderNextBlock(bufferHHOH, midiMessages, 0, bufferHHOH.getNumSamples());
    samplerCymbalsOH.renderNextBlock(bufferCymbalsOH, midiMessages, 0, bufferCymbalsOH.getNumSamples());

    bufferOH.addFrom(0, 0, bufferKickOH, 0, 0, bufferKickOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickOHSliderValue));
    bufferOH.addFrom(1, 0, bufferKickOH, 1, 0, bufferKickOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickOHSliderValue));
    bufferOH.addFrom(0, 0, bufferSnareOH, 0, 0, bufferSnareOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareOHSliderValue));
    bufferOH.addFrom(1, 0, bufferSnareOH, 1, 0, bufferSnareOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareOHSliderValue));
    bufferOH.addFrom(0, 0, bufferTomsOH, 0, 0, bufferTomsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsOHSliderValue));
    bufferOH.addFrom(1, 0, bufferTomsOH, 1, 0, bufferTomsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsOHSliderValue));
    bufferOH.addFrom(0, 0, bufferHHOH, 0, 0, bufferHHOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhOHSliderValue));
    bufferOH.addFrom(1, 0, bufferHHOH, 1, 0, bufferHHOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhOHSliderValue));
    bufferOH.addFrom(0, 0, bufferCymbalsOH, 0, 0, bufferCymbalsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsOHSliderValue));
    bufferOH.addFrom(1, 0, bufferCymbalsOH, 1, 0, bufferCymbalsOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsOHSliderValue));

    samplerKickRoom.renderNextBlock(bufferKickRoom, midiMessages, 0, bufferKickRoom.getNumSamples());
    samplerSnareRoom.renderNextBlock(bufferSnareRoom, midiMessages, 0, bufferSnareRoom.getNumSamples());
    samplerTomsRoom.renderNextBlock(bufferTomsRoom, midiMessages, 0, bufferTomsRoom.getNumSamples());
    samplerHHRoom.renderNextBlock(bufferHHRoom, midiMessages, 0, bufferHHRoom.getNumSamples());
    samplerCymbalsRoom.renderNextBlock(bufferCymbalsRoom, midiMessages, 0, bufferCymbalsRoom.getNumSamples());

    bufferRoom.addFrom(0, 0, bufferKickRoom, 0, 0, bufferKickRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickRoomSliderValue));
    bufferRoom.addFrom(1, 0, bufferKickRoom, 1, 0, bufferKickRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickRoomSliderValue));
    bufferRoom.addFrom(0, 0, bufferSnareRoom, 0, 0, bufferSnareRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareRoomSliderValue));
    bufferRoom.addFrom(1, 0, bufferSnareRoom, 1, 0, bufferSnareRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareRoomSliderValue));
    bufferRoom.addFrom(0, 0, bufferTomsRoom, 0, 0, bufferTomsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsRoomSliderValue));
    bufferRoom.addFrom(1, 0, bufferTomsRoom, 1, 0, bufferTomsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsRoomSliderValue));
    bufferRoom.addFrom(0, 0, bufferHHRoom, 0, 0, bufferHHRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhRoomSliderValue));
    bufferRoom.addFrom(1, 0, bufferHHRoom, 1, 0, bufferHHRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhRoomSliderValue));
    bufferRoom.addFrom(0, 0, bufferCymbalsRoom, 0, 0, bufferCymbalsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsRoomSliderValue));
    bufferRoom.addFrom(1, 0, bufferCymbalsRoom, 1, 0, bufferCymbalsRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsRoomSliderValue));

    samplerKickBleed.renderNextBlock(bufferKickBleed, midiMessages, 0, bufferKickBleed.getNumSamples());
    samplerSnareBleed.renderNextBlock(bufferSnareBleed, midiMessages, 0, bufferSnareBleed.getNumSamples());
    samplerTomsBleed.renderNextBlock(bufferTomsBleed, midiMessages, 0, bufferTomsBleed.getNumSamples());
    samplerHHBleed.renderNextBlock(bufferHHBleed, midiMessages, 0, bufferHHBleed.getNumSamples());
    samplerCymbalsBleed.renderNextBlock(bufferCymbalsBleed, midiMessages, 0, bufferCymbalsBleed.getNumSamples());

    bufferBleed.addFrom(0, 0, bufferKickBleed, 0, 0, bufferKickBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickBleedSliderValue));
    bufferBleed.addFrom(1, 0, bufferKickBleed, 1, 0, bufferKickBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*kickBleedSliderValue));
    bufferBleed.addFrom(0, 0, bufferSnareBleed, 0, 0, bufferSnareBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBleedSliderValue));
    bufferBleed.addFrom(1, 0, bufferSnareBleed, 1, 0, bufferSnareBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*snareBleedSliderValue));
    bufferBleed.addFrom(0, 0, bufferTomsBleed, 0, 0, bufferTomsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsBleedSliderValue));
    bufferBleed.addFrom(1, 0, bufferTomsBleed, 1, 0, bufferTomsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*tomsBleedSliderValue));
    bufferBleed.addFrom(0, 0, bufferHHBleed, 0, 0, bufferHHBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhBleedSliderValue));
    bufferBleed.addFrom(1, 0, bufferHHBleed, 1, 0, bufferHHBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*hhBleedSliderValue));
    bufferBleed.addFrom(0, 0, bufferCymbalsBleed, 0, 0, bufferCymbalsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsBleedSliderValue));
    bufferBleed.addFrom(1, 0, bufferCymbalsBleed, 1, 0, bufferCymbalsBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*cymbalsBleedSliderValue));


    buffer.addFrom(0, 0, bufferClose, 0, 0, bufferClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*sliderValue));
    buffer.addFrom(1, 0, bufferClose, 1, 0, bufferClose.getNumSamples(), juce::Decibels::decibelsToGain<float>(*sliderValue));

    samplerOH.renderNextBlock(bufferOH, midiMessages, 0, bufferOH.getNumSamples());
    buffer.addFrom(0, 0, bufferOH, 0, 0, bufferOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*OHsliderValue));
    buffer.addFrom(1, 0, bufferOH, 1, 0, bufferOH.getNumSamples(), juce::Decibels::decibelsToGain<float>(*OHsliderValue));

    samplerRoom.renderNextBlock(bufferRoom, midiMessages, 0, bufferRoom.getNumSamples());
    buffer.addFrom(0, 0, bufferRoom, 0, 0, bufferRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*RoomSliderValue));
    buffer.addFrom(1, 0, bufferRoom, 1, 0, bufferRoom.getNumSamples(), juce::Decibels::decibelsToGain<float>(*RoomSliderValue));

    samplerBleed.renderNextBlock(bufferBleed, midiMessages, 0, bufferBleed.getNumSamples());
    buffer.addFrom(0, 0, bufferBleed, 0, 0, bufferBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*BleedSliderValue));
    buffer.addFrom(1, 0, bufferBleed, 1, 0, bufferBleed.getNumSamples(), juce::Decibels::decibelsToGain<float>(*BleedSliderValue));

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
    auto tambCloseSliderValue = treeState.getRawParameterValue(TAMB_CLOSE_GAIN_ID);
    auto hhOHSliderValue = treeState.getRawParameterValue(HH_OH_GAIN_ID);
    auto hhRoomSliderValue = treeState.getRawParameterValue(HH_ROOM_GAIN_ID);
    auto hhBleedSliderValue = treeState.getRawParameterValue(HH_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*tambCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*hhBleedSliderValue);

    auto crashCloseSliderValue = treeState.getRawParameterValue(CRASH_CLOSE_GAIN_ID);
    auto rideCloseSliderValue = treeState.getRawParameterValue(RIDE_CLOSE_GAIN_ID);
    auto cymbalsOHSliderValue = treeState.getRawParameterValue(HH_OH_GAIN_ID);
    auto cymbalsRoomSliderValue = treeState.getRawParameterValue(HH_ROOM_GAIN_ID);
    auto cymbalsBleedSliderValue = treeState.getRawParameterValue(HH_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*crashCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*rideCloseSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsOHSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsRoomSliderValue);
    juce::MemoryOutputStream(destData, true).writeFloat(*cymbalsBleedSliderValue);

}

void HDrumsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(treeState.state.getType()))
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));

    //auto sliderValue = treeState.getRawParameterValue(GAIN_ID);
    //*sliderValue = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
    //auto OHsliderValue = treeState.getRawParameterValue(OH_GAIN_ID);
    //*OHsliderValue = juce::MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HDrumsAudioProcessor();
}
