#pragma once
#ifndef SAMPLERSOUNDLAYER_H_INCLUDED
#define SAMPLERSOUNDLAYER_H_INCLUDED

#include "JuceHeader.h"

class SamplerSoundLayer : public juce::SamplerSound
{
public:
    SamplerSoundLayer(const juce::String& name,
        juce::AudioFormatReader& source, const juce::BigInteger& midiNotes,
        int midiNoteForNormalPitch, juce::Range<float> velocityRange,
        double attackTimeSecs, double releaseTimeSecs,
        double maxSampleLengthSeconds);

    ~SamplerSoundLayer();
    bool appliesTo(int midiNoteNumber, float velocity);
private:
    juce::Range<float> velocity;
};

#endif