#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    bool logarhytmic = false;
    float maxValueOfLogCurve = log10(128);

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
                {
                    currentMessage.setVelocity(log10(currentMessage.getVelocity()) / maxValueOfLogCurve);    // setVelocity takes velocity values from 0 to 1
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