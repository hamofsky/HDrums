#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    bool logarhytmic = false;
    float maxValueOfLogCurve = log10(128);

    int defaultMidiNotes[20] = { 71, 72, 73, 74, 75, 76, 78, 79, 80, 81, 83, 85, 86, 87, 90, 91, 92, 94, 95, 96 };
    int newMidiNotes[20] = { 71, 72, 73, 74, 75, 76, 78, 79, 80, 81, 83, 85, 86, 87, 90, 91, 92, 94, 95, 96 };

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
                    if (currentMessage.getNoteNumber() == defaultMidiNotes[i] && newMidiNotes[i] != defaultMidiNotes[i])
                        currentMessage.setNoteNumber(newMidiNotes[i]);
                    else if (currentMessage.getNoteNumber() == newMidiNotes[i] && newMidiNotes[i] != defaultMidiNotes[i])
                        currentMessage.setNoteNumber(defaultMidiNotes[i]);
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