#include "SamplerSoundLayer.h"

SamplerSoundLayer::SamplerSoundLayer(const juce::String& soundName,
    juce::AudioFormatReader& source, const juce::BigInteger& notes,
    const int midiNoteForNormalPitch, juce::Range<float> velocityRange,
    const double attackTimeSecs, const double releaseTimeSecs,
    const double maxSampleLengthSeconds) : SamplerSound(
        soundName, source, notes, midiNoteForNormalPitch,
        attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds),
    velocity(velocityRange) {}

SamplerSoundLayer::~SamplerSoundLayer()
{
}

bool SamplerSoundLayer::appliesTo(int midiNoteNumber, float velocity)
{
    bool appliesToMidiNote = appliesToNote(midiNoteNumber);
    bool isInVelocityRange = this->velocity.contains(velocity);

    return appliesToMidiNote && isInVelocityRange;
}
