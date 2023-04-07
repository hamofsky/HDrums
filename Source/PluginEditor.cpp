#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"
#include "MidiProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "MainSlidersPage.h"
#include "CymbalsSlidersPage.h"
#include "MidiNoteChoosingPage.h"
#include "MyLookAndFeel.h"

HDrumsAudioProcessorEditor::HDrumsAudioProcessorEditor(HDrumsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), myTabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
    mainSlidersPage(), kickSlidersPage(), snareSlidersPage(), tomsSlidersPage(), cymbalsSlidersPage(), midiNotesChoosingPage(),
    guiKickButton("GUI Kick Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiSnareButton("GUI Snare Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiTomButton("GUI Tom Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiFTomButton("GUI FTom Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiTambButton("GUI Tamb Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiHHButton("GUI HH Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiRideButton("GUI Ride Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f)),
    guiCrashButton("GUI Crash Button", juce::Colours::black.withAlpha(0.01f), juce::Colours::black.withAlpha(0.04f), juce::Colours::black.withAlpha(0.1f))//, openButton("Browse for directory")
{
    setSize(1000, 500);

    midiNoteChanged();

    // GUI Buttons overlaying the artwork ==============================================================
    juce::Path guiKickButtonShape;
    juce::Path guiSnareButtonShape;
    juce::Path guiTomButtonShape;
    juce::Path guiFTomButtonShape;
    juce::Path guiTambButtonShape;
    juce::Path guiHHButtonShape;
    juce::Path guiRideButtonShape;
    juce::Path guiCrashButtonShape;
    guiKickButtonShape.addEllipse(0, 0, 149.0f, 149.0f);
    guiSnareButtonShape.addEllipse(0, 0, 124.0f, 70.0f);
    guiTomButtonShape.addEllipse(0, 0, 86.0f, 39.0f);
    guiFTomButtonShape.addEllipse(0, 0, 125.0f, 62.0f);
    guiTambButtonShape.addEllipse(0, 0, 78.0f, 50.0f);
    guiHHButtonShape.addEllipse(0, 0, 120.0f, 46.0f);
    guiRideButtonShape.addEllipse(0, 0, 180.0f, 79.0f);
    guiCrashButtonShape.addEllipse(0, 0, 125.0f, 50.0f);
    guiKickButton.setShape(guiKickButtonShape, true, true, false);
    guiSnareButton.setShape(guiSnareButtonShape, true, true, false);
    guiTomButton.setShape(guiTomButtonShape, true, true, false);
    guiFTomButton.setShape(guiFTomButtonShape, true, true, false);
    guiTambButton.setShape(guiTambButtonShape, true, true, false);
    guiHHButton.setShape(guiHHButtonShape, true, true, false);
    guiRideButton.setShape(guiRideButtonShape, true, true, false);
    guiCrashButton.setShape(guiCrashButtonShape, true, true, false);

    addAndMakeVisible(&guiKickButton);
    addAndMakeVisible(&guiSnareButton);
    addAndMakeVisible(&guiTomButton);
    addAndMakeVisible(&guiFTomButton);
    addAndMakeVisible(&guiTambButton);
    addAndMakeVisible(&guiHHButton);
    addAndMakeVisible(&guiRideButton);
    addAndMakeVisible(&guiCrashButton);
    guiKickButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.kickNoteMenu.getSelectedId()); };
    guiSnareButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareNoteMenu.getSelectedId()); };
    guiTomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tomNoteMenu.getSelectedId()); };
    guiFTomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ftomNoteMenu.getSelectedId()); };
    guiTambButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tambNoteMenu.getSelectedId()); };
    guiHHButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId()); };
    guiRideButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ridePointNoteMenu.getSelectedId()); };
    guiCrashButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.crashPointNoteMenu.getSelectedId()); };

    // Tabbed Component 
    addAndMakeVisible(&myTabbedComponent);
    myTabbedComponent.addTab("Main", juce::Colours::black.withAlpha(0.7f), &mainSlidersPage, true);
    myTabbedComponent.addTab("Kick", juce::Colours::black.withAlpha(0.7f), &kickSlidersPage, true);
    myTabbedComponent.addTab("Snare", juce::Colours::black.withAlpha(0.7f), &snareSlidersPage, true);
    myTabbedComponent.addTab("Toms", juce::Colours::black.withAlpha(0.7f), &tomsSlidersPage, true);
    myTabbedComponent.addTab("Cymbals", juce::Colours::black.withAlpha(0.7f), &cymbalsSlidersPage, true);
    myTabbedComponent.addTab("MIDI", juce::Colours::grey.withAlpha(0.8f), &midiNotesChoosingPage, true);

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

    // buttons from MidiNoteChoosingPage
    midiNotesChoosingPage.kickNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.kickButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.kickNoteMenu.getSelectedId()); };

    midiNotesChoosingPage.snareNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.snareButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.snareFlamNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.snareFlamButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareFlamNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.snareRoundNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.snareRoundButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareRoundNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.snareWirelessNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.snareWirelessButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareWirelessNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.snareWirelessRoundNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.snareWirelessRoundButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.snareWirelessRoundNoteMenu.getSelectedId()); };

    midiNotesChoosingPage.tomNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.tomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tomNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.tomFlamNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.tomFlamButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tomFlamNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.ftomNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.ftomButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ftomNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.ftomFlamNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.ftomFlamButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ftomFlamNoteMenu.getSelectedId()); };

    midiNotesChoosingPage.tambNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.tambButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.tambNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.hhClosedNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.hhClosedButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.hhHalfNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.hhHalfButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.hhHalfNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.hhOpenNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.hhOpenButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.hhOpenNoteMenu.getSelectedId()); };

    midiNotesChoosingPage.ridePointNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.ridePointButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.ridePointNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.rideBellNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.rideBellButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.rideBellNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.rideOpenNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.rideOpenButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.rideOpenNoteMenu.getSelectedId()); };
    
    midiNotesChoosingPage.crashPointNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.crashPointButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.crashPointNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.crashBellNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.crashBellButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.crashBellNoteMenu.getSelectedId()); };
    midiNotesChoosingPage.crashOpenNoteMenu.onChange = [this] { midiNoteChanged(); };
    midiNotesChoosingPage.crashOpenButton.onClick = [this] { playMidiNote(midiNotesChoosingPage.crashOpenNoteMenu.getSelectedId()); };

    //addAndMakeVisible(&openButton);
    //openButton.onClick = [this] { loadDirectory(); };

    samplePackAttachment = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SAMPLE_PACK_ID, samplePackMenu);
    curveMenuAttachment = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CURVE_MENU_ID, curveMenu);

    kickNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, KICK_MIDI_NOTE_ID, midiNotesChoosingPage.kickNoteMenu);
    snareNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_MIDI_NOTE_ID, midiNotesChoosingPage.snareNoteMenu);
    snareFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.snareFlamNoteMenu);
    snareRoundNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_ROUND_MIDI_NOTE_ID, midiNotesChoosingPage.snareRoundNoteMenu);
    snareWirelessNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_WIRELESS_MIDI_NOTE_ID, midiNotesChoosingPage.snareWirelessNoteMenu);
    snareWirelessRoundNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, SNARE_WIRELESS_ROUND_MIDI_NOTE_ID, midiNotesChoosingPage.snareWirelessRoundNoteMenu);

    tomNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TOM_MIDI_NOTE_ID, midiNotesChoosingPage.tomNoteMenu);
    tomFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TOM_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.tomFlamNoteMenu);
    ftomNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, FTOM_MIDI_NOTE_ID, midiNotesChoosingPage.ftomNoteMenu);
    ftomFlamNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, FTOM_FLAM_MIDI_NOTE_ID, midiNotesChoosingPage.ftomFlamNoteMenu);

    tambNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, TAMB_MIDI_NOTE_ID, midiNotesChoosingPage.tambNoteMenu);
    hhClosedNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_CLOSED_MIDI_NOTE_ID, midiNotesChoosingPage.hhClosedNoteMenu);
    hhHalfNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_HALF_MIDI_NOTE_ID, midiNotesChoosingPage.hhHalfNoteMenu);
    hhOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, HH_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.hhOpenNoteMenu);

    ridePointNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_POINT_MIDI_NOTE_ID, midiNotesChoosingPage.ridePointNoteMenu);
    rideBellNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_BELL_MIDI_NOTE_ID, midiNotesChoosingPage.rideBellNoteMenu);
    rideOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, RIDE_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.rideOpenNoteMenu);

    crashPointNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_POINT_MIDI_NOTE_ID, midiNotesChoosingPage.crashPointNoteMenu);
    crashBellNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_BELL_MIDI_NOTE_ID, midiNotesChoosingPage.crashBellNoteMenu);
    crashOpenNote = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.treeState, CRASH_OPEN_MIDI_NOTE_ID, midiNotesChoosingPage.crashOpenNoteMenu);

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

    // MIDI Menus =============================================
    auto kickNoteMenuValue = audioProcessor.treeState.getRawParameterValue(KICK_MIDI_NOTE_ID);
    auto snareNoteMenuValue = audioProcessor.treeState.getRawParameterValue(SNARE_MIDI_NOTE_ID);
    auto snareFlamNoteMenuValue = audioProcessor.treeState.getRawParameterValue(SNARE_FLAM_MIDI_NOTE_ID);
    auto snareRoundNoteMenuValue = audioProcessor.treeState.getRawParameterValue(SNARE_ROUND_MIDI_NOTE_ID);
    auto snareWirelessNoteMenuValue = audioProcessor.treeState.getRawParameterValue(SNARE_WIRELESS_MIDI_NOTE_ID);
    auto snareWirelessRoundNoteMenuValue = audioProcessor.treeState.getRawParameterValue(SNARE_WIRELESS_ROUND_MIDI_NOTE_ID);
    auto tomNoteMenuValue = audioProcessor.treeState.getRawParameterValue(TOM_MIDI_NOTE_ID);
    auto tomFlamNoteMenuValue = audioProcessor.treeState.getRawParameterValue(TOM_FLAM_MIDI_NOTE_ID);
    auto ftomNoteMenuValue = audioProcessor.treeState.getRawParameterValue(FTOM_MIDI_NOTE_ID);
    auto ftomFlamNoteMenuValue = audioProcessor.treeState.getRawParameterValue(FTOM_FLAM_MIDI_NOTE_ID);
    auto tambNoteMenuValue = audioProcessor.treeState.getRawParameterValue(TAMB_MIDI_NOTE_ID);
    auto hhClosedNoteMenuValue = audioProcessor.treeState.getRawParameterValue(HH_CLOSED_MIDI_NOTE_ID);
    auto hhHalfNoteMenuValue = audioProcessor.treeState.getRawParameterValue(HH_HALF_MIDI_NOTE_ID);
    auto hhOpenNoteMenuValue = audioProcessor.treeState.getRawParameterValue(HH_OPEN_MIDI_NOTE_ID); 
    auto ridePointNoteMenuValue = audioProcessor.treeState.getRawParameterValue(RIDE_POINT_MIDI_NOTE_ID);
    auto rideBellNoteMenuValue = audioProcessor.treeState.getRawParameterValue(RIDE_BELL_MIDI_NOTE_ID);
    auto rideOpenNoteMenuValue = audioProcessor.treeState.getRawParameterValue(RIDE_OPEN_MIDI_NOTE_ID);
    auto crashPointNoteMenuValue = audioProcessor.treeState.getRawParameterValue(CRASH_POINT_MIDI_NOTE_ID);
    auto crashBellNoteMenuValue = audioProcessor.treeState.getRawParameterValue(CRASH_BELL_MIDI_NOTE_ID);
    auto crashOpenNoteMenuValue = audioProcessor.treeState.getRawParameterValue(CRASH_OPEN_MIDI_NOTE_ID);
    
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.kickNoteMenu, kickNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.snareNoteMenu, snareNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.snareFlamNoteMenu, snareFlamNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.snareRoundNoteMenu, snareRoundNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.snareWirelessNoteMenu, snareWirelessNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.snareWirelessRoundNoteMenu, snareWirelessRoundNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.tomNoteMenu, tomNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.tomFlamNoteMenu, tomFlamNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.ftomNoteMenu, ftomNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.ftomFlamNoteMenu, ftomFlamNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.tambNoteMenu, tambNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.hhClosedNoteMenu, hhClosedNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.hhHalfNoteMenu, hhHalfNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.hhOpenNoteMenu, hhOpenNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.ridePointNoteMenu, ridePointNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.rideBellNoteMenu, rideBellNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.rideOpenNoteMenu, rideOpenNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.crashPointNoteMenu, crashPointNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.crashBellNoteMenu, crashBellNoteMenuValue);
    setNoteInMidiNotesChoosingPage(midiNotesChoosingPage.crashOpenNoteMenu, crashOpenNoteMenuValue);

}

