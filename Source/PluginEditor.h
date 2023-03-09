#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class HDrumsAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    HDrumsAudioProcessorEditor (HDrumsAudioProcessor&);
    ~HDrumsAudioProcessorEditor() override;

    juce::Font textFont{ 12.0f };
    juce::ComboBox samplePackMenu;
    juce::ComboBox curveMenu;

    juce::ComboBox snareNoteMenu;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;//

    HDrumsAudioProcessor& audioProcessor;

    juce::TextButton snareDrumButton;
    juce::TextButton kickDrumButton;
    juce::TextButton floorTomButton;
    juce::TextButton floorTomButton2;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> OHsliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> RoomSliderValue;

private:
    
    juce::TextButton openButton;
    //juce::String loadDirectory();
    juce::AudioFormatManager formatManager;

    juce::Slider gainSlider;
    juce::Label gainLabel;
    juce::Slider OHgainSlider;
    juce::Label OHgainLabel;
    juce::Slider RoomGainSlider;
    juce::Label RoomGainLabel;

    void samplePackMenuChanged();

    juce::String midiNotes[128] = {"C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
                                    "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
                                    "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
                                    "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
                                    "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A4", "B4",
                                    "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
                                    "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
                                    "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
                                    "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "A#8", "B8",
                                    "C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "A#9", "B9",
                                    "C10", "C#10", "D10", "D#10", "E10", "F10", "F#10", "G10"};

    void playMidiNote(int noteNumber);
    
    juce::Image background;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessorEditor)
};