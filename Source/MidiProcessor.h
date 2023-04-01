#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    bool logarhytmic = false;
    float maxValueOfLogCurve = log10(128);
    int newKickMidiNote = 59 + 12;
    int newSnareMidiNote = 60 + 12;
    int newSnareFlamMidiNote = 61 + 12;
    int newSnareRoundMidiNote = 62 + 12;
    int newSnareWirelessMidiNote = 63 + 12;
    int newSnareWirelessRoundMidiNote = 64 + 12;
    int newTomMidiNote = 66 + 12;
    int newTomFlamMidiNote = 67 + 12;
    int newFTomMidiNote = 68 + 12;
    int newFTomFlamMidiNote = 69 + 12;
    int newTambMidiNote = 71 + 12;
    int newHHClosedMidiNote = 73 + 12;
    int newHHHalfMidiNote = 74 + 12;
    int newHHOpenMidiNote = 75 + 12;
    int newRidePointMidiNote = 78 + 12;
    int newRideBellMidiNote = 79 + 12;
    int newRideOpenMidiNote = 80 + 12;
    int newCrashPointMidiNote = 82 + 12;
    int newCrashBellMidiNote = 83 + 12;
    int newCrashOpenMidiNote = 84 + 12;

    void process(juce::MidiBuffer& midiMessages)
    {
        processedBuffer.clear();

        juce::MidiBuffer::Iterator it(midiMessages);
        juce::MidiMessage currentMessage;
        int samplePos;


        while (it.getNextEvent(currentMessage, samplePos))
        {
            DBG(currentMessage.getDescription());
            if (currentMessage.isNoteOn())
            {
                if (logarhytmic)
                    currentMessage.setVelocity(log10(currentMessage.getVelocity()) / maxValueOfLogCurve);    // setVelocity takes velocity values from 0 to 1

                if (currentMessage.getNoteNumber() == newKickMidiNote)
                    currentMessage.setNoteNumber(59 + 12);
                if (currentMessage.getNoteNumber() == newSnareMidiNote)
                    currentMessage.setNoteNumber(60 + 12);
                if (currentMessage.getNoteNumber() == newSnareFlamMidiNote)
                    currentMessage.setNoteNumber(61 + 12);
                if (currentMessage.getNoteNumber() == newSnareRoundMidiNote)
                    currentMessage.setNoteNumber(62 + 12);
                if (currentMessage.getNoteNumber() == newSnareWirelessMidiNote)
                    currentMessage.setNoteNumber(63 + 12);
                if (currentMessage.getNoteNumber() == newSnareWirelessRoundMidiNote)
                    currentMessage.setNoteNumber(64 + 12);
                if (currentMessage.getNoteNumber() == newTomMidiNote)
                    currentMessage.setNoteNumber(66 + 12);
                if (currentMessage.getNoteNumber() == newTomFlamMidiNote)
                    currentMessage.setNoteNumber(67 + 12);
                if (currentMessage.getNoteNumber() == newFTomMidiNote)
                    currentMessage.setNoteNumber(68 + 12);
                if (currentMessage.getNoteNumber() == newFTomFlamMidiNote)
                    currentMessage.setNoteNumber(69 + 12);
                if (currentMessage.getNoteNumber() == newTambMidiNote)
                    currentMessage.setNoteNumber(71 + 12);
                if (currentMessage.getNoteNumber() == newHHClosedMidiNote)
                    currentMessage.setNoteNumber(73 + 12);
                if (currentMessage.getNoteNumber() == newHHHalfMidiNote)
                    currentMessage.setNoteNumber(74 + 12);
                if (currentMessage.getNoteNumber() == newHHOpenMidiNote)
                    currentMessage.setNoteNumber(75 + 12);
                if (currentMessage.getNoteNumber() == newRidePointMidiNote)
                    currentMessage.setNoteNumber(78 + 12);
                if (currentMessage.getNoteNumber() == newRideBellMidiNote)
                    currentMessage.setNoteNumber(79 + 12);
                if (currentMessage.getNoteNumber() == newRideOpenMidiNote)
                    currentMessage.setNoteNumber(80 + 12);
                if (currentMessage.getNoteNumber() == newCrashPointMidiNote)
                    currentMessage.setNoteNumber(82 + 12);
                if (currentMessage.getNoteNumber() == newCrashBellMidiNote)
                    currentMessage.setNoteNumber(83 + 12);
                if (currentMessage.getNoteNumber() == newCrashOpenMidiNote)
                    currentMessage.setNoteNumber(84 + 12);

                processedBuffer.addEvent(currentMessage, samplePos);

            }

        }
        midiMessages.swapWith(processedBuffer);
    }
    juce::MidiBuffer processedBuffer;

private:
    juce::AudioFormatManager mFormatManager;
};