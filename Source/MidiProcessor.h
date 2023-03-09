#pragma once

#include "JuceHeader.h"

class MidiProcessor {
public:
    void process(juce::MidiBuffer& midiMessages)
    {
        processedBuffer.clear();

        juce::MidiBuffer::Iterator it(midiMessages);
        juce::MidiMessage currentMessage;
        int samplePos;

        //processedBuffer.addEvent(currentMessage, samplePos);

        while (it.getNextEvent(currentMessage, samplePos))
        {
            DBG(currentMessage.getDescription());
            if (currentMessage.isNoteOn())
            {
                //currentMessage.setNoteNumber(60);
                processedBuffer.addEvent(currentMessage, samplePos);

            }

        }
        midiMessages.swapWith(processedBuffer);
    }
    juce::MidiBuffer processedBuffer;

private:
    juce::AudioFormatManager mFormatManager;
};