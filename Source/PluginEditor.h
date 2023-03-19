#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "HHSlidersPage.h"
#include "CymbalsSlidersPage.h"
#include "MidiNoteChoosingPage.h"

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
    MidiNotesChoosingPage midiNotesChoosingPage;

    juce::Font textFont{ 12.0f };
    juce::ComboBox samplePackMenu;
    juce::ComboBox curveMenu;

    void paint (juce::Graphics&) override;
    void resized() override;

    HDrumsAudioProcessor& audioProcessor;

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

    //juce::TextButton openButton;
    //juce::String loadDirectory();

    juce::Image background;
    juce::Image background2;

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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessorEditor)
};