#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"
#include "MidiProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "MainSlidersPage.h"
#include "CymbalsSlidersPage.h"
#include "MidiNotesChoosingPage.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

HDrumsAudioProcessorEditor::HDrumsAudioProcessorEditor(HDrumsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), myTabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
    mainSlidersPage(), kickSlidersPage(), snareSlidersPage(), tomsSlidersPage(), cymbalsSlidersPage(), midiNotesChoosingPage(),
    guiKickButton("GUI Kick Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.07f)),
    guiSnareButton("GUI Snare Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiTomButton("GUI Tom Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiFTomButton("GUI FTom Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiTambButton("GUI Tamb Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiHHButton("GUI HH Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiRideButton("GUI Ride Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiCrashButton("GUI Crash Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiPiccoloButton("GUI Piccolo Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f)),
    guiStackButton("GUI Stack Button", juce::Colours::black.withAlpha(0.001f), juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.1f))
{
    setSize(1050, 500);
    
    //midiNoteChanged();

    // GUI Buttons overlaying the artwork ==============================================================
    juce::Path guiKickButtonShape;
    juce::Path guiSnareButtonShape;
    juce::Path guiTomButtonShape;
    juce::Path guiFTomButtonShape;
    juce::Path guiTambButtonShape;
    juce::Path guiHHButtonShape;
    juce::Path guiRideButtonShape;
    juce::Path guiCrashButtonShape;
    juce::Path guiPiccoloButtonShape;
    juce::Path guiStackButtonShape;
    guiKickButtonShape.addEllipse(0, 0, 149.0f, 149.0f);
    guiSnareButtonShape.addEllipse(0, 0, 123.0f, 66.0f);
    guiTomButtonShape.addEllipse(0, 0, 84.0f, 35.0f);
    guiFTomButtonShape.addEllipse(0, 0, 125.0f, 61.0f);
    guiTambButtonShape.addEllipse(0, 0, 78.0f, 50.0f);
    guiHHButtonShape.addEllipse(0, 0, 122.0f, 46.0f);
    guiRideButtonShape.addEllipse(0, 0, 185.0f, 78.0f);
    guiCrashButtonShape.addEllipse(0, 0, 125.0f, 51.0f);
    guiPiccoloButtonShape.addEllipse(0, 0, 66.0f, 39.0f);
    guiStackButtonShape.addEllipse(0, 0, 152.0f, 62.0f);
    guiKickButton.setShape(guiKickButtonShape, true, true, false);
    guiSnareButton.setShape(guiSnareButtonShape, true, true, false);
    guiTomButton.setShape(guiTomButtonShape, true, true, false);
    guiFTomButton.setShape(guiFTomButtonShape, true, true, false);
    guiTambButton.setShape(guiTambButtonShape, true, true, false);
    guiHHButton.setShape(guiHHButtonShape, true, true, false);
    guiRideButton.setShape(guiRideButtonShape, true, true, false);
    guiCrashButton.setShape(guiCrashButtonShape, true, true, false);
    guiPiccoloButton.setShape(guiPiccoloButtonShape, true, true, false);
    guiStackButton.setShape(guiStackButtonShape, true, true, false);

    addAndMakeVisible(&guiKickButton);
    addAndMakeVisible(&guiSnareButton);
    addAndMakeVisible(&guiTomButton);
    addAndMakeVisible(&guiFTomButton);
    addAndMakeVisible(&guiTambButton);
    addAndMakeVisible(&guiHHButton);
    addAndMakeVisible(&guiRideButton);
    addAndMakeVisible(&guiCrashButton);
    addAndMakeVisible(&guiPiccoloButton);
    addAndMakeVisible(&guiStackButton);
    guiKickButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.kickNoteMenu.getSelectedId()); };
    guiSnareButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareNoteMenu.getSelectedId()); };
    guiTomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tomNoteMenu.getSelectedId()); };
    guiFTomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ftomNoteMenu.getSelectedId()); };
    guiTambButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tambNoteMenu.getSelectedId()); };
    guiHHButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId()); };
    guiRideButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ridePointNoteMenu.getSelectedId()); };
    guiCrashButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.crashOpenNoteMenu.getSelectedId()); };
    guiPiccoloButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snarePiccoloNoteMenu.getSelectedId()); };
    guiStackButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.stackOpenNoteMenu.getSelectedId()); };

    // Tabbed Component ===========================================================================
    addAndMakeVisible(&myTabbedComponent);
    myTabbedComponent.addTab("Main", juce::Colours::black.withAlpha(0.6f), &mainSlidersPage, true);
    myTabbedComponent.addTab("Kick", juce::Colours::black.withAlpha(0.6f), &kickSlidersPage, true);
    myTabbedComponent.addTab("Snare", juce::Colours::black.withAlpha(0.6f), &snareSlidersPage, true);
    myTabbedComponent.addTab("Toms", juce::Colours::black.withAlpha(0.6f), &tomsSlidersPage, true);
    myTabbedComponent.addTab("Cymbals", juce::Colours::black.withAlpha(0.6f), &cymbalsSlidersPage, true);
    myTabbedComponent.addTab("MIDI", juce::Colours::grey.withAlpha(0.7f), &midiNotesChoosingPage, true);

    // Slider attachments =========================================================================
    kickCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, KICK_CLOSE_GAIN_ID, kickSlidersPage.kickCloseSlider);
    kickOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, KICK_OH_GAIN_ID, kickSlidersPage.kickOHSlider);
    kickRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, KICK_ROOM_GAIN_ID, kickSlidersPage.kickRoomSlider);
    kickBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, KICK_BLEED_GAIN_ID, kickSlidersPage.kickBleedSlider);

    snareTopCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, SNARE_TOP_CLOSE_GAIN_ID, snareSlidersPage.snareTopCloseSlider);
    snareBotCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, SNARE_BOT_CLOSE_GAIN_ID, snareSlidersPage.snareBotCloseSlider);
    snareOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, SNARE_OH_GAIN_ID, snareSlidersPage.snareOHSlider);
    snareRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, SNARE_ROOM_GAIN_ID, snareSlidersPage.snareRoomSlider);
    snareBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, SNARE_BLEED_GAIN_ID, snareSlidersPage.snareBleedSlider);

    tomCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, TOM_CLOSE_GAIN_ID, tomsSlidersPage.tomCloseSlider);
    ftomCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, FTOM_CLOSE_GAIN_ID, tomsSlidersPage.ftomCloseSlider);
    tomsOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, TOMS_OH_GAIN_ID, tomsSlidersPage.tomsOHSlider);
    tomsRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, TOMS_ROOM_GAIN_ID, tomsSlidersPage.tomsRoomSlider);
    tomsBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, TOMS_BLEED_GAIN_ID, tomsSlidersPage.tomsBleedSlider);

    hhCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, HH_CLOSE_GAIN_ID, cymbalsSlidersPage.hhCloseSlider);
    cymbalsOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_OH_GAIN_ID, cymbalsSlidersPage.cymbalsOHSlider);
    cymbalsRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_ROOM_GAIN_ID, cymbalsSlidersPage.cymbalsRoomSlider);
    cymbalsBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_BLEED_GAIN_ID, cymbalsSlidersPage.cymbalsBleedSlider);

    // Solo buttons ==========================================================
    binauralState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, BINAURAL_ID, binauralButton);
    
    closeSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CLOSE_SOLO_ID, mainSlidersPage.closeSolo);
    OHSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, OH_SOLO_ID, mainSlidersPage.OHSolo);
    roomSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, ROOM_SOLO_ID, mainSlidersPage.roomSolo);
    bleedSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, BLEED_SOLO_ID, mainSlidersPage.bleedSolo);

    kickCloseSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_CLOSE_SOLO_ID, kickSlidersPage.kickCloseSolo);
    kickOHSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_OH_SOLO_ID, kickSlidersPage.kickOHSolo);
    kickRoomSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_ROOM_SOLO_ID, kickSlidersPage.kickRoomSolo);
    kickBleedSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_BLEED_SOLO_ID, kickSlidersPage.kickBleedSolo);

    snareTopSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_TOP_SOLO_ID, snareSlidersPage.snareTopSolo);
    snareBotSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_BOT_SOLO_ID, snareSlidersPage.snareBotSolo);
    snareOHSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_OH_SOLO_ID, snareSlidersPage.snareOHSolo);
    snareRoomSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_ROOM_SOLO_ID, snareSlidersPage.snareRoomSolo);
    snareBleedSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_BLEED_SOLO_ID, snareSlidersPage.snareBleedSolo);

    tomCloseSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOM_CLOSE_SOLO_ID, tomsSlidersPage.tomCloseSolo);
    ftomCloseSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, FTOM_CLOSE_SOLO_ID, tomsSlidersPage.ftomCloseSolo);
    tomsOHSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_OH_SOLO_ID, tomsSlidersPage.tomsOHSolo);
    tomsRoomSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_ROOM_SOLO_ID, tomsSlidersPage.tomsRoomSolo);
    tomsBleedSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_BLEED_SOLO_ID, tomsSlidersPage.tomsBleedSolo);

    hhCloseSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, HH_CLOSE_SOLO_ID, cymbalsSlidersPage.hhCloseSolo);
    cymbalsOHSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_OH_SOLO_ID, cymbalsSlidersPage.cymbalsOHSolo);
    cymbalsRoomSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_ROOM_SOLO_ID, cymbalsSlidersPage.cymbalsRoomSolo);
    cymbalsBleedSoloState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_BLEED_SOLO_ID, cymbalsSlidersPage.cymbalsBleedSolo);

    // Mute buttons ==========================================================
    closeMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CLOSE_MUTE_ID, mainSlidersPage.closeMute);
    OHMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, OH_MUTE_ID, mainSlidersPage.OHMute);
    roomMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, ROOM_MUTE_ID, mainSlidersPage.roomMute);
    bleedMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, BLEED_MUTE_ID, mainSlidersPage.bleedMute);

    kickCloseMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_CLOSE_MUTE_ID, kickSlidersPage.kickCloseMute);
    kickOHMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_OH_MUTE_ID, kickSlidersPage.kickOHMute);
    kickRoomMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_ROOM_MUTE_ID, kickSlidersPage.kickRoomMute);
    kickBleedMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, KICK_BLEED_MUTE_ID, kickSlidersPage.kickBleedMute);
    
    snareTopMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_TOP_MUTE_ID, snareSlidersPage.snareTopMute);
    snareBotMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_BOT_MUTE_ID, snareSlidersPage.snareBotMute);
    snareOHMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_OH_MUTE_ID, snareSlidersPage.snareOHMute);
    snareRoomMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_ROOM_MUTE_ID, snareSlidersPage.snareRoomMute);
    snareBleedMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, SNARE_BLEED_MUTE_ID, snareSlidersPage.snareBleedMute);
    
    tomCloseMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOM_CLOSE_MUTE_ID, tomsSlidersPage.tomCloseMute);
    ftomCloseMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, FTOM_CLOSE_MUTE_ID, tomsSlidersPage.ftomCloseMute);
    tomsOHMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_OH_MUTE_ID, tomsSlidersPage.tomsOHMute);
    tomsRoomMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_ROOM_MUTE_ID, tomsSlidersPage.tomsRoomMute);
    tomsBleedMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, TOMS_BLEED_MUTE_ID, tomsSlidersPage.tomsBleedMute);
    
    hhCloseMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, HH_CLOSE_MUTE_ID, cymbalsSlidersPage.hhCloseMute);
    cymbalsOHMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_OH_MUTE_ID, cymbalsSlidersPage.cymbalsOHMute);
    cymbalsRoomMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_ROOM_MUTE_ID, cymbalsSlidersPage.cymbalsRoomMute);
    cymbalsBleedMuteState = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.treeState, CYMBALS_BLEED_MUTE_ID, cymbalsSlidersPage.cymbalsBleedMute);

    samplePackAttachment = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SAMPLE_PACK_ID, samplePackMenu);
    curveMenuAttachment = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CURVE_MENU_ID, curveMenu);

    kickNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, KICK_MIDI_NOTE_ID, midiNotesChoosingPage.kickNoteMenu);
    snareNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_MIDI_NOTE_ID, midiNotesChoosingPage.snareNoteMenu);
    snareSwirlNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_SWIRL_MIDI_NOTE_ID, midiNotesChoosingPage.snareSwirlNoteMenu);
    snareFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.snareFlamNoteMenu);
    snareRoundNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_ROUND_MIDI_NOTE_ID, midiNotesChoosingPage.snareRoundNoteMenu);
    snareWirelessNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_WIRELESS_MIDI_NOTE_ID, midiNotesChoosingPage.snareWirelessNoteMenu);
    snareWirelessRoundNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_WIRELESS_ROUND_MIDI_NOTE_ID, midiNotesChoosingPage.snareWirelessRoundNoteMenu);

    snarePiccoloNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_PICCOLO_MIDI_NOTE_ID, midiNotesChoosingPage.snarePiccoloNoteMenu);
    snarePiccoloSwirlNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_PICCOLO_SWIRL_MIDI_NOTE_ID, midiNotesChoosingPage.snarePiccoloSwirlNoteMenu);

    tomNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TOM_MIDI_NOTE_ID, midiNotesChoosingPage.tomNoteMenu);
    tomFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TOM_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.tomFlamNoteMenu);
    ftomNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, FTOM_MIDI_NOTE_ID, midiNotesChoosingPage.ftomNoteMenu);
    ftomFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, FTOM_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.ftomFlamNoteMenu);

    hhFootNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_FOOT_MIDI_NOTE_ID, midiNotesChoosingPage.hhFootNoteMenu);
    hhClosedNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_CLOSED_MIDI_NOTE_ID, midiNotesChoosingPage.hhClosedNoteMenu);
    hhHalfNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_HALF_MIDI_NOTE_ID, midiNotesChoosingPage.hhHalfNoteMenu);
    hhOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.hhOpenNoteMenu);

    tambNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TAMB_MIDI_NOTE_ID, midiNotesChoosingPage.tambNoteMenu);

    ridePointNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_POINT_MIDI_NOTE_ID, midiNotesChoosingPage.ridePointNoteMenu);
    rideBellNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_BELL_MIDI_NOTE_ID, midiNotesChoosingPage.rideBellNoteMenu);
    rideOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.rideOpenNoteMenu);

    crashPointNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_POINT_MIDI_NOTE_ID, midiNotesChoosingPage.crashPointNoteMenu);
    crashBellNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_BELL_MIDI_NOTE_ID, midiNotesChoosingPage.crashBellNoteMenu);
    crashOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.crashOpenNoteMenu);

    stackClosedNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, STACK_CLOSED_MIDI_NOTE_ID, midiNotesChoosingPage.stackClosedNoteMenu);
    stackOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, STACK_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.stackOpenNoteMenu);
    sticksNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, STICKS_MIDI_NOTE_ID, midiNotesChoosingPage.sticksNoteMenu);


    sliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, GAIN_ID, mainSlidersPage.closeSlider);
    OHsliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, OH_GAIN_ID, mainSlidersPage.OHSlider);
    RoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, ROOM_GAIN_ID, mainSlidersPage.roomSlider);
    BleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, BLEED_GAIN_ID, mainSlidersPage.bleedSlider);

    // Menus ==================================================
    addAndMakeVisible(&samplePackMenu);
    samplePackMenu.setJustificationType(juce::Justification::centred);
    samplePackMenu.addItem("Electronic Drum Kit", 1);
    samplePackMenu.addItem("Acoustic Drum Kit", 2);
    samplePackMenu.addItem("Dry Drum Kit", 3);
    samplePackMenu.onChange = [this] { samplePackMenuChanged(); };
    auto samplePackMenuValue = audioProcessor.treeState.getRawParameterValue(SAMPLE_PACK_ID);
    samplePackMenu.setSelectedId(*samplePackMenuValue + 1);
    
    addAndMakeVisible(&curveMenu);
    curveMenu.setJustificationType(juce::Justification::centred);
    curveMenu.addItem("Logarhytmic", 1);
    curveMenu.addItem("Linear", 2);
    curveMenu.onChange = [this] { velocityCurveChanged(); };
    auto curveMenuValue = audioProcessor.treeState.getRawParameterValue(CURVE_MENU_ID);
    curveMenu.setSelectedId(*curveMenuValue + 1);

    addAndMakeVisible(&binauralButton);

    for (int i = 0; i < midiNoteHiddenMenus.size(); i++)
    {
        midiNoteHiddenMenus[i]->setSelectedId(audioProcessor.midiProcessor.newMidiNotes[i + 1]);
        audioProcessor.midiProcessor.newMidiNotes[i + 1] = midiNoteHiddenMenus[i]->getSelectedId();
    }

    midiNotesChoosingPage.allSounds.onChange = [this] { changeMidiNoteMenuWhenSoundChanged(); };
    midiNotesChoosingPage.soundNoteMenu.onChange = [this] { midiNoteChanged2(); };
    midiNotesChoosingPage.soundNoteMenu.setSelectedId(audioProcessor.midiProcessor.newMidiNotes[midiNotesChoosingPage.allSounds.getSelectedId()]);
    midiNotesChoosingPage.soundButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.soundNoteMenu.getSelectedId()); };



    for (int i = 0; i < soloButtons.size(); i++)
    {
        if (soloButtons[i]->getToggleState())
            soloButtons[i]->setToggleState(true, true);
        
        //soloButtons[i]->onClick = [this] { soloStateChanged(i); };
    }
    soloButtons[0]->onClick = [this] { soloStateChanged(0); };
    soloButtons[1]->onClick = [this] { soloStateChanged(1); };
    soloButtons[2]->onClick = [this] { soloStateChanged(2); };
    soloButtons[3]->onClick = [this] { soloStateChanged(3); };
    soloButtons[4]->onClick = [this] { soloStateChanged(4); };
    soloButtons[5]->onClick = [this] { soloStateChanged(5); };
    soloButtons[6]->onClick = [this] { soloStateChanged(6); };
    soloButtons[7]->onClick = [this] { soloStateChanged(7); };
    soloButtons[8]->onClick = [this] { soloStateChanged(8); };
    soloButtons[9]->onClick = [this] { soloStateChanged(9); };
    soloButtons[10]->onClick = [this] { soloStateChanged(10); };
    soloButtons[11]->onClick = [this] { soloStateChanged(11); };
    soloButtons[12]->onClick = [this] { soloStateChanged(12); };
    soloButtons[13]->onClick = [this] { soloStateChanged(13); };
    soloButtons[14]->onClick = [this] { soloStateChanged(14); };
    soloButtons[15]->onClick = [this] { soloStateChanged(15); };
    soloButtons[16]->onClick = [this] { soloStateChanged(16); };
    soloButtons[17]->onClick = [this] { soloStateChanged(17); };

}

