#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "MainSlidersPage.h"
#include "CymbalsSlidersPage.h"
#include "MidiNotesChoosingPage.h"

class HDrumsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HDrumsAudioProcessorEditor(HDrumsAudioProcessor&);
    ~HDrumsAudioProcessorEditor() override;

    juce::ShapeButton guiKickButton;
    juce::ShapeButton guiSnareButton;
    juce::ShapeButton guiTomButton;
    juce::ShapeButton guiFTomButton;
    juce::ShapeButton guiTambButton;
    juce::ShapeButton guiHHButton;
    juce::ShapeButton guiRideButton;
    juce::ShapeButton guiCrashButton;
    juce::ShapeButton guiPiccoloButton;
    juce::ShapeButton guiStackButton;

    juce::TabbedComponent myTabbedComponent;
    MainSlidersPage mainSlidersPage;
    KickSlidersPage kickSlidersPage;
    SnareSlidersPage snareSlidersPage;
    TomsSlidersPage tomsSlidersPage;
    CymbalsSlidersPage cymbalsSlidersPage;
    MidiNotesChoosingPage midiNotesChoosingPage;


    std::vector<juce::ComboBox*> midiNoteHiddenMenus = { & midiNotesChoosingPage.kickNoteMenu, & midiNotesChoosingPage.snareNoteMenu, & midiNotesChoosingPage.snareSwirlNoteMenu,
                & midiNotesChoosingPage.snareFlamNoteMenu, & midiNotesChoosingPage.snareRoundNoteMenu, & midiNotesChoosingPage.snareWirelessNoteMenu,
                & midiNotesChoosingPage.snareWirelessRoundNoteMenu, & midiNotesChoosingPage.snarePiccoloNoteMenu, & midiNotesChoosingPage.snarePiccoloSwirlNoteMenu,
                & midiNotesChoosingPage.tomNoteMenu, & midiNotesChoosingPage.tomFlamNoteMenu, & midiNotesChoosingPage.ftomNoteMenu, & midiNotesChoosingPage.ftomFlamNoteMenu,
                & midiNotesChoosingPage.hhFootNoteMenu, & midiNotesChoosingPage.hhClosedNoteMenu, & midiNotesChoosingPage.hhHalfNoteMenu, & midiNotesChoosingPage.hhOpenNoteMenu, & midiNotesChoosingPage.tambNoteMenu,
                & midiNotesChoosingPage.ridePointNoteMenu, & midiNotesChoosingPage.rideBellNoteMenu, & midiNotesChoosingPage.rideOpenNoteMenu,
                & midiNotesChoosingPage.crashPointNoteMenu, & midiNotesChoosingPage.crashBellNoteMenu, & midiNotesChoosingPage.crashOpenNoteMenu,
                & midiNotesChoosingPage.stackClosedNoteMenu, & midiNotesChoosingPage.stackOpenNoteMenu, & midiNotesChoosingPage.sticksNoteMenu };


    // =====================================================================
    void soloStateChanged(int soloButtonId);

    MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;
    std::vector<juce::ToggleButton*> soloButtons = { & kickSlidersPage.kickCloseSolo, & kickSlidersPage.kickOHSolo, & kickSlidersPage.kickRoomSolo, & kickSlidersPage.kickBleedSolo,
                    & snareSlidersPage.snareTopSolo, & snareSlidersPage.snareBotSolo, & snareSlidersPage.snareOHSolo,& snareSlidersPage.snareRoomSolo, & snareSlidersPage.snareBleedSolo,
                    & tomsSlidersPage.tomCloseSolo,& tomsSlidersPage.ftomCloseSolo,& tomsSlidersPage.tomsOHSolo,& tomsSlidersPage.tomsRoomSolo,& tomsSlidersPage.tomsBleedSolo,
                    & cymbalsSlidersPage.hhCloseSolo,& cymbalsSlidersPage.cymbalsOHSolo,& cymbalsSlidersPage.cymbalsRoomSolo,& cymbalsSlidersPage.cymbalsBleedSolo };
    
    std::vector<juce::ToggleButton*> muteButtons = { & kickSlidersPage.kickCloseMute, & kickSlidersPage.kickOHMute, & kickSlidersPage.kickRoomMute, & kickSlidersPage.kickBleedMute,
            & snareSlidersPage.snareTopMute, & snareSlidersPage.snareBotMute, & snareSlidersPage.snareOHMute, & snareSlidersPage.snareRoomMute, & snareSlidersPage.snareBleedMute,
            & tomsSlidersPage.tomCloseMute,& tomsSlidersPage.ftomCloseMute,& tomsSlidersPage.tomsOHMute,& tomsSlidersPage.tomsRoomMute,& tomsSlidersPage.tomsBleedMute,
            & cymbalsSlidersPage.hhCloseMute,& cymbalsSlidersPage.cymbalsOHMute,& cymbalsSlidersPage.cymbalsRoomMute,& cymbalsSlidersPage.cymbalsBleedMute };
    
    bool muteStateBeforeFirstSolo[18] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool soloAlreadyEngaged = false;

    std::vector<juce::AudioProcessorValueTreeState::ButtonAttachment*> soloButtonsStates = {
                            kickCloseSoloState, kickOHSoloState, kickRoomSoloState, kickBleedSoloState,
                            snareTopSoloState, snareBotSoloState, snareOHSoloState, snareRoomSoloState, snareBleedSoloState,
                            tomCloseSoloState, ftomCloseSoloState, tomsOHSoloState, tomsRoomSoloState, tomsBleedSoloState,
                            hhCloseSoloState, cymbalsOHSoloState, cymbalsRoomSoloState, cymbalsBleedSoloState };

    std::vector<juce::AudioProcessorValueTreeState::ButtonAttachment*> muteButtonsStates = {
                            kickCloseMuteState, kickOHMuteState, kickRoomMuteState, kickBleedMuteState,
                            snareTopMuteState, snareBotMuteState, snareOHMuteState, snareRoomMuteState, snareBleedMuteState,
                            tomCloseMuteState, ftomCloseMuteState, tomsOHMuteState, tomsRoomMuteState, tomsBleedMuteState,
                            hhCloseMuteState, cymbalsOHMuteState, cymbalsRoomMuteState, cymbalsBleedMuteState };
    // =====================================================================================================

    juce::Font textFont{ 12.0f };
    juce::ComboBox samplePackMenu;
    juce::ComboBox curveMenu;

    void paint (juce::Graphics&) override;
    void resized() override;

    HDrumsAudioProcessor& audioProcessor;

    // comboBox attachments ==========================================================================
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> samplePackAttachment;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> curveMenuAttachment;

    // MIDI note combobox attachments =====================================================
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> kickNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareSwirlNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareRoundNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareWirelessNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snareWirelessRoundNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snarePiccoloNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> snarePiccoloSwirlNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> tomNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> tomFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> ftomNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> ftomFlamNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> hhFootNote;
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
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> stackClosedNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> stackOpenNote;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> sticksNote;

    // Slider values attachments ========================================================== 
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

    // Solo buttons attachments ==============================================================
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> binauralState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> closeSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> OHSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> roomSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> bleedSoloState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickCloseSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickOHSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickRoomSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickBleedSoloState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareTopSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareBotSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareOHSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareRoomSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareBleedSoloState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomCloseSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> ftomCloseSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsOHSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsRoomSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsBleedSoloState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> hhCloseSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsOHSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsRoomSoloState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsBleedSoloState;

    // Mute Buttons attachments ==============================================================
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> closeMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> OHMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> roomMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> bleedMuteState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickCloseMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickOHMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickRoomMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> kickBleedMuteState;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareTopMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareBotMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareOHMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareRoomMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> snareBleedMuteState;
    
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomCloseMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> ftomCloseMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsOHMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsRoomMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> tomsBleedMuteState;
    
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> hhCloseMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsOHMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsRoomMuteState;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ButtonAttachment> cymbalsBleedMuteState;

private:
    
    juce::AudioFormatManager formatManager;

    juce::Image electronicBackground;
    juce::Image acousticBackground;
    juce::Image dryBackground;

    juce::ToggleButton binauralButton;
    MyLookAndFeelBinaural myLookAndFeelBinaural;

    void setNoteInMidiNotesChoosingPage(juce::ComboBox& menu, std::atomic <float>* note);
    void velocityCurveChanged();
    void samplePackMenuChanged();
    void midiNoteChanged();
    void midiNoteChanged2();
    void changeMidiNoteMenuWhenSoundChanged();
    void playMidiNote(int noteNumber);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HDrumsAudioProcessorEditor)
};