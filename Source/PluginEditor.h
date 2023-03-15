#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "HHSlidersPage.h"
#include "CymbalsSlidersPage.h"

class HDrumsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HDrumsAudioProcessorEditor(HDrumsAudioProcessor&);
    ~HDrumsAudioProcessorEditor() override;

    juce::TabbedComponent myTabbedComponent;
    KickSlidersPage kickSlidersPage;
    SnareSlidersPage snareSlidersPage;
    TomsSlidersPage tomsSlidersPage;
    HHSlidersPage hhSlidersPage;
    CymbalsSlidersPage cymbalsSlidersPage;

    juce::Font textFont{ 12.0f };
    juce::ComboBox samplePackMenu;
    juce::ComboBox curveMenu;

    juce::ComboBox snareNoteMenu;
    juce::ComboBox kickNoteMenu;

    void paint (juce::Graphics&) override;
    void resized() override;

    HDrumsAudioProcessor& audioProcessor;

    juce::TextButton snareDrumButton;
    juce::TextButton kickDrumButton;
    juce::TextButton floorTomButton;
    juce::TextButton floorTomButton2;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> OHsliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> RoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> BleedSliderValue;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> kickCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> kickOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> kickRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> kickBleedSliderValue;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareTopCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareBotCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareBleedSliderValue;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> tomCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> ftomCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> tomsOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> tomsRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> tomsBleedSliderValue;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> hhCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> tambCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> hhOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> hhRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> hhBleedSliderValue;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> crashCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> rideCloseSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsBleedSliderValue;

private:
    
    juce::AudioFormatManager formatManager;

    juce::TextButton openButton;
    //juce::String loadDirectory();

    juce::Image background;

    juce::Slider gainSlider;
    juce::Slider OHgainSlider;
    juce::Slider RoomGainSlider;
    juce::Slider BleedGainSlider;
    juce::Label gainLabel;
    juce::Label OHgainLabel;
    juce::Label RoomGainLabel;
    juce::Label BleedGainLabel;

    void samplePackMenuChanged();
    void playMidiNote(int noteNumber);

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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessorEditor)
};