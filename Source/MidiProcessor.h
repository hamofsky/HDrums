#pragma once
#include "JuceHeader.h"
#include <cmath>
using namespace std;

class MidiProcessor {
public:
    bool natural = false;
    float P0[2] = { 0 , 0 };
    float P1[2] = { 35 , 0.8 };
    float P2[2] = { 128 , 1 };
    float naturalCurve[128];
    float naturalCurveApproximation[128] = { 0,	0.025, 0.0498, 0.0621, 0.0864, 0.1104, 0.1223, 0.1458, 0.1575, 0.1806, 0.1921, 0.2147, 0.2259, 0.2482, 0.2592, 0.2809, 0.2917, 0.3024, 0.3236, 0.3341, 0.3445, 0.3651, 0.3752, 0.3853, 0.3954, 0.4152, 0.425, 0.4348, 0.4444, 0.454, 0.4729, 0.4823, 0.4916, 0.5008, 0.51, 0.519, 0.528, 0.5369, 0.5545, 0.5632, 0.5718, 0.5804, 0.5889, 0.5972, 0.6056, 0.6138, 0.622, 0.6301, 0.6381, 0.6461, 0.6539, 0.6617, 0.6695, 0.6771, 0.6847, 0.6922, 0.6996, 0.707, 0.7142, 0.7214, 0.7286, 0.7286, 0.7356, 0.7426, 0.7495, 0.7564, 0.7631, 0.7698, 0.7764, 0.7829, 0.7894, 0.7894, 0.7958, 0.8021, 0.8083, 0.8145, 0.8206, 0.8266, 0.8266, 0.8325, 0.8384, 0.8442, 0.8499, 0.8556, 0.8556, 0.8611, 0.8666, 0.872, 0.8774, 0.8774, 0.8826, 0.8878, 0.893, 0.898, 0.898, 0.903, 0.9079, 0.9127, 0.9127, 0.9175, 0.9221, 0.9267, 0.9267, 0.9313, 0.9357, 0.9401, 0.9401, 0.9444, 0.9486, 0.9528, 0.9528, 0.9568, 0.9609, 0.9609, 0.9648, 0.9686, 0.9724, 0.9724, 0.9761, 0.9798, 0.9798, 0.9833, 0.9868, 0.9902, 0.9902, 0.9936, 0.9968, 0.9968 };
    void initializeCurve()
    {
        for (int i = 0; i < 128; i++)
        {
            float a = pow((1 - i / 128.0), 2);
            float b = pow(i / 128.0, 2);
            naturalCurve[i] == P0[1] * a + P1[1] * 2 * i / 128.0 * (1 - i / 128.0) + P2[1] * b;
        }
    }

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
                if (natural)
                    currentMessage.setVelocity(naturalCurveApproximation[currentMessage.getVelocity()]);    // setVelocity takes velocity values from 0 to 1
                
                for (int i = 0; i < 28; i++)
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