HDrumsAudioProcessorEditor::~HDrumsAudioProcessorEditor()
{

}

void HDrumsAudioProcessorEditor::setNoteInMidiNotesChoosingPage(juce::ComboBox &menu, std::atomic <float> *note)
{
    if (*note < 64)
        menu.setSelectedId(*note + 1);
    else
        menu.setSelectedId(*note);
}

//juce::String HDrumsAudioProcessorEditor::loadDirectory()
//{
//    juce::FileChooser myChooser("Select directory");
//    if (myChooser.browseForDirectory())
//    {
//        juce::File MyDir(myChooser.getResult());
//        DBG(MyDir.getFullPathName());
//        return MyDir.getFullPathName();
//    }
//}

//==============================================================================
void HDrumsAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    background = juce::ImageCache::getFromMemory(BinaryData::blue_400x400_png, BinaryData::blue_400x400_pngSize);
    background2 = juce::ImageCache::getFromMemory(BinaryData::grey_400x400_png, BinaryData::grey_400x400_pngSize);
    dryBackground = juce::ImageCache::getFromMemory(BinaryData::dryDrumsImage_png, BinaryData::dryDrumsImage_pngSize);

    if (samplePackMenu.getSelectedId() == 1)
        g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    else if (samplePackMenu.getSelectedId() == 2)
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    else
        g.drawImageWithin(dryBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        

}

