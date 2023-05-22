#pragma once
#include "SamplerSoundLayer.h"
using namespace std;

class LoadingSamples
{
public:
    int samplePack = 1;
    bool missingSample = false;

    void addSample(string sampleName, string destination,
        int midiNote, float lowestVelocity, float highestVelocity, double release, double maxLength,
        string bus, std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        juce::File file(destination);
        unique_ptr<juce::AudioFormatReader>audioReader(formatManager.createReaderFor(file));
        if (audioReader != nullptr) {
            juce::BigInteger midiNotes;
            midiNotes.setRange(midiNote, 1, true);
            juce::Range<float> velocities(1.f / 127 * lowestVelocity, 1.f / 127 * highestVelocity);

            if (bus == "Close")
                samplers[0]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "OH")
                samplers[1]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "Room")
                samplers[2]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "Bleed")
                samplers[3]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

            else if (bus == "KickClose")
                samplers[4]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "KickOH")
                samplers[5]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "KickRoom")
                samplers[6]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "KickBleed")
                samplers[7]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

            else if (bus == "SnareTop")
                samplers[8]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "SnareBot")
                samplers[9]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "SnareOH")
                samplers[10]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "SnareRoom")
                samplers[11]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "SnareBleed")
                samplers[12]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

            else if (bus == "TomClose")
                samplers[13]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "FTomClose")
                samplers[14]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "TomsOH")
                samplers[15]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "TomsRoom")
                samplers[16]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "TomsBleed")
                samplers[17]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

            else if (bus == "HHClose")
                samplers[18]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "CymbalsOH")
                samplers[19]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "CymbalsRoom")
                samplers[20]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
            else if (bus == "CymbalsBleed")
                samplers[21]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

            else if (bus == "Binaural")
                samplers[22]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        }
        else
        {
            missingSample = true;
        }
    }


    
    void addSample2(string sampleName, const void* sourceData, size_t sourceDataSize,
                    int midiNote, float lowestVelocity, float highestVelocity, double release, double maxLength,
                    string bus, std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        auto input = new juce::MemoryInputStream(sourceData, sourceDataSize, false);
        unique_ptr<juce::AudioFormatReader>audioReader(formatManager.createReaderFor(std::unique_ptr<juce::InputStream>(input)));
        juce::BigInteger midiNotes;
        midiNotes.setRange(midiNote, 1, true);
        juce::Range<float> velocities(1.f / 127 * lowestVelocity, 1.f / 127 * highestVelocity);

        if (bus == "Close")
            samplers[0]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "OH")
            samplers[1]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "Room")
            samplers[2]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "Bleed")
            samplers[3]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "KickClose")
            samplers[4]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickOH")
            samplers[5]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickRoom")
            samplers[6]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "KickBleed")
            samplers[7]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "SnareTop")
            samplers[8]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareBot")
            samplers[9]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareOH")
            samplers[10]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareRoom")
            samplers[11]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "SnareBleed")
            samplers[12]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "TomClose")
            samplers[13]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "FTomClose")
            samplers[14]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsOH")
            samplers[15]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsRoom")
            samplers[16]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "TomsBleed")
            samplers[17]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));

        else if (bus == "HHClose")
            samplers[18]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsOH")
            samplers[19]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsRoom")
            samplers[20]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        else if (bus == "CymbalsBleed")
            samplers[21]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
        
        else if (bus == "Binaural")
            samplers[22]->addSound(new SamplerSoundLayer(sampleName, *audioReader, midiNotes, midiNote, velocities, 0.01, release, maxLength));
    }


    void loadElectronicSamples(std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        addSample2("Electronic Kick Close", BinaryData::e_kick_close_wav, BinaryData::e_kick_close_wavSize, defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickClose", samplers, formatManager);
        addSample2("Electronic Kick OH", BinaryData::e_kick_OH_wav, BinaryData::e_kick_OH_wavSize, defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickOH", samplers, formatManager);
        addSample2("Electronic Kick Room", BinaryData::e_kick_room_wav, BinaryData::e_kick_room_wavSize, defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickRoom", samplers, formatManager);
        addSample2("Electronic Kick Bleed", BinaryData::e_kick_bleed_wav, BinaryData::e_kick_bleed_wavSize, defaultMidiNotes[0], 1, 127, 0.5, 1.0, "KickBleed", samplers, formatManager);

        addSample2("Electronic Snare Close", BinaryData::e_snare_close_wav, BinaryData::e_snare_close_wavSize, defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareTop", samplers, formatManager);
        addSample2("Electronic Snare OH", BinaryData::e_snare_OH_wav, BinaryData::e_snare_OH_wavSize, defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareOH", samplers, formatManager);
        addSample2("Electronic Snare Room", BinaryData::e_snare_room_wav, BinaryData::e_snare_room_wavSize, defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareRoom", samplers, formatManager);
        addSample2("Electronic Snare Bleed", BinaryData::e_snare_bleed_wav, BinaryData::e_snare_bleed_wavSize, defaultMidiNotes[1], 1, 127, 0.5, 1.0, "SnareBleed", samplers, formatManager);

        addSample2("Electronic Tom Close", BinaryData::e_tom_close_wav, BinaryData::e_tom_close_wavSize, defaultMidiNotes[9], 1, 127, 0.5, 1.0, "TomClose", samplers, formatManager);
        addSample2("Electronic Tom OH", BinaryData::e_tom_OH_wav, BinaryData::e_tom_OH_wavSize, defaultMidiNotes[9], 1, 127, 0.5, 1.0, "TomsOH", samplers, formatManager);
        addSample2("Electronic Tom Room", BinaryData::e_tom_room_wav, BinaryData::e_tom_room_wavSize, defaultMidiNotes[9], 1, 127, 0.5, 1.0, "TomsRoom", samplers, formatManager);
        addSample2("Electronic Tom Bleed", BinaryData::e_tom_bleed_wav, BinaryData::e_tom_bleed_wavSize, defaultMidiNotes[9], 1, 127, 0.5, 1.0, "TomsBleed", samplers, formatManager);

        addSample2("Electronic FTom Close", BinaryData::e_ftom_close_wav, BinaryData::e_ftom_close_wavSize, defaultMidiNotes[11], 1, 127, 0.5, 1.0, "FTomClose", samplers, formatManager);
        addSample2("Electronic FTom OH", BinaryData::e_ftom_OH_wav, BinaryData::e_ftom_OH_wavSize, defaultMidiNotes[11], 1, 127, 0.5, 1.0, "TomsOH", samplers, formatManager);
        addSample2("Electronic FTom Room", BinaryData::e_ftom_room_wav, BinaryData::e_ftom_room_wavSize, defaultMidiNotes[11], 1, 127, 0.5, 1.0, "TomsRoom", samplers, formatManager);
        addSample2("Electronic FTom Bleed", BinaryData::e_ftom_bleed_wav, BinaryData::e_ftom_bleed_wavSize, defaultMidiNotes[11], 1, 127, 0.5, 1.0, "TomsBleed", samplers, formatManager);

        addSample2("Electronic HH Closed Close", BinaryData::e_hhClosed_close_wav, BinaryData::e_hhClosed_close_wavSize, defaultMidiNotes[14], 1, 127, 0.5, 1.0, "HHClose", samplers, formatManager);
        addSample2("Electronic HH Closed OH", BinaryData::e_hhClosed_OH_wav, BinaryData::e_hhClosed_OH_wavSize, defaultMidiNotes[14], 1, 127, 0.5, 1.0, "CymbalsOH", samplers, formatManager);
        addSample2("Electronic HH Closed Room", BinaryData::e_hhClosed_room_wav, BinaryData::e_hhClosed_room_wavSize, defaultMidiNotes[14], 1, 127, 0.5, 1.0, "CymbalsRoom", samplers, formatManager);
        addSample2("Electronic HH Closed Bleed", BinaryData::e_hhClosed_bleed_wav, BinaryData::e_hhClosed_bleed_wavSize, defaultMidiNotes[14], 1, 127, 0.5, 1.0, "CymbalsBleed", samplers, formatManager);
        addSample2("Electronic HH Open Close", BinaryData::e_hhOpen_close_wav, BinaryData::e_hhOpen_close_wavSize, defaultMidiNotes[16], 1, 127, 0.5, 1.0, "HHClose", samplers, formatManager);
        addSample2("Electronic HH Open OH", BinaryData::e_hhOpen_OH_wav, BinaryData::e_hhOpen_OH_wavSize, defaultMidiNotes[16], 1, 127, 0.5, 1.0, "CymbalsOH", samplers, formatManager);
        addSample2("Electronic HH Open Room", BinaryData::e_hhOpen_room_wav, BinaryData::e_hhOpen_room_wavSize, defaultMidiNotes[16], 1, 127, 0.5, 1.0, "CymbalsRoom", samplers, formatManager);
        addSample2("Electronic HH Open Bleed", BinaryData::e_hhOpen_bleed_wav, BinaryData::e_hhOpen_bleed_wavSize, defaultMidiNotes[16], 1, 127, 0.5, 1.0, "CymbalsBleed", samplers, formatManager);

        addSample2("Electronic Ride OH", BinaryData::e_ride_OH_wav, BinaryData::e_ride_OH_wavSize, defaultMidiNotes[18], 1, 127, 0.8, 2.4, "CymbalsOH", samplers, formatManager);
        addSample2("Electronic Ride Room", BinaryData::e_ride_room_wav, BinaryData::e_ride_room_wavSize, defaultMidiNotes[18], 1, 127, 0.8, 2.4, "CymbalsRoom", samplers, formatManager);
        addSample2("Electronic Ride Bleed", BinaryData::e_ride_bleed_wav, BinaryData::e_ride_bleed_wavSize, defaultMidiNotes[18], 1, 127, 0.8, 2.4, "CymbalsBleed", samplers, formatManager);

        addSample2("Electronic Crash OH", BinaryData::e_crash_OH_wav, BinaryData::e_crash_OH_wavSize, defaultMidiNotes[23], 1, 127, 0.8, 2.4, "CymbalsOH", samplers, formatManager);
        addSample2("Electronic Crash Room", BinaryData::e_crash_room_wav, BinaryData::e_crash_room_wavSize, defaultMidiNotes[23], 1, 127, 0.8, 2.4, "CymbalsRoom", samplers, formatManager);
        addSample2("Electronic Crash Bleed", BinaryData::e_crash_bleed_wav, BinaryData::e_crash_bleed_wavSize, defaultMidiNotes[23], 1, 127, 0.8, 2.4, "CymbalsBleed", samplers, formatManager);
    }

    void loadEssentialSamples(int samplePack, std::vector<Sampler*> samplers, juce::AudioFormatManager& formatManager)
    {
        for (int i = 0; i < samplers.size(); i++)
            samplers[i]->clearSounds();

        if (samplePack == 2)
        {
            double kickRelease = 0.6;
            double kickMaxLen = 1.4;
            addSample2("Acoustic Kick 5 Close", BinaryData::a_kick_5_close_wav, BinaryData::a_kick_5_close_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample2("Acoustic Kick 5 OH", BinaryData::a_kick_5_oh_wav, BinaryData::a_kick_5_oh_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample2("Acoustic Kick 5 Room", BinaryData::a_kick_5_room_wav, BinaryData::a_kick_5_room_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample2("Acoustic Kick 5 Bleed", BinaryData::a_kick_5_bleed_wav, BinaryData::a_kick_5_bleed_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample2("Acoustic Kick 5 Binaural", BinaryData::a_kick_5_binaural_wav, BinaryData::a_kick_5_binaural_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);

            double snareRelease = 0.5;
            double snareMaxLen = 1.6;
            addSample2("Acoustic Snare 6 Top", BinaryData::a_snare_6_top_wav, BinaryData::a_snare_6_top_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare 6 Bot", BinaryData::a_snare_6_bot_wav, BinaryData::a_snare_6_bot_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare 6 OH", BinaryData::a_snare_6_oh_wav, BinaryData::a_snare_6_oh_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare 6 Room", BinaryData::a_snare_6_room_wav, BinaryData::a_snare_6_room_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare 6 Bleed", BinaryData::a_snare_6_bleed_wav, BinaryData::a_snare_6_bleed_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare 6 Binaural", BinaryData::a_snare_6_binaural_wav, BinaryData::a_snare_6_binaural_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Swirl 3 Top", BinaryData::a_snareSwirl_3_top_wav, BinaryData::a_snareSwirl_3_top_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Swirl 3 Bot", BinaryData::a_snareSwirl_3_bot_wav, BinaryData::a_snareSwirl_3_bot_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare Swirl 3 OH", BinaryData::a_snareSwirl_3_oh_wav, BinaryData::a_snareSwirl_3_oh_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Swirl 3 Room", BinaryData::a_snareSwirl_3_room_wav, BinaryData::a_snareSwirl_3_room_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Swirl 3 Bleed", BinaryData::a_snareSwirl_3_bleed_wav, BinaryData::a_snareSwirl_3_bleed_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Swirl 3 Binaural", BinaryData::a_snareSwirl_3_binaural_wav, BinaryData::a_snareSwirl_3_binaural_wavSize, defaultMidiNotes[2], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Flam 6 Top", BinaryData::a_snareFlam_6_top_wav, BinaryData::a_snareFlam_6_top_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Flam 6 Bot", BinaryData::a_snareFlam_6_bot_wav, BinaryData::a_snareFlam_6_bot_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare Flam 6 OH", BinaryData::a_snareFlam_6_oh_wav, BinaryData::a_snareFlam_6_oh_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Flam 6 Room", BinaryData::a_snareFlam_6_room_wav, BinaryData::a_snareFlam_6_room_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Flam 6 Bleed", BinaryData::a_snareFlam_6_bleed_wav, BinaryData::a_snareFlam_6_bleed_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Flam 6 Binaural", BinaryData::a_snareFlam_6_binaural_wav, BinaryData::a_snareFlam_6_binaural_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Round 4 Top", BinaryData::a_snareRound_4_top_wav, BinaryData::a_snareRound_4_top_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Round 4 Bot", BinaryData::a_snareRound_4_bot_wav, BinaryData::a_snareRound_4_bot_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare Round 4 OH", BinaryData::a_snareRound_4_oh_wav, BinaryData::a_snareRound_4_oh_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Round 4 Room", BinaryData::a_snareRound_4_room_wav, BinaryData::a_snareRound_4_room_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Round 4 Bleed", BinaryData::a_snareRound_4_bleed_wav, BinaryData::a_snareRound_4_bleed_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Round 4 Binaural", BinaryData::a_snareRound_4_binaural_wav, BinaryData::a_snareRound_4_binaural_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Wireless 4 Top", BinaryData::a_snareWireless_4_top_wav, BinaryData::a_snareWireless_4_top_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Wireless 4 Bot", BinaryData::a_snareWireless_4_bot_wav, BinaryData::a_snareWireless_4_bot_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare Wireless 4 OH", BinaryData::a_snareWireless_4_oh_wav, BinaryData::a_snareWireless_4_oh_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Wireless 4 Room", BinaryData::a_snareWireless_4_room_wav, BinaryData::a_snareWireless_4_room_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Wireless 4 Bleed", BinaryData::a_snareWireless_4_bleed_wav, BinaryData::a_snareWireless_4_bleed_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Wireless 4 Binaural", BinaryData::a_snareWireless_4_binaural_wav, BinaryData::a_snareWireless_4_binaural_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Wireless Round 4 Top", BinaryData::a_snareWirelessRound_4_top_wav, BinaryData::a_snareWirelessRound_4_top_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Wireless Round 4 Bot", BinaryData::a_snareWirelessRound_4_bot_wav, BinaryData::a_snareWirelessRound_4_bot_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Acoustic Snare Wireless Round 4 OH", BinaryData::a_snareWirelessRound_4_oh_wav, BinaryData::a_snareWirelessRound_4_oh_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Wireless Round 4 Room", BinaryData::a_snareWirelessRound_4_room_wav, BinaryData::a_snareWirelessRound_4_room_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Wireless Round 4 Bleed", BinaryData::a_snareWirelessRound_4_bleed_wav, BinaryData::a_snareWirelessRound_4_bleed_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Wireless Round 4 Binaural", BinaryData::a_snareWirelessRound_4_binaural_wav, BinaryData::a_snareWirelessRound_4_binaural_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Piccolo 4 Close", BinaryData::a_snarePiccolo_4_close_wav, BinaryData::a_snarePiccolo_4_close_wavSize, defaultMidiNotes[7], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo 4 OH", BinaryData::a_snarePiccolo_4_oh_wav, BinaryData::a_snarePiccolo_4_oh_wavSize, defaultMidiNotes[7], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo 4 Room", BinaryData::a_snarePiccolo_4_room_wav, BinaryData::a_snarePiccolo_4_room_wavSize, defaultMidiNotes[7], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo 4 Bleed", BinaryData::a_snarePiccolo_4_bleed_wav, BinaryData::a_snarePiccolo_4_bleed_wavSize, defaultMidiNotes[7], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo 4 Binaural", BinaryData::a_snarePiccolo_4_binaural_wav, BinaryData::a_snarePiccolo_4_binaural_wavSize, defaultMidiNotes[7], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Snare Piccolo Swirl 2 Close", BinaryData::a_snarePiccoloSwirl_2_close_wav, BinaryData::a_snarePiccoloSwirl_2_close_wavSize, defaultMidiNotes[8], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo Swirl 2 OH", BinaryData::a_snarePiccoloSwirl_2_oh_wav, BinaryData::a_snarePiccoloSwirl_2_oh_wavSize, defaultMidiNotes[8], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo Swirl 2 Room", BinaryData::a_snarePiccoloSwirl_2_room_wav, BinaryData::a_snarePiccoloSwirl_2_room_wavSize, defaultMidiNotes[8], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo Swirl 2 Bleed", BinaryData::a_snarePiccoloSwirl_2_bleed_wav, BinaryData::a_snarePiccoloSwirl_2_bleed_wavSize, defaultMidiNotes[8], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample2("Acoustic Snare Piccolo Swirl 2 Binaural", BinaryData::a_snarePiccoloSwirl_2_binaural_wav, BinaryData::a_snarePiccoloSwirl_2_binaural_wavSize, defaultMidiNotes[8], 1, 127, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            double tomRelease = 0.6;
            double tomMaxLen = 2.4;
            addSample2("Acoustic Tom 4 Close", BinaryData::a_tom_4_close_wav, BinaryData::a_tom_4_close_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample2("Acoustic Tom 4 OH", BinaryData::a_tom_4_oh_wav, BinaryData::a_tom_4_oh_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Acoustic Tom 4 Room", BinaryData::a_tom_4_room_wav, BinaryData::a_tom_4_room_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Acoustic Tom 4 Bleed", BinaryData::a_tom_4_bleed_wav, BinaryData::a_tom_4_bleed_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample2("Acoustic Tom 4 Binaural", BinaryData::a_tom_4_binaural_wav, BinaryData::a_tom_4_binaural_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Tom Flam 4 Close", BinaryData::a_tomFlam_4_close_wav, BinaryData::a_tomFlam_4_close_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample2("Acoustic Tom Flam 4 OH", BinaryData::a_tomFlam_4_oh_wav, BinaryData::a_tomFlam_4_oh_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Acoustic Tom Flam 4 Room", BinaryData::a_tomFlam_4_room_wav, BinaryData::a_tomFlam_4_room_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Acoustic Tom Flam 4 Bleed", BinaryData::a_tomFlam_4_bleed_wav, BinaryData::a_tomFlam_4_bleed_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample2("Acoustic Tom Flam 4 Binaural", BinaryData::a_tomFlam_4_binaural_wav, BinaryData::a_tomFlam_4_binaural_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            double ftomRelease = 0.7;
            addSample2("Acoustic FTom 4 Close", BinaryData::a_ftom_4_close_wav, BinaryData::a_ftom_4_close_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample2("Acoustic FTom 4 OH", BinaryData::a_ftom_4_oh_wav, BinaryData::a_ftom_4_oh_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Acoustic FTom 4 Room", BinaryData::a_ftom_4_room_wav, BinaryData::a_ftom_4_room_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Acoustic FTom 4 Bleed", BinaryData::a_ftom_4_bleed_wav, BinaryData::a_ftom_4_bleed_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample2("Acoustic FTom 4 Binaural", BinaryData::a_ftom_4_binaural_wav, BinaryData::a_ftom_4_binaural_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic FTom Flam 4 Close", BinaryData::a_ftomFlam_4_close_wav, BinaryData::a_ftomFlam_4_close_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample2("Acoustic FTom Flam 4 OH", BinaryData::a_ftomFlam_4_oh_wav, BinaryData::a_ftomFlam_4_oh_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Acoustic FTom Flam 4 Room", BinaryData::a_ftomFlam_4_room_wav, BinaryData::a_ftomFlam_4_room_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Acoustic FTom Flam 4 Bleed", BinaryData::a_ftomFlam_4_bleed_wav, BinaryData::a_ftomFlam_4_bleed_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample2("Acoustic FTom Flam 4 Binaural", BinaryData::a_ftomFlam_4_binaural_wav, BinaryData::a_ftomFlam_4_binaural_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            double hhRelease = 0.12;
            double hhClosedMaxLen = 0.5;
            addSample2("Acoustic HH Stomp 2 Close", BinaryData::a_hhStomp_2_close_wav, BinaryData::a_hhStomp_2_close_wavSize, defaultMidiNotes[13], 1, 127, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample2("Acoustic HH Stomp 2 OH", BinaryData::a_hhStomp_2_oh_wav, BinaryData::a_hhStomp_2_oh_wavSize, defaultMidiNotes[13], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic HH Stomp 2 Room", BinaryData::a_hhStomp_2_room_wav, BinaryData::a_hhStomp_2_room_wavSize, defaultMidiNotes[13], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic HH Stomp 2 Bleed", BinaryData::a_hhStomp_2_bleed_wav, BinaryData::a_hhStomp_2_bleed_wavSize, defaultMidiNotes[13], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic HH Stomp 2 Binaural", BinaryData::a_hhStomp_2_binaural_wav, BinaryData::a_hhStomp_2_binaural_wavSize, defaultMidiNotes[13], 1, 127, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic HH Closed 6 Close", BinaryData::a_hhClosed_6_close_wav, BinaryData::a_hhClosed_6_close_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample2("Acoustic HH Closed 6 OH", BinaryData::a_hhClosed_6_oh_wav, BinaryData::a_hhClosed_6_oh_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic HH Closed 6 Room", BinaryData::a_hhClosed_6_room_wav, BinaryData::a_hhClosed_6_room_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic HH Closed 6 Bleed", BinaryData::a_hhClosed_6_bleed_wav, BinaryData::a_hhClosed_6_bleed_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic HH Closed 6 Binaural", BinaryData::a_hhClosed_6_binaural_wav, BinaryData::a_hhClosed_6_binaural_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic HH Half 5 Close", BinaryData::a_hhHalf_5_close_wav, BinaryData::a_hhHalf_5_close_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "HHClose", samplers, formatManager);
            addSample2("Acoustic HH Half 5 OH", BinaryData::a_hhHalf_5_oh_wav, BinaryData::a_hhHalf_5_oh_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic HH Half 5 Room", BinaryData::a_hhHalf_5_room_wav, BinaryData::a_hhHalf_5_room_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic HH Half 5 Bleed", BinaryData::a_hhHalf_5_bleed_wav, BinaryData::a_hhHalf_5_bleed_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic HH Half 5 Binaural", BinaryData::a_hhHalf_5_binaural_wav, BinaryData::a_hhHalf_5_binaural_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "Binaural", samplers, formatManager);

            addSample2("Acoustic HH Open 4 Close", BinaryData::a_hhOpen_4_close_wav, BinaryData::a_hhOpen_4_close_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "HHClose", samplers, formatManager);
            addSample2("Acoustic HH Open 4 OH", BinaryData::a_hhOpen_4_oh_wav, BinaryData::a_hhOpen_4_oh_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic HH Open 4 Room", BinaryData::a_hhOpen_4_room_wav, BinaryData::a_hhOpen_4_room_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic HH Open 4 Bleed", BinaryData::a_hhOpen_4_bleed_wav, BinaryData::a_hhOpen_4_bleed_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic HH Open 4 Binaural", BinaryData::a_hhOpen_4_binaural_wav, BinaryData::a_hhOpen_4_binaural_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "Binaural", samplers, formatManager);

            double rideRelease = 0.7;
            addSample2("Acoustic Ride Point 5 OH", BinaryData::a_ridePoint_5_oh_wav, BinaryData::a_ridePoint_5_oh_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Ride Point 5 Room", BinaryData::a_ridePoint_5_room_wav, BinaryData::a_ridePoint_5_room_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Ride Point 5 Bleed", BinaryData::a_ridePoint_5_bleed_wav, BinaryData::a_ridePoint_5_bleed_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Ride Point 5 Binaural", BinaryData::a_ridePoint_5_binaural_wav, BinaryData::a_ridePoint_5_binaural_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "Binaural", samplers, formatManager);

            addSample2("Acoustic Ride Bell 5 OH", BinaryData::a_rideBell_5_oh_wav, BinaryData::a_rideBell_5_oh_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Ride Bell 5 Room", BinaryData::a_rideBell_5_room_wav, BinaryData::a_rideBell_5_room_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Ride Bell 5 Bleed", BinaryData::a_rideBell_5_bleed_wav, BinaryData::a_rideBell_5_bleed_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Ride Bell 5 Binaural", BinaryData::a_rideBell_5_binaural_wav, BinaryData::a_rideBell_5_binaural_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "Binaural", samplers, formatManager);

            double rideOpenRelease = 4.5;
            addSample2("Acoustic Ride Open 5 OH", BinaryData::a_rideOpen_5_oh_wav, BinaryData::a_rideOpen_5_oh_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Ride Open 5 Room", BinaryData::a_rideOpen_5_room_wav, BinaryData::a_rideOpen_5_room_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Ride Open 5 Bleed", BinaryData::a_rideOpen_5_bleed_wav, BinaryData::a_rideOpen_5_bleed_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Ride Open 5 Binaural", BinaryData::a_rideOpen_5_binaural_wav, BinaryData::a_rideOpen_5_binaural_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "Binaural", samplers, formatManager);

            addSample2("Acoustic Crash Point 5 OH", BinaryData::a_crashPoint_5_oh_wav, BinaryData::a_crashPoint_5_oh_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Crash Point 5 Room", BinaryData::a_crashPoint_5_room_wav, BinaryData::a_crashPoint_5_room_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Crash Point 5 Bleed", BinaryData::a_crashPoint_5_bleed_wav, BinaryData::a_crashPoint_5_bleed_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Crash Point 5 Binaural", BinaryData::a_crashPoint_5_binaural_wav, BinaryData::a_crashPoint_5_binaural_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "Binaural", samplers, formatManager);

            addSample2("Acoustic Crash Bell 5 OH", BinaryData::a_crashBell_5_oh_wav, BinaryData::a_crashBell_5_oh_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Crash Bell 5 Room", BinaryData::a_crashBell_5_room_wav, BinaryData::a_crashBell_5_room_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Crash Bell 5 Bleed", BinaryData::a_crashBell_5_bleed_wav, BinaryData::a_crashBell_5_bleed_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Crash Bell 5 Binaural", BinaryData::a_crashBell_5_binaural_wav, BinaryData::a_crashBell_5_binaural_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "Binaural", samplers, formatManager);

            double crashOpenRelease = 0.15;
            addSample2("Acoustic Crash Open 5 OH", BinaryData::a_crashOpen_5_oh_wav, BinaryData::a_crashOpen_5_oh_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Crash Open 5 Room", BinaryData::a_crashOpen_5_room_wav, BinaryData::a_crashOpen_5_room_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Crash Open 5 Bleed", BinaryData::a_crashOpen_5_bleed_wav, BinaryData::a_crashOpen_5_bleed_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Crash Open 5 Binaural", BinaryData::a_crashOpen_5_binaural_wav, BinaryData::a_crashOpen_5_binaural_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "Binaural", samplers, formatManager);

            addSample2("Acoustic Stack Closed 4 OH", BinaryData::a_stackClosed_4_oh_wav, BinaryData::a_stackClosed_4_oh_wavSize, defaultMidiNotes[24], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Stack Closed 4 Room", BinaryData::a_stackClosed_4_room_wav, BinaryData::a_stackClosed_4_room_wavSize, defaultMidiNotes[24], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Stack Closed 4 Bleed", BinaryData::a_stackClosed_4_bleed_wav, BinaryData::a_stackClosed_4_bleed_wavSize, defaultMidiNotes[24], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Stack Closed 4 Binaural", BinaryData::a_stackClosed_4_binaural_wav, BinaryData::a_stackClosed_4_binaural_wavSize, defaultMidiNotes[24], 1, 127, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Stack Open 4 OH", BinaryData::a_stackOpen_4_oh_wav, BinaryData::a_stackOpen_4_oh_wavSize, defaultMidiNotes[25], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Stack Open 4 Room", BinaryData::a_stackOpen_4_room_wav, BinaryData::a_stackOpen_4_room_wavSize, defaultMidiNotes[25], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Stack Open 4 Bleed", BinaryData::a_stackOpen_4_bleed_wav, BinaryData::a_stackOpen_4_bleed_wavSize, defaultMidiNotes[25], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Stack Open 4 Binaural", BinaryData::a_stackOpen_4_binaural_wav, BinaryData::a_stackOpen_4_binaural_wavSize, defaultMidiNotes[25], 1, 127, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            addSample2("Acoustic Sticks 3 OH", BinaryData::a_sticks_3_oh_wav, BinaryData::a_sticks_3_oh_wavSize, defaultMidiNotes[26], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Acoustic Sticks 3 Room", BinaryData::a_sticks_3_room_wav, BinaryData::a_sticks_3_room_wavSize, defaultMidiNotes[26], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Acoustic Sticks 3 Bleed", BinaryData::a_sticks_3_bleed_wav, BinaryData::a_sticks_3_bleed_wavSize, defaultMidiNotes[26], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample2("Acoustic Sticks 3 Binaural", BinaryData::a_sticks_3_binaural_wav, BinaryData::a_sticks_3_binaural_wavSize, defaultMidiNotes[26], 1, 127, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
        }
        else if (samplePack == 3)
        {
            double kickRelease = 0.6;
            double kickMaxLen = 1.4;
            addSample2("Dry Kick 4 Close", BinaryData::d_kick_4_close_wav, BinaryData::d_kick_4_close_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample2("Dry Kick 4 OH", BinaryData::d_kick_4_OH_wav, BinaryData::d_kick_4_OH_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample2("Dry Kick 4 Room", BinaryData::d_kick_4_room_wav, BinaryData::d_kick_4_room_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample2("Dry Kick 4 Bleed", BinaryData::d_kick_4_bleed_wav, BinaryData::d_kick_4_bleed_wavSize, defaultMidiNotes[0], 1, 127, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);

            double snareRelease = 0.5;
            double snareMaxLen = 1.6;
            addSample2("Dry Snare 5 Top", BinaryData::d_snare_5_top_wav, BinaryData::d_snare_5_top_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Dry Snare 5 Bot", BinaryData::d_snare_5_bot_wav, BinaryData::d_snare_5_bot_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Dry Snare 5 OH", BinaryData::d_snare_5_OH_wav, BinaryData::d_snare_5_OH_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Dry Snare 5 Room", BinaryData::d_snare_5_room_wav, BinaryData::d_snare_5_room_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Dry Snare 5 Bleed", BinaryData::d_snare_5_bleed_wav, BinaryData::d_snare_5_bleed_wavSize, defaultMidiNotes[1], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);

            addSample2("Dry Snare Flam 3 Top", BinaryData::d_snareFlam_3_top_wav, BinaryData::d_snareFlam_3_top_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Dry Snare Flam 3 Bot", BinaryData::d_snareFlam_3_bot_wav, BinaryData::d_snareFlam_3_bot_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Dry Snare Flam 3 OH", BinaryData::d_snareFlam_3_OH_wav, BinaryData::d_snareFlam_3_OH_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Dry Snare Flam 3 Room", BinaryData::d_snareFlam_3_room_wav, BinaryData::d_snareFlam_3_room_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Dry Snare Flam 3 Bleed", BinaryData::d_snareFlam_3_bleed_wav, BinaryData::d_snareFlam_3_bleed_wavSize, defaultMidiNotes[3], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);

            addSample2("Dry Snare Round 2 Top", BinaryData::d_snareRound_2_top_wav, BinaryData::d_snareRound_2_top_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Dry Snare Round 2 Bot", BinaryData::d_snareRound_2_bot_wav, BinaryData::d_snareRound_2_bot_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Dry Snare Round 2 OH", BinaryData::d_snareRound_2_OH_wav, BinaryData::d_snareRound_2_OH_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Dry Snare Round 2 Room", BinaryData::d_snareRound_2_room_wav, BinaryData::d_snareRound_2_room_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Dry Snare Round 2 Bleed", BinaryData::d_snareRound_2_bleed_wav, BinaryData::d_snareRound_2_bleed_wavSize, defaultMidiNotes[4], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);

            addSample2("Dry Snare Wireless 3 Top", BinaryData::d_snareWireless_3_top_wav, BinaryData::d_snareWireless_3_top_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Dry Snare Wireless 3 Bot", BinaryData::d_snareWireless_3_bot_wav, BinaryData::d_snareWireless_3_bot_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Dry Snare Wireless 3 OH", BinaryData::d_snareWireless_3_OH_wav, BinaryData::d_snareWireless_3_OH_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Dry Snare Wireless 3 Room", BinaryData::d_snareWireless_3_room_wav, BinaryData::d_snareWireless_3_room_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Dry Snare Wireless 3 Bleed", BinaryData::d_snareWireless_3_bleed_wav, BinaryData::d_snareWireless_3_bleed_wavSize, defaultMidiNotes[5], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);

            addSample2("Dry Snare Wireless Round 2 Top", BinaryData::d_snareWirelessRound_2_top_wav, BinaryData::d_snareWirelessRound_2_top_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample2("Dry Snare Wireless Round 2 Bot", BinaryData::d_snareWirelessRound_2_bot_wav, BinaryData::d_snareWirelessRound_2_bot_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample2("Dry Snare Wireless Round 2 OH", BinaryData::d_snareWirelessRound_2_OH_wav, BinaryData::d_snareWirelessRound_2_OH_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample2("Dry Snare Wireless Round 2 Room", BinaryData::d_snareWirelessRound_2_room_wav, BinaryData::d_snareWirelessRound_2_room_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample2("Dry Snare Wireless Round 2 Bleed", BinaryData::d_snareWirelessRound_2_bleed_wav, BinaryData::d_snareWirelessRound_2_bleed_wavSize, defaultMidiNotes[6], 1, 127, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);

            double tomRelease = 0.6;
            double tomMaxLen = 2.4;
            addSample2("Dry Tom 3 Close", BinaryData::d_tom_3_close_wav, BinaryData::d_tom_3_close_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample2("Dry Tom 3 OH", BinaryData::d_tom_3_OH_wav, BinaryData::d_tom_3_OH_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Dry Tom 3 Room", BinaryData::d_tom_3_room_wav, BinaryData::d_tom_3_room_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Dry Tom 3 Bleed", BinaryData::d_tom_3_bleed_wav, BinaryData::d_tom_3_bleed_wavSize, defaultMidiNotes[9], 1, 127, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);

            addSample2("Dry Tom Flam 2 Close", BinaryData::d_tomFlam_2_close_wav, BinaryData::d_tomFlam_2_close_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample2("Dry Tom Flam 2 OH", BinaryData::d_tomFlam_2_OH_wav, BinaryData::d_tomFlam_2_OH_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Dry Tom Flam 2 Room", BinaryData::d_tomFlam_2_room_wav, BinaryData::d_tomFlam_2_room_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Dry Tom Flam 2 Bleed", BinaryData::d_tomFlam_2_bleed_wav, BinaryData::d_tomFlam_2_bleed_wavSize, defaultMidiNotes[10], 1, 127, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);

            double ftomRelease = 0.7;
            addSample2("Dry FTom 3 Close", BinaryData::d_ftom_3_close_wav, BinaryData::d_ftom_3_close_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample2("Dry FTom 3 OH", BinaryData::d_ftom_3_OH_wav, BinaryData::d_ftom_3_OH_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Dry FTom 3 Room", BinaryData::d_ftom_3_room_wav, BinaryData::d_ftom_3_room_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Dry FTom 3 Bleed", BinaryData::d_ftom_3_bleed_wav, BinaryData::d_ftom_3_bleed_wavSize, defaultMidiNotes[11], 1, 127, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);

            addSample2("Dry FTom Flam 2 Close", BinaryData::d_ftomFlam_2_close_wav, BinaryData::d_ftomFlam_2_close_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample2("Dry FTom Flam 2 OH", BinaryData::d_ftomFlam_2_OH_wav, BinaryData::d_ftomFlam_2_OH_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample2("Dry FTom Flam 2 Room", BinaryData::d_ftomFlam_2_room_wav, BinaryData::d_ftomFlam_2_room_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample2("Dry FTom Flam 2 Bleed", BinaryData::d_ftomFlam_2_bleed_wav, BinaryData::d_ftomFlam_2_bleed_wavSize, defaultMidiNotes[12], 1, 127, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);

            double hhRelease = 0.12;
            double hhClosedMaxLen = 0.5;
            addSample2("Dry HH Closed 4 Close", BinaryData::d_hhClosed_4_close_wav, BinaryData::d_hhClosed_4_close_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample2("Dry HH Closed 4 OH", BinaryData::d_hhClosed_4_OH_wav, BinaryData::d_hhClosed_4_OH_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample2("Dry HH Closed 4 Room", BinaryData::d_hhClosed_4_room_wav, BinaryData::d_hhClosed_4_room_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry HH Closed 4 Bleed", BinaryData::d_hhClosed_4_bleed_wav, BinaryData::d_hhClosed_4_bleed_wavSize, defaultMidiNotes[14], 1, 127, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);

            addSample2("Dry HH Half 3 Close", BinaryData::d_hhHalf_3_close_wav, BinaryData::d_hhHalf_3_close_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "HHClose", samplers, formatManager);
            addSample2("Dry HH Half 3 OH", BinaryData::d_hhHalf_3_OH_wav, BinaryData::d_hhHalf_3_OH_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsOH", samplers, formatManager);
            addSample2("Dry HH Half 3 Room", BinaryData::d_hhHalf_3_room_wav, BinaryData::d_hhHalf_3_room_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry HH Half 3 Bleed", BinaryData::d_hhHalf_3_bleed_wav, BinaryData::d_hhHalf_3_bleed_wavSize, defaultMidiNotes[15], 1, 127, hhRelease, 1.6, "CymbalsBleed", samplers, formatManager);

            addSample2("Dry HH Open 3 Close", BinaryData::d_hhOpen_3_close_wav, BinaryData::d_hhOpen_3_close_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "HHClose", samplers, formatManager);
            addSample2("Dry HH Open 3 OH", BinaryData::d_hhOpen_3_OH_wav, BinaryData::d_hhOpen_3_OH_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsOH", samplers, formatManager);
            addSample2("Dry HH Open 3 Room", BinaryData::d_hhOpen_3_room_wav, BinaryData::d_hhOpen_3_room_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry HH Open 3 Bleed", BinaryData::d_hhOpen_3_bleed_wav, BinaryData::d_hhOpen_3_bleed_wavSize, defaultMidiNotes[16], 1, 127, hhRelease, 9.1, "CymbalsBleed", samplers, formatManager);

            double rideRelease = 0.7;
            addSample2("Dry Ride Point 3 OH", BinaryData::d_ridePoint_3_OH_wav, BinaryData::d_ridePoint_3_OH_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Ride Point 3 Room", BinaryData::d_ridePoint_3_room_wav, BinaryData::d_ridePoint_3_room_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Ride Point 3 Bleed", BinaryData::d_ridePoint_3_bleed_wav, BinaryData::d_ridePoint_3_bleed_wavSize, defaultMidiNotes[18], 1, 127, rideRelease, 10.3, "CymbalsBleed", samplers, formatManager);

            addSample2("Dry Ride Bell 3 OH", BinaryData::d_rideBell_3_OH_wav, BinaryData::d_rideBell_3_OH_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Ride Bell 3 Room", BinaryData::d_rideBell_3_room_wav, BinaryData::d_rideBell_3_room_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Ride Bell 3 Bleed", BinaryData::d_rideBell_3_bleed_wav, BinaryData::d_rideBell_3_bleed_wavSize, defaultMidiNotes[19], 1, 127, rideRelease, 10.9, "CymbalsBleed", samplers, formatManager);

            double rideOpenRelease = 4.5;
            addSample2("Dry Ride Open 3 OH", BinaryData::d_rideOpen_3_OH_wav, BinaryData::d_rideOpen_3_OH_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Ride Open 3 Room", BinaryData::d_rideOpen_3_room_wav, BinaryData::d_rideOpen_3_room_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Ride Open 3 Bleed", BinaryData::d_rideOpen_3_bleed_wav, BinaryData::d_rideOpen_3_bleed_wavSize, defaultMidiNotes[20], 1, 127, rideOpenRelease, 10.9, "CymbalsBleed", samplers, formatManager);

            addSample2("Dry Crash Point 2 OH", BinaryData::d_crashPoint_2_OH_wav, BinaryData::d_crashPoint_2_OH_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Crash Point 2 Room", BinaryData::d_crashPoint_2_room_wav, BinaryData::d_crashPoint_2_room_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Crash Point 2 Bleed", BinaryData::d_crashPoint_2_bleed_wav, BinaryData::d_crashPoint_2_bleed_wavSize, defaultMidiNotes[21], 1, 127, rideRelease, 7.3, "CymbalsBleed", samplers, formatManager);

            addSample2("Dry Crash Bell 2 OH", BinaryData::d_crashBell_2_OH_wav, BinaryData::d_crashBell_2_OH_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Crash Bell 2 Room", BinaryData::d_crashBell_2_room_wav, BinaryData::d_crashBell_2_room_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Crash Bell 2 Bleed", BinaryData::d_crashBell_2_bleed_wav, BinaryData::d_crashBell_2_bleed_wavSize, defaultMidiNotes[22], 1, 127, rideRelease, 7.9, "CymbalsBleed", samplers, formatManager);

            double crashOpenRelease = 0.15;
            addSample2("Dry Crash Open 3 OH", BinaryData::d_crashOpen_3_OH_wav, BinaryData::d_crashOpen_3_OH_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample2("Dry Crash Open 3 Room", BinaryData::d_crashOpen_3_room_wav, BinaryData::d_crashOpen_3_room_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample2("Dry Crash Open 3 Bleed", BinaryData::d_crashOpen_3_bleed_wav, BinaryData::d_crashOpen_3_bleed_wavSize, defaultMidiNotes[23], 1, 127, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
        }
        else
            loadElectronicSamples(samplers, formatManager);
    }

    void loadAcousticSamples(std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        string destinationAll = "C:/Users/damia/Desktop/Sampelki/";
        string acousticDestination = destinationAll + "acousticSamples/";

        if (missingSample)
        {
            loadEssentialSamples(samplePack, samplers, formatManager);
        }
        else
        {
            double kickRelease = 0.6;
            double kickMaxLen = 1.4;
            string kickDestination = acousticDestination + "a_kick/";
            addSample("Acoustic Kick 1 Close", kickDestination + "a_kick_1_close_wav", defaultMidiNotes[0], curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 2 Close", kickDestination + "a_kick_2_close_wav", defaultMidiNotes[0], curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 3 Close", kickDestination + "a_kick_3_close_wav", defaultMidiNotes[0], curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 4 Close", kickDestination + "a_kick_4_close_wav", defaultMidiNotes[0], curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 5 Close", kickDestination + "a_kick_5_close_wav", defaultMidiNotes[0], curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 6 Close", kickDestination + "a_kick_6_close_wav", defaultMidiNotes[0], curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Acoustic Kick 1 OH", kickDestination + "a_kick_1_oh_wav", defaultMidiNotes[0], curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 2 OH", kickDestination + "a_kick_2_oh_wav", defaultMidiNotes[0], curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 3 OH", kickDestination + "a_kick_3_oh_wav", defaultMidiNotes[0], curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 4 OH", kickDestination + "a_kick_4_oh_wav", defaultMidiNotes[0], curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 5 OH", kickDestination + "a_kick_5_oh_wav", defaultMidiNotes[0], curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 6 OH", kickDestination + "a_kick_6_oh_wav", defaultMidiNotes[0], curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Acoustic Kick 1 Room", kickDestination + "a_kick_1_room_wav", defaultMidiNotes[0], curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 2 Room", kickDestination + "a_kick_2_room_wav", defaultMidiNotes[0], curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 3 Room", kickDestination + "a_kick_3_room_wav", defaultMidiNotes[0], curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 4 Room", kickDestination + "a_kick_4_room_wav", defaultMidiNotes[0], curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 5 Room", kickDestination + "a_kick_5_room_wav", defaultMidiNotes[0], curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 6 Room", kickDestination + "a_kick_6_room_wav", defaultMidiNotes[0], curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Acoustic Kick 1 Bleed", kickDestination + "a_kick_1_bleed_wav", defaultMidiNotes[0], curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 2 Bleed", kickDestination + "a_kick_2_bleed_wav", defaultMidiNotes[0], curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 3 Bleed", kickDestination + "a_kick_3_bleed_wav", defaultMidiNotes[0], curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 4 Bleed", kickDestination + "a_kick_4_bleed_wav", defaultMidiNotes[0], curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 5 Bleed", kickDestination + "a_kick_5_bleed_wav", defaultMidiNotes[0], curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 6 Bleed", kickDestination + "a_kick_6_bleed_wav", defaultMidiNotes[0], curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Acoustic Kick 1 Binaural", kickDestination + "a_kick_1_binaural_wav", defaultMidiNotes[0], curveFor6[0], curveFor6[1] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Kick 2 Binaural", kickDestination + "a_kick_2_binaural_wav", defaultMidiNotes[0], curveFor6[1], curveFor6[2] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Kick 3 Binaural", kickDestination + "a_kick_3_binaural_wav", defaultMidiNotes[0], curveFor6[2], curveFor6[3] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Kick 4 Binaural", kickDestination + "a_kick_4_binaural_wav", defaultMidiNotes[0], curveFor6[3], curveFor6[4] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Kick 5 Binaural", kickDestination + "a_kick_5_binaural_wav", defaultMidiNotes[0], curveFor6[4], curveFor6[5] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Kick 6 Binaural", kickDestination + "a_kick_6_binaural_wav", defaultMidiNotes[0], curveFor6[5], curveFor6[6] - 1, kickRelease, kickMaxLen, "Binaural", samplers, formatManager);

            double snareRelease = 0.5;
            double snareMaxLen = 1.6;
            string snareAllDestination = acousticDestination + "a_snareAll/";
            string snareDestination = snareAllDestination + "a_snare/";
            addSample("Acoustic Snare 1 Top", snareDestination + "a_snare_1_top_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 2 Top", snareDestination + "a_snare_2_top_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 3 Top", snareDestination + "a_snare_3_top_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 4 Top", snareDestination + "a_snare_4_top_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 5 Top", snareDestination + "a_snare_5_top_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 6 Top", snareDestination + "a_snare_6_top_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 7 Top", snareDestination + "a_snare_7_top_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare 1 Bot", snareDestination + "a_snare_1_bot_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 2 Bot", snareDestination + "a_snare_2_bot_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 3 Bot", snareDestination + "a_snare_3_bot_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 4 Bot", snareDestination + "a_snare_4_bot_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 5 Bot", snareDestination + "a_snare_5_bot_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 6 Bot", snareDestination + "a_snare_6_bot_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 7 Bot", snareDestination + "a_snare_7_bot_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare 1 OH", snareDestination + "a_snare_1_oh_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 2 OH", snareDestination + "a_snare_2_oh_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 3 OH", snareDestination + "a_snare_3_oh_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 4 OH", snareDestination + "a_snare_4_oh_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 5 OH", snareDestination + "a_snare_5_oh_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 6 OH", snareDestination + "a_snare_6_oh_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 7 OH", snareDestination + "a_snare_7_oh_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare 1 Room", snareDestination + "a_snare_1_room_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 2 Room", snareDestination + "a_snare_2_room_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 3 Room", snareDestination + "a_snare_3_room_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 4 Room", snareDestination + "a_snare_4_room_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 5 Room", snareDestination + "a_snare_5_room_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 6 Room", snareDestination + "a_snare_6_room_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 7 Room", snareDestination + "a_snare_7_room_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare 1 Bleed", snareDestination + "a_snare_1_bleed_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 2 Bleed", snareDestination + "a_snare_2_bleed_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 3 Bleed", snareDestination + "a_snare_3_bleed_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 4 Bleed", snareDestination + "a_snare_4_bleed_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 5 Bleed", snareDestination + "a_snare_5_bleed_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 6 Bleed", snareDestination + "a_snare_6_bleed_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 7 Bleed", snareDestination + "a_snare_7_bleed_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare 1 Binaural", snareDestination + "a_snare_1_binaural_wav", defaultMidiNotes[1], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 2 Binaural", snareDestination + "a_snare_2_binaural_wav", defaultMidiNotes[1], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 3 Binaural", snareDestination + "a_snare_3_binaural_wav", defaultMidiNotes[1], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 4 Binaural", snareDestination + "a_snare_4_binaural_wav", defaultMidiNotes[1], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 5 Binaural", snareDestination + "a_snare_5_binaural_wav", defaultMidiNotes[1], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 6 Binaural", snareDestination + "a_snare_6_binaural_wav", defaultMidiNotes[1], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare 7 Binaural", snareDestination + "a_snare_7_binaural_wav", defaultMidiNotes[1], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snareSwirlDestination = acousticDestination + "a_snareSwirl/";
            addSample("Acoustic Snare Swirl 1 Top", snareSwirlDestination + "a_snareSwirl_1_top_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 Top", snareSwirlDestination + "a_snareSwirl_2_top_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 Top", snareSwirlDestination + "a_snareSwirl_3_top_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 Top", snareSwirlDestination + "a_snareSwirl_4_top_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Swirl 1 Bot", snareSwirlDestination + "a_snareSwirl_1_bot_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 Bot", snareSwirlDestination + "a_snareSwirl_2_bot_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 Bot", snareSwirlDestination + "a_snareSwirl_3_bot_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 Bot", snareSwirlDestination + "a_snareSwirl_4_bot_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Swirl 1 OH", snareSwirlDestination + "a_snareSwirl_1_oh_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 OH", snareSwirlDestination + "a_snareSwirl_2_oh_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 OH", snareSwirlDestination + "a_snareSwirl_3_oh_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 OH", snareSwirlDestination + "a_snareSwirl_4_oh_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Swirl 1 Room", snareSwirlDestination + "a_snareSwirl_1_room_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 Room", snareSwirlDestination + "a_snareSwirl_2_room_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 Room", snareSwirlDestination + "a_snareSwirl_3_room_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 Room", snareSwirlDestination + "a_snareSwirl_4_room_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Swirl 1 Bleed", snareSwirlDestination + "a_snareSwirl_1_bleed_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 Bleed", snareSwirlDestination + "a_snareSwirl_2_bleed_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 Bleed", snareSwirlDestination + "a_snareSwirl_3_bleed_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 Bleed", snareSwirlDestination + "a_snareSwirl_4_bleed_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Swirl 1 Binaural", snareSwirlDestination + "a_snareSwirl_1_binaural_wav", defaultMidiNotes[2], curveFor4[0], curveFor4[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Swirl 2 Binaural", snareSwirlDestination + "a_snareSwirl_2_binaural_wav", defaultMidiNotes[2], curveFor4[1], curveFor4[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Swirl 3 Binaural", snareSwirlDestination + "a_snareSwirl_3_binaural_wav", defaultMidiNotes[2], curveFor4[2], curveFor4[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Swirl 4 Binaural", snareSwirlDestination + "a_snareSwirl_4_binaural_wav", defaultMidiNotes[2], curveFor4[3], curveFor4[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snareFlamDestination = snareAllDestination + "a_snareFlam/";
            addSample("Acoustic Snare Flam 1 Top", snareFlamDestination + "a_snareFlam_1_top_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 Top", snareFlamDestination + "a_snareFlam_2_top_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 Top", snareFlamDestination + "a_snareFlam_3_top_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 Top", snareFlamDestination + "a_snareFlam_4_top_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 Top", snareFlamDestination + "a_snareFlam_5_top_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 Top", snareFlamDestination + "a_snareFlam_6_top_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 Top", snareFlamDestination + "a_snareFlam_7_top_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Flam 1 Bot", snareFlamDestination + "a_snareFlam_1_bot_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 Bot", snareFlamDestination + "a_snareFlam_2_bot_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 Bot", snareFlamDestination + "a_snareFlam_3_bot_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 Bot", snareFlamDestination + "a_snareFlam_4_bot_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 Bot", snareFlamDestination + "a_snareFlam_5_bot_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 Bot", snareFlamDestination + "a_snareFlam_6_bot_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 Bot", snareFlamDestination + "a_snareFlam_7_bot_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Flam 1 OH", snareFlamDestination + "a_snareFlam_1_oh_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 OH", snareFlamDestination + "a_snareFlam_2_oh_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 OH", snareFlamDestination + "a_snareFlam_3_oh_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 OH", snareFlamDestination + "a_snareFlam_4_oh_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 OH", snareFlamDestination + "a_snareFlam_5_oh_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 OH", snareFlamDestination + "a_snareFlam_6_oh_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 OH", snareFlamDestination + "a_snareFlam_7_oh_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Flam 1 Room", snareFlamDestination + "a_snareFlam_1_room_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 Room", snareFlamDestination + "a_snareFlam_2_room_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 Room", snareFlamDestination + "a_snareFlam_3_room_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 Room", snareFlamDestination + "a_snareFlam_4_room_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 Room", snareFlamDestination + "a_snareFlam_5_room_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 Room", snareFlamDestination + "a_snareFlam_6_room_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 Room", snareFlamDestination + "a_snareFlam_7_room_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Flam 1 Bleed", snareFlamDestination + "a_snareFlam_1_bleed_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 Bleed", snareFlamDestination + "a_snareFlam_2_bleed_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 Bleed", snareFlamDestination + "a_snareFlam_3_bleed_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 Bleed", snareFlamDestination + "a_snareFlam_4_bleed_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 Bleed", snareFlamDestination + "a_snareFlam_5_bleed_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 Bleed", snareFlamDestination + "a_snareFlam_6_bleed_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 Bleed", snareFlamDestination + "a_snareFlam_7_bleed_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Flam 1 Binaural", snareFlamDestination + "a_snareFlam_1_binaural_wav", defaultMidiNotes[3], curveFor7[0], curveFor7[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 2 Binaural", snareFlamDestination + "a_snareFlam_2_binaural_wav", defaultMidiNotes[3], curveFor7[1], curveFor7[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 3 Binaural", snareFlamDestination + "a_snareFlam_3_binaural_wav", defaultMidiNotes[3], curveFor7[2], curveFor7[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 4 Binaural", snareFlamDestination + "a_snareFlam_4_binaural_wav", defaultMidiNotes[3], curveFor7[3], curveFor7[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 5 Binaural", snareFlamDestination + "a_snareFlam_5_binaural_wav", defaultMidiNotes[3], curveFor7[4], curveFor7[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 6 Binaural", snareFlamDestination + "a_snareFlam_6_binaural_wav", defaultMidiNotes[3], curveFor7[5], curveFor7[6] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Flam 7 Binaural", snareFlamDestination + "a_snareFlam_7_binaural_wav", defaultMidiNotes[3], curveFor7[6], curveFor7[7] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snareRoundDestination = snareAllDestination + "a_snareRound/";
            addSample("Acoustic Snare Round 1 Top", snareRoundDestination + "a_snareRound_1_top_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Round 2 Top", snareRoundDestination + "a_snareRound_2_top_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Round 3 Top", snareRoundDestination + "a_snareRound_3_top_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Round 4 Top", snareRoundDestination + "a_snareRound_4_top_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Round 5 Top", snareRoundDestination + "a_snareRound_5_top_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Round 1 Bot", snareRoundDestination + "a_snareRound_1_bot_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Round 2 Bot", snareRoundDestination + "a_snareRound_2_bot_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Round 3 Bot", snareRoundDestination + "a_snareRound_3_bot_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Round 4 Bot", snareRoundDestination + "a_snareRound_4_bot_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Round 5 Bot", snareRoundDestination + "a_snareRound_5_bot_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Round 1 OH", snareRoundDestination + "a_snareRound_1_oh_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Round 2 OH", snareRoundDestination + "a_snareRound_2_oh_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Round 3 OH", snareRoundDestination + "a_snareRound_3_oh_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Round 4 OH", snareRoundDestination + "a_snareRound_4_oh_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Round 5 OH", snareRoundDestination + "a_snareRound_5_oh_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Round 1 Room", snareRoundDestination + "a_snareRound_1_room_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Round 2 Room", snareRoundDestination + "a_snareRound_2_room_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Round 3 Room", snareRoundDestination + "a_snareRound_3_room_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Round 4 Room", snareRoundDestination + "a_snareRound_4_room_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Round 5 Room", snareRoundDestination + "a_snareRound_5_room_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Round 1 Bleed", snareRoundDestination + "a_snareRound_1_bleed_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Round 2 Bleed", snareRoundDestination + "a_snareRound_2_bleed_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Round 3 Bleed", snareRoundDestination + "a_snareRound_3_bleed_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Round 4 Bleed", snareRoundDestination + "a_snareRound_4_bleed_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Round 5 Bleed", snareRoundDestination + "a_snareRound_5_bleed_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Round 1 Binaural", snareRoundDestination + "a_snareRound_1_binaural_wav", defaultMidiNotes[4], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Round 2 Binaural", snareRoundDestination + "a_snareRound_2_binaural_wav", defaultMidiNotes[4], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Round 3 Binaural", snareRoundDestination + "a_snareRound_3_binaural_wav", defaultMidiNotes[4], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Round 4 Binaural", snareRoundDestination + "a_snareRound_4_binaural_wav", defaultMidiNotes[4], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Round 5 Binaural", snareRoundDestination + "a_snareRound_5_binaural_wav", defaultMidiNotes[4], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snareWireless = snareAllDestination + "a_snareWireless/";
            addSample("Acoustic Snare Wireless 1 Top", snareWireless + "a_snareWireless_1_top_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 Top", snareWireless + "a_snareWireless_2_top_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 Top", snareWireless + "a_snareWireless_3_top_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 Top", snareWireless + "a_snareWireless_4_top_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 Top", snareWireless + "a_snareWireless_5_top_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless 1 Bot", snareWireless + "a_snareWireless_1_bot_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 Bot", snareWireless + "a_snareWireless_2_bot_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 Bot", snareWireless + "a_snareWireless_3_bot_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 Bot", snareWireless + "a_snareWireless_4_bot_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 Bot", snareWireless + "a_snareWireless_5_bot_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless 1 OH", snareWireless + "a_snareWireless_1_oh_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 OH", snareWireless + "a_snareWireless_2_oh_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 OH", snareWireless + "a_snareWireless_3_oh_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 OH", snareWireless + "a_snareWireless_4_oh_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 OH", snareWireless + "a_snareWireless_5_oh_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless 1 Room", snareWireless + "a_snareWireless_1_room_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 Room", snareWireless + "a_snareWireless_2_room_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 Room", snareWireless + "a_snareWireless_3_room_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 Room", snareWireless + "a_snareWireless_4_room_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 Room", snareWireless + "a_snareWireless_5_room_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless 1 Bleed", snareWireless + "a_snareWireless_1_bleed_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 Bleed", snareWireless + "a_snareWireless_2_bleed_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 Bleed", snareWireless + "a_snareWireless_3_bleed_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 Bleed", snareWireless + "a_snareWireless_4_bleed_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 Bleed", snareWireless + "a_snareWireless_5_bleed_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless 1 Binaural", snareWireless + "a_snareWireless_1_binaural_wav", defaultMidiNotes[5], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless 2 Binaural", snareWireless + "a_snareWireless_2_binaural_wav", defaultMidiNotes[5], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless 3 Binaural", snareWireless + "a_snareWireless_3_binaural_wav", defaultMidiNotes[5], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless 4 Binaural", snareWireless + "a_snareWireless_4_binaural_wav", defaultMidiNotes[5], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless 5 Binaural", snareWireless + "a_snareWireless_5_binaural_wav", defaultMidiNotes[5], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snareWirelessRoundDestination = snareAllDestination + "a_snareWirelessRound/";
            addSample("Acoustic Snare Wireless Round 1 Top", snareWirelessRoundDestination + "a_snareWirelessRound_1_top_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 Top", snareWirelessRoundDestination + "a_snareWirelessRound_2_top_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 Top", snareWirelessRoundDestination + "a_snareWirelessRound_3_top_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 Top", snareWirelessRoundDestination + "a_snareWirelessRound_4_top_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 Top", snareWirelessRoundDestination + "a_snareWirelessRound_5_top_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 1 Bot", snareWirelessRoundDestination + "a_snareWirelessRound_1_bot_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 Bot", snareWirelessRoundDestination + "a_snareWirelessRound_2_bot_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 Bot", snareWirelessRoundDestination + "a_snareWirelessRound_3_bot_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 Bot", snareWirelessRoundDestination + "a_snareWirelessRound_4_bot_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 Bot", snareWirelessRoundDestination + "a_snareWirelessRound_5_bot_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBot", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 1 OH", snareWirelessRoundDestination + "a_snareWirelessRound_1_oh_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 OH", snareWirelessRoundDestination + "a_snareWirelessRound_2_oh_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 OH", snareWirelessRoundDestination + "a_snareWirelessRound_3_oh_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 OH", snareWirelessRoundDestination + "a_snareWirelessRound_4_oh_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 OH", snareWirelessRoundDestination + "a_snareWirelessRound_5_oh_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 1 Room", snareWirelessRoundDestination + "a_snareWirelessRound_1_room_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 Room", snareWirelessRoundDestination + "a_snareWirelessRound_2_room_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 Room", snareWirelessRoundDestination + "a_snareWirelessRound_3_room_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 Room", snareWirelessRoundDestination + "a_snareWirelessRound_4_room_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 Room", snareWirelessRoundDestination + "a_snareWirelessRound_5_room_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 1 Bleed", snareWirelessRoundDestination + "a_snareWirelessRound_1_bleed_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 Bleed", snareWirelessRoundDestination + "a_snareWirelessRound_2_bleed_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 Bleed", snareWirelessRoundDestination + "a_snareWirelessRound_3_bleed_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 Bleed", snareWirelessRoundDestination + "a_snareWirelessRound_4_bleed_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 Bleed", snareWirelessRoundDestination + "a_snareWirelessRound_5_bleed_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 1 Binaural", snareWirelessRoundDestination + "a_snareWirelessRound_1_binaural_wav", defaultMidiNotes[6], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 2 Binaural", snareWirelessRoundDestination + "a_snareWirelessRound_2_binaural_wav", defaultMidiNotes[6], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 3 Binaural", snareWirelessRoundDestination + "a_snareWirelessRound_3_binaural_wav", defaultMidiNotes[6], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 4 Binaural", snareWirelessRoundDestination + "a_snareWirelessRound_4_binaural_wav", defaultMidiNotes[6], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Snare Wireless Round 5 Binaural", snareWirelessRoundDestination + "a_snareWirelessRound_5_binaural_wav", defaultMidiNotes[6], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snarePiccoloDestination = snareAllDestination + "a_snarePiccolo/";
            addSample("Acoustic Piccolo 1 Close", snarePiccoloDestination + "a_snarePiccolo_1_close_wav", defaultMidiNotes[7], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo 2 Close", snarePiccoloDestination + "a_snarePiccolo_2_close_wav", defaultMidiNotes[7], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo 3 Close", snarePiccoloDestination + "a_snarePiccolo_3_close_wav", defaultMidiNotes[7], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo 4 Close", snarePiccoloDestination + "a_snarePiccolo_4_close_wav", defaultMidiNotes[7], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo 5 Close", snarePiccoloDestination + "a_snarePiccolo_5_close_wav", defaultMidiNotes[7], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo 1 OH", snarePiccoloDestination + "a_snarePiccolo_1_oh_wav", defaultMidiNotes[7], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo 2 OH", snarePiccoloDestination + "a_snarePiccolo_2_oh_wav", defaultMidiNotes[7], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo 3 OH", snarePiccoloDestination + "a_snarePiccolo_3_oh_wav", defaultMidiNotes[7], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo 4 OH", snarePiccoloDestination + "a_snarePiccolo_4_oh_wav", defaultMidiNotes[7], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo 5 OH", snarePiccoloDestination + "a_snarePiccolo_5_oh_wav", defaultMidiNotes[7], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo 1 Room", snarePiccoloDestination + "a_snarePiccolo_1_room_wav", defaultMidiNotes[7], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo 2 Room", snarePiccoloDestination + "a_snarePiccolo_2_room_wav", defaultMidiNotes[7], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo 3 Room", snarePiccoloDestination + "a_snarePiccolo_3_room_wav", defaultMidiNotes[7], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo 4 Room", snarePiccoloDestination + "a_snarePiccolo_4_room_wav", defaultMidiNotes[7], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo 5 Room", snarePiccoloDestination + "a_snarePiccolo_5_room_wav", defaultMidiNotes[7], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo 1 Bleed", snarePiccoloDestination + "a_snarePiccolo_1_bleed_wav", defaultMidiNotes[7], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo 2 Bleed", snarePiccoloDestination + "a_snarePiccolo_2_bleed_wav", defaultMidiNotes[7], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo 3 Bleed", snarePiccoloDestination + "a_snarePiccolo_3_bleed_wav", defaultMidiNotes[7], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo 4 Bleed", snarePiccoloDestination + "a_snarePiccolo_4_bleed_wav", defaultMidiNotes[7], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo 5 Bleed", snarePiccoloDestination + "a_snarePiccolo_5_bleed_wav", defaultMidiNotes[7], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo 1 Binaural", snarePiccoloDestination + "a_snarePiccolo_1_binaural_wav", defaultMidiNotes[7], curveFor5[0], curveFor5[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo 2 Binaural", snarePiccoloDestination + "a_snarePiccolo_2_binaural_wav", defaultMidiNotes[7], curveFor5[1], curveFor5[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo 3 Binaural", snarePiccoloDestination + "a_snarePiccolo_3_binaural_wav", defaultMidiNotes[7], curveFor5[2], curveFor5[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo 4 Binaural", snarePiccoloDestination + "a_snarePiccolo_4_binaural_wav", defaultMidiNotes[7], curveFor5[3], curveFor5[4] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo 5 Binaural", snarePiccoloDestination + "a_snarePiccolo_5_binaural_wav", defaultMidiNotes[7], curveFor5[4], curveFor5[5] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            string snarePiccoloSwirlDestination = snareAllDestination + "a_snarePiccoloSwirl/";
            addSample("Acoustic Piccolo Swirl 1 Close", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_1_close_wav", defaultMidiNotes[8], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 2 Close", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_2_close_wav", defaultMidiNotes[8], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 3 Close", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_3_close_wav", defaultMidiNotes[8], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen, "SnareTop", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 1 OH", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_1_oh_wav", defaultMidiNotes[8], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 2 OH", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_2_oh_wav", defaultMidiNotes[8], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 3 OH", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_3_oh_wav", defaultMidiNotes[8], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen, "SnareOH", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 1 Room", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_1_room_wav", defaultMidiNotes[8], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 2 Room", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_2_room_wav", defaultMidiNotes[8], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 3 Room", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_3_room_wav", defaultMidiNotes[8], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen, "SnareRoom", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 1 Bleed", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_1_bleed_wav", defaultMidiNotes[8], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 2 Bleed", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_2_bleed_wav", defaultMidiNotes[8], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 3 Bleed", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_3_bleed_wav", defaultMidiNotes[8], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen, "SnareBleed", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 1 Binaural", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_1_binaural_wav", defaultMidiNotes[8], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 2 Binaural", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_2_binaural_wav", defaultMidiNotes[8], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Piccolo Swirl 3 Binaural", snarePiccoloSwirlDestination + "a_snarePiccoloSwirl_3_binaural_wav", defaultMidiNotes[8], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen, "Binaural", samplers, formatManager);

            double tomRelease = 0.6;
            double tomMaxLen = 2.4;
            string tomsAllDestination = acousticDestination + "a_tomsAll/";
            string tomDestination = tomsAllDestination + "a_tom/";
            addSample("Acoustic Tom 1 Close", tomDestination + "a_tom_1_close_wav", defaultMidiNotes[9], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom 2 Close", tomDestination + "a_tom_2_close_wav", defaultMidiNotes[9], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom 3 Close", tomDestination + "a_tom_3_close_wav", defaultMidiNotes[9], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom 4 Close", tomDestination + "a_tom_4_close_wav", defaultMidiNotes[9], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom 5 Close", tomDestination + "a_tom_5_close_wav", defaultMidiNotes[9], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom 1 OH", tomDestination + "a_tom_1_oh_wav", defaultMidiNotes[9], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom 2 OH", tomDestination + "a_tom_2_oh_wav", defaultMidiNotes[9], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom 3 OH", tomDestination + "a_tom_3_oh_wav", defaultMidiNotes[9], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom 4 OH", tomDestination + "a_tom_4_oh_wav", defaultMidiNotes[9], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom 5 OH", tomDestination + "a_tom_5_oh_wav", defaultMidiNotes[9], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom 1 Room", tomDestination + "a_tom_1_room_wav", defaultMidiNotes[9], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom 2 Room", tomDestination + "a_tom_2_room_wav", defaultMidiNotes[9], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom 3 Room", tomDestination + "a_tom_3_room_wav", defaultMidiNotes[9], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom 4 Room", tomDestination + "a_tom_4_room_wav", defaultMidiNotes[9], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom 5 Room", tomDestination + "a_tom_5_room_wav", defaultMidiNotes[9], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom 1 Bleed", tomDestination + "a_tom_1_bleed_wav", defaultMidiNotes[9], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom 2 Bleed", tomDestination + "a_tom_2_bleed_wav", defaultMidiNotes[9], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom 3 Bleed", tomDestination + "a_tom_3_bleed_wav", defaultMidiNotes[9], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom 4 Bleed", tomDestination + "a_tom_4_bleed_wav", defaultMidiNotes[9], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom 5 Bleed", tomDestination + "a_tom_5_bleed_wav", defaultMidiNotes[9], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom 1 Binaural", tomDestination + "a_tom_1_binaural_wav", defaultMidiNotes[9], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom 2 Binaural", tomDestination + "a_tom_2_binaural_wav", defaultMidiNotes[9], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom 3 Binaural", tomDestination + "a_tom_3_binaural_wav", defaultMidiNotes[9], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom 4 Binaural", tomDestination + "a_tom_4_binaural_wav", defaultMidiNotes[9], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom 5 Binaural", tomDestination + "a_tom_5_binaural_wav", defaultMidiNotes[9], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            string tomFlamDestination = tomsAllDestination + "a_tomFlam/";
            addSample("Acoustic Tom Flam 1 Close", tomFlamDestination + "a_tomFlam_1_close_wav", defaultMidiNotes[10], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom Flam 2 Close", tomFlamDestination + "a_tomFlam_2_close_wav", defaultMidiNotes[10], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom Flam 3 Close", tomFlamDestination + "a_tomFlam_3_close_wav", defaultMidiNotes[10], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom Flam 4 Close", tomFlamDestination + "a_tomFlam_4_close_wav", defaultMidiNotes[10], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom Flam 5 Close", tomFlamDestination + "a_tomFlam_5_close_wav", defaultMidiNotes[10], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomClose", samplers, formatManager);
            addSample("Acoustic Tom Flam 1 OH", tomFlamDestination + "a_tomFlam_1_oh_wav", defaultMidiNotes[10], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom Flam 2 OH", tomFlamDestination + "a_tomFlam_2_oh_wav", defaultMidiNotes[10], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom Flam 3 OH", tomFlamDestination + "a_tomFlam_3_oh_wav", defaultMidiNotes[10], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom Flam 4 OH", tomFlamDestination + "a_tomFlam_4_oh_wav", defaultMidiNotes[10], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom Flam 5 OH", tomFlamDestination + "a_tomFlam_5_oh_wav", defaultMidiNotes[10], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic Tom Flam 1 Room", tomFlamDestination + "a_tomFlam_1_room_wav", defaultMidiNotes[10], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom Flam 2 Room", tomFlamDestination + "a_tomFlam_2_room_wav", defaultMidiNotes[10], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom Flam 3 Room", tomFlamDestination + "a_tomFlam_3_room_wav", defaultMidiNotes[10], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom Flam 4 Room", tomFlamDestination + "a_tomFlam_4_room_wav", defaultMidiNotes[10], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom Flam 5 Room", tomFlamDestination + "a_tomFlam_5_room_wav", defaultMidiNotes[10], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic Tom Flam 1 Bleed", tomFlamDestination + "a_tomFlam_1_bleed_wav", defaultMidiNotes[10], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom Flam 2 Bleed", tomFlamDestination + "a_tomFlam_2_bleed_wav", defaultMidiNotes[10], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom Flam 3 Bleed", tomFlamDestination + "a_tomFlam_3_bleed_wav", defaultMidiNotes[10], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom Flam 4 Bleed", tomFlamDestination + "a_tomFlam_4_bleed_wav", defaultMidiNotes[10], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom Flam 5 Bleed", tomFlamDestination + "a_tomFlam_5_bleed_wav", defaultMidiNotes[10], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic Tom Flam 1 Binaural", tomFlamDestination + "a_tomFlam_1_binaural_wav", defaultMidiNotes[10], curveFor5[0], curveFor5[1] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom Flam 2 Binaural", tomFlamDestination + "a_tomFlam_2_binaural_wav", defaultMidiNotes[10], curveFor5[1], curveFor5[2] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom Flam 3 Binaural", tomFlamDestination + "a_tomFlam_3_binaural_wav", defaultMidiNotes[10], curveFor5[2], curveFor5[3] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom Flam 4 Binaural", tomFlamDestination + "a_tomFlam_4_binaural_wav", defaultMidiNotes[10], curveFor5[3], curveFor5[4] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Tom Flam 5 Binaural", tomFlamDestination + "a_tomFlam_5_binaural_wav", defaultMidiNotes[10], curveFor5[4], curveFor5[5] - 1, tomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            double ftomRelease = 0.7;
            string ftomDestination = tomsAllDestination + "a_ftom/";
            addSample("Acoustic FTom 1 Close", ftomDestination + "a_ftom_1_close_wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom 2 Close", ftomDestination + "a_ftom_2_close_wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom 3 Close", ftomDestination + "a_ftom_3_close_wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom 4 Close", ftomDestination + "a_ftom_4_close_wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom 5 Close", ftomDestination + "a_ftom_5_close_wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom 1 OH", ftomDestination + "a_ftom_1_oh_wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom 2 OH", ftomDestination + "a_ftom_2_oh_wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom 3 OH", ftomDestination + "a_ftom_3_oh_wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom 4 OH", ftomDestination + "a_ftom_4_oh_wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom 5 OH", ftomDestination + "a_ftom_5_oh_wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom 1 Room", ftomDestination + "a_ftom_1_room_wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom 2 Room", ftomDestination + "a_ftom_2_room_wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom 3 Room", ftomDestination + "a_ftom_3_room_wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom 4 Room", ftomDestination + "a_ftom_4_room_wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom 5 Room", ftomDestination + "a_ftom_5_room_wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom 1 Bleed", ftomDestination + "a_ftom_1_bleed_wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom 2 Bleed", ftomDestination + "a_ftom_2_bleed_wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom 3 Bleed", ftomDestination + "a_ftom_3_bleed_wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom 4 Bleed", ftomDestination + "a_ftom_4_bleed_wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom 5 Bleed", ftomDestination + "a_ftom_5_bleed_wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom 1 Binaural", ftomDestination + "a_ftom_1_binaural_wav", defaultMidiNotes[11], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom 2 Binaural", ftomDestination + "a_ftom_2_binaural_wav", defaultMidiNotes[11], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom 3 Binaural", ftomDestination + "a_ftom_3_binaural_wav", defaultMidiNotes[11], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom 4 Binaural", ftomDestination + "a_ftom_4_binaural_wav", defaultMidiNotes[11], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom 5 Binaural", ftomDestination + "a_ftom_5_binaural_wav", defaultMidiNotes[11], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            string ftomFlamDestination = tomsAllDestination + "a_ftomFlam/";
            addSample("Acoustic FTom Flam 1 Close", ftomFlamDestination + "a_ftomFlam_1_close_wav", defaultMidiNotes[12], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom Flam 2 Close", ftomFlamDestination + "a_ftomFlam_2_close_wav", defaultMidiNotes[12], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom Flam 3 Close", ftomFlamDestination + "a_ftomFlam_3_close_wav", defaultMidiNotes[12], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom Flam 4 Close", ftomFlamDestination + "a_ftomFlam_4_close_wav", defaultMidiNotes[12], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom Flam 5 Close", ftomFlamDestination + "a_ftomFlam_5_close_wav", defaultMidiNotes[12], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "FTomClose", samplers, formatManager);
            addSample("Acoustic FTom Flam 1 OH", ftomFlamDestination + "a_ftomFlam_1_oh_wav", defaultMidiNotes[12], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom Flam 2 OH", ftomFlamDestination + "a_ftomFlam_2_oh_wav", defaultMidiNotes[12], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom Flam 3 OH", ftomFlamDestination + "a_ftomFlam_3_oh_wav", defaultMidiNotes[12], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom Flam 4 OH", ftomFlamDestination + "a_ftomFlam_4_oh_wav", defaultMidiNotes[12], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom Flam 5 OH", ftomFlamDestination + "a_ftomFlam_5_oh_wav", defaultMidiNotes[12], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsOH", samplers, formatManager);
            addSample("Acoustic FTom Flam 1 Room", ftomFlamDestination + "a_ftomFlam_1_room_wav", defaultMidiNotes[12], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom Flam 2 Room", ftomFlamDestination + "a_ftomFlam_2_room_wav", defaultMidiNotes[12], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom Flam 3 Room", ftomFlamDestination + "a_ftomFlam_3_room_wav", defaultMidiNotes[12], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom Flam 4 Room", ftomFlamDestination + "a_ftomFlam_4_room_wav", defaultMidiNotes[12], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom Flam 5 Room", ftomFlamDestination + "a_ftomFlam_5_room_wav", defaultMidiNotes[12], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsRoom", samplers, formatManager);
            addSample("Acoustic FTom Flam 1 Bleed", ftomFlamDestination + "a_ftomFlam_1_bleed_wav", defaultMidiNotes[12], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom Flam 2 Bleed", ftomFlamDestination + "a_ftomFlam_2_bleed_wav", defaultMidiNotes[12], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom Flam 3 Bleed", ftomFlamDestination + "a_ftomFlam_3_bleed_wav", defaultMidiNotes[12], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom Flam 4 Bleed", ftomFlamDestination + "a_ftomFlam_4_bleed_wav", defaultMidiNotes[12], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom Flam 5 Bleed", ftomFlamDestination + "a_ftomFlam_5_bleed_wav", defaultMidiNotes[12], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "TomsBleed", samplers, formatManager);
            addSample("Acoustic FTom Flam 1 Binaural", ftomFlamDestination + "a_ftomFlam_1_binaural_wav", defaultMidiNotes[12], curveFor5[0], curveFor5[1] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom Flam 2 Binaural", ftomFlamDestination + "a_ftomFlam_2_binaural_wav", defaultMidiNotes[12], curveFor5[1], curveFor5[2] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom Flam 3 Binaural", ftomFlamDestination + "a_ftomFlam_3_binaural_wav", defaultMidiNotes[12], curveFor5[2], curveFor5[3] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom Flam 4 Binaural", ftomFlamDestination + "a_ftomFlam_4_binaural_wav", defaultMidiNotes[12], curveFor5[3], curveFor5[4] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic FTom Flam 5 Binaural", ftomFlamDestination + "a_ftomFlam_5_binaural_wav", defaultMidiNotes[12], curveFor5[4], curveFor5[5] - 1, ftomRelease, tomMaxLen, "Binaural", samplers, formatManager);

            double hhRelease = 0.12;
            double hhClosedMaxLen = 0.5;
            string hhAllDestination = acousticDestination + "a_hhAll/";
            string hhStompDestination = hhAllDestination + "a_hhStomp/";
            addSample("Acoustic HH Stomp 1 Close", hhStompDestination + "a_hhStomp_1_close_wav", defaultMidiNotes[13], curveFor3[0], curveFor3[1] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Stomp 2 Close", hhStompDestination + "a_hhStomp_2_close_wav", defaultMidiNotes[13], curveFor3[1], curveFor3[2] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Stomp 3 Close", hhStompDestination + "a_hhStomp_3_close_wav", defaultMidiNotes[13], curveFor3[2], curveFor3[3] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Stomp 1 OH", hhStompDestination + "a_hhStomp_1_oh_wav", defaultMidiNotes[13], curveFor3[0], curveFor3[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Stomp 2 OH", hhStompDestination + "a_hhStomp_2_oh_wav", defaultMidiNotes[13], curveFor3[1], curveFor3[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Stomp 3 OH", hhStompDestination + "a_hhStomp_3_oh_wav", defaultMidiNotes[13], curveFor3[2], curveFor3[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Stomp 1 Room", hhStompDestination + "a_hhStomp_1_room_wav", defaultMidiNotes[13], curveFor3[0], curveFor3[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Stomp 2 Room", hhStompDestination + "a_hhStomp_2_room_wav", defaultMidiNotes[13], curveFor3[1], curveFor3[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Stomp 3 Room", hhStompDestination + "a_hhStomp_3_room_wav", defaultMidiNotes[13], curveFor3[2], curveFor3[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Stomp 1 Bleed", hhStompDestination + "a_hhStomp_1_bleed_wav", defaultMidiNotes[13], curveFor3[0], curveFor3[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Stomp 2 Bleed", hhStompDestination + "a_hhStomp_2_bleed_wav", defaultMidiNotes[13], curveFor3[1], curveFor3[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Stomp 3 Bleed", hhStompDestination + "a_hhStomp_3_bleed_wav", defaultMidiNotes[13], curveFor3[2], curveFor3[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Stomp 1 Binaural", hhStompDestination + "a_hhStomp_1_binaural_wav", defaultMidiNotes[13], curveFor3[0], curveFor3[1] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Stomp 2 Binaural", hhStompDestination + "a_hhStomp_2_binaural_wav", defaultMidiNotes[13], curveFor3[1], curveFor3[2] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Stomp 3 Binaural", hhStompDestination + "a_hhStomp_3_binaural_wav", defaultMidiNotes[13], curveFor3[2], curveFor3[3] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            string hhClosedDestination = hhAllDestination + "a_hhClosed/";
            addSample("Acoustic HH Closed 1 Close", hhClosedDestination + "a_hhClosed_1_close_wav", defaultMidiNotes[14], curveFor7[0], curveFor7[1] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 2 Close", hhClosedDestination + "a_hhClosed_2_close_wav", defaultMidiNotes[14], curveFor7[1], curveFor7[2] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 3 Close", hhClosedDestination + "a_hhClosed_3_close_wav", defaultMidiNotes[14], curveFor7[2], curveFor7[3] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 4 Close", hhClosedDestination + "a_hhClosed_4_close_wav", defaultMidiNotes[14], curveFor7[3], curveFor7[4] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 5 Close", hhClosedDestination + "a_hhClosed_5_close_wav", defaultMidiNotes[14], curveFor7[4], curveFor7[5] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 6 Close", hhClosedDestination + "a_hhClosed_6_close_wav", defaultMidiNotes[14], curveFor7[5], curveFor7[6] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 7 Close", hhClosedDestination + "a_hhClosed_7_close_wav", defaultMidiNotes[14], curveFor7[6], curveFor7[7] - 1, hhRelease, hhClosedMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Closed 1 OH", hhClosedDestination + "a_hhClosed_1_oh_wav", defaultMidiNotes[14], curveFor7[0], curveFor7[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 2 OH", hhClosedDestination + "a_hhClosed_2_oh_wav", defaultMidiNotes[14], curveFor7[1], curveFor7[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 3 OH", hhClosedDestination + "a_hhClosed_3_oh_wav", defaultMidiNotes[14], curveFor7[2], curveFor7[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 4 OH", hhClosedDestination + "a_hhClosed_4_oh_wav", defaultMidiNotes[14], curveFor7[3], curveFor7[4] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 5 OH", hhClosedDestination + "a_hhClosed_5_oh_wav", defaultMidiNotes[14], curveFor7[4], curveFor7[5] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 6 OH", hhClosedDestination + "a_hhClosed_6_oh_wav", defaultMidiNotes[14], curveFor7[5], curveFor7[6] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 7 OH", hhClosedDestination + "a_hhClosed_7_oh_wav", defaultMidiNotes[14], curveFor7[6], curveFor7[7] - 1, hhRelease, hhClosedMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Closed 1 Room", hhClosedDestination + "a_hhClosed_1_room_wav", defaultMidiNotes[14], curveFor7[0], curveFor7[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 2 Room", hhClosedDestination + "a_hhClosed_2_room_wav", defaultMidiNotes[14], curveFor7[1], curveFor7[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 3 Room", hhClosedDestination + "a_hhClosed_3_room_wav", defaultMidiNotes[14], curveFor7[2], curveFor7[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 4 Room", hhClosedDestination + "a_hhClosed_4_room_wav", defaultMidiNotes[14], curveFor7[3], curveFor7[4] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 5 Room", hhClosedDestination + "a_hhClosed_5_room_wav", defaultMidiNotes[14], curveFor7[4], curveFor7[5] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 6 Room", hhClosedDestination + "a_hhClosed_6_room_wav", defaultMidiNotes[14], curveFor7[5], curveFor7[6] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 7 Room", hhClosedDestination + "a_hhClosed_7_room_wav", defaultMidiNotes[14], curveFor7[6], curveFor7[7] - 1, hhRelease, hhClosedMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Closed 1 Bleed", hhClosedDestination + "a_hhClosed_1_bleed_wav", defaultMidiNotes[14], curveFor7[0], curveFor7[1] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 2 Bleed", hhClosedDestination + "a_hhClosed_2_bleed_wav", defaultMidiNotes[14], curveFor7[1], curveFor7[2] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 3 Bleed", hhClosedDestination + "a_hhClosed_3_bleed_wav", defaultMidiNotes[14], curveFor7[2], curveFor7[3] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 4 Bleed", hhClosedDestination + "a_hhClosed_4_bleed_wav", defaultMidiNotes[14], curveFor7[3], curveFor7[4] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 5 Bleed", hhClosedDestination + "a_hhClosed_5_bleed_wav", defaultMidiNotes[14], curveFor7[4], curveFor7[5] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 6 Bleed", hhClosedDestination + "a_hhClosed_6_bleed_wav", defaultMidiNotes[14], curveFor7[5], curveFor7[6] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 7 Bleed", hhClosedDestination + "a_hhClosed_7_bleed_wav", defaultMidiNotes[14], curveFor7[6], curveFor7[7] - 1, hhRelease, hhClosedMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Closed 1 Binaural", hhClosedDestination + "a_hhClosed_1_binaural_wav", defaultMidiNotes[14], curveFor7[0], curveFor7[1] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 2 Binaural", hhClosedDestination + "a_hhClosed_2_binaural_wav", defaultMidiNotes[14], curveFor7[1], curveFor7[2] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 3 Binaural", hhClosedDestination + "a_hhClosed_3_binaural_wav", defaultMidiNotes[14], curveFor7[2], curveFor7[3] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 4 Binaural", hhClosedDestination + "a_hhClosed_4_binaural_wav", defaultMidiNotes[14], curveFor7[3], curveFor7[4] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 5 Binaural", hhClosedDestination + "a_hhClosed_5_binaural_wav", defaultMidiNotes[14], curveFor7[4], curveFor7[5] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 6 Binaural", hhClosedDestination + "a_hhClosed_6_binaural_wav", defaultMidiNotes[14], curveFor7[5], curveFor7[6] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Closed 7 Binaural", hhClosedDestination + "a_hhClosed_7_binaural_wav", defaultMidiNotes[14], curveFor7[6], curveFor7[7] - 1, hhRelease, hhClosedMaxLen, "Binaural", samplers, formatManager);

            double hhHalfMaxLen = 1.6;
            string hhHalfDestination = hhAllDestination + "a_hhHalf/";
            addSample("Acoustic HH Half 1 Close", hhHalfDestination + "a_hhHalf_1_close_wav", defaultMidiNotes[15], curveFor6[0], curveFor6[1] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 2 Close", hhHalfDestination + "a_hhHalf_2_close_wav", defaultMidiNotes[15], curveFor6[1], curveFor6[2] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 3 Close", hhHalfDestination + "a_hhHalf_3_close_wav", defaultMidiNotes[15], curveFor6[2], curveFor6[3] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 4 Close", hhHalfDestination + "a_hhHalf_4_close_wav", defaultMidiNotes[15], curveFor6[3], curveFor6[4] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 5 Close", hhHalfDestination + "a_hhHalf_5_close_wav", defaultMidiNotes[15], curveFor6[4], curveFor6[5] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 6 Close", hhHalfDestination + "a_hhHalf_6_close_wav", defaultMidiNotes[15], curveFor6[5], curveFor6[6] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Half 1 OH", hhHalfDestination + "a_hhHalf_1_oh_wav", defaultMidiNotes[15], curveFor6[0], curveFor6[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 2 OH", hhHalfDestination + "a_hhHalf_2_oh_wav", defaultMidiNotes[15], curveFor6[1], curveFor6[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 3 OH", hhHalfDestination + "a_hhHalf_3_oh_wav", defaultMidiNotes[15], curveFor6[2], curveFor6[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 4 OH", hhHalfDestination + "a_hhHalf_4_oh_wav", defaultMidiNotes[15], curveFor6[3], curveFor6[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 5 OH", hhHalfDestination + "a_hhHalf_5_oh_wav", defaultMidiNotes[15], curveFor6[4], curveFor6[5] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 6 OH", hhHalfDestination + "a_hhHalf_6_oh_wav", defaultMidiNotes[15], curveFor6[5], curveFor6[6] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Half 1 Room", hhHalfDestination + "a_hhHalf_1_room_wav", defaultMidiNotes[15], curveFor6[0], curveFor6[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 2 Room", hhHalfDestination + "a_hhHalf_2_room_wav", defaultMidiNotes[15], curveFor6[1], curveFor6[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 3 Room", hhHalfDestination + "a_hhHalf_3_room_wav", defaultMidiNotes[15], curveFor6[2], curveFor6[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 4 Room", hhHalfDestination + "a_hhHalf_4_room_wav", defaultMidiNotes[15], curveFor6[3], curveFor6[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 5 Room", hhHalfDestination + "a_hhHalf_5_room_wav", defaultMidiNotes[15], curveFor6[4], curveFor6[5] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 6 Room", hhHalfDestination + "a_hhHalf_6_room_wav", defaultMidiNotes[15], curveFor6[5], curveFor6[6] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Half 1 Bleed", hhHalfDestination + "a_hhHalf_1_bleed_wav", defaultMidiNotes[15], curveFor6[0], curveFor6[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 2 Bleed", hhHalfDestination + "a_hhHalf_2_bleed_wav", defaultMidiNotes[15], curveFor6[1], curveFor6[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 3 Bleed", hhHalfDestination + "a_hhHalf_3_bleed_wav", defaultMidiNotes[15], curveFor6[2], curveFor6[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 4 Bleed", hhHalfDestination + "a_hhHalf_4_bleed_wav", defaultMidiNotes[15], curveFor6[3], curveFor6[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 5 Bleed", hhHalfDestination + "a_hhHalf_5_bleed_wav", defaultMidiNotes[15], curveFor6[4], curveFor6[5] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 6 Bleed", hhHalfDestination + "a_hhHalf_6_bleed_wav", defaultMidiNotes[15], curveFor6[5], curveFor6[6] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Half 1 Binaural", hhHalfDestination + "a_hhHalf_1_binaural_wav", defaultMidiNotes[15], curveFor6[0], curveFor6[1] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Half 2 Binaural", hhHalfDestination + "a_hhHalf_2_binaural_wav", defaultMidiNotes[15], curveFor6[1], curveFor6[2] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Half 3 Binaural", hhHalfDestination + "a_hhHalf_3_binaural_wav", defaultMidiNotes[15], curveFor6[2], curveFor6[3] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Half 4 Binaural", hhHalfDestination + "a_hhHalf_4_binaural_wav", defaultMidiNotes[15], curveFor6[3], curveFor6[4] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Half 5 Binaural", hhHalfDestination + "a_hhHalf_5_binaural_wav", defaultMidiNotes[15], curveFor6[4], curveFor6[5] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Half 6 Binaural", hhHalfDestination + "a_hhHalf_6_binaural_wav", defaultMidiNotes[15], curveFor6[5], curveFor6[6] - 1, hhRelease, hhHalfMaxLen, "Binaural", samplers, formatManager);

            string hhOpenDestination = hhAllDestination + "a_hhOpen/";
            addSample("Acoustic HH Open 1 Close", hhOpenDestination + "a_hhOpen_1_close_wav", defaultMidiNotes[16], curveFor5[0], curveFor5[1] - 1, hhRelease, 6.6, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Open 2 Close", hhOpenDestination + "a_hhOpen_2_close_wav", defaultMidiNotes[16], curveFor5[1], curveFor5[2] - 1, hhRelease, 8.5, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Open 3 Close", hhOpenDestination + "a_hhOpen_3_close_wav", defaultMidiNotes[16], curveFor5[2], curveFor5[3] - 1, hhRelease, 8.5, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Open 4 Close", hhOpenDestination + "a_hhOpen_4_close_wav", defaultMidiNotes[16], curveFor5[3], curveFor5[4] - 1, hhRelease, 9.1, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Open 5 Close", hhOpenDestination + "a_hhOpen_5_close_wav", defaultMidiNotes[16], curveFor5[4], curveFor5[5] - 1, hhRelease, 9.6, "HHClose", samplers, formatManager);
            addSample("Acoustic HH Open 1 OH", hhOpenDestination + "a_hhOpen_1_oh_wav", defaultMidiNotes[16], curveFor5[0], curveFor5[1] - 1, hhRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Open 2 OH", hhOpenDestination + "a_hhOpen_2_oh_wav", defaultMidiNotes[16], curveFor5[1], curveFor5[2] - 1, hhRelease, 8.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Open 3 OH", hhOpenDestination + "a_hhOpen_3_oh_wav", defaultMidiNotes[16], curveFor5[2], curveFor5[3] - 1, hhRelease, 8.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Open 4 OH", hhOpenDestination + "a_hhOpen_4_oh_wav", defaultMidiNotes[16], curveFor5[3], curveFor5[4] - 1, hhRelease, 9.1, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Open 5 OH", hhOpenDestination + "a_hhOpen_5_oh_wav", defaultMidiNotes[16], curveFor5[4], curveFor5[5] - 1, hhRelease, 9.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic HH Open 1 Room", hhOpenDestination + "a_hhOpen_1_room_wav", defaultMidiNotes[16], curveFor5[0], curveFor5[1] - 1, hhRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Open 2 Room", hhOpenDestination + "a_hhOpen_2_room_wav", defaultMidiNotes[16], curveFor5[1], curveFor5[2] - 1, hhRelease, 8.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Open 3 Room", hhOpenDestination + "a_hhOpen_3_room_wav", defaultMidiNotes[16], curveFor5[2], curveFor5[3] - 1, hhRelease, 8.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Open 4 Room", hhOpenDestination + "a_hhOpen_4_room_wav", defaultMidiNotes[16], curveFor5[3], curveFor5[4] - 1, hhRelease, 9.1, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Open 5 Room", hhOpenDestination + "a_hhOpen_5_room_wav", defaultMidiNotes[16], curveFor5[4], curveFor5[5] - 1, hhRelease, 9.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic HH Open 1 Bleed", hhOpenDestination + "a_hhOpen_1_bleed_wav", defaultMidiNotes[16], curveFor5[0], curveFor5[1] - 1, hhRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Open 2 Bleed", hhOpenDestination + "a_hhOpen_2_bleed_wav", defaultMidiNotes[16], curveFor5[1], curveFor5[2] - 1, hhRelease, 8.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Open 3 Bleed", hhOpenDestination + "a_hhOpen_3_bleed_wav", defaultMidiNotes[16], curveFor5[2], curveFor5[3] - 1, hhRelease, 8.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Open 4 Bleed", hhOpenDestination + "a_hhOpen_4_bleed_wav", defaultMidiNotes[16], curveFor5[3], curveFor5[4] - 1, hhRelease, 9.1, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Open 5 Bleed", hhOpenDestination + "a_hhOpen_5_bleed_wav", defaultMidiNotes[16], curveFor5[4], curveFor5[5] - 1, hhRelease, 9.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic HH Open 1 Binaural", hhOpenDestination + "a_hhOpen_1_binaural_wav", defaultMidiNotes[16], curveFor5[0], curveFor5[1] - 1, hhRelease, 6.6, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Open 2 Binaural", hhOpenDestination + "a_hhOpen_2_binaural_wav", defaultMidiNotes[16], curveFor5[1], curveFor5[2] - 1, hhRelease, 8.5, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Open 3 Binaural", hhOpenDestination + "a_hhOpen_3_binaural_wav", defaultMidiNotes[16], curveFor5[2], curveFor5[3] - 1, hhRelease, 8.5, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Open 4 Binaural", hhOpenDestination + "a_hhOpen_4_binaural_wav", defaultMidiNotes[16], curveFor5[3], curveFor5[4] - 1, hhRelease, 9.1, "Binaural", samplers, formatManager);
            addSample("Acoustic HH Open 5 Binaural", hhOpenDestination + "a_hhOpen_5_binaural_wav", defaultMidiNotes[16], curveFor5[4], curveFor5[5] - 1, hhRelease, 9.6, "Binaural", samplers, formatManager);

            double rideRelease = 0.7;
            string rideAllDestination = acousticDestination + "a_rideAll/";
            string ridePointDestination = rideAllDestination + "a_ridePoint/";
            addSample("Acoustic Ride Point 1 OH", ridePointDestination + "a_ridePoint_1_oh_wav", defaultMidiNotes[18], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.50, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 2 OH", ridePointDestination + "a_ridePoint_2_oh_wav", defaultMidiNotes[18], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 3 OH", ridePointDestination + "a_ridePoint_3_oh_wav", defaultMidiNotes[18], curveFor6[2], curveFor6[3] - 1, rideRelease, 8.50, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 6 OH", ridePointDestination + "a_ridePoint_6_oh_wav", defaultMidiNotes[18], curveFor6[5], curveFor6[6] - 1, rideRelease, 9.10, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 4 OH", ridePointDestination + "a_ridePoint_4_oh_wav", defaultMidiNotes[18], curveFor6[3], curveFor6[4] - 1, rideRelease, 10.3, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 5 OH", ridePointDestination + "a_ridePoint_5_oh_wav", defaultMidiNotes[18], curveFor6[4], curveFor6[5] - 1, rideRelease, 12.1, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Point 1 Room", ridePointDestination + "a_ridePoint_1_room_wav", defaultMidiNotes[18], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.50, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 2 Room", ridePointDestination + "a_ridePoint_2_room_wav", defaultMidiNotes[18], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 3 Room", ridePointDestination + "a_ridePoint_3_room_wav", defaultMidiNotes[18], curveFor6[2], curveFor6[3] - 1, rideRelease, 8.50, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 4 Room", ridePointDestination + "a_ridePoint_4_room_wav", defaultMidiNotes[18], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 5 Room", ridePointDestination + "a_ridePoint_5_room_wav", defaultMidiNotes[18], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.3, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 6 Room", ridePointDestination + "a_ridePoint_6_room_wav", defaultMidiNotes[18], curveFor6[5], curveFor6[6] - 1, rideRelease, 12.1, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Point 1 Bleed", ridePointDestination + "a_ridePoint_1_bleed_wav", defaultMidiNotes[18], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.50, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 2 Bleed", ridePointDestination + "a_ridePoint_2_bleed_wav", defaultMidiNotes[18], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 3 Bleed", ridePointDestination + "a_ridePoint_3_bleed_wav", defaultMidiNotes[18], curveFor6[2], curveFor6[3] - 1, rideRelease, 8.50, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 4 Bleed", ridePointDestination + "a_ridePoint_4_bleed_wav", defaultMidiNotes[18], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 5 Bleed", ridePointDestination + "a_ridePoint_5_bleed_wav", defaultMidiNotes[18], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.3, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 6 Bleed", ridePointDestination + "a_ridePoint_6_bleed_wav", defaultMidiNotes[18], curveFor6[5], curveFor6[6] - 1, rideRelease, 12.1, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Point 1 Binaural", ridePointDestination + "a_ridePoint_1_binaural_wav", defaultMidiNotes[18], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.50, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Point 2 Binaural", ridePointDestination + "a_ridePoint_2_binaural_wav", defaultMidiNotes[18], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Point 3 Binaural", ridePointDestination + "a_ridePoint_3_binaural_wav", defaultMidiNotes[18], curveFor6[2], curveFor6[3] - 1, rideRelease, 8.50, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Point 4 Binaural", ridePointDestination + "a_ridePoint_4_binaural_wav", defaultMidiNotes[18], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Point 5 Binaural", ridePointDestination + "a_ridePoint_5_binaural_wav", defaultMidiNotes[18], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.3, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Point 6 Binaural", ridePointDestination + "a_ridePoint_6_binaural_wav", defaultMidiNotes[18], curveFor6[5], curveFor6[6] - 1, rideRelease, 12.1, "Binaural", samplers, formatManager);

            string rideBellDestination = rideAllDestination + "a_rideBell/";
            addSample("Acoustic Ride Bell 1 OH", rideBellDestination + "a_rideBell_1_oh_wav", defaultMidiNotes[19], curveFor6[0], curveFor6[1] - 1, rideRelease, 5.50, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 2 OH", rideBellDestination + "a_rideBell_2_oh_wav", defaultMidiNotes[19], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 3 OH", rideBellDestination + "a_rideBell_3_oh_wav", defaultMidiNotes[19], curveFor6[2], curveFor6[3] - 1, rideRelease, 7.90, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 6 OH", rideBellDestination + "a_rideBell_6_oh_wav", defaultMidiNotes[19], curveFor6[5], curveFor6[6] - 1, rideRelease, 9.10, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 4 OH", rideBellDestination + "a_rideBell_4_oh_wav", defaultMidiNotes[19], curveFor6[3], curveFor6[4] - 1, rideRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 5 OH", rideBellDestination + "a_rideBell_5_oh_wav", defaultMidiNotes[19], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.3, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Bell 1 Room", rideBellDestination + "a_rideBell_1_room_wav", defaultMidiNotes[19], curveFor6[0], curveFor6[1] - 1, rideRelease, 5.50, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 2 Room", rideBellDestination + "a_rideBell_2_room_wav", defaultMidiNotes[19], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 3 Room", rideBellDestination + "a_rideBell_3_room_wav", defaultMidiNotes[19], curveFor6[2], curveFor6[3] - 1, rideRelease, 7.90, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 4 Room", rideBellDestination + "a_rideBell_4_room_wav", defaultMidiNotes[19], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 5 Room", rideBellDestination + "a_rideBell_5_room_wav", defaultMidiNotes[19], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 6 Room", rideBellDestination + "a_rideBell_6_room_wav", defaultMidiNotes[19], curveFor6[5], curveFor6[6] - 1, rideRelease, 10.3, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Bell 1 Bleed", rideBellDestination + "a_rideBell_1_bleed_wav", defaultMidiNotes[19], curveFor6[0], curveFor6[1] - 1, rideRelease, 5.50, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 2 Bleed", rideBellDestination + "a_rideBell_2_bleed_wav", defaultMidiNotes[19], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 3 Bleed", rideBellDestination + "a_rideBell_3_bleed_wav", defaultMidiNotes[19], curveFor6[2], curveFor6[3] - 1, rideRelease, 7.90, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 4 Bleed", rideBellDestination + "a_rideBell_4_bleed_wav", defaultMidiNotes[19], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 5 Bleed", rideBellDestination + "a_rideBell_5_bleed_wav", defaultMidiNotes[19], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.9, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 6 Bleed", rideBellDestination + "a_rideBell_6_bleed_wav", defaultMidiNotes[19], curveFor6[5], curveFor6[6] - 1, rideRelease, 10.3, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Bell 1 Binaural", rideBellDestination + "a_rideBell_1_binaural_wav", defaultMidiNotes[19], curveFor6[0], curveFor6[1] - 1, rideRelease, 5.50, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Bell 2 Binaural", rideBellDestination + "a_rideBell_2_binaural_wav", defaultMidiNotes[19], curveFor6[1], curveFor6[2] - 1, rideRelease, 6.60, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Bell 3 Binaural", rideBellDestination + "a_rideBell_3_binaural_wav", defaultMidiNotes[19], curveFor6[2], curveFor6[3] - 1, rideRelease, 7.90, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Bell 4 Binaural", rideBellDestination + "a_rideBell_4_binaural_wav", defaultMidiNotes[19], curveFor6[3], curveFor6[4] - 1, rideRelease, 9.10, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Bell 5 Binaural", rideBellDestination + "a_rideBell_5_binaural_wav", defaultMidiNotes[19], curveFor6[4], curveFor6[5] - 1, rideRelease, 10.9, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Bell 6 Binaural", rideBellDestination + "a_rideBell_6_binaural_wav", defaultMidiNotes[19], curveFor6[5], curveFor6[6] - 1, rideRelease, 10.3, "Binaural", samplers, formatManager);

            double rideOpenRelease = 4.5;
            string rideOpenDestination = rideAllDestination + "a_rideOpen/";
            addSample("Acoustic Ride Open 1 OH", rideOpenDestination + "a_rideOpen_1_oh_wav", defaultMidiNotes[20], curveFor6[0], curveFor6[1] - 1, rideOpenRelease, 4.50, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 2 OH", rideOpenDestination + "a_rideOpen_2_oh_wav", defaultMidiNotes[20], curveFor6[1], curveFor6[2] - 1, rideOpenRelease, 8.50, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 3 OH", rideOpenDestination + "a_rideOpen_3_oh_wav", defaultMidiNotes[20], curveFor6[2], curveFor6[3] - 1, rideOpenRelease, 9.40, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 6 OH", rideOpenDestination + "a_rideOpen_6_oh_wav", defaultMidiNotes[20], curveFor6[5], curveFor6[6] - 1, rideOpenRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 4 OH", rideOpenDestination + "a_rideOpen_4_oh_wav", defaultMidiNotes[20], curveFor6[3], curveFor6[4] - 1, rideOpenRelease, 12.7, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 5 OH", rideOpenDestination + "a_rideOpen_5_oh_wav", defaultMidiNotes[20], curveFor6[4], curveFor6[5] - 1, rideOpenRelease, 10.9, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Ride Open 1 Room", rideOpenDestination + "a_rideOpen_1_room_wav", defaultMidiNotes[20], curveFor6[0], curveFor6[1] - 1, rideOpenRelease, 4.50, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 2 Room", rideOpenDestination + "a_rideOpen_2_room_wav", defaultMidiNotes[20], curveFor6[1], curveFor6[2] - 1, rideOpenRelease, 8.50, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 3 Room", rideOpenDestination + "a_rideOpen_3_room_wav", defaultMidiNotes[20], curveFor6[2], curveFor6[3] - 1, rideOpenRelease, 9.40, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 4 Room", rideOpenDestination + "a_rideOpen_4_room_wav", defaultMidiNotes[20], curveFor6[3], curveFor6[4] - 1, rideOpenRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 5 Room", rideOpenDestination + "a_rideOpen_5_room_wav", defaultMidiNotes[20], curveFor6[4], curveFor6[5] - 1, rideOpenRelease, 12.7, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 6 Room", rideOpenDestination + "a_rideOpen_6_room_wav", defaultMidiNotes[20], curveFor6[5], curveFor6[6] - 1, rideOpenRelease, 10.9, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Ride Open 1 Bleed", rideOpenDestination + "a_rideOpen_1_bleed_wav", defaultMidiNotes[20], curveFor6[0], curveFor6[1] - 1, rideOpenRelease, 4.50, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 2 Bleed", rideOpenDestination + "a_rideOpen_2_bleed_wav", defaultMidiNotes[20], curveFor6[1], curveFor6[2] - 1, rideOpenRelease, 8.50, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 3 Bleed", rideOpenDestination + "a_rideOpen_3_bleed_wav", defaultMidiNotes[20], curveFor6[2], curveFor6[3] - 1, rideOpenRelease, 9.40, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 4 Bleed", rideOpenDestination + "a_rideOpen_4_bleed_wav", defaultMidiNotes[20], curveFor6[3], curveFor6[4] - 1, rideOpenRelease, 10.9, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 5 Bleed", rideOpenDestination + "a_rideOpen_5_bleed_wav", defaultMidiNotes[20], curveFor6[4], curveFor6[5] - 1, rideOpenRelease, 12.7, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 6 Bleed", rideOpenDestination + "a_rideOpen_6_bleed_wav", defaultMidiNotes[20], curveFor6[5], curveFor6[6] - 1, rideOpenRelease, 10.9, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Ride Open 1 Binaural", rideOpenDestination + "a_rideOpen_1_binaural_wav", defaultMidiNotes[20], curveFor6[0], curveFor6[1] - 1, rideOpenRelease, 4.50, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Open 2 Binaural", rideOpenDestination + "a_rideOpen_2_binaural_wav", defaultMidiNotes[20], curveFor6[1], curveFor6[2] - 1, rideOpenRelease, 8.50, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Open 3 Binaural", rideOpenDestination + "a_rideOpen_3_binaural_wav", defaultMidiNotes[20], curveFor6[2], curveFor6[3] - 1, rideOpenRelease, 9.40, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Open 4 Binaural", rideOpenDestination + "a_rideOpen_4_binaural_wav", defaultMidiNotes[20], curveFor6[3], curveFor6[4] - 1, rideOpenRelease, 10.9, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Open 5 Binaural", rideOpenDestination + "a_rideOpen_5_binaural_wav", defaultMidiNotes[20], curveFor6[4], curveFor6[5] - 1, rideOpenRelease, 12.7, "Binaural", samplers, formatManager);
            addSample("Acoustic Ride Open 6 Binaural", rideOpenDestination + "a_rideOpen_6_binaural_wav", defaultMidiNotes[20], curveFor6[5], curveFor6[6] - 1, rideOpenRelease, 10.9, "Binaural", samplers, formatManager);

            string crashAllDestination = acousticDestination + "a_crashAll/";
            string crashPointDestination = crashAllDestination + "a_crashPoint/";
            addSample("Acoustic Crash Point 1 OH", crashPointDestination + "a_crashPoint_1_oh_wav", defaultMidiNotes[21], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.2, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 2 OH", crashPointDestination + "a_crashPoint_2_oh_wav", defaultMidiNotes[21], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 3 OH", crashPointDestination + "a_crashPoint_3_oh_wav", defaultMidiNotes[21], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 6 OH", crashPointDestination + "a_crashPoint_6_oh_wav", defaultMidiNotes[21], curveFor6[5], curveFor6[6] - 1, rideRelease, 6.0, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 4 OH", crashPointDestination + "a_crashPoint_4_oh_wav", defaultMidiNotes[21], curveFor6[3], curveFor6[4] - 1, rideRelease, 7.3, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 5 OH", crashPointDestination + "a_crashPoint_5_oh_wav", defaultMidiNotes[21], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.3, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Point 1 Room", crashPointDestination + "a_crashPoint_1_room_wav", defaultMidiNotes[21], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.2, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 2 Room", crashPointDestination + "a_crashPoint_2_room_wav", defaultMidiNotes[21], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 3 Room", crashPointDestination + "a_crashPoint_3_room_wav", defaultMidiNotes[21], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 4 Room", crashPointDestination + "a_crashPoint_4_room_wav", defaultMidiNotes[21], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.0, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 5 Room", crashPointDestination + "a_crashPoint_5_room_wav", defaultMidiNotes[21], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.3, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 6 Room", crashPointDestination + "a_crashPoint_6_room_wav", defaultMidiNotes[21], curveFor6[5], curveFor6[6] - 1, rideRelease, 7.3, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Point 1 Bleed", crashPointDestination + "a_crashPoint_1_bleed_wav", defaultMidiNotes[21], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.2, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 2 Bleed", crashPointDestination + "a_crashPoint_2_bleed_wav", defaultMidiNotes[21], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 3 Bleed", crashPointDestination + "a_crashPoint_3_bleed_wav", defaultMidiNotes[21], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 4 Bleed", crashPointDestination + "a_crashPoint_4_bleed_wav", defaultMidiNotes[21], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.0, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 5 Bleed", crashPointDestination + "a_crashPoint_5_bleed_wav", defaultMidiNotes[21], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.3, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 6 Bleed", crashPointDestination + "a_crashPoint_6_bleed_wav", defaultMidiNotes[21], curveFor6[5], curveFor6[6] - 1, rideRelease, 7.3, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Point 1 Binaural", crashPointDestination + "a_crashPoint_1_binaural_wav", defaultMidiNotes[21], curveFor6[0], curveFor6[1] - 1, rideRelease, 4.2, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Point 2 Binaural", crashPointDestination + "a_crashPoint_2_binaural_wav", defaultMidiNotes[21], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.5, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Point 3 Binaural", crashPointDestination + "a_crashPoint_3_binaural_wav", defaultMidiNotes[21], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Point 4 Binaural", crashPointDestination + "a_crashPoint_4_binaural_wav", defaultMidiNotes[21], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.0, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Point 5 Binaural", crashPointDestination + "a_crashPoint_5_binaural_wav", defaultMidiNotes[21], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.3, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Point 6 Binaural", crashPointDestination + "a_crashPoint_6_binaural_wav", defaultMidiNotes[21], curveFor6[5], curveFor6[6] - 1, rideRelease, 7.3, "Binaural", samplers, formatManager);

            string crashBellDestination = crashAllDestination + "a_crashBell/";
            addSample("Acoustic Crash Bell 1 OH", crashBellDestination + "a_crashBell_1_oh_wav", defaultMidiNotes[22], curveFor6[0], curveFor6[1] - 1, rideRelease, 3.7, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 2 OH", crashBellDestination + "a_crashBell_2_oh_wav", defaultMidiNotes[22], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.2, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 3 OH", crashBellDestination + "a_crashBell_3_oh_wav", defaultMidiNotes[22], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 6 OH", crashBellDestination + "a_crashBell_6_oh_wav", defaultMidiNotes[22], curveFor6[5], curveFor6[6] - 1, rideRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 4 OH", crashBellDestination + "a_crashBell_4_oh_wav", defaultMidiNotes[22], curveFor6[3], curveFor6[4] - 1, rideRelease, 7.9, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 5 OH", crashBellDestination + "a_crashBell_5_oh_wav", defaultMidiNotes[22], curveFor6[4], curveFor6[5] - 1, rideRelease, 8.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Bell 1 Room", crashBellDestination + "a_crashBell_1_room_wav", defaultMidiNotes[22], curveFor6[0], curveFor6[1] - 1, rideRelease, 3.7, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 2 Room", crashBellDestination + "a_crashBell_2_room_wav", defaultMidiNotes[22], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.2, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 3 Room", crashBellDestination + "a_crashBell_3_room_wav", defaultMidiNotes[22], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 4 Room", crashBellDestination + "a_crashBell_4_room_wav", defaultMidiNotes[22], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 5 Room", crashBellDestination + "a_crashBell_5_room_wav", defaultMidiNotes[22], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.9, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 6 Room", crashBellDestination + "a_crashBell_6_room_wav", defaultMidiNotes[22], curveFor6[5], curveFor6[6] - 1, rideRelease, 8.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Bell 1 Bleed", crashBellDestination + "a_crashBell_1_bleed_wav", defaultMidiNotes[22], curveFor6[0], curveFor6[1] - 1, rideRelease, 3.7, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 2 Bleed", crashBellDestination + "a_crashBell_2_bleed_wav", defaultMidiNotes[22], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.2, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 3 Bleed", crashBellDestination + "a_crashBell_3_bleed_wav", defaultMidiNotes[22], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 4 Bleed", crashBellDestination + "a_crashBell_4_bleed_wav", defaultMidiNotes[22], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 5 Bleed", crashBellDestination + "a_crashBell_5_bleed_wav", defaultMidiNotes[22], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.9, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 6 Bleed", crashBellDestination + "a_crashBell_6_bleed_wav", defaultMidiNotes[22], curveFor6[5], curveFor6[6] - 1, rideRelease, 8.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Bell 1 Binaural", crashBellDestination + "a_crashBell_1_binaural_wav", defaultMidiNotes[22], curveFor6[0], curveFor6[1] - 1, rideRelease, 3.7, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Bell 2 Binaural", crashBellDestination + "a_crashBell_2_binaural_wav", defaultMidiNotes[22], curveFor6[1], curveFor6[2] - 1, rideRelease, 4.2, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Bell 3 Binaural", crashBellDestination + "a_crashBell_3_binaural_wav", defaultMidiNotes[22], curveFor6[2], curveFor6[3] - 1, rideRelease, 4.5, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Bell 4 Binaural", crashBellDestination + "a_crashBell_4_binaural_wav", defaultMidiNotes[22], curveFor6[3], curveFor6[4] - 1, rideRelease, 6.6, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Bell 5 Binaural", crashBellDestination + "a_crashBell_5_binaural_wav", defaultMidiNotes[22], curveFor6[4], curveFor6[5] - 1, rideRelease, 7.9, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Bell 6 Binaural", crashBellDestination + "a_crashBell_6_binaural_wav", defaultMidiNotes[22], curveFor6[5], curveFor6[6] - 1, rideRelease, 8.5, "Binaural", samplers, formatManager);

            double crashOpenRelease = 0.15;
            string crashOpenDestination = crashAllDestination + "a_crashOpen/";
            addSample("Acoustic Crash Open 1 OH", crashOpenDestination + "a_crashOpen_1_oh_wav", defaultMidiNotes[23], curveFor6[0], curveFor6[1] - 1, crashOpenRelease, 5.5, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 2 OH", crashOpenDestination + "a_crashOpen_2_oh_wav", defaultMidiNotes[23], curveFor6[1], curveFor6[2] - 1, crashOpenRelease, 6.8, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 3 OH", crashOpenDestination + "a_crashOpen_3_oh_wav", defaultMidiNotes[23], curveFor6[2], curveFor6[3] - 1, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 6 OH", crashOpenDestination + "a_crashOpen_6_oh_wav", defaultMidiNotes[23], curveFor6[5], curveFor6[6] - 1, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 4 OH", crashOpenDestination + "a_crashOpen_4_oh_wav", defaultMidiNotes[23], curveFor6[3], curveFor6[4] - 1, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 5 OH", crashOpenDestination + "a_crashOpen_5_oh_wav", defaultMidiNotes[23], curveFor6[4], curveFor6[5] - 1, crashOpenRelease, 6.6, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Crash Open 1 Room", crashOpenDestination + "a_crashOpen_1_room_wav", defaultMidiNotes[23], curveFor6[0], curveFor6[1] - 1, crashOpenRelease, 5.5, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 2 Room", crashOpenDestination + "a_crashOpen_2_room_wav", defaultMidiNotes[23], curveFor6[1], curveFor6[2] - 1, crashOpenRelease, 6.8, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 3 Room", crashOpenDestination + "a_crashOpen_3_room_wav", defaultMidiNotes[23], curveFor6[2], curveFor6[3] - 1, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 4 Room", crashOpenDestination + "a_crashOpen_4_room_wav", defaultMidiNotes[23], curveFor6[3], curveFor6[4] - 1, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 5 Room", crashOpenDestination + "a_crashOpen_5_room_wav", defaultMidiNotes[23], curveFor6[4], curveFor6[5] - 1, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 6 Room", crashOpenDestination + "a_crashOpen_6_room_wav", defaultMidiNotes[23], curveFor6[5], curveFor6[6] - 1, crashOpenRelease, 6.6, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Crash Open 1 Bleed", crashOpenDestination + "a_crashOpen_1_bleed_wav", defaultMidiNotes[23], curveFor6[0], curveFor6[1] - 1, crashOpenRelease, 5.5, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 2 Bleed", crashOpenDestination + "a_crashOpen_2_bleed_wav", defaultMidiNotes[23], curveFor6[1], curveFor6[2] - 1, crashOpenRelease, 6.8, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 3 Bleed", crashOpenDestination + "a_crashOpen_3_bleed_wav", defaultMidiNotes[23], curveFor6[2], curveFor6[3] - 1, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 4 Bleed", crashOpenDestination + "a_crashOpen_4_bleed_wav", defaultMidiNotes[23], curveFor6[3], curveFor6[4] - 1, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 5 Bleed", crashOpenDestination + "a_crashOpen_5_bleed_wav", defaultMidiNotes[23], curveFor6[4], curveFor6[5] - 1, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 6 Bleed", crashOpenDestination + "a_crashOpen_6_bleed_wav", defaultMidiNotes[23], curveFor6[5], curveFor6[6] - 1, crashOpenRelease, 6.6, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Crash Open 1 Binaural", crashOpenDestination + "a_crashOpen_1_binaural_wav", defaultMidiNotes[23], curveFor6[0], curveFor6[1] - 1, crashOpenRelease, 5.5, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Open 2 Binaural", crashOpenDestination + "a_crashOpen_2_binaural_wav", defaultMidiNotes[23], curveFor6[1], curveFor6[2] - 1, crashOpenRelease, 6.8, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Open 3 Binaural", crashOpenDestination + "a_crashOpen_3_binaural_wav", defaultMidiNotes[23], curveFor6[2], curveFor6[3] - 1, crashOpenRelease, 6.6, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Open 4 Binaural", crashOpenDestination + "a_crashOpen_4_binaural_wav", defaultMidiNotes[23], curveFor6[3], curveFor6[4] - 1, crashOpenRelease, 6.6, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Open 5 Binaural", crashOpenDestination + "a_crashOpen_5_binaural_wav", defaultMidiNotes[23], curveFor6[4], curveFor6[5] - 1, crashOpenRelease, 6.6, "Binaural", samplers, formatManager);
            addSample("Acoustic Crash Open 6 Binaural", crashOpenDestination + "a_crashOpen_6_binaural_wav", defaultMidiNotes[23], curveFor6[5], curveFor6[6] - 1, crashOpenRelease, 6.6, "Binaural", samplers, formatManager);

            double stackMaxLen = 0.6;
            string stackAllDestination = acousticDestination + "a_stackAll/";
            string stackClosedDestination = stackAllDestination + "a_stackClosed/";
            addSample("Acoustic Stack Closed 1 OH", stackClosedDestination + "a_stackClosed_1_oh_wav", defaultMidiNotes[24], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Closed 2 OH", stackClosedDestination + "a_stackClosed_2_oh_wav", defaultMidiNotes[24], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Closed 3 OH", stackClosedDestination + "a_stackClosed_3_oh_wav", defaultMidiNotes[24], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Closed 4 OH", stackClosedDestination + "a_stackClosed_4_oh_wav", defaultMidiNotes[24], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Closed 5 OH", stackClosedDestination + "a_stackClosed_5_oh_wav", defaultMidiNotes[24], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Closed 1 Room", stackClosedDestination + "a_stackClosed_1_room_wav", defaultMidiNotes[24], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Closed 2 Room", stackClosedDestination + "a_stackClosed_2_room_wav", defaultMidiNotes[24], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Closed 3 Room", stackClosedDestination + "a_stackClosed_3_room_wav", defaultMidiNotes[24], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Closed 4 Room", stackClosedDestination + "a_stackClosed_4_room_wav", defaultMidiNotes[24], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Closed 5 Room", stackClosedDestination + "a_stackClosed_5_room_wav", defaultMidiNotes[24], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Closed 1 Bleed", stackClosedDestination + "a_stackClosed_1_bleed_wav", defaultMidiNotes[24], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Closed 2 Bleed", stackClosedDestination + "a_stackClosed_2_bleed_wav", defaultMidiNotes[24], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Closed 3 Bleed", stackClosedDestination + "a_stackClosed_3_bleed_wav", defaultMidiNotes[24], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Closed 4 Bleed", stackClosedDestination + "a_stackClosed_4_bleed_wav", defaultMidiNotes[24], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Closed 5 Bleed", stackClosedDestination + "a_stackClosed_5_bleed_wav", defaultMidiNotes[24], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Closed 1 Binaural", stackClosedDestination + "a_stackClosed_1_binaural_wav", defaultMidiNotes[24], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Closed 2 Binaural", stackClosedDestination + "a_stackClosed_2_binaural_wav", defaultMidiNotes[24], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Closed 3 Binaural", stackClosedDestination + "a_stackClosed_3_binaural_wav", defaultMidiNotes[24], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Closed 4 Binaural", stackClosedDestination + "a_stackClosed_4_binaural_wav", defaultMidiNotes[24], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Closed 5 Binaural", stackClosedDestination + "a_stackClosed_5_binaural_wav", defaultMidiNotes[24], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);

            string stackOpenDestination = stackAllDestination + "a_stackOpen/";
            addSample("Acoustic Stack Open 1 OH", stackOpenDestination + "a_stackOpen_1_oh_wav", defaultMidiNotes[25], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Open 2 OH", stackOpenDestination + "a_stackOpen_2_oh_wav", defaultMidiNotes[25], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Open 3 OH", stackOpenDestination + "a_stackOpen_3_oh_wav", defaultMidiNotes[25], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Open 4 OH", stackOpenDestination + "a_stackOpen_4_oh_wav", defaultMidiNotes[25], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Open 5 OH", stackOpenDestination + "a_stackOpen_5_oh_wav", defaultMidiNotes[25], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Stack Open 1 Room", stackOpenDestination + "a_stackOpen_1_room_wav", defaultMidiNotes[25], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Open 2 Room", stackOpenDestination + "a_stackOpen_2_room_wav", defaultMidiNotes[25], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Open 3 Room", stackOpenDestination + "a_stackOpen_3_room_wav", defaultMidiNotes[25], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Open 4 Room", stackOpenDestination + "a_stackOpen_4_room_wav", defaultMidiNotes[25], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Open 5 Room", stackOpenDestination + "a_stackOpen_5_room_wav", defaultMidiNotes[25], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Stack Open 1 Bleed", stackOpenDestination + "a_stackOpen_1_bleed_wav", defaultMidiNotes[25], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Open 2 Bleed", stackOpenDestination + "a_stackOpen_2_bleed_wav", defaultMidiNotes[25], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Open 3 Bleed", stackOpenDestination + "a_stackOpen_3_bleed_wav", defaultMidiNotes[25], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Open 4 Bleed", stackOpenDestination + "a_stackOpen_4_bleed_wav", defaultMidiNotes[25], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Open 5 Bleed", stackOpenDestination + "a_stackOpen_5_bleed_wav", defaultMidiNotes[25], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Stack Open 1 Binaural", stackOpenDestination + "a_stackOpen_1_binaural_wav", defaultMidiNotes[25], curveFor5[0], curveFor5[1] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Open 2 Binaural", stackOpenDestination + "a_stackOpen_2_binaural_wav", defaultMidiNotes[25], curveFor5[1], curveFor5[2] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Open 3 Binaural", stackOpenDestination + "a_stackOpen_3_binaural_wav", defaultMidiNotes[25], curveFor5[2], curveFor5[3] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Open 4 Binaural", stackOpenDestination + "a_stackOpen_4_binaural_wav", defaultMidiNotes[25], curveFor5[3], curveFor5[4] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Stack Open 5 Binaural", stackOpenDestination + "a_stackOpen_5_binaural_wav", defaultMidiNotes[25], curveFor5[4], curveFor5[5] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);

            string sticksDestination = acousticDestination + "a_sticks/";
            addSample("Acoustic Sticks 1 OH", sticksDestination + "a_sticks_1_oh_wav", defaultMidiNotes[26], curveFor4[0], curveFor4[1] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Sticks 2 OH", sticksDestination + "a_sticks_2_oh_wav", defaultMidiNotes[26], curveFor4[1], curveFor4[2] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Sticks 3 OH", sticksDestination + "a_sticks_3_oh_wav", defaultMidiNotes[26], curveFor4[2], curveFor4[3] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Sticks 4 OH", sticksDestination + "a_sticks_4_oh_wav", defaultMidiNotes[26], curveFor4[3], curveFor4[4] - 1, hhRelease, stackMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Acoustic Sticks 1 Room", sticksDestination + "a_sticks_1_room_wav", defaultMidiNotes[26], curveFor4[0], curveFor4[1] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Sticks 2 Room", sticksDestination + "a_sticks_2_room_wav", defaultMidiNotes[26], curveFor4[1], curveFor4[2] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Sticks 3 Room", sticksDestination + "a_sticks_3_room_wav", defaultMidiNotes[26], curveFor4[2], curveFor4[3] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Sticks 4 Room", sticksDestination + "a_sticks_4_room_wav", defaultMidiNotes[26], curveFor4[3], curveFor4[4] - 1, hhRelease, stackMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Acoustic Sticks 1 Bleed", sticksDestination + "a_sticks_1_bleed_wav", defaultMidiNotes[26], curveFor4[0], curveFor4[1] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Sticks 2 Bleed", sticksDestination + "a_sticks_2_bleed_wav", defaultMidiNotes[26], curveFor4[1], curveFor4[2] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Sticks 3 Bleed", sticksDestination + "a_sticks_3_bleed_wav", defaultMidiNotes[26], curveFor4[2], curveFor4[3] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Sticks 4 Bleed", sticksDestination + "a_sticks_4_bleed_wav", defaultMidiNotes[26], curveFor4[3], curveFor4[4] - 1, hhRelease, stackMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Acoustic Sticks 1 Binaural", sticksDestination + "a_sticks_1_binaural_wav", defaultMidiNotes[26], curveFor4[0], curveFor4[1] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Sticks 2 Binaural", sticksDestination + "a_sticks_2_binaural_wav", defaultMidiNotes[26], curveFor4[1], curveFor4[2] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Sticks 3 Binaural", sticksDestination + "a_sticks_3_binaural_wav", defaultMidiNotes[26], curveFor4[2], curveFor4[3] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
            addSample("Acoustic Sticks 4 Binaural", sticksDestination + "a_sticks_4_binaural_wav", defaultMidiNotes[26], curveFor4[3], curveFor4[4] - 1, hhRelease, stackMaxLen, "Binaural", samplers, formatManager);
        }

        if (missingSample)
            loadEssentialSamples(samplePack, samplers, formatManager);

    }

    void loadDrySamples(std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        string destinationAll = "C:/Users/damia/Desktop/Sampelki/";

        if (missingSample)
        {
            loadEssentialSamples(samplePack, samplers, formatManager);
        }
        else
        {
            double kickRelease = 0.5;
            double kickMaxLen = 2.0;
            string dryDestination = destinationAll + "drySamples2/";
            // sampleName, File destination, midiNote, lowestVelocity, highestVelocity, release in s, maxLength in s, bus select (0 - Close Mics, 1 - OH, 2 - Room)
            string kickDestination = dryDestination + "kick/";
            addSample("Dry Kick 1 Close", kickDestination + "kick_1_close.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Dry Kick 2 Close", kickDestination + "kick_2_close.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Dry Kick 3 Close", kickDestination + "kick_3_close.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Dry Kick 4 Close", kickDestination + "kick_4_close.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Dry Kick 5 Close", kickDestination + "kick_5_close.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickClose", samplers, formatManager);
            addSample("Dry Kick 1 OH", kickDestination + "kick_1_OH.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Dry Kick 2 OH", kickDestination + "kick_2_OH.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Dry Kick 3 OH", kickDestination + "kick_3_OH.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Dry Kick 4 OH", kickDestination + "kick_4_OH.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Dry Kick 5 OH", kickDestination + "kick_5_OH.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickOH", samplers, formatManager);
            addSample("Dry Kick 1 Room", kickDestination + "kick_1_room.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Dry Kick 2 Room", kickDestination + "kick_2_room.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Dry Kick 3 Room", kickDestination + "kick_3_room.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Dry Kick 4 Room", kickDestination + "kick_4_room.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Dry Kick 5 Room", kickDestination + "kick_5_room.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickRoom", samplers, formatManager);
            addSample("Dry Kick 1 Bleed", kickDestination + "kick_1_bleed.wav", defaultMidiNotes[0], curveFor5[0], curveFor5[1] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Dry Kick 2 Bleed", kickDestination + "kick_2_bleed.wav", defaultMidiNotes[0], curveFor5[1], curveFor5[2] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Dry Kick 3 Bleed", kickDestination + "kick_3_bleed.wav", defaultMidiNotes[0], curveFor5[2], curveFor5[3] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Dry Kick 4 Bleed", kickDestination + "kick_4_bleed.wav", defaultMidiNotes[0], curveFor5[3], curveFor5[4] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);
            addSample("Dry Kick 5 Bleed", kickDestination + "kick_5_bleed.wav", defaultMidiNotes[0], curveFor5[4], curveFor5[5] - 1, kickRelease, kickMaxLen, "KickBleed", samplers, formatManager);


            double snareRelease = 0.5;
            double snareMaxLen = 2.0;
            string snareAllDestination = dryDestination + "snareAll/";
            string snareDestination = snareAllDestination + "snare/";
            addSample("Dry Snare 1 Top", snareDestination + "snare_1_top.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 2 Top", snareDestination + "snare_2_top.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 3 Top", snareDestination + "snare_3_top.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 4 Top", snareDestination + "snare_4_top.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 5 Top", snareDestination + "snare_5_top.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 6 Top", snareDestination + "snare_6_top.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareTop", samplers, formatManager);
            addSample("Dry Snare 1 Bot", snareDestination + "snare_1_bot.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 2 Bot", snareDestination + "snare_2_bot.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 3 Bot", snareDestination + "snare_3_bot.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 4 Bot", snareDestination + "snare_4_bot.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 5 Bot", snareDestination + "snare_5_bot.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 6 Bot", snareDestination + "snare_6_bot.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareBot", samplers, formatManager);
            addSample("Dry Snare 1 OH", snareDestination + "snare_1_OH.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 2 OH", snareDestination + "snare_2_OH.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 3 OH", snareDestination + "snare_3_OH.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 4 OH", snareDestination + "snare_4_OH.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 5 OH", snareDestination + "snare_5_OH.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 6 OH", snareDestination + "snare_6_OH.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareOH", samplers, formatManager);
            addSample("Dry Snare 1 Room", snareDestination + "snare_1_room.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 2 Room", snareDestination + "snare_2_room.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 3 Room", snareDestination + "snare_3_room.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 4 Room", snareDestination + "snare_4_room.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 5 Room", snareDestination + "snare_5_room.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 6 Room", snareDestination + "snare_6_room.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareRoom", samplers, formatManager);
            addSample("Dry Snare 1 Bleed", snareDestination + "snare_1_bleed.wav", defaultMidiNotes[1], curveFor6[0], curveFor6[1] - 1, snareRelease, 1.0, "SnareBleed", samplers, formatManager);
            addSample("Dry Snare 2 Bleed", snareDestination + "snare_2_bleed.wav", defaultMidiNotes[1], curveFor6[1], curveFor6[2] - 1, snareRelease, 1.1, "SnareBleed", samplers, formatManager);
            addSample("Dry Snare 3 Bleed", snareDestination + "snare_3_bleed.wav", defaultMidiNotes[1], curveFor6[2], curveFor6[3] - 1, snareRelease, 1.3, "SnareBleed", samplers, formatManager);
            addSample("Dry Snare 4 Bleed", snareDestination + "snare_4_bleed.wav", defaultMidiNotes[1], curveFor6[3], curveFor6[4] - 1, snareRelease, 1.3, "SnareBleed", samplers, formatManager);
            addSample("Dry Snare 5 Bleed", snareDestination + "snare_5_bleed.wav", defaultMidiNotes[1], curveFor6[4], curveFor6[5] - 1, snareRelease, 1.5, "SnareBleed", samplers, formatManager);
            addSample("Dry Snare 6 Bleed", snareDestination + "snare_6_bleed.wav", defaultMidiNotes[1], curveFor6[5], curveFor6[6] - 1, snareRelease, 1.8, "SnareBleed", samplers, formatManager);

            string snareFlamDestination = snareAllDestination + "snareFlam/";
            addSample("Dry SnareFlam 1 Top", snareFlamDestination + "snareFlam_1_top.wav", defaultMidiNotes[3], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareTop", samplers, formatManager);
            addSample("Dry SnareFlam 2 Top", snareFlamDestination + "snareFlam_2_top.wav", defaultMidiNotes[3], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareTop", samplers, formatManager);
            addSample("Dry SnareFlam 3 Top", snareFlamDestination + "snareFlam_3_top.wav", defaultMidiNotes[3], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareTop", samplers, formatManager);
            addSample("Dry SnareFlam 4 Top", snareFlamDestination + "snareFlam_4_top.wav", defaultMidiNotes[3], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareTop", samplers, formatManager);
            addSample("Dry SnareFlam 1 Bot", snareFlamDestination + "snareFlam_1_bot.wav", defaultMidiNotes[3], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareBot", samplers, formatManager);
            addSample("Dry SnareFlam 2 Bot", snareFlamDestination + "snareFlam_2_bot.wav", defaultMidiNotes[3], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareBot", samplers, formatManager);
            addSample("Dry SnareFlam 3 Bot", snareFlamDestination + "snareFlam_3_bot.wav", defaultMidiNotes[3], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareBot", samplers, formatManager);
            addSample("Dry SnareFlam 4 Bot", snareFlamDestination + "snareFlam_4_bot.wav", defaultMidiNotes[3], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareBot", samplers, formatManager);
            addSample("Dry SnareFlam 1 OH", snareFlamDestination + "snareFlam_1_OH.wav", defaultMidiNotes[3], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareOH", samplers, formatManager);
            addSample("Dry SnareFlam 2 OH", snareFlamDestination + "snareFlam_2_OH.wav", defaultMidiNotes[3], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareOH", samplers, formatManager);
            addSample("Dry SnareFlam 3 OH", snareFlamDestination + "snareFlam_3_OH.wav", defaultMidiNotes[3], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareOH", samplers, formatManager);
            addSample("Dry SnareFlam 4 OH", snareFlamDestination + "snareFlam_4_OH.wav", defaultMidiNotes[3], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareOH", samplers, formatManager);
            addSample("Dry SnareFlam 1 Room", snareFlamDestination + "snareFlam_1_room.wav", defaultMidiNotes[3], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareFlam 2 Room", snareFlamDestination + "snareFlam_2_room.wav", defaultMidiNotes[3], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareFlam 3 Room", snareFlamDestination + "snareFlam_3_room.wav", defaultMidiNotes[3], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareFlam 4 Room", snareFlamDestination + "snareFlam_4_room.wav", defaultMidiNotes[3], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareFlam 1 Bleed", snareFlamDestination + "snareFlam_1_bleed.wav", defaultMidiNotes[3], curveFor4[0], curveFor4[1] - 1, snareRelease, 1.8, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareFlam 2 Bleed", snareFlamDestination + "snareFlam_2_bleed.wav", defaultMidiNotes[3], curveFor4[1], curveFor4[2] - 1, snareRelease, 1.3, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareFlam 3 Bleed", snareFlamDestination + "snareFlam_3_bleed.wav", defaultMidiNotes[3], curveFor4[2], curveFor4[3] - 1, snareRelease, 1.3, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareFlam 4 Bleed", snareFlamDestination + "snareFlam_4_bleed.wav", defaultMidiNotes[3], curveFor4[3], curveFor4[4] - 1, snareRelease, 1.4, "SnareBleed", samplers, formatManager);

            double snareMaxLen2 = 1.1;
            string snareRoundDestination = snareAllDestination + "snareRound/";
            addSample("Dry SnareRound 1 Top", snareRoundDestination + "snareRound_1_top.wav", defaultMidiNotes[4], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareTop", samplers, formatManager);
            addSample("Dry SnareRound 2 Top", snareRoundDestination + "snareRound_2_top.wav", defaultMidiNotes[4], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareTop", samplers, formatManager);
            addSample("Dry SnareRound 3 Top", snareRoundDestination + "snareRound_3_top.wav", defaultMidiNotes[4], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareTop", samplers, formatManager);
            addSample("Dry SnareRound 1 Bot", snareRoundDestination + "snareRound_1_bot.wav", defaultMidiNotes[4], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareBot", samplers, formatManager);
            addSample("Dry SnareRound 2 Bot", snareRoundDestination + "snareRound_2_bot.wav", defaultMidiNotes[4], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareBot", samplers, formatManager);
            addSample("Dry SnareRound 3 Bot", snareRoundDestination + "snareRound_3_bot.wav", defaultMidiNotes[4], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareBot", samplers, formatManager);
            addSample("Dry SnareRound 1 OH", snareRoundDestination + "snareRound_1_OH.wav", defaultMidiNotes[4], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareOH", samplers, formatManager);
            addSample("Dry SnareRound 2 OH", snareRoundDestination + "snareRound_2_OH.wav", defaultMidiNotes[4], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareOH", samplers, formatManager);
            addSample("Dry SnareRound 3 OH", snareRoundDestination + "snareRound_3_OH.wav", defaultMidiNotes[4], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareOH", samplers, formatManager);
            addSample("Dry SnareRound 1 Room", snareRoundDestination + "snareRound_1_room.wav", defaultMidiNotes[4], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareRound 2 Room", snareRoundDestination + "snareRound_2_room.wav", defaultMidiNotes[4], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareRound 3 Room", snareRoundDestination + "snareRound_3_room.wav", defaultMidiNotes[4], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareRound 1 Bleed", snareRoundDestination + "snareRound_1_bleed.wav", defaultMidiNotes[4], curveFor3[0], curveFor3[1] - 1, snareRelease, snareMaxLen2, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareRound 2 Bleed", snareRoundDestination + "snareRound_2_bleed.wav", defaultMidiNotes[4], curveFor3[1], curveFor3[2] - 1, snareRelease, snareMaxLen2, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareRound 3 Bleed", snareRoundDestination + "snareRound_3_bleed.wav", defaultMidiNotes[4], curveFor3[2], curveFor3[3] - 1, snareRelease, snareMaxLen2, "SnareBleed", samplers, formatManager);

            string snareWirelessDestination = snareAllDestination + "snareWireless/";
            addSample("Dry SnareWireless 1 Top", snareWirelessDestination + "snareWireless_1_top.wav", defaultMidiNotes[5], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWireless 2 Top", snareWirelessDestination + "snareWireless_2_top.wav", defaultMidiNotes[5], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWireless 3 Top", snareWirelessDestination + "snareWireless_3_top.wav", defaultMidiNotes[5], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWireless 4 Top", snareWirelessDestination + "snareWireless_4_top.wav", defaultMidiNotes[5], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWireless 1 Bot", snareWirelessDestination + "snareWireless_1_bot.wav", defaultMidiNotes[5], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWireless 2 Bot", snareWirelessDestination + "snareWireless_2_bot.wav", defaultMidiNotes[5], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWireless 3 Bot", snareWirelessDestination + "snareWireless_3_bot.wav", defaultMidiNotes[5], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWireless 4 Bot", snareWirelessDestination + "snareWireless_4_bot.wav", defaultMidiNotes[5], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWireless 1 OH", snareWirelessDestination + "snareWireless_1_OH.wav", defaultMidiNotes[5], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWireless 2 OH", snareWirelessDestination + "snareWireless_2_OH.wav", defaultMidiNotes[5], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWireless 3 OH", snareWirelessDestination + "snareWireless_3_OH.wav", defaultMidiNotes[5], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWireless 4 OH", snareWirelessDestination + "snareWireless_4_OH.wav", defaultMidiNotes[5], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWireless 1 Room", snareWirelessDestination + "snareWireless_1_room.wav", defaultMidiNotes[5], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWireless 2 Room", snareWirelessDestination + "snareWireless_2_room.wav", defaultMidiNotes[5], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWireless 3 Room", snareWirelessDestination + "snareWireless_3_room.wav", defaultMidiNotes[5], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWireless 4 Room", snareWirelessDestination + "snareWireless_4_room.wav", defaultMidiNotes[5], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWireless 1 Bleed", snareWirelessDestination + "snareWireless_1_bleed.wav", defaultMidiNotes[5], curveFor4[0], curveFor4[1] - 1, snareRelease, 0.75, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareWireless 2 Bleed", snareWirelessDestination + "snareWireless_2_bleed.wav", defaultMidiNotes[5], curveFor4[1], curveFor4[2] - 1, snareRelease, 0.75, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareWireless 3 Bleed", snareWirelessDestination + "snareWireless_3_bleed.wav", defaultMidiNotes[5], curveFor4[2], curveFor4[3] - 1, snareRelease, 0.99, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareWireless 4 Bleed", snareWirelessDestination + "snareWireless_4_bleed.wav", defaultMidiNotes[5], curveFor4[3], curveFor4[4] - 1, snareRelease, 0.99, "SnareBleed", samplers, formatManager);

            string snareWirelessRoundDestination = snareAllDestination + "snareWirelessRound/";
            addSample("Dry SnareWirelessRound 1 Top", snareWirelessRoundDestination + "snareWirelessRound_1_top.wav", defaultMidiNotes[6], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWirelessRound 2 Top", snareWirelessRoundDestination + "snareWirelessRound_2_top.wav", defaultMidiNotes[6], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWirelessRound 3 Top", snareWirelessRoundDestination + "snareWirelessRound_3_top.wav", defaultMidiNotes[6], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareTop", samplers, formatManager);
            addSample("Dry SnareWirelessRound 1 Bot", snareWirelessRoundDestination + "snareWirelessRound_1_bot.wav", defaultMidiNotes[6], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWirelessRound 2 Bot", snareWirelessRoundDestination + "snareWirelessRound_2_bot.wav", defaultMidiNotes[6], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWirelessRound 3 Bot", snareWirelessRoundDestination + "snareWirelessRound_3_bot.wav", defaultMidiNotes[6], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareBot", samplers, formatManager);
            addSample("Dry SnareWirelessRound 1 OH", snareWirelessRoundDestination + "snareWirelessRound_1_OH.wav", defaultMidiNotes[6], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWirelessRound 2 OH", snareWirelessRoundDestination + "snareWirelessRound_2_OH.wav", defaultMidiNotes[6], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWirelessRound 3 OH", snareWirelessRoundDestination + "snareWirelessRound_3_OH.wav", defaultMidiNotes[6], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareOH", samplers, formatManager);
            addSample("Dry SnareWirelessRound 1 Room", snareWirelessRoundDestination + "snareWirelessRound_1_room.wav", defaultMidiNotes[6], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWirelessRound 2 Room", snareWirelessRoundDestination + "snareWirelessRound_2_room.wav", defaultMidiNotes[6], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWirelessRound 3 Room", snareWirelessRoundDestination + "snareWirelessRound_3_room.wav", defaultMidiNotes[6], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareRoom", samplers, formatManager);
            addSample("Dry SnareWirelessRound 1 Bleed", snareWirelessRoundDestination + "snareWirelessRound_1_bleed.wav", defaultMidiNotes[6], curveFor3[0], curveFor3[1] - 1, snareRelease, 0.5, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareWirelessRound 2 Bleed", snareWirelessRoundDestination + "snareWirelessRound_2_bleed.wav", defaultMidiNotes[6], curveFor3[1], curveFor3[2] - 1, snareRelease, 0.5, "SnareBleed", samplers, formatManager);
            addSample("Dry SnareWirelessRound 3 Bleed", snareWirelessRoundDestination + "snareWirelessRound_3_bleed.wav", defaultMidiNotes[6], curveFor3[2], curveFor3[3] - 1, snareRelease, 0.5, "SnareBleed", samplers, formatManager);

            double tomRelease = 0.6;
            double tomMaxLen = 2.2;
            string tomAllDestination = dryDestination + "tomAll/";
            string tomDestination = tomAllDestination + "tom/";
            addSample("Dry Tom 1 Close", tomDestination + "tom_1_close.wav", defaultMidiNotes[9], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomClose", samplers, formatManager);
            addSample("Dry Tom 2 Close", tomDestination + "tom_2_close.wav", defaultMidiNotes[9], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomClose", samplers, formatManager);
            addSample("Dry Tom 3 Close", tomDestination + "tom_3_close.wav", defaultMidiNotes[9], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomClose", samplers, formatManager);
            addSample("Dry Tom 4 Close", tomDestination + "tom_4_close.wav", defaultMidiNotes[9], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomClose", samplers, formatManager);
            addSample("Dry Tom 1 OH", tomDestination + "tom_1_OH.wav", defaultMidiNotes[9], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsOH", samplers, formatManager);
            addSample("Dry Tom 2 OH", tomDestination + "tom_2_OH.wav", defaultMidiNotes[9], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsOH", samplers, formatManager);
            addSample("Dry Tom 3 OH", tomDestination + "tom_3_OH.wav", defaultMidiNotes[9], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsOH", samplers, formatManager);
            addSample("Dry Tom 4 OH", tomDestination + "tom_4_OH.wav", defaultMidiNotes[9], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsOH", samplers, formatManager);
            addSample("Dry Tom 1 Room", tomDestination + "tom_1_room.wav", defaultMidiNotes[9], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsRoom", samplers, formatManager);
            addSample("Dry Tom 2 Room", tomDestination + "tom_2_room.wav", defaultMidiNotes[9], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsRoom", samplers, formatManager);
            addSample("Dry Tom 3 Room", tomDestination + "tom_3_room.wav", defaultMidiNotes[9], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsRoom", samplers, formatManager);
            addSample("Dry Tom 4 Room", tomDestination + "tom_4_room.wav", defaultMidiNotes[9], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsRoom", samplers, formatManager);
            addSample("Dry Tom 1 Bleed", tomDestination + "tom_1_bleed.wav", defaultMidiNotes[9], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.7, "TomsBleed", samplers, formatManager);
            addSample("Dry Tom 2 Bleed", tomDestination + "tom_2_bleed.wav", defaultMidiNotes[9], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.7, "TomsBleed", samplers, formatManager);
            addSample("Dry Tom 3 Bleed", tomDestination + "tom_3_bleed.wav", defaultMidiNotes[9], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsBleed", samplers, formatManager);
            addSample("Dry Tom 4 Bleed", tomDestination + "tom_4_bleed.wav", defaultMidiNotes[9], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsBleed", samplers, formatManager);

            string tomFlamDestination = tomAllDestination + "tomFlam/";
            addSample("Dry TomFlam 1 Close", tomFlamDestination + "tomFlam_1_close.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomClose", samplers, formatManager);
            addSample("Dry TomFlam 2 Close", tomFlamDestination + "tomFlam_2_close.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomClose", samplers, formatManager);
            addSample("Dry TomFlam 3 Close", tomFlamDestination + "tomFlam_3_close.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomClose", samplers, formatManager);
            addSample("Dry TomFlam 1 OH", tomFlamDestination + "tomFlam_1_OH.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsOH", samplers, formatManager);
            addSample("Dry TomFlam 2 OH", tomFlamDestination + "tomFlam_2_OH.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsOH", samplers, formatManager);
            addSample("Dry TomFlam 3 OH", tomFlamDestination + "tomFlam_3_OH.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsOH", samplers, formatManager);
            addSample("Dry TomFlam 1 Room", tomFlamDestination + "tomFlam_1_room.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsRoom", samplers, formatManager);
            addSample("Dry TomFlam 2 Room", tomFlamDestination + "tomFlam_2_room.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsRoom", samplers, formatManager);
            addSample("Dry TomFlam 3 Room", tomFlamDestination + "tomFlam_3_room.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsRoom", samplers, formatManager);
            addSample("Dry TomFlam 1 Bleed", tomFlamDestination + "tomFlam_1_bleed.wav", defaultMidiNotes[10], curveFor3[0], curveFor3[1] - 1, tomRelease, 0.9, "TomsBleed", samplers, formatManager);
            addSample("Dry TomFlam 2 Bleed", tomFlamDestination + "tomFlam_2_bleed.wav", defaultMidiNotes[10], curveFor3[1], curveFor3[2] - 1, tomRelease, 1.0, "TomsBleed", samplers, formatManager);
            addSample("Dry TomFlam 3 Bleed", tomFlamDestination + "tomFlam_3_bleed.wav", defaultMidiNotes[10], curveFor3[2], curveFor3[3] - 1, tomRelease, 1.1, "TomsBleed", samplers, formatManager);

            double ftomRelease = 0.7;
            double ftomMaxLen = 2.5;
            string ftomAllDestination = dryDestination + "ftomAll/";
            string ftomDestination = ftomAllDestination + "ftom/";
            addSample("Dry FTom 1 Close", ftomDestination + "ftom_1_close.wav", defaultMidiNotes[11], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "FTomClose", samplers, formatManager);
            addSample("Dry FTom 2 Close", ftomDestination + "ftom_2_close.wav", defaultMidiNotes[11], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "FTomClose", samplers, formatManager);
            addSample("Dry FTom 3 Close", ftomDestination + "ftom_3_close.wav", defaultMidiNotes[11], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "FTomClose", samplers, formatManager);
            addSample("Dry FTom 4 Close", ftomDestination + "ftom_4_close.wav", defaultMidiNotes[11], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "FTomClose", samplers, formatManager);
            addSample("Dry FTom 1 OH", ftomDestination + "ftom_1_OH.wav", defaultMidiNotes[11], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "TomsOH", samplers, formatManager);
            addSample("Dry FTom 2 OH", ftomDestination + "ftom_2_OH.wav", defaultMidiNotes[11], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "TomsOH", samplers, formatManager);
            addSample("Dry FTom 3 OH", ftomDestination + "ftom_3_OH.wav", defaultMidiNotes[11], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "TomsOH", samplers, formatManager);
            addSample("Dry FTom 4 OH", ftomDestination + "ftom_4_OH.wav", defaultMidiNotes[11], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "TomsOH", samplers, formatManager);
            addSample("Dry FTom 1 Room", ftomDestination + "ftom_1_room.wav", defaultMidiNotes[11], curveFor4[0], curveFor4[1] - 1, ftomRelease, 0.4, "TomsRoom", samplers, formatManager);
            addSample("Dry FTom 2 Room", ftomDestination + "ftom_2_room.wav", defaultMidiNotes[11], curveFor4[1], curveFor4[2] - 1, ftomRelease, 0.9, "TomsRoom", samplers, formatManager);
            addSample("Dry FTom 3 Room", ftomDestination + "ftom_3_room.wav", defaultMidiNotes[11], curveFor4[2], curveFor4[3] - 1, ftomRelease, 0.9, "TomsRoom", samplers, formatManager);
            addSample("Dry FTom 4 Room", ftomDestination + "ftom_4_room.wav", defaultMidiNotes[11], curveFor4[3], curveFor4[4] - 1, ftomRelease, 1.0, "TomsRoom", samplers, formatManager);
            addSample("Dry FTom 1 Bleed", ftomDestination + "ftom_1_bleed.wav", defaultMidiNotes[11], curveFor4[0], curveFor4[1] - 1, tomRelease, 0.4, "TomsBleed", samplers, formatManager);
            addSample("Dry FTom 2 Bleed", ftomDestination + "ftom_2_bleed.wav", defaultMidiNotes[11], curveFor4[1], curveFor4[2] - 1, tomRelease, 0.9, "TomsBleed", samplers, formatManager);
            addSample("Dry FTom 3 Bleed", ftomDestination + "ftom_3_bleed.wav", defaultMidiNotes[11], curveFor4[2], curveFor4[3] - 1, tomRelease, 0.9, "TomsBleed", samplers, formatManager);
            addSample("Dry FTom 4 Bleed", ftomDestination + "ftom_4_bleed.wav", defaultMidiNotes[11], curveFor4[3], curveFor4[4] - 1, tomRelease, 1.0, "TomsBleed", samplers, formatManager);

            string ftomFlamDestination = ftomAllDestination + "ftomFlam/";
            addSample("Dry FTomFlam 1 Close", ftomFlamDestination + "ftomFlam_1_close.wav", defaultMidiNotes[12], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "FTomClose", samplers, formatManager);
            addSample("Dry FTomFlam 2 Close", ftomFlamDestination + "ftomFlam_2_close.wav", defaultMidiNotes[12], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "FTomClose", samplers, formatManager);
            addSample("Dry FTomFlam 3 Close", ftomFlamDestination + "ftomFlam_3_close.wav", defaultMidiNotes[12], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "FTomClose", samplers, formatManager);
            addSample("Dry FTomFlam 1 OH", ftomFlamDestination + "ftomFlam_1_OH.wav", defaultMidiNotes[12], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsOH", samplers, formatManager);
            addSample("Dry FTomFlam 2 OH", ftomFlamDestination + "ftomFlam_2_OH.wav", defaultMidiNotes[12], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsOH", samplers, formatManager);
            addSample("Dry FTomFlam 3 OH", ftomFlamDestination + "ftomFlam_3_OH.wav", defaultMidiNotes[12], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsOH", samplers, formatManager);
            addSample("Dry FTomFlam 1 Room", ftomFlamDestination + "ftomFlam_1_room.wav", defaultMidiNotes[12], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsRoom", samplers, formatManager);
            addSample("Dry FTomFlam 2 Room", ftomFlamDestination + "ftomFlam_2_room.wav", defaultMidiNotes[12], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsRoom", samplers, formatManager);
            addSample("Dry FTomFlam 3 Room", ftomFlamDestination + "ftomFlam_3_room.wav", defaultMidiNotes[12], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsRoom", samplers, formatManager);
            addSample("Dry FTomFlam 1 Bleed", ftomFlamDestination + "ftomFlam_1_bleed.wav", defaultMidiNotes[12], curveFor3[0], curveFor3[1] - 1, ftomRelease, 0.9, "TomsBleed", samplers, formatManager);
            addSample("Dry FTomFlam 2 Bleed", ftomFlamDestination + "ftomFlam_2_bleed.wav", defaultMidiNotes[12], curveFor3[1], curveFor3[2] - 1, ftomRelease, 1.0, "TomsBleed", samplers, formatManager);
            addSample("Dry FTomFlam 3 Bleed", ftomFlamDestination + "ftomFlam_3_bleed.wav", defaultMidiNotes[12], curveFor3[2], curveFor3[3] - 1, ftomRelease, 1.1, "TomsBleed", samplers, formatManager);

            double hhRelease = 0.12;
            double hhMaxLen = 1.0;
            string HHAllDestination = dryDestination + "HHAll/";
            string HHClosedDestination = HHAllDestination + "HHClosed/";
            addSample("Dry HHClosed 1 Close", HHClosedDestination + "HHClosed_1_close.wav", defaultMidiNotes[14], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "HHClose", samplers, formatManager);
            addSample("Dry HHClosed 2 Close", HHClosedDestination + "HHClosed_2_close.wav", defaultMidiNotes[14], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "HHClose", samplers, formatManager);
            addSample("Dry HHClosed 3 Close", HHClosedDestination + "HHClosed_3_close.wav", defaultMidiNotes[14], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "HHClose", samplers, formatManager);
            addSample("Dry HHClosed 4 Close", HHClosedDestination + "HHClosed_4_close.wav", defaultMidiNotes[14], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "HHClose", samplers, formatManager);
            addSample("Dry HHClosed 5 Close", HHClosedDestination + "HHClosed_5_close.wav", defaultMidiNotes[14], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "HHClose", samplers, formatManager);
            addSample("Dry HHClosed 1 OH", HHClosedDestination + "HHClosed_1_OH.wav", defaultMidiNotes[14], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHClosed 2 OH", HHClosedDestination + "HHClosed_2_OH.wav", defaultMidiNotes[14], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHClosed 3 OH", HHClosedDestination + "HHClosed_3_OH.wav", defaultMidiNotes[14], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHClosed 4 OH", HHClosedDestination + "HHClosed_4_OH.wav", defaultMidiNotes[14], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHClosed 5 OH", HHClosedDestination + "HHClosed_5_OH.wav", defaultMidiNotes[14], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHClosed 1 Room", HHClosedDestination + "HHClosed_1_room.wav", defaultMidiNotes[14], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHClosed 2 Room", HHClosedDestination + "HHClosed_2_room.wav", defaultMidiNotes[14], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHClosed 3 Room", HHClosedDestination + "HHClosed_3_room.wav", defaultMidiNotes[14], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHClosed 4 Room", HHClosedDestination + "HHClosed_4_room.wav", defaultMidiNotes[14], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHClosed 5 Room", HHClosedDestination + "HHClosed_5_room.wav", defaultMidiNotes[14], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHClosed 1 Bleed", HHClosedDestination + "HHClosed_1_bleed.wav", defaultMidiNotes[14], curveFor5[0], curveFor5[1] - 1, hhRelease, 0.9, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHClosed 2 Bleed", HHClosedDestination + "HHClosed_2_bleed.wav", defaultMidiNotes[14], curveFor5[1], curveFor5[2] - 1, hhRelease, 0.9, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHClosed 3 Bleed", HHClosedDestination + "HHClosed_3_bleed.wav", defaultMidiNotes[14], curveFor5[2], curveFor5[3] - 1, hhRelease, 1.0, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHClosed 4 Bleed", HHClosedDestination + "HHClosed_4_bleed.wav", defaultMidiNotes[14], curveFor5[3], curveFor5[4] - 1, hhRelease, 1.3, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHClosed 5 Bleed", HHClosedDestination + "HHClosed_5_bleed.wav", defaultMidiNotes[14], curveFor5[4], curveFor5[5] - 1, hhRelease, 1.0, "CymbalsBleed", samplers, formatManager);

            double hhHalfMaxLen = 1.4;
            string HHHalfDestination = HHAllDestination + "HHHalf/";
            addSample("Dry HHHalf 1 Close", HHHalfDestination + "HHHalf_1_close.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Dry HHHalf 2 Close", HHHalfDestination + "HHHalf_2_close.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Dry HHHalf 3 Close", HHHalfDestination + "HHHalf_3_close.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Dry HHHalf 4 Close", HHHalfDestination + "HHHalf_4_close.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "HHClose", samplers, formatManager);
            addSample("Dry HHHalf 1 OH", HHHalfDestination + "HHHalf_1_OH.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHHalf 2 OH", HHHalfDestination + "HHHalf_2_OH.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHHalf 3 OH", HHHalfDestination + "HHHalf_3_OH.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHHalf 4 OH", HHHalfDestination + "HHHalf_4_OH.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHHalf 1 Room", HHHalfDestination + "HHHalf_1_room.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHHalf 2 Room", HHHalfDestination + "HHHalf_2_room.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHHalf 3 Room", HHHalfDestination + "HHHalf_3_room.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHHalf 4 Room", HHHalfDestination + "HHHalf_4_room.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHHalf 1 Bleed", HHHalfDestination + "HHHalf_1_bleed.wav", defaultMidiNotes[15], curveFor4[0], curveFor4[1] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHHalf 2 Bleed", HHHalfDestination + "HHHalf_2_bleed.wav", defaultMidiNotes[15], curveFor4[1], curveFor4[2] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHHalf 3 Bleed", HHHalfDestination + "HHHalf_3_bleed.wav", defaultMidiNotes[15], curveFor4[2], curveFor4[3] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHHalf 4 Bleed", HHHalfDestination + "HHHalf_4_bleed.wav", defaultMidiNotes[15], curveFor4[3], curveFor4[4] - 1, hhRelease, hhHalfMaxLen, "CymbalsBleed", samplers, formatManager);

            double hhOpenMaxLen = 5.0;
            string HHOpenDestination = HHAllDestination + "HHOpen/";
            addSample("Dry HHOpen 1 Close", HHOpenDestination + "HHOpen_1_close.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "HHClose", samplers, formatManager);
            addSample("Dry HHOpen 2 Close", HHOpenDestination + "HHOpen_2_close.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "HHClose", samplers, formatManager);
            addSample("Dry HHOpen 3 Close", HHOpenDestination + "HHOpen_3_close.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "HHClose", samplers, formatManager);
            addSample("Dry HHOpen 4 Close", HHOpenDestination + "HHOpen_4_close.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "HHClose", samplers, formatManager);
            addSample("Dry HHOpen 1 OH", HHOpenDestination + "HHOpen_1_OH.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHOpen 2 OH", HHOpenDestination + "HHOpen_2_OH.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHOpen 3 OH", HHOpenDestination + "HHOpen_3_OH.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHOpen 4 OH", HHOpenDestination + "HHOpen_4_OH.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsOH", samplers, formatManager);
            addSample("Dry HHOpen 1 Room", HHOpenDestination + "HHOpen_1_room.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHOpen 2 Room", HHOpenDestination + "HHOpen_2_room.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHOpen 3 Room", HHOpenDestination + "HHOpen_3_room.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHOpen 4 Room", HHOpenDestination + "HHOpen_4_room.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsRoom", samplers, formatManager);
            addSample("Dry HHOpen 1 Bleed", HHOpenDestination + "HHOpen_1_bleed.wav", defaultMidiNotes[16], curveFor4[0], curveFor4[1] - 1, hhRelease, 2.0, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHOpen 2 Bleed", HHOpenDestination + "HHOpen_2_bleed.wav", defaultMidiNotes[16], curveFor4[1], curveFor4[2] - 1, hhRelease, 3.2, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHOpen 3 Bleed", HHOpenDestination + "HHOpen_3_bleed.wav", defaultMidiNotes[16], curveFor4[2], curveFor4[3] - 1, hhRelease, 3.0, "CymbalsBleed", samplers, formatManager);
            addSample("Dry HHOpen 4 Bleed", HHOpenDestination + "HHOpen_4_bleed.wav", defaultMidiNotes[16], curveFor4[3], curveFor4[4] - 1, hhRelease, 4.2, "CymbalsBleed", samplers, formatManager);

            string tambDestination = dryDestination + "tambourine/";
            addSample("Dry Tambourine 1 OH", tambDestination + "tambourine_1_OH.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsOH", samplers, formatManager);
            addSample("Dry Tambourine 2 OH", tambDestination + "tambourine_2_OH.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsOH", samplers, formatManager);
            addSample("Dry Tambourine 3 OH", tambDestination + "tambourine_3_OH.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsOH", samplers, formatManager);
            addSample("Dry Tambourine 1 Room", tambDestination + "tambourine_1_room.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsRoom", samplers, formatManager);
            addSample("Dry Tambourine 2 Room", tambDestination + "tambourine_2_room.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsRoom", samplers, formatManager);
            addSample("Dry Tambourine 3 Room", tambDestination + "tambourine_3_room.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsRoom", samplers, formatManager);
            addSample("Dry Tambourine 1 Bleed", tambDestination + "tambourine_1_bleed.wav", defaultMidiNotes[17], curveFor3[0], curveFor3[1] - 1, hhRelease, 0.5, "CymbalsBleed", samplers, formatManager);
            addSample("Dry Tambourine 2 Bleed", tambDestination + "tambourine_2_bleed.wav", defaultMidiNotes[17], curveFor3[1], curveFor3[2] - 1, hhRelease, 0.9, "CymbalsBleed", samplers, formatManager);
            addSample("Dry Tambourine 3 Bleed", tambDestination + "tambourine_3_bleed.wav", defaultMidiNotes[17], curveFor3[2], curveFor3[3] - 1, hhRelease, 0.8, "CymbalsBleed", samplers, formatManager);

            double RideRelease = 0.7;
            string RideAllDestination = dryDestination + "rideAll/";
            string RidePointDestination = RideAllDestination + "ridePoint/";
            addSample("Dry RidePoint 1 OH", RidePointDestination + "ridePoint_1_OH.wav", defaultMidiNotes[18], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsOH", samplers, formatManager);
            addSample("Dry RidePoint 2 OH", RidePointDestination + "ridePoint_2_OH.wav", defaultMidiNotes[18], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsOH", samplers, formatManager);
            addSample("Dry RidePoint 3 OH", RidePointDestination + "ridePoint_3_OH.wav", defaultMidiNotes[18], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsOH", samplers, formatManager);
            addSample("Dry RidePoint 4 OH", RidePointDestination + "ridePoint_4_OH.wav", defaultMidiNotes[18], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsOH", samplers, formatManager);
            addSample("Dry RidePoint 1 Room", RidePointDestination + "ridePoint_1_room.wav", defaultMidiNotes[18], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RidePoint 2 Room", RidePointDestination + "ridePoint_2_room.wav", defaultMidiNotes[18], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RidePoint 3 Room", RidePointDestination + "ridePoint_3_room.wav", defaultMidiNotes[18], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RidePoint 4 Room", RidePointDestination + "ridePoint_4_room.wav", defaultMidiNotes[18], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RidePoint 1 Bleed", RidePointDestination + "ridePoint_1_bleed.wav", defaultMidiNotes[18], curveFor4[0], curveFor4[1] - 1, RideRelease, 3.5, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RidePoint 2 Bleed", RidePointDestination + "ridePoint_2_bleed.wav", defaultMidiNotes[18], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.7, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RidePoint 3 Bleed", RidePointDestination + "ridePoint_3_bleed.wav", defaultMidiNotes[18], curveFor4[2], curveFor4[3] - 1, RideRelease, 4.5, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RidePoint 4 Bleed", RidePointDestination + "ridePoint_4_bleed.wav", defaultMidiNotes[18], curveFor4[3], curveFor4[4] - 1, RideRelease, 5.3, "CymbalsBleed", samplers, formatManager);

            string RideBellDestination = RideAllDestination + "rideBell/";
            addSample("Dry RideBell 1 OH", RideBellDestination + "rideBell_1_OH.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideBell 2 OH", RideBellDestination + "rideBell_2_OH.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideBell 3 OH", RideBellDestination + "rideBell_3_OH.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideBell 4 OH", RideBellDestination + "rideBell_4_OH.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideBell 1 Room", RideBellDestination + "rideBell_1_room.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideBell 2 Room", RideBellDestination + "rideBell_2_room.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideBell 3 Room", RideBellDestination + "rideBell_3_room.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideBell 4 Room", RideBellDestination + "rideBell_4_room.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideBell 1 Bleed", RideBellDestination + "rideBell_1_bleed.wav", defaultMidiNotes[19], curveFor4[0], curveFor4[1] - 1, RideRelease, 2.95, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideBell 2 Bleed", RideBellDestination + "rideBell_2_bleed.wav", defaultMidiNotes[19], curveFor4[1], curveFor4[2] - 1, RideRelease, 3.32, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideBell 3 Bleed", RideBellDestination + "rideBell_3_bleed.wav", defaultMidiNotes[19], curveFor4[2], curveFor4[3] - 1, RideRelease, 3.70, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideBell 4 Bleed", RideBellDestination + "rideBell_4_bleed.wav", defaultMidiNotes[19], curveFor4[3], curveFor4[4] - 1, RideRelease, 4.30, "CymbalsBleed", samplers, formatManager);

            double RideOpenRelease = 4.5;
            string RideOpenDestination = RideAllDestination + "rideOpen/";
            addSample("Dry RideOpen 1 OH", RideOpenDestination + "rideOpen_1_OH.wav", defaultMidiNotes[20], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideOpen 2 OH", RideOpenDestination + "rideOpen_2_OH.wav", defaultMidiNotes[20], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideOpen 3 OH", RideOpenDestination + "rideOpen_3_OH.wav", defaultMidiNotes[20], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideOpen 4 OH", RideOpenDestination + "rideOpen_4_OH.wav", defaultMidiNotes[20], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsOH", samplers, formatManager);
            addSample("Dry RideOpen 1 Room", RideOpenDestination + "rideOpen_1_room.wav", defaultMidiNotes[20], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideOpen 2 Room", RideOpenDestination + "rideOpen_2_room.wav", defaultMidiNotes[20], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideOpen 3 Room", RideOpenDestination + "rideOpen_3_room.wav", defaultMidiNotes[20], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideOpen 4 Room", RideOpenDestination + "rideOpen_4_room.wav", defaultMidiNotes[20], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsRoom", samplers, formatManager);
            addSample("Dry RideOpen 1 Bleed", RideOpenDestination + "rideOpen_1_bleed.wav", defaultMidiNotes[20], curveFor4[0], curveFor4[1] - 1, RideOpenRelease, 5.80, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideOpen 2 Bleed", RideOpenDestination + "rideOpen_2_bleed.wav", defaultMidiNotes[20], curveFor4[1], curveFor4[2] - 1, RideOpenRelease, 5.30, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideOpen 3 Bleed", RideOpenDestination + "rideOpen_3_bleed.wav", defaultMidiNotes[20], curveFor4[2], curveFor4[3] - 1, RideOpenRelease, 5.85, "CymbalsBleed", samplers, formatManager);
            addSample("Dry RideOpen 4 Bleed", RideOpenDestination + "rideOpen_4_bleed.wav", defaultMidiNotes[20], curveFor4[3], curveFor4[4] - 1, RideOpenRelease, 7.80, "CymbalsBleed", samplers, formatManager);


            double CrashRelease = 0.12;
            string CrashAllDestination = dryDestination + "crashAll/";
            string CrashPointDestination = CrashAllDestination + "crashPoint/";
            addSample("Dry CrashPoint 1 OH", CrashPointDestination + "crashPoint_1_OH.wav", defaultMidiNotes[21], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashPoint 2 OH", CrashPointDestination + "crashPoint_2_OH.wav", defaultMidiNotes[21], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashPoint 3 OH", CrashPointDestination + "crashPoint_3_OH.wav", defaultMidiNotes[21], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashPoint 1 Room", CrashPointDestination + "crashPoint_1_room.wav", defaultMidiNotes[21], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashPoint 2 Room", CrashPointDestination + "crashPoint_2_room.wav", defaultMidiNotes[21], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashPoint 3 Room", CrashPointDestination + "crashPoint_3_room.wav", defaultMidiNotes[21], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashPoint 1 Bleed", CrashPointDestination + "crashPoint_1_bleed.wav", defaultMidiNotes[21], curveFor3[0], curveFor3[1] - 1, CrashRelease, 2.08, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashPoint 2 Bleed", CrashPointDestination + "crashPoint_2_bleed.wav", defaultMidiNotes[21], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.96, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashPoint 3 Bleed", CrashPointDestination + "crashPoint_3_bleed.wav", defaultMidiNotes[21], curveFor3[2], curveFor3[3] - 1, CrashRelease, 3.20, "CymbalsBleed", samplers, formatManager);

            string CrashBellDestination = CrashAllDestination + "crashBell/";
            addSample("Dry CrashBell 1 OH", CrashBellDestination + "crashBell_1_OH.wav", defaultMidiNotes[22], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashBell 2 OH", CrashBellDestination + "crashBell_2_OH.wav", defaultMidiNotes[22], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashBell 3 OH", CrashBellDestination + "crashBell_3_OH.wav", defaultMidiNotes[22], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashBell 1 Room", CrashBellDestination + "crashBell_1_room.wav", defaultMidiNotes[22], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashBell 2 Room", CrashBellDestination + "crashBell_2_room.wav", defaultMidiNotes[22], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashBell 3 Room", CrashBellDestination + "crashBell_3_room.wav", defaultMidiNotes[22], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashBell 1 Bleed", CrashBellDestination + "crashBell_1_bleed.wav", defaultMidiNotes[22], curveFor3[0], curveFor3[1] - 1, CrashRelease, 1.22, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashBell 2 Bleed", CrashBellDestination + "crashBell_2_bleed.wav", defaultMidiNotes[22], curveFor3[1], curveFor3[2] - 1, CrashRelease, 1.84, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashBell 3 Bleed", CrashBellDestination + "crashBell_3_bleed.wav", defaultMidiNotes[22], curveFor3[2], curveFor3[3] - 1, CrashRelease, 2.81, "CymbalsBleed", samplers, formatManager);

            double CrashOpenRelease = 0.14;
            double CrashOpenMaxLen = 6.0;
            string CrashOpenDestination = CrashAllDestination + "crashOpen/";
            addSample("Dry CrashOpen 1 OH", CrashOpenDestination + "crashOpen_1_OH.wav", defaultMidiNotes[23], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashOpen 2 OH", CrashOpenDestination + "crashOpen_2_OH.wav", defaultMidiNotes[23], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashOpen 3 OH", CrashOpenDestination + "crashOpen_3_OH.wav", defaultMidiNotes[23], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashOpen 4 OH", CrashOpenDestination + "crashOpen_4_OH.wav", defaultMidiNotes[23], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsOH", samplers, formatManager);
            addSample("Dry CrashOpen 1 Room", CrashOpenDestination + "crashOpen_1_room.wav", defaultMidiNotes[23], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashOpen 2 Room", CrashOpenDestination + "crashOpen_2_room.wav", defaultMidiNotes[23], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashOpen 3 Room", CrashOpenDestination + "crashOpen_3_room.wav", defaultMidiNotes[23], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashOpen 4 Room", CrashOpenDestination + "crashOpen_4_room.wav", defaultMidiNotes[23], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsRoom", samplers, formatManager);
            addSample("Dry CrashOpen 1 Bleed", CrashOpenDestination + "crashOpen_1_bleed.wav", defaultMidiNotes[23], curveFor4[0], curveFor4[1] - 1, CrashOpenRelease, 2.45, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashOpen 2 Bleed", CrashOpenDestination + "crashOpen_2_bleed.wav", defaultMidiNotes[23], curveFor4[1], curveFor4[2] - 1, CrashOpenRelease, 3.30, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashOpen 3 Bleed", CrashOpenDestination + "crashOpen_3_bleed.wav", defaultMidiNotes[23], curveFor4[2], curveFor4[3] - 1, CrashOpenRelease, 3.80, "CymbalsBleed", samplers, formatManager);
            addSample("Dry CrashOpen 4 Bleed", CrashOpenDestination + "crashOpen_4_bleed.wav", defaultMidiNotes[23], curveFor4[3], curveFor4[4] - 1, CrashOpenRelease, 4.90, "CymbalsBleed", samplers, formatManager);
        }

        if (missingSample)
        {
            loadEssentialSamples(samplePack, samplers, formatManager);
        }
    }



private:
    
    int defaultMidiNotes[27] = { 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };
    
    float curveFor3[4] = { 0.0, 43.0, 85.0, 129.0 };
    float curveFor4[5] = { 0.0, 32.0, 64.0, 96.0, 129.0 };
    float curveFor5[6] = { 0.0, 26.0, 51.0, 77.0, 102.0, 129.0 };
    float curveFor6[7] = { 0.0, 21.0, 43.0, 64.0, 85.0, 107.0, 129.0 };
    float curveFor7[8] = { 0.0, 18.0, 37.0, 55.0, 73.0, 91.0, 110.0, 129.0 };
};