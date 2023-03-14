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
    for (auto i = 0; i < 30; i++)    // i < x+1 defines how many sounds can play at the same time
    {
        sampler.addVoice(new juce::SamplerVoice());
        samplerOH.addVoice(new juce::SamplerVoice());
        samplerRoom.addVoice(new juce::SamplerVoice());
        samplerBleed.addVoice(new juce::SamplerVoice());
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
    params.push_back(std::move(gainParam));
    auto OHgainParam = std::make_unique<juce::AudioParameterFloat>(OH_GAIN_ID, OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(OHgainParam));
    auto RoomGainParam = std::make_unique<juce::AudioParameterFloat>(ROOM_GAIN_ID, ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(RoomGainParam));
    auto BleedGainParam = std::make_unique<juce::AudioParameterFloat>(BLEED_GAIN_ID, BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(BleedGainParam));

    auto KickCloseGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_CLOSE_GAIN_ID, KICK_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(KickCloseGainParam));
    auto KickOHGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_OH_GAIN_ID, KICK_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(KickOHGainParam));
    auto KickRoomGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_ROOM_GAIN_ID, KICK_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(KickRoomGainParam));
    auto KickBleedGainParam = std::make_unique<juce::AudioParameterFloat>(KICK_BLEED_GAIN_ID, KICK_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(KickBleedGainParam));

    auto SnareTopCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_TOP_CLOSE_GAIN_ID, SNARE_TOP_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareTopCloseGainParam));
    auto SnareBotCloseGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BOT_CLOSE_GAIN_ID, SNARE_BOT_CLOSE_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareBotCloseGainParam));
    auto SnareOHGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_OH_GAIN_ID, SNARE_OH_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareOHGainParam));
    auto SnareRoomGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_ROOM_GAIN_ID, SNARE_ROOM_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareRoomGainParam));
    auto SnareBleedGainParam = std::make_unique<juce::AudioParameterFloat>(SNARE_BLEED_GAIN_ID, SNARE_BLEED_GAIN_NAME, -48.0f, 10.0f, 0.0f);
    params.push_back(std::move(SnareBleedGainParam));

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

    auto curve = linCurve;
    if (curveMenuID == 1) {
        curve = linCurve;
    }
    else if (curveMenuID == 2) {
        curve = logCurve;
    }

    if (samplePackID == 1) {
        clearSoundsFromAllSamplers();
        float snareRelease = 0.5;
        float snareMaxLen = 2.0;

        string destinationP = destinationAll + "Perkusja/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        addSample("Ride Hard", destinationP + "Ride Hard.wav", 65, curve[0], 127, 5.0, 8.0, "Close");
        addSample("Ride Smooth", destinationP + "Ride Smooth.wav", 65, 1, curve[0] - 1, 0.5, 8.0, "Close");
        string GGDdestination = destinationP + "GGD/";
        addSample("HH open", GGDdestination + "HH open.wav", 64, 1, 127, 0.12, 6.5, "Close");
        addSample("HH closed", GGDdestination + "HH closed.wav", 62, 1, 127, 0.1, 2.0, "Close");

        string snareDestination = destinationP + "Konrad1/Snare/";
        addSample("Snare 1_1", snareDestination + "Snare 1_1.wav", snareNoteID, curve[4], 127, snareRelease, snareMaxLen, "Close");
        addSample("Snare 2_1", snareDestination + "Snare 2_1.wav", snareNoteID, curve[3], curve[4] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 3_1", snareDestination + "Snare 3_1.wav", snareNoteID, curve[2], curve[3] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 4_1", snareDestination + "Snare 4_1.wav", snareNoteID, curve[1], curve[2] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 5_1", snareDestination + "Snare 5_1.wav", snareNoteID, curve[0], curve[1] - 1, snareRelease, snareMaxLen, "Close");
        addSample("Snare 6_1", snareDestination + "Snare 6_1.wav", snareNoteID, 1, curve[0] - 1, snareRelease, snareMaxLen, "Close");
        string kickDestination = destinationP + "Konrad1/Kick/";
        addSample("Kick 0_1", kickDestination + "Kick 0_1.wav", kickNoteID, 126, 127, 0.6, 2.0, "Close");
        addSample("Kick 1_1", kickDestination + "Kick 1_1.wav", kickNoteID, 114, 125, 0.6, 2.0, "Close");
        addSample("Kick 2_1", kickDestination + "Kick 2_1.wav", kickNoteID, 100, 113, 0.6, 2.0, "Close");
        addSample("Kick 3_1", kickDestination + "Kick 3_1.wav", kickNoteID, 85, 99, 0.6, 2.0, "Close");
        addSample("Kick 4_1", kickDestination + "Kick 4_1.wav", kickNoteID, 75, 84, 0.6, 2.0, "Close");
        addSample("Kick 5_1", kickDestination + "Kick 5_1.wav", kickNoteID, 66, 74, 0.6, 2.0, "Close");
        addSample("Kick 6_1", kickDestination + "Kick 6_1.wav", kickNoteID, curve[0], curve[1] - 1, 0.6, 2.0, "Close");
        addSample("Kick 7_1", kickDestination + "Kick 7_1.wav", kickNoteID, 1, curve[0] - 1, 0.6, 2.0, "Close");
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
        float snareRelease = 0.5;
        float snareMaxLen = 2.0;

        string dryDestination = destinationAll + "drySamples/";
        // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
        string snareAllDestination = dryDestination + "snareAll/";
        string snareDestination = snareAllDestination + "snare/";
        addSample("Snare 6 Top", snareDestination + "snare_6_top.wav", snareNoteID, 1, 127, snareRelease, snareMaxLen, "Close");
        addSample("Snare 6 Bot", snareDestination + "snare_6_bot.wav", snareNoteID, 1, 127, snareRelease, snareMaxLen, "Close");
        addSample("Snare 6 OH", snareDestination + "snare_6_OH.wav", snareNoteID, 1, 127, snareRelease, snareMaxLen, "OH");
        addSample("Snare 6 room", snareDestination + "snare_6_room.wav", snareNoteID, 1, 127, snareRelease, snareMaxLen, "Room");
        addSample("Snare 6 bleed", snareDestination + "snare_6_bleed.wav", snareNoteID, 1, 127, snareRelease, snareMaxLen, "Bleed");
    }
}

