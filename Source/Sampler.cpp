#include "Sampler.h"
#include "SamplerSoundLayer.h"

void Sampler::noteOn(const int midiChannel, const int midiNoteNumber, const float velocity)
{
    const juce::ScopedLock sl(lock);

    for (int i = sounds.size(); --i >= 0;)
    {
        juce::SynthesiserSound* const soundSource = sounds.getUnchecked(i).get();
        SamplerSoundLayer* const sound = static_cast<SamplerSoundLayer* const> (soundSource);

        if (sound->appliesTo(midiNoteNumber, velocity)
            && sound->appliesToChannel(midiChannel))
        {
            for (int j = voices.size(); --j >= 0; )
            {
                juce::SynthesiserVoice* const voice = voices.getUnchecked(j);
                // wyjatek dla HH Open (87) konczacy sie przy uderzeniu w HH Half (86) || HH Closed (85) || HH Foot (84)
                if (voice->getCurrentlyPlayingNote() == 87)
                {
                    if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(86, velocity)))
                        stopVoice(voice, 1.0f, true);
                    else if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(85, velocity)))
                        stopVoice(voice, 1.0f, true);
                    else if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(84, velocity)))
                        stopVoice(voice, 1.0f, true);
                }
                // analogicznie dla HH Half (86) zamykanego przez HH Open (87) || HH Closed (85) || HH Foot (84)
                else if (voice->getCurrentlyPlayingNote() == 86)
                {
                    if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(87, velocity)))
                        stopVoice(voice, 1.0f, true);
                    else if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(85, velocity)))
                        stopVoice(voice, 1.0f, true);
                    else if (voice->isPlayingChannel(midiChannel) && (sound->appliesTo(84, velocity)))
                        stopVoice(voice, 1.0f, true);
                }
                // pozostale przypadki (ta sama nuta konczy te sama)
                else if (voice->getCurrentlyPlayingNote() == midiNoteNumber
                    && voice->isPlayingChannel(midiChannel) && sound->appliesTo(midiNoteNumber, velocity))
                    stopVoice(voice, 1.0f, true);
            }
            startVoice(findFreeVoice(sound, midiChannel, midiNoteNumber, isNoteStealingEnabled()),
                sound, midiChannel, midiNoteNumber, velocity);
        }
    }
}

void Sampler::noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff)
{
    const juce::ScopedLock sl(lock);

    for (auto* voice : voices)
    {
        if (voice->getCurrentlyPlayingNote() == midiNoteNumber
            && voice->isPlayingChannel(midiChannel))
        {
            if (auto sound = voice->getCurrentlyPlayingSound())
            {
                if (sound->appliesToNote(midiNoteNumber)
                    && sound->appliesToChannel(midiChannel))
                {
                    //jassert(!voice->keyIsDown || voice->isSustainPedalDown() == sustainPedalsDown[midiChannel]);

                    voice->setKeyDown(true);

                    //if (!(voice->isSustainPedalDown() || voice->isSostenutoPedalDown()))
                        //stopVoice(voice, velocity, false);
                }
            }
        }
    }
}