void HDrumsAudioProcessorEditor::resized()
{
    auto halfWidth = getWidth() / 4;
    
    //openButton.setBounds(10, 10, getWidth() - 20, 30);
    
    guiKickButton.setCentrePosition(230, 212);
    guiSnareButton.setCentrePosition(110, 235);
    guiTomButton.setCentrePosition(162, 147);
    guiFTomButton.setCentrePosition(373, 233);
    guiTambButton.setCentrePosition(279, 121);
    guiHHButton.setCentrePosition(32, 128);
    guiRideButton.setCentrePosition(372, 124);
    guiCrashButton.setCentrePosition(150, 76);

    samplePackMenu.setBounds(10, 10, 285, 20);
    curveMenu.setBounds(305, 10, 285, 20);

    myTabbedComponent.setBounds(getWidth() / 2 + 100, 0, getWidth() / 2 - 100, getHeight());
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
}

void HDrumsAudioProcessorEditor::midiNoteChanged()
{
    audioProcessor.midiProcessor.newMidiNotes[0] = midiNotesChoosingPage.kickNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[1] = midiNotesChoosingPage.snareNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[2] = midiNotesChoosingPage.snareFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[3] = midiNotesChoosingPage.snareRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[4] = midiNotesChoosingPage.snareWirelessNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[5] = midiNotesChoosingPage.snareWirelessRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[6] = midiNotesChoosingPage.tomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[7] = midiNotesChoosingPage.tomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[8] = midiNotesChoosingPage.ftomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[9] = midiNotesChoosingPage.ftomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[10] = midiNotesChoosingPage.tambNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[11] = midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[12] = midiNotesChoosingPage.hhHalfNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[13] = midiNotesChoosingPage.hhOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[14] = midiNotesChoosingPage.ridePointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[15] = midiNotesChoosingPage.rideBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[16] = midiNotesChoosingPage.rideOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[17] = midiNotesChoosingPage.crashPointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[18] = midiNotesChoosingPage.crashBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newMidiNotes[19] = midiNotesChoosingPage.crashOpenNoteMenu.getSelectedId();
}

void HDrumsAudioProcessorEditor::playMidiNote(int noteNumber)
{
    float vel;
    if (noteNumber == audioProcessor.midiProcessor.newMidiNotes[12])    // lower velocity for HH Half
        vel = 0.77f;
    else if (noteNumber == audioProcessor.midiProcessor.newMidiNotes[17])   // lower velocity for Crash Point
        vel = 0.56f;
    else
        vel = 0.93f;
    
    juce::MidiMessage message = juce::MidiMessage::noteOn(1, noteNumber, vel);
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001 - 0.0);
    audioProcessor.getMidiMessageCollector().addMessageToQueue(message);
}