void HDrumsAudioProcessor::clearSoundsFromAllSamplers()
{
    sampler.clearSounds();
    samplerOH.clearSounds();
    samplerRoom.clearSounds();
    samplerBleed.clearSounds();
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
    sampler.setCurrentPlaybackSampleRate(sampleRate);
    samplerOH.setCurrentPlaybackSampleRate(sampleRate);
    samplerRoom.setCurrentPlaybackSampleRate(sampleRate);
    samplerBleed.setCurrentPlaybackSampleRate(sampleRate);
    midiMessageCollector.reset(sampleRate);
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

    auto snareTopCloseSliderValue = treeState.getRawParameterValue(SNARE_TOP_CLOSE_GAIN_ID);
    auto snareBotCloseSliderValue = treeState.getRawParameterValue(SNARE_BOT_CLOSE_GAIN_ID);
    auto snareOHSliderValue = treeState.getRawParameterValue(SNARE_OH_GAIN_ID);
    auto snareRoomSliderValue = treeState.getRawParameterValue(SNARE_ROOM_GAIN_ID);
    auto snareBleedSliderValue = treeState.getRawParameterValue(SNARE_BLEED_GAIN_ID);

    juce::AudioBuffer<float> bufferClose;
    juce::AudioBuffer<float> bufferOH;
    juce::AudioBuffer<float> bufferRoom;
    juce::AudioBuffer<float> bufferBleed;
    bufferClose.makeCopyOf(buffer);
    bufferOH.makeCopyOf(buffer);
    bufferRoom.makeCopyOf(buffer);
    bufferBleed.makeCopyOf(buffer);

    sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    buffer.applyGain(juce::Decibels::decibelsToGain<float>(*sliderValue));
    buffer.applyGain(juce::Decibels::decibelsToGain<float>(*kickCloseSliderValue));

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
    juce::MemoryOutputStream(destData, true).writeFloat(*sliderValue);
    auto OHsliderValue = treeState.getRawParameterValue(OH_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*OHsliderValue);
    auto RoomSliderValue = treeState.getRawParameterValue(ROOM_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*RoomSliderValue);
    auto BleedSliderValue = treeState.getRawParameterValue(BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*BleedSliderValue);

    auto kickCloseSliderValue = treeState.getRawParameterValue(KICK_CLOSE_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickCloseSliderValue);
    auto kickOHSliderValue = treeState.getRawParameterValue(KICK_OH_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickOHSliderValue);
    auto kickRoomSliderValue = treeState.getRawParameterValue(KICK_ROOM_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickRoomSliderValue);
    auto kickBleedSliderValue = treeState.getRawParameterValue(KICK_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*kickBleedSliderValue);

    auto snareTopCloseSliderValue = treeState.getRawParameterValue(SNARE_TOP_CLOSE_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareTopCloseSliderValue);
    auto snareBotCloseSliderValue = treeState.getRawParameterValue(SNARE_BOT_CLOSE_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBotCloseSliderValue);
    auto snareOHSliderValue = treeState.getRawParameterValue(SNARE_OH_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareOHSliderValue);
    auto snareRoomSliderValue = treeState.getRawParameterValue(SNARE_ROOM_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareRoomSliderValue);
    auto snareBleedSliderValue = treeState.getRawParameterValue(SNARE_BLEED_GAIN_ID);
    juce::MemoryOutputStream(destData, true).writeFloat(*snareBleedSliderValue);
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

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HDrumsAudioProcessor();
}
