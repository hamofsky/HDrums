#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    bool logarhytmic = false;
    float maxValueOfLogCurve = log10(128);

    int defaultMidiNotes[28] = { 0, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };
    int newMidiNotes[28] = { 0, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };

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
                
                for (int i = 0; i < 19; i++)
                {
                    if (currentMessage.getNoteNumber() == newMidiNotes[i] && newMidiNotes[i] != defaultMidiNotes[i])
                        currentMessage.setNoteNumber(defaultMidiNotes[i]);
                    else if (currentMessage.getNoteNumber() == defaultMidiNotes[i] && newMidiNotes[i] != defaultMidiNotes[i])
                        currentMessage.setNoteNumber(newMidiNotes[i]);
                }

                processedBuffer.addEvent(currentMessage, samplePos);

            }

        }
        midiMessages.swapWith(processedBuffer);
    }
    juce::MidiBuffer processedBuffer;

private:
    juce::AudioFormatManager mFormatManager;
};