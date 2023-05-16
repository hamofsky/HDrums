#pragma once
#include "SamplerSoundLayer.h"
using namespace std;

class LoadingSamples
{
public:
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

    void loadAcousticSamples(std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {

    }

    void loadDrySamples(std::vector<Sampler*> samplers, juce::AudioFormatManager &formatManager)
    {
        string destinationAll = "C:/Users/damia/Desktop/Sampelki/";

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



private:
    
    int defaultMidiNotes[27] = { 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };
    
    float curveFor3[4] = { 0.0, 43.0, 85.0, 129.0 };
    float curveFor4[5] = { 0.0, 32.0, 64.0, 96.0, 129.0 };
    float curveFor5[6] = { 0.0, 26.0, 51.0, 77.0, 102.0, 129.0 };
    float curveFor6[7] = { 0.0, 21.0, 43.0, 64.0, 85.0, 107.0, 129.0 };
    float curveFor7[8] = { 0.0, 18.0, 37.0, 55.0, 73.0, 91.0, 110.0, 129.0 };
};