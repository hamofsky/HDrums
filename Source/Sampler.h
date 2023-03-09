#pragma once
#define SAMPLER_H_INCLUDED

#include "JuceHeader.h"

class Sampler : public juce::Synthesiser
{
public:
    void noteOn(const int midiChannel, const int midiNoteNumber, const float velocity) override;
    void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override;
    
private:
    int minimumSubBlockSize = 32;
    bool subBlockSubdivisionIsStrict = false;
    double currentSampleRate = 44100.0;
    float* gainValue;

};