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

    loadSamples(1, 1, 57, 60, 61, 62, 63, 64, 66, 67, 68, 69, 71, 72, 73, 74, 85, 76, 77, 78, 79, 81, 82, 83);// default settings for samples (samplePackMenuId, curveMenuId, kick, snare, snareFlam, ...)

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
        else if (bus == "TambClose")
            samplerTambClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "HHOH")
            samplerHHOH.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "HHRoom")
            samplerHHRoom.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "HHBleed")
            samplerHHBleed.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "CrashClose")
            samplerCrashClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "RideClose")
            samplerRideClose.addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
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

void HDrumsAudioProcessor::loadSamples(int samplePackID, int curveMenuID, int kickNoteID, int snareNoteID, int snareFlamNoteID, int snareWirelessNoteID,
                                        int snareRoundNoteID, int snareWirelessRoundNoteID, int tomNoteID, int tomFlamNoteID, int ftomNoteID, int ftomFlamNoteID,
                                        int hhBellNoteID, int hhClosedNoteID, int hhHalfNoteID, int hhOpenNoteID, int tambourineNoteID, int ridePointNoteID,
                                        int rideHalfNoteID, int rideBellNoteID, int rideOpenNoteID, int crashPointNoteID, int crashBellNoteID, int crashOpenNoteID)
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
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select
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

        string snareFlamDestination = snareAllDestination + "snareFlam/";
        addSample("SnareFlam 1 Top", snareFlamDestination + "snareFlam_1_top.wav", snareFlamNoteID, curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareFlam 2 Top", snareFlamDestination + "snareFlam_2_top.wav", snareFlamNoteID, curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareFlam 3 Top", snareFlamDestination + "snareFlam_3_top.wav", snareFlamNoteID, curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareFlam 4 Top", snareFlamDestination + "snareFlam_4_top.wav", snareFlamNoteID, curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareFlam 5 Top", snareFlamDestination + "snareFlam_5_top.wav", snareFlamNoteID, curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareFlam 1 Bot", snareFlamDestination + "snareFlam_1_bot.wav", snareFlamNoteID, curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareFlam 2 Bot", snareFlamDestination + "snareFlam_2_bot.wav", snareFlamNoteID, curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareFlam 3 Bot", snareFlamDestination + "snareFlam_3_bot.wav", snareFlamNoteID, curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareFlam 4 Bot", snareFlamDestination + "snareFlam_4_bot.wav", snareFlamNoteID, curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareFlam 5 Bot", snareFlamDestination + "snareFlam_5_bot.wav", snareFlamNoteID, curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareFlam 1 OH", snareFlamDestination + "snareFlam_1_OH.wav", snareFlamNoteID, curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareFlam 2 OH", snareFlamDestination + "snareFlam_2_OH.wav", snareFlamNoteID, curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareFlam 3 OH", snareFlamDestination + "snareFlam_3_OH.wav", snareFlamNoteID, curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareFlam 4 OH", snareFlamDestination + "snareFlam_4_OH.wav", snareFlamNoteID, curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareFlam 5 OH", snareFlamDestination + "snareFlam_5_OH.wav", snareFlamNoteID, curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareFlam 1 Room", snareFlamDestination + "snareFlam_1_room.wav", snareFlamNoteID, curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareFlam 2 Room", snareFlamDestination + "snareFlam_2_room.wav", snareFlamNoteID, curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareFlam 3 Room", snareFlamDestination + "snareFlam_3_room.wav", snareFlamNoteID, curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareFlam 4 Room", snareFlamDestination + "snareFlam_4_room.wav", snareFlamNoteID, curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareFlam 5 Room", snareFlamDestination + "snareFlam_5_room.wav", snareFlamNoteID, curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareFlam 1 Bleed", snareFlamDestination + "snareFlam_1_bleed.wav", snareFlamNoteID, curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareFlam 2 Bleed", snareFlamDestination + "snareFlam_2_bleed.wav", snareFlamNoteID, curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareFlam 3 Bleed", snareFlamDestination + "snareFlam_3_bleed.wav", snareFlamNoteID, curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareFlam 4 Bleed", snareFlamDestination + "snareFlam_4_bleed.wav", snareFlamNoteID, curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareFlam 5 Bleed", snareFlamDestination + "snareFlam_5_bleed.wav", snareFlamNoteID, curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBleed");

        string snareWirelessDestination = snareAllDestination + "snareWireless/";
        addSample("SnareWireless 1 Top", snareWirelessDestination + "snareWireless_1_top.wav", snareWirelessNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWireless 2 Top", snareWirelessDestination + "snareWireless_2_top.wav", snareWirelessNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWireless 3 Top", snareWirelessDestination + "snareWireless_3_top.wav", snareWirelessNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWireless 4 Top", snareWirelessDestination + "snareWireless_4_top.wav", snareWirelessNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWireless 1 Bot", snareWirelessDestination + "snareWireless_1_bot.wav", snareWirelessNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWireless 2 Bot", snareWirelessDestination + "snareWireless_2_bot.wav", snareWirelessNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWireless 3 Bot", snareWirelessDestination + "snareWireless_3_bot.wav", snareWirelessNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWireless 4 Bot", snareWirelessDestination + "snareWireless_4_bot.wav", snareWirelessNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWireless 1 OH", snareWirelessDestination + "snareWireless_1_OH.wav", snareWirelessNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWireless 2 OH", snareWirelessDestination + "snareWireless_2_OH.wav", snareWirelessNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWireless 3 OH", snareWirelessDestination + "snareWireless_3_OH.wav", snareWirelessNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWireless 4 OH", snareWirelessDestination + "snareWireless_4_OH.wav", snareWirelessNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWireless 1 Room", snareWirelessDestination + "snareWireless_1_room.wav", snareWirelessNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWireless 2 Room", snareWirelessDestination + "snareWireless_2_room.wav", snareWirelessNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWireless 3 Room", snareWirelessDestination + "snareWireless_3_room.wav", snareWirelessNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWireless 4 Room", snareWirelessDestination + "snareWireless_4_room.wav", snareWirelessNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWireless 1 Bleed", snareWirelessDestination + "snareWireless_1_bleed.wav", snareWirelessNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWireless 2 Bleed", snareWirelessDestination + "snareWireless_2_bleed.wav", snareWirelessNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWireless 3 Bleed", snareWirelessDestination + "snareWireless_3_bleed.wav", snareWirelessNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWireless 4 Bleed", snareWirelessDestination + "snareWireless_4_bleed.wav", snareWirelessNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBleed");

        string snareRoundDestination = snareAllDestination + "snareRound/";
        addSample("SnareRound 1 Top", snareRoundDestination + "snareRound_1_top.wav", snareRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareRound 2 Top", snareRoundDestination + "snareRound_2_top.wav", snareRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareRound 3 Top", snareRoundDestination + "snareRound_3_top.wav", snareRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareRound 4 Top", snareRoundDestination + "snareRound_4_top.wav", snareRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareRound 1 Bot", snareRoundDestination + "snareRound_1_bot.wav", snareRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareRound 2 Bot", snareRoundDestination + "snareRound_2_bot.wav", snareRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareRound 3 Bot", snareRoundDestination + "snareRound_3_bot.wav", snareRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareRound 4 Bot", snareRoundDestination + "snareRound_4_bot.wav", snareRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareRound 1 OH", snareRoundDestination + "snareRound_1_OH.wav", snareRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareRound 2 OH", snareRoundDestination + "snareRound_2_OH.wav", snareRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareRound 3 OH", snareRoundDestination + "snareRound_3_OH.wav", snareRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareRound 4 OH", snareRoundDestination + "snareRound_4_OH.wav", snareRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareRound 1 Room", snareRoundDestination + "snareRound_1_room.wav", snareRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareRound 2 Room", snareRoundDestination + "snareRound_2_room.wav", snareRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareRound 3 Room", snareRoundDestination + "snareRound_3_room.wav", snareRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareRound 4 Room", snareRoundDestination + "snareRound_4_room.wav", snareRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareRound 1 Bleed", snareRoundDestination + "snareRound_1_bleed.wav", snareRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareRound 2 Bleed", snareRoundDestination + "snareRound_2_bleed.wav", snareRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareRound 3 Bleed", snareRoundDestination + "snareRound_3_bleed.wav", snareRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareRound 4 Bleed", snareRoundDestination + "snareRound_4_bleed.wav", snareRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBleed");

        string snareWirelessRoundDestination = snareAllDestination + "snareWirelessRound/";
        addSample("SnareWirelessRound 1 Top", snareWirelessRoundDestination + "snareWirelessRound_1_top.wav", snareWirelessRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWirelessRound 2 Top", snareWirelessRoundDestination + "snareWirelessRound_2_top.wav", snareWirelessRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWirelessRound 3 Top", snareWirelessRoundDestination + "snareWirelessRound_3_top.wav", snareWirelessRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWirelessRound 4 Top", snareWirelessRoundDestination + "snareWirelessRound_4_top.wav", snareWirelessRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareTop");
        addSample("SnareWirelessRound 1 Bot", snareWirelessRoundDestination + "snareWirelessRound_1_bot.wav", snareWirelessRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWirelessRound 2 Bot", snareWirelessRoundDestination + "snareWirelessRound_2_bot.wav", snareWirelessRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWirelessRound 3 Bot", snareWirelessRoundDestination + "snareWirelessRound_3_bot.wav", snareWirelessRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWirelessRound 4 Bot", snareWirelessRoundDestination + "snareWirelessRound_4_bot.wav", snareWirelessRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBot");
        addSample("SnareWirelessRound 1 OH", snareWirelessRoundDestination + "snareWirelessRound_1_OH.wav", snareWirelessRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWirelessRound 2 OH", snareWirelessRoundDestination + "snareWirelessRound_2_OH.wav", snareWirelessRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWirelessRound 3 OH", snareWirelessRoundDestination + "snareWirelessRound_3_OH.wav", snareWirelessRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWirelessRound 4 OH", snareWirelessRoundDestination + "snareWirelessRound_4_OH.wav", snareWirelessRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareOH");
        addSample("SnareWirelessRound 1 Room", snareWirelessRoundDestination + "snareWirelessRound_1_room.wav", snareWirelessRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWirelessRound 2 Room", snareWirelessRoundDestination + "snareWirelessRound_2_room.wav", snareWirelessRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWirelessRound 3 Room", snareWirelessRoundDestination + "snareWirelessRound_3_room.wav", snareWirelessRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWirelessRound 4 Room", snareWirelessRoundDestination + "snareWirelessRound_4_room.wav", snareWirelessRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareRoom");
        addSample("SnareWirelessRound 1 Bleed", snareWirelessRoundDestination + "snareWirelessRound_1_bleed.wav", snareWirelessRoundNoteID, curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWirelessRound 2 Bleed", snareWirelessRoundDestination + "snareWirelessRound_2_bleed.wav", snareWirelessRoundNoteID, curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWirelessRound 3 Bleed", snareWirelessRoundDestination + "snareWirelessRound_3_bleed.wav", snareWirelessRoundNoteID, curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBleed");
        addSample("SnareWirelessRound 4 Bleed", snareWirelessRoundDestination + "snareWirelessRound_4_bleed.wav", snareWirelessRoundNoteID, curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBleed");

        float tomRelease = 0.6;
        float tomMaxLen = 2.2;
        string tomAllDestination = dryDestination + "tomAll/";
        string tomDestination = tomAllDestination + "tom/";
        addSample("Tom 1 Close", tomDestination + "tom_1_close.wav", tomNoteID, curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("Tom 2 Close", tomDestination + "tom_2_close.wav", tomNoteID, curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("Tom 3 Close", tomDestination + "tom_3_close.wav", tomNoteID, curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("Tom 4 Close", tomDestination + "tom_4_close.wav", tomNoteID, curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("Tom 5 Close", tomDestination + "tom_5_close.wav", tomNoteID, curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("Tom 1 OH", tomDestination + "tom_1_OH.wav", tomNoteID, curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("Tom 2 OH", tomDestination + "tom_2_OH.wav", tomNoteID, curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("Tom 3 OH", tomDestination + "tom_3_OH.wav", tomNoteID, curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("Tom 4 OH", tomDestination + "tom_4_OH.wav", tomNoteID, curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("Tom 5 OH", tomDestination + "tom_5_OH.wav", tomNoteID, curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("Tom 1 Room", tomDestination + "tom_1_room.wav", tomNoteID, curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("Tom 2 Room", tomDestination + "tom_2_room.wav", tomNoteID, curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("Tom 3 Room", tomDestination + "tom_3_room.wav", tomNoteID, curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("Tom 4 Room", tomDestination + "tom_4_room.wav", tomNoteID, curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("Tom 5 Room", tomDestination + "tom_5_room.wav", tomNoteID, curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("Tom 1 Bleed", tomDestination + "tom_1_bleed.wav", tomNoteID, curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("Tom 2 Bleed", tomDestination + "tom_2_bleed.wav", tomNoteID, curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("Tom 3 Bleed", tomDestination + "tom_3_bleed.wav", tomNoteID, curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("Tom 4 Bleed", tomDestination + "tom_4_bleed.wav", tomNoteID, curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("Tom 5 Bleed", tomDestination + "tom_5_bleed.wav", tomNoteID, curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsBleed");

        string tomFlamDestination = tomAllDestination + "tomFlam/";
        addSample("TomFlam 1 Close", tomFlamDestination + "tomFlam_1_close.wav", tomFlamNoteID, curveFor3[0], curveFor3[1] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("TomFlam 2 Close", tomFlamDestination + "tomFlam_2_close.wav", tomFlamNoteID, curveFor3[1], curveFor3[2] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("TomFlam 3 Close", tomFlamDestination + "tomFlam_3_close.wav", tomFlamNoteID, curveFor3[2], curveFor3[3] - 1, tomRelease, tomMaxLen, "TomClose");
        addSample("TomFlam 1 OH", tomFlamDestination + "tomFlam_1_OH.wav", tomFlamNoteID, curveFor3[0], curveFor3[1] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("TomFlam 2 OH", tomFlamDestination + "tomFlam_2_OH.wav", tomFlamNoteID, curveFor3[1], curveFor3[2] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("TomFlam 3 OH", tomFlamDestination + "tomFlam_3_OH.wav", tomFlamNoteID, curveFor3[2], curveFor3[3] - 1, tomRelease, tomMaxLen, "TomsOH");
        addSample("TomFlam 1 Room", tomFlamDestination + "tomFlam_1_room.wav", tomFlamNoteID, curveFor3[0], curveFor3[1] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("TomFlam 2 Room", tomFlamDestination + "tomFlam_2_room.wav", tomFlamNoteID, curveFor3[1], curveFor3[2] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("TomFlam 3 Room", tomFlamDestination + "tomFlam_3_room.wav", tomFlamNoteID, curveFor3[2], curveFor3[3] - 1, tomRelease, tomMaxLen, "TomsRoom");
        addSample("TomFlam 1 Bleed", tomFlamDestination + "tomFlam_1_bleed.wav", tomFlamNoteID, curveFor3[0], curveFor3[1] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("TomFlam 2 Bleed", tomFlamDestination + "tomFlam_2_bleed.wav", tomFlamNoteID, curveFor3[1], curveFor3[2] - 1, tomRelease, tomMaxLen, "TomsBleed");
        addSample("TomFlam 3 Bleed", tomFlamDestination + "tomFlam_3_bleed.wav", tomFlamNoteID, curveFor3[2], curveFor3[3] - 1, tomRelease, tomMaxLen, "TomsBleed");

        float ftomRelease = 0.7;
        float ftomMaxLen = 2.5;
        string ftomAllDestination = dryDestination + "ftomAll/";
        string ftomDestination = ftomAllDestination + "ftom/";
        addSample("FTom 1 Close", ftomDestination + "ftom_1_close.wav", ftomNoteID, curveFor5[0], curveFor5[1] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTom 2 Close", ftomDestination + "ftom_2_close.wav", ftomNoteID, curveFor5[1], curveFor5[2] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTom 3 Close", ftomDestination + "ftom_3_close.wav", ftomNoteID, curveFor5[2], curveFor5[3] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTom 4 Close", ftomDestination + "ftom_4_close.wav", ftomNoteID, curveFor5[3], curveFor5[4] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTom 5 Close", ftomDestination + "ftom_5_close.wav", ftomNoteID, curveFor5[4], curveFor5[5] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTom 1 OH", ftomDestination + "ftom_1_OH.wav", ftomNoteID, curveFor5[0], curveFor5[1] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTom 2 OH", ftomDestination + "ftom_2_OH.wav", ftomNoteID, curveFor5[1], curveFor5[2] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTom 3 OH", ftomDestination + "ftom_3_OH.wav", ftomNoteID, curveFor5[2], curveFor5[3] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTom 4 OH", ftomDestination + "ftom_4_OH.wav", ftomNoteID, curveFor5[3], curveFor5[4] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTom 5 OH", ftomDestination + "ftom_5_OH.wav", ftomNoteID, curveFor5[4], curveFor5[5] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTom 1 Room", ftomDestination + "ftom_1_room.wav", ftomNoteID, curveFor5[0], curveFor5[1] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTom 2 Room", ftomDestination + "ftom_2_room.wav", ftomNoteID, curveFor5[1], curveFor5[2] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTom 3 Room", ftomDestination + "ftom_3_room.wav", ftomNoteID, curveFor5[2], curveFor5[3] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTom 4 Room", ftomDestination + "ftom_4_room.wav", ftomNoteID, curveFor5[3], curveFor5[4] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTom 5 Room", ftomDestination + "ftom_5_room.wav", ftomNoteID, curveFor5[4], curveFor5[5] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTom 1 Bleed", ftomDestination + "ftom_1_bleed.wav", ftomNoteID, curveFor5[0], curveFor5[1] - 1, tomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTom 2 Bleed", ftomDestination + "ftom_2_bleed.wav", ftomNoteID, curveFor5[1], curveFor5[2] - 1, tomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTom 3 Bleed", ftomDestination + "ftom_3_bleed.wav", ftomNoteID, curveFor5[2], curveFor5[3] - 1, tomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTom 4 Bleed", ftomDestination + "ftom_4_bleed.wav", ftomNoteID, curveFor5[3], curveFor5[4] - 1, tomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTom 5 Bleed", ftomDestination + "ftom_5_bleed.wav", ftomNoteID, curveFor5[4], curveFor5[5] - 1, tomRelease, ftomMaxLen, "TomsBleed");

        string ftomFlamDestination = ftomAllDestination + "ftomFlam/";
        addSample("FTomFlam 1 Close", ftomFlamDestination + "ftomFlam_1_close.wav", ftomFlamNoteID, curveFor3[0], curveFor3[1] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTomFlam 2 Close", ftomFlamDestination + "ftomFlam_2_close.wav", ftomFlamNoteID, curveFor3[1], curveFor3[2] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTomFlam 3 Close", ftomFlamDestination + "ftomFlam_3_close.wav", ftomFlamNoteID, curveFor3[2], curveFor3[3] - 1, ftomRelease, ftomMaxLen, "FTomClose");
        addSample("FTomFlam 1 OH", ftomFlamDestination + "ftomFlam_1_OH.wav", ftomFlamNoteID, curveFor3[0], curveFor3[1] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTomFlam 2 OH", ftomFlamDestination + "ftomFlam_2_OH.wav", ftomFlamNoteID, curveFor3[1], curveFor3[2] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTomFlam 3 OH", ftomFlamDestination + "ftomFlam_3_OH.wav", ftomFlamNoteID, curveFor3[2], curveFor3[3] - 1, ftomRelease, ftomMaxLen, "TomsOH");
        addSample("FTomFlam 1 Room", ftomFlamDestination + "ftomFlam_1_room.wav", ftomFlamNoteID, curveFor3[0], curveFor3[1] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTomFlam 2 Room", ftomFlamDestination + "ftomFlam_2_room.wav", ftomFlamNoteID, curveFor3[1], curveFor3[2] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTomFlam 3 Room", ftomFlamDestination + "ftomFlam_3_room.wav", ftomFlamNoteID, curveFor3[2], curveFor3[3] - 1, ftomRelease, ftomMaxLen, "TomsRoom");
        addSample("FTomFlam 1 Bleed", ftomFlamDestination + "ftomFlam_1_bleed.wav", ftomFlamNoteID, curveFor3[0], curveFor3[1] - 1, ftomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTomFlam 2 Bleed", ftomFlamDestination + "ftomFlam_2_bleed.wav", ftomFlamNoteID, curveFor3[1], curveFor3[2] - 1, ftomRelease, ftomMaxLen, "TomsBleed");
        addSample("FTomFlam 3 Bleed", ftomFlamDestination + "ftomFlam_3_bleed.wav", ftomFlamNoteID, curveFor3[2], curveFor3[3] - 1, ftomRelease, ftomMaxLen, "TomsBleed");

        float hhRelease = 0.12;
        float hhMaxLen = 2.0;
        string tambDestination = dryDestination + "tambourine/";
        addSample("Tambourine 1 Close", tambDestination + "tambourine_1_bleed.wav", tambourineNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "TambClose");
        addSample("Tambourine 2 Close", tambDestination + "tambourine_2_bleed.wav", tambourineNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "TambClose");
        addSample("Tambourine 3 Close", tambDestination + "tambourine_3_bleed.wav", tambourineNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "TambClose");
        addSample("Tambourine 1 OH", tambDestination + "tambourine_1_OH.wav", tambourineNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("Tambourine 2 OH", tambDestination + "tambourine_2_OH.wav", tambourineNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("Tambourine 3 OH", tambDestination + "tambourine_3_OH.wav", tambourineNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("Tambourine 1 Room", tambDestination + "tambourine_1_room.wav", tambourineNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("Tambourine 2 Room", tambDestination + "tambourine_2_room.wav", tambourineNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("Tambourine 3 Room", tambDestination + "tambourine_3_room.wav", tambourineNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("Tambourine 1 Bleed", tambDestination + "tambourine_1_bleed.wav", tambourineNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("Tambourine 2 Bleed", tambDestination + "tambourine_2_bleed.wav", tambourineNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("Tambourine 3 Bleed", tambDestination + "tambourine_3_bleed.wav", tambourineNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHBleed");


        string HHAllDestination = dryDestination + "HHAll/";
        string HHBellDestination = HHAllDestination + "HHBell/";
        addSample("HHBell 1 Close", HHBellDestination + "HHBell_1_close.wav", hhBellNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHBell 2 Close", HHBellDestination + "HHBell_2_close.wav", hhBellNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHBell 3 Close", HHBellDestination + "HHBell_3_close.wav", hhBellNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHBell 1 OH", HHBellDestination + "HHBell_1_OH.wav", hhBellNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHBell 2 OH", HHBellDestination + "HHBell_2_OH.wav", hhBellNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHBell 3 OH", HHBellDestination + "HHBell_3_OH.wav", hhBellNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHBell 1 Room", HHBellDestination + "HHBell_1_room.wav", hhBellNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHBell 2 Room", HHBellDestination + "HHBell_2_room.wav", hhBellNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHBell 3 Room", HHBellDestination + "HHBell_3_room.wav", hhBellNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHBell 1 Bleed", HHBellDestination + "HHBell_1_bleed.wav", hhBellNoteID, curveFor3[0], curveFor3[1] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHBell 2 Bleed", HHBellDestination + "HHBell_2_bleed.wav", hhBellNoteID, curveFor3[1], curveFor3[2] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHBell 3 Bleed", HHBellDestination + "HHBell_3_bleed.wav", hhBellNoteID, curveFor3[2], curveFor3[3] - 1, hhRelease, hhMaxLen, "HHBleed");

        string HHClosedDestination = HHAllDestination + "HHClosed/";
        addSample("HHClosed 1 Close", HHClosedDestination + "HHClosed_1_close.wav", hhClosedNoteID, curveFor6[0], curveFor6[1] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 2 Close", HHClosedDestination + "HHClosed_2_close.wav", hhClosedNoteID, curveFor6[1], curveFor6[2] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 3 Close", HHClosedDestination + "HHClosed_3_close.wav", hhClosedNoteID, curveFor6[2], curveFor6[3] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 4 Close", HHClosedDestination + "HHClosed_4_close.wav", hhClosedNoteID, curveFor6[3], curveFor6[4] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 5 Close", HHClosedDestination + "HHClosed_5_close.wav", hhClosedNoteID, curveFor6[4], curveFor6[5] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 6 Close", HHClosedDestination + "HHClosed_6_close.wav", hhClosedNoteID, curveFor6[5], curveFor6[6] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHClosed 1 OH", HHClosedDestination + "HHClosed_1_OH.wav", hhClosedNoteID, curveFor6[0], curveFor6[1] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 2 OH", HHClosedDestination + "HHClosed_2_OH.wav", hhClosedNoteID, curveFor6[1], curveFor6[2] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 3 OH", HHClosedDestination + "HHClosed_3_OH.wav", hhClosedNoteID, curveFor6[2], curveFor6[3] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 4 OH", HHClosedDestination + "HHClosed_4_OH.wav", hhClosedNoteID, curveFor6[3], curveFor6[4] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 5 OH", HHClosedDestination + "HHClosed_5_OH.wav", hhClosedNoteID, curveFor6[4], curveFor6[5] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 6 OH", HHClosedDestination + "HHClosed_6_OH.wav", hhClosedNoteID, curveFor6[5], curveFor6[6] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHClosed 1 Room", HHClosedDestination + "HHClosed_1_room.wav", hhClosedNoteID, curveFor6[0], curveFor6[1] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 2 Room", HHClosedDestination + "HHClosed_2_room.wav", hhClosedNoteID, curveFor6[1], curveFor6[2] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 3 Room", HHClosedDestination + "HHClosed_3_room.wav", hhClosedNoteID, curveFor6[2], curveFor6[3] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 4 Room", HHClosedDestination + "HHClosed_4_room.wav", hhClosedNoteID, curveFor6[3], curveFor6[4] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 5 Room", HHClosedDestination + "HHClosed_5_room.wav", hhClosedNoteID, curveFor6[4], curveFor6[5] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 6 Room", HHClosedDestination + "HHClosed_6_room.wav", hhClosedNoteID, curveFor6[5], curveFor6[6] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHClosed 1 Bleed", HHClosedDestination + "HHClosed_1_bleed.wav", hhClosedNoteID, curveFor6[0], curveFor6[1] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHClosed 2 Bleed", HHClosedDestination + "HHClosed_2_bleed.wav", hhClosedNoteID, curveFor6[1], curveFor6[2] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHClosed 3 Bleed", HHClosedDestination + "HHClosed_3_bleed.wav", hhClosedNoteID, curveFor6[2], curveFor6[3] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHClosed 4 Bleed", HHClosedDestination + "HHClosed_4_bleed.wav", hhClosedNoteID, curveFor6[3], curveFor6[4] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHClosed 5 Bleed", HHClosedDestination + "HHClosed_5_bleed.wav", hhClosedNoteID, curveFor6[4], curveFor6[5] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHClosed 6 Bleed", HHClosedDestination + "HHClosed_6_bleed.wav", hhClosedNoteID, curveFor6[5], curveFor6[6] - 1, hhRelease, hhMaxLen, "HHBleed");

        string HHHalfDestination = HHAllDestination + "HHHalf/";
        addSample("HHHalf 1 Close", HHHalfDestination + "HHHalf_1_close.wav", hhHalfNoteID, curveFor4[0], curveFor4[1] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHHalf 2 Close", HHHalfDestination + "HHHalf_2_close.wav", hhHalfNoteID, curveFor4[1], curveFor4[2] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHHalf 3 Close", HHHalfDestination + "HHHalf_3_close.wav", hhHalfNoteID, curveFor4[2], curveFor4[3] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHHalf 4 Close", HHHalfDestination + "HHHalf_4_close.wav", hhHalfNoteID, curveFor4[3], curveFor4[4] - 1, hhRelease, hhMaxLen, "HHClose");
        addSample("HHHalf 1 OH", HHHalfDestination + "HHHalf_1_OH.wav", hhHalfNoteID, curveFor4[0], curveFor4[1] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHHalf 2 OH", HHHalfDestination + "HHHalf_2_OH.wav", hhHalfNoteID, curveFor4[1], curveFor4[2] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHHalf 3 OH", HHHalfDestination + "HHHalf_3_OH.wav", hhHalfNoteID, curveFor4[2], curveFor4[3] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHHalf 4 OH", HHHalfDestination + "HHHalf_4_OH.wav", hhHalfNoteID, curveFor4[3], curveFor4[4] - 1, hhRelease, hhMaxLen, "HHOH");
        addSample("HHHalf 1 Room", HHHalfDestination + "HHHalf_1_room.wav", hhHalfNoteID, curveFor4[0], curveFor4[1] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHHalf 2 Room", HHHalfDestination + "HHHalf_2_room.wav", hhHalfNoteID, curveFor4[1], curveFor4[2] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHHalf 3 Room", HHHalfDestination + "HHHalf_3_room.wav", hhHalfNoteID, curveFor4[2], curveFor4[3] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHHalf 4 Room", HHHalfDestination + "HHHalf_4_room.wav", hhHalfNoteID, curveFor4[3], curveFor4[4] - 1, hhRelease, hhMaxLen, "HHRoom");
        addSample("HHHalf 1 Bleed", HHHalfDestination + "HHHalf_1_bleed.wav", hhHalfNoteID, curveFor4[0], curveFor4[1] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHHalf 2 Bleed", HHHalfDestination + "HHHalf_2_bleed.wav", hhHalfNoteID, curveFor4[1], curveFor4[2] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHHalf 3 Bleed", HHHalfDestination + "HHHalf_3_bleed.wav", hhHalfNoteID, curveFor4[2], curveFor4[3] - 1, hhRelease, hhMaxLen, "HHBleed");
        addSample("HHHalf 4 Bleed", HHHalfDestination + "HHHalf_4_bleed.wav", hhHalfNoteID, curveFor4[3], curveFor4[4] - 1, hhRelease, hhMaxLen, "HHBleed");

        float hhOpenMaxLen = 5.0;
        string HHOpenDestination = HHAllDestination + "HHOpen/";
        addSample("HHOpen 1 Close", HHOpenDestination + "HHOpen_1_close.wav", hhOpenNoteID, curveFor5[0], curveFor5[1] - 1, hhRelease, hhOpenMaxLen, "HHClose");
        addSample("HHOpen 2 Close", HHOpenDestination + "HHOpen_2_close.wav", hhOpenNoteID, curveFor5[1], curveFor5[2] - 1, hhRelease, hhOpenMaxLen, "HHClose");
        addSample("HHOpen 3 Close", HHOpenDestination + "HHOpen_3_close.wav", hhOpenNoteID, curveFor5[2], curveFor5[3] - 1, hhRelease, hhOpenMaxLen, "HHClose");
        addSample("HHOpen 4 Close", HHOpenDestination + "HHOpen_4_close.wav", hhOpenNoteID, curveFor5[3], curveFor5[4] - 1, hhRelease, hhOpenMaxLen, "HHClose");
        addSample("HHOpen 5 Close", HHOpenDestination + "HHOpen_5_close.wav", hhOpenNoteID, curveFor5[4], curveFor5[5] - 1, hhRelease, hhOpenMaxLen, "HHClose");
        addSample("HHOpen 1 OH", HHOpenDestination + "HHOpen_1_OH.wav", hhOpenNoteID, curveFor5[0], curveFor5[1] - 1, hhRelease, hhOpenMaxLen, "HHOH");
        addSample("HHOpen 2 OH", HHOpenDestination + "HHOpen_2_OH.wav", hhOpenNoteID, curveFor5[1], curveFor5[2] - 1, hhRelease, hhOpenMaxLen, "HHOH");
        addSample("HHOpen 3 OH", HHOpenDestination + "HHOpen_3_OH.wav", hhOpenNoteID, curveFor5[2], curveFor5[3] - 1, hhRelease, hhOpenMaxLen, "HHOH");
        addSample("HHOpen 4 OH", HHOpenDestination + "HHOpen_4_OH.wav", hhOpenNoteID, curveFor5[3], curveFor5[4] - 1, hhRelease, hhOpenMaxLen, "HHOH");
        addSample("HHOpen 5 OH", HHOpenDestination + "HHOpen_5_OH.wav", hhOpenNoteID, curveFor5[4], curveFor5[5] - 1, hhRelease, hhOpenMaxLen, "HHOH");
        addSample("HHOpen 1 Room", HHOpenDestination + "HHOpen_1_room.wav", hhOpenNoteID, curveFor5[0], curveFor5[1] - 1, hhRelease, hhOpenMaxLen, "HHRoom");
        addSample("HHOpen 2 Room", HHOpenDestination + "HHOpen_2_room.wav", hhOpenNoteID, curveFor5[1], curveFor5[2] - 1, hhRelease, hhOpenMaxLen, "HHRoom");
        addSample("HHOpen 3 Room", HHOpenDestination + "HHOpen_3_room.wav", hhOpenNoteID, curveFor5[2], curveFor5[3] - 1, hhRelease, hhOpenMaxLen, "HHRoom");
        addSample("HHOpen 4 Room", HHOpenDestination + "HHOpen_4_room.wav", hhOpenNoteID, curveFor5[3], curveFor5[4] - 1, hhRelease, hhOpenMaxLen, "HHRoom");
        addSample("HHOpen 5 Room", HHOpenDestination + "HHOpen_5_room.wav", hhOpenNoteID, curveFor5[4], curveFor5[5] - 1, hhRelease, hhOpenMaxLen, "HHRoom");
        addSample("HHOpen 1 Bleed", HHOpenDestination + "HHOpen_1_bleed.wav", hhOpenNoteID, curveFor5[0], curveFor5[1] - 1, hhRelease, hhOpenMaxLen, "HHBleed");
        addSample("HHOpen 2 Bleed", HHOpenDestination + "HHOpen_2_bleed.wav", hhOpenNoteID, curveFor5[1], curveFor5[2] - 1, hhRelease, hhOpenMaxLen, "HHBleed");
        addSample("HHOpen 3 Bleed", HHOpenDestination + "HHOpen_3_bleed.wav", hhOpenNoteID, curveFor5[2], curveFor5[3] - 1, hhRelease, hhOpenMaxLen, "HHBleed");
        addSample("HHOpen 4 Bleed", HHOpenDestination + "HHOpen_4_bleed.wav", hhOpenNoteID, curveFor5[3], curveFor5[4] - 1, hhRelease, hhOpenMaxLen, "HHBleed");
        addSample("HHOpen 5 Bleed", HHOpenDestination + "HHOpen_5_bleed.wav", hhOpenNoteID, curveFor5[4], curveFor5[5] - 1, hhRelease, hhOpenMaxLen, "HHBleed");

        float RideRelease = 0.7;
        float RideMaxLen = 12.0;
        string RideAllDestination = dryDestination + "rideAll/";
        string RidePointDestination = RideAllDestination + "ridePoint/";
        addSample("RidePoint 1 Close", RidePointDestination + "ridePoint_1_bleed.wav", ridePointNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RidePoint 2 Close", RidePointDestination + "ridePoint_2_bleed.wav", ridePointNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RidePoint 3 Close", RidePointDestination + "ridePoint_3_bleed.wav", ridePointNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RidePoint 4 Close", RidePointDestination + "ridePoint_4_bleed.wav", ridePointNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RidePoint 5 Close", RidePointDestination + "ridePoint_5_bleed.wav", ridePointNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RidePoint 1 OH", RidePointDestination + "ridePoint_1_OH.wav", ridePointNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RidePoint 2 OH", RidePointDestination + "ridePoint_2_OH.wav", ridePointNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RidePoint 3 OH", RidePointDestination + "ridePoint_3_OH.wav", ridePointNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RidePoint 4 OH", RidePointDestination + "ridePoint_4_OH.wav", ridePointNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RidePoint 5 OH", RidePointDestination + "ridePoint_5_OH.wav", ridePointNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RidePoint 1 Room", RidePointDestination + "ridePoint_1_room.wav", ridePointNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RidePoint 2 Room", RidePointDestination + "ridePoint_2_room.wav", ridePointNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RidePoint 3 Room", RidePointDestination + "ridePoint_3_room.wav", ridePointNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RidePoint 4 Room", RidePointDestination + "ridePoint_4_room.wav", ridePointNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RidePoint 5 Room", RidePointDestination + "ridePoint_5_room.wav", ridePointNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RidePoint 1 Bleed", RidePointDestination + "ridePoint_1_bleed.wav", ridePointNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RidePoint 2 Bleed", RidePointDestination + "ridePoint_2_bleed.wav", ridePointNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RidePoint 3 Bleed", RidePointDestination + "ridePoint_3_bleed.wav", ridePointNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RidePoint 4 Bleed", RidePointDestination + "ridePoint_4_bleed.wav", ridePointNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RidePoint 5 Bleed", RidePointDestination + "ridePoint_5_bleed.wav", ridePointNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsBleed");

        string RideHalfDestination = RideAllDestination + "rideHalf/";
        addSample("RideHalf 1 Close", RideHalfDestination + "rideHalf_1_bleed.wav", rideHalfNoteID, curveFor3[0], curveFor3[1] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideHalf 2 Close", RideHalfDestination + "rideHalf_2_bleed.wav", rideHalfNoteID, curveFor3[1], curveFor3[2] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideHalf 3 Close", RideHalfDestination + "rideHalf_3_bleed.wav", rideHalfNoteID, curveFor3[2], curveFor3[3] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideHalf 1 OH", RideHalfDestination + "rideHalf_1_OH.wav", rideHalfNoteID, curveFor3[0], curveFor3[1] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideHalf 2 OH", RideHalfDestination + "rideHalf_2_OH.wav", rideHalfNoteID, curveFor3[1], curveFor3[2] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideHalf 3 OH", RideHalfDestination + "rideHalf_3_OH.wav", rideHalfNoteID, curveFor3[2], curveFor3[3] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideHalf 1 Room", RideHalfDestination + "rideHalf_1_room.wav", rideHalfNoteID, curveFor3[0], curveFor3[1] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideHalf 2 Room", RideHalfDestination + "rideHalf_2_room.wav", rideHalfNoteID, curveFor3[1], curveFor3[2] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideHalf 3 Room", RideHalfDestination + "rideHalf_3_room.wav", rideHalfNoteID, curveFor3[2], curveFor3[3] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideHalf 1 Bleed", RideHalfDestination + "rideHalf_1_bleed.wav", rideHalfNoteID, curveFor3[0], curveFor3[1] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideHalf 2 Bleed", RideHalfDestination + "rideHalf_2_bleed.wav", rideHalfNoteID, curveFor3[1], curveFor3[2] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideHalf 3 Bleed", RideHalfDestination + "rideHalf_3_bleed.wav", rideHalfNoteID, curveFor3[2], curveFor3[3] - 1, RideRelease, RideMaxLen, "CymbalsBleed");

        string RideBellDestination = RideAllDestination + "rideBell/";
        addSample("RideBell 1 Close", RideBellDestination + "rideBell_1_bleed.wav", rideBellNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideBell 2 Close", RideBellDestination + "rideBell_2_bleed.wav", rideBellNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideBell 3 Close", RideBellDestination + "rideBell_3_bleed.wav", rideBellNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideBell 4 Close", RideBellDestination + "rideBell_4_bleed.wav", rideBellNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideBell 5 Close", RideBellDestination + "rideBell_5_bleed.wav", rideBellNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "RideClose");
        addSample("RideBell 1 OH", RideBellDestination + "rideBell_1_OH.wav", rideBellNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideBell 2 OH", RideBellDestination + "rideBell_2_OH.wav", rideBellNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideBell 3 OH", RideBellDestination + "rideBell_3_OH.wav", rideBellNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideBell 4 OH", RideBellDestination + "rideBell_4_OH.wav", rideBellNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideBell 5 OH", RideBellDestination + "rideBell_5_OH.wav", rideBellNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsOH");
        addSample("RideBell 1 Room", RideBellDestination + "rideBell_1_room.wav", rideBellNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideBell 2 Room", RideBellDestination + "rideBell_2_room.wav", rideBellNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideBell 3 Room", RideBellDestination + "rideBell_3_room.wav", rideBellNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideBell 4 Room", RideBellDestination + "rideBell_4_room.wav", rideBellNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideBell 5 Room", RideBellDestination + "rideBell_5_room.wav", rideBellNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideBell 1 Bleed", RideBellDestination + "rideBell_1_bleed.wav", rideBellNoteID, curveFor5[0], curveFor5[1] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideBell 2 Bleed", RideBellDestination + "rideBell_2_bleed.wav", rideBellNoteID, curveFor5[1], curveFor5[2] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideBell 3 Bleed", RideBellDestination + "rideBell_3_bleed.wav", rideBellNoteID, curveFor5[2], curveFor5[3] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideBell 4 Bleed", RideBellDestination + "rideBell_4_bleed.wav", rideBellNoteID, curveFor5[3], curveFor5[4] - 1, RideRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideBell 5 Bleed", RideBellDestination + "rideBell_5_bleed.wav", rideBellNoteID, curveFor5[4], curveFor5[5] - 1, RideRelease, RideMaxLen, "CymbalsBleed");

        float RideOpenRelease = 4.5;
        string RideOpenDestination = RideAllDestination + "rideOpen/";
        addSample("RideOpen 1 Close", RideOpenDestination + "rideOpen_1_bleed.wav", rideOpenNoteID, curveFor5[0], curveFor5[1] - 1, RideOpenRelease, RideMaxLen, "RideClose");
        addSample("RideOpen 2 Close", RideOpenDestination + "rideOpen_2_bleed.wav", rideOpenNoteID, curveFor5[1], curveFor5[2] - 1, RideOpenRelease, RideMaxLen, "RideClose");
        addSample("RideOpen 3 Close", RideOpenDestination + "rideOpen_3_bleed.wav", rideOpenNoteID, curveFor5[2], curveFor5[3] - 1, RideOpenRelease, RideMaxLen, "RideClose");
        addSample("RideOpen 4 Close", RideOpenDestination + "rideOpen_4_bleed.wav", rideOpenNoteID, curveFor5[3], curveFor5[4] - 1, RideOpenRelease, RideMaxLen, "RideClose");
        addSample("RideOpen 5 Close", RideOpenDestination + "rideOpen_5_bleed.wav", rideOpenNoteID, curveFor5[4], curveFor5[5] - 1, RideOpenRelease, RideMaxLen, "RideClose");
        addSample("RideOpen 1 OH", RideOpenDestination + "rideOpen_1_OH.wav", rideOpenNoteID, curveFor5[0], curveFor5[1] - 1, RideOpenRelease, RideMaxLen, "CymbalsOH");
        addSample("RideOpen 2 OH", RideOpenDestination + "rideOpen_2_OH.wav", rideOpenNoteID, curveFor5[1], curveFor5[2] - 1, RideOpenRelease, RideMaxLen, "CymbalsOH");
        addSample("RideOpen 3 OH", RideOpenDestination + "rideOpen_3_OH.wav", rideOpenNoteID, curveFor5[2], curveFor5[3] - 1, RideOpenRelease, RideMaxLen, "CymbalsOH");
        addSample("RideOpen 4 OH", RideOpenDestination + "rideOpen_4_OH.wav", rideOpenNoteID, curveFor5[3], curveFor5[4] - 1, RideOpenRelease, RideMaxLen, "CymbalsOH");
        addSample("RideOpen 5 OH", RideOpenDestination + "rideOpen_5_OH.wav", rideOpenNoteID, curveFor5[4], curveFor5[5] - 1, RideOpenRelease, RideMaxLen, "CymbalsOH");
        addSample("RideOpen 1 Room", RideOpenDestination + "rideOpen_1_room.wav", rideOpenNoteID, curveFor5[0], curveFor5[1] - 1, RideOpenRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideOpen 2 Room", RideOpenDestination + "rideOpen_2_room.wav", rideOpenNoteID, curveFor5[1], curveFor5[2] - 1, RideOpenRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideOpen 3 Room", RideOpenDestination + "rideOpen_3_room.wav", rideOpenNoteID, curveFor5[2], curveFor5[3] - 1, RideOpenRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideOpen 4 Room", RideOpenDestination + "rideOpen_4_room.wav", rideOpenNoteID, curveFor5[3], curveFor5[4] - 1, RideOpenRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideOpen 5 Room", RideOpenDestination + "rideOpen_5_room.wav", rideOpenNoteID, curveFor5[4], curveFor5[5] - 1, RideOpenRelease, RideMaxLen, "CymbalsRoom");
        addSample("RideOpen 1 Bleed", RideOpenDestination + "rideOpen_1_bleed.wav", rideOpenNoteID, curveFor5[0], curveFor5[1] - 1, RideOpenRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideOpen 2 Bleed", RideOpenDestination + "rideOpen_2_bleed.wav", rideOpenNoteID, curveFor5[1], curveFor5[2] - 1, RideOpenRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideOpen 3 Bleed", RideOpenDestination + "rideOpen_3_bleed.wav", rideOpenNoteID, curveFor5[2], curveFor5[3] - 1, RideOpenRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideOpen 4 Bleed", RideOpenDestination + "rideOpen_4_bleed.wav", rideOpenNoteID, curveFor5[3], curveFor5[4] - 1, RideOpenRelease, RideMaxLen, "CymbalsBleed");
        addSample("RideOpen 5 Bleed", RideOpenDestination + "rideOpen_5_bleed.wav", rideOpenNoteID, curveFor5[4], curveFor5[5] - 1, RideOpenRelease, RideMaxLen, "CymbalsBleed");


        float CrashRelease = 0.12;
        float CrashMaxLen = 6.0;
        string CrashAllDestination = dryDestination + "crashAll/";


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