HDrumsAudioProcessorEditor::~HDrumsAudioProcessorEditor()
{
    muteButtons.clear();
    soloButtons.clear();
    soloButtonsStates.clear();
    muteButtonsStates.clear();
    muteButtons.shrink_to_fit();
    soloButtons.shrink_to_fit();
    soloButtonsStates.shrink_to_fit();
    muteButtonsStates.shrink_to_fit();
}

void HDrumsAudioProcessorEditor::soloStateChanged(int soloButtonId)
{
    // solo clicked for the first time
    if (soloButtons[soloButtonId]->getToggleState() && !soloAlreadyEngaged)
    {
        muteAndSoloButtonsFunctionality.muteButtonsWhenSoloFirstTime(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
        soloAlreadyEngaged = true;
        muteAndSoloButtonsFunctionality.unsoloButtonsWhenSolo(soloButtonId, soloButtons);
    }
    // solo clicked for the n-th time
    else if (soloButtons[soloButtonId]->getToggleState() && soloAlreadyEngaged)
    {
        muteAndSoloButtonsFunctionality.muteButtonsWhenSoloAgain(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
        muteAndSoloButtonsFunctionality.unsoloButtonsWhenSolo(soloButtonId, soloButtons);
    }
    // solo unclicked
    else if (!soloButtons[soloButtonId]->getToggleState())
    {
        muteAndSoloButtonsFunctionality.unmuteButtonsWhenSolo(muteButtons, muteStateBeforeFirstSolo);
        soloAlreadyEngaged = false;
    }
}

void HDrumsAudioProcessorEditor::setNoteInMidiNotesChoosingPage(juce::ComboBox &menu, std::atomic <float> *note)
{
    menu.setSelectedId(*note);
}

void HDrumsAudioProcessorEditor::changeMidiNoteMenuWhenSoundChanged()
{
    midiNotesChoosingPage.soundNoteMenu.setSelectedId(audioProcessor.midiProcessor.newMidiNotes[midiNotesChoosingPage.allSounds.getSelectedId()]);
}

void HDrumsAudioProcessorEditor::midiNoteChanged()
{
    audioProcessor.midiProcessor.newMidiNotes[1] = midiNotesChoosingPage.kickNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[2] = midiNotesChoosingPage.snareNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[3] = midiNotesChoosingPage.snareSwirlNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[4] = midiNotesChoosingPage.snareFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[5] = midiNotesChoosingPage.snareRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[6] = midiNotesChoosingPage.snareWirelessNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[7] = midiNotesChoosingPage.snareWirelessRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[8] = midiNotesChoosingPage.snarePiccoloNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[9] = midiNotesChoosingPage.snarePiccoloSwirlNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[10] = midiNotesChoosingPage.tomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[11] = midiNotesChoosingPage.tomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[12] = midiNotesChoosingPage.ftomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[13] = midiNotesChoosingPage.ftomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[14] = midiNotesChoosingPage.hhFootNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[15] = midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[16] = midiNotesChoosingPage.hhHalfNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[17] = midiNotesChoosingPage.hhOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[18] = midiNotesChoosingPage.tambNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[19] = midiNotesChoosingPage.ridePointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[20] = midiNotesChoosingPage.rideBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[21] = midiNotesChoosingPage.rideOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[22] = midiNotesChoosingPage.crashPointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[23] = midiNotesChoosingPage.crashBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[24] = midiNotesChoosingPage.crashOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[25] = midiNotesChoosingPage.stackClosedNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[26] = midiNotesChoosingPage.stackOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[27] = midiNotesChoosingPage.sticksNoteMenu.getSelectedId();
}

void HDrumsAudioProcessorEditor::midiNoteChanged2()
{
    midiNoteHiddenMenus[midiNotesChoosingPage.allSounds.getSelectedId() - 1]->setSelectedId(midiNotesChoosingPage.soundNoteMenu.getSelectedId());
    audioProcessor.midiProcessor.newMidiNotes[midiNotesChoosingPage.allSounds.getSelectedId()] = midiNotesChoosingPage.soundNoteMenu.getSelectedId();
}

//==============================================================================
void HDrumsAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    if (samplePackMenu.getSelectedId() == 1)
    {
        electronicBackground = juce::ImageCache::getFromMemory(BinaryData::electronicDrumsImageWide_png, BinaryData::electronicDrumsImageWide_pngSize);
        g.drawImageWithin(electronicBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    }
    else if (samplePackMenu.getSelectedId() == 2)
    {
        acousticBackground = juce::ImageCache::getFromMemory(BinaryData::acousticDrumsImageWide_png, BinaryData::acousticDrumsImageWide_pngSize);
        g.drawImageWithin(acousticBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        g.drawImageWithin(dryBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        dryBackground = juce::ImageCache::getFromMemory(BinaryData::dryDrumsImageWide_png, BinaryData::dryDrumsImageWide_pngSize);
    }
}

void HDrumsAudioProcessorEditor::resized()
{
    guiKickButton.setCentrePosition(303, 286);
    guiSnareButton.setCentrePosition(171, 272);
    guiTomButton.setCentrePosition(205, 167);
    guiTambButton.setCentrePosition(318, 146);
    guiHHButton.setCentrePosition(91, 150);
    guiRideButton.setCentrePosition(461, 163);
    guiCrashButton.setCentrePosition(212, 102);
    guiPiccoloButton.setCentrePosition(57, 250);
    guiStackButton.setCentrePosition(557, 226);

    samplePackMenu.setBounds(12, 12, 308, 30);
    curveMenu.setBounds(330, 12, 308, 30);

    binauralButton.setBounds(525, 60, 100, 50);
    binauralButton.setLookAndFeel(&myLookAndFeelBinaural);

    myTabbedComponent.setBounds(getWidth() / 2 + 125, 0, getWidth() / 2 - 125, getHeight());
    
    if (samplePackMenu.getSelectedId() == 1)
    {   // Electronic
        guiTambButton.setVisible(false);
        guiStackButton.setVisible(false);
        guiPiccoloButton.setVisible(false);
        guiFTomButton.setCentrePosition(433, 264);
        binauralButton.setVisible(false);
    }
    else if (samplePackMenu.getSelectedId() == 2)
    {   // Acoustic
        guiTambButton.setVisible(false);
        guiStackButton.setVisible(true);
        guiPiccoloButton.setVisible(true);
        guiFTomButton.setCentrePosition(433, 270);
        binauralButton.setVisible(true);
    }
    else
    {   // Dry
        guiTambButton.setVisible(true);
        guiStackButton.setVisible(false);
        guiPiccoloButton.setVisible(false);
        guiFTomButton.setCentrePosition(433, 264);
        binauralButton.setVisible(false);
    }
}

void HDrumsAudioProcessorEditor::velocityCurveChanged()
{
    if (curveMenu.getSelectedId() == 1)
        audioProcessor.midiProcessor.logarhytmic = true;
    else
        audioProcessor.midiProcessor.logarhytmic = false;
}

void HDrumsAudioProcessorEditor::samplePackMenuChanged()
{
    audioProcessor.loadSamples(samplePackMenu.getSelectedId());
    repaint();
    resized();
}

void HDrumsAudioProcessorEditor::playMidiNote(int noteNumber)
{
    float vel;
    if (noteNumber == audioProcessor.midiProcessor.newMidiNotes[16])    // lower velocity for HH Half
        vel = 0.77f;
    else if (noteNumber == audioProcessor.midiProcessor.newMidiNotes[22])   // lower velocity for Crash Point
        vel = 0.56f;
    else
        vel = 0.93f;
    
    juce::MidiMessage message = juce::MidiMessage::noteOn(1, noteNumber, vel);
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001 - 0.0);
    audioProcessor.getMidiMessageCollector().addMessageToQueue(message);
}