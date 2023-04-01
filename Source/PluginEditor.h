#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "MainSlidersPage.h"
#include "CymbalsSlidersPage.h"
#include "MidiNoteChoosingPage.h"

class HDrumsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HDrumsAudioProcessorEditor(HDrumsAudioProcessor&);
    ~HDrumsAudioProcessorEditor() override;

    juce::TabbedComponent myTabbedComponent;
    MainSlidersPage mainSlidersPage;
    KickSlidersPage kickSlidersPage;
    SnareSlidersPage snareSlidersPage;
    TomsSlidersPage tomsSlidersPage;
    CymbalsSlidersPage cymbalsSlidersPage;
    MidiNotesChoosingPage midiNotesChoosingPage;

    juce::Font textFont{ 12.0f };
    juce::ComboBox samplePackMenu;
    juce::ComboBox curveMenu;

    void paint (juce::Graphics&) override;
    void resized() override;

    HDrumsAudioProcessor& audioProcessor;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> samplePackAttachment;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> curveMenuAttachment;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> kickNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareRoundNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareWirelessNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareWirelessRoundNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> tomNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> tomFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> ftomNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> ftomFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> hhClosedNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> hhHalfNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> hhOpenNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> tambNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> ridePointNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> rideBellNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> rideOpenNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> crashPointNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> crashBellNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> crashOpenNote;

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
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsOHSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsRoomSliderValue;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cymbalsBleedSliderValue;

private:
    
    juce::AudioFormatManager formatManager;

    //juce::TextButton openButton;
    //juce::String loadDirectory();

    juce::Image background;
    juce::Image background2;
    juce::Image dryBackground;

    void velocityCurveChanged();
    void samplePackMenuChanged();
    void midiNoteChanged();
    void playMidiNote(int noteNumber);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessorEditor)
};