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

HDrumsAudioProcessorEditor::HDrumsAudioProcessorEditor(HDrumsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), myTabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
    mainSlidersPage(), kickSlidersPage(), snareSlidersPage(), tomsSlidersPage(), cymbalsSlidersPage(), midiNotesChoosingPage()//, openButton("Browse for directory")
{
    setSize(1000, 500);

    midiNoteChanged();

    addAndMakeVisible(&myTabbedComponent);
    myTabbedComponent.addTab("Main", juce::Colours::red.withAlpha(0.5f), &mainSlidersPage, true);
    myTabbedComponent.addTab("Kick", juce::Colours::pink.withAlpha(0.5f), &kickSlidersPage, true);
    myTabbedComponent.addTab("Snare", juce::Colours::aqua.withAlpha(0.5f), &snareSlidersPage, true);
    myTabbedComponent.addTab("Toms", juce::Colours::green.withAlpha(0.5f), &tomsSlidersPage, true);
    myTabbedComponent.addTab("Cymbals", juce::Colours::beige.withAlpha(0.5f), &cymbalsSlidersPage, true);
    myTabbedComponent.addTab("MIDI", juce::Colours::darkred.withAlpha(0.5f), &midiNotesChoosingPage, true);

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

    // Menu ===========================================================
    addAndMakeVisible(&samplePackMenu);
    samplePackMenu.setJustificationType(juce::Justification::centred);
    samplePackMenu.addItem("Acoustic Drum Kit", 1);
    samplePackMenu.addItem("Electronic Drum Kit", 2);
    samplePackMenu.addItem("Dry Drum Kit", 3);
    samplePackMenu.onChange = [this] { samplePackMenuChanged(); };
    auto samplePackMenuValue = audioProcessor.treeState.getRawParameterValue(SAMPLE_PACK_ID);
    samplePackMenu.setSelectedId(*samplePackMenuValue + 1);
    
    addAndMakeVisible(&curveMenu);
    curveMenu.setJustificationType(juce::Justification::centred);
    curveMenu.addItem("Linear", 1);
    curveMenu.addItem("Logarhytmic", 2);
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
    midiNotesChoosingPage.kickNoteMenu.setSelectedId(*kickNoteMenuValue);
    midiNotesChoosingPage.snareNoteMenu.setSelectedId(*snareNoteMenuValue);
    midiNotesChoosingPage.snareFlamNoteMenu.setSelectedId(*snareFlamNoteMenuValue);
    midiNotesChoosingPage.snareRoundNoteMenu.setSelectedId(*snareRoundNoteMenuValue);
    midiNotesChoosingPage.snareWirelessNoteMenu.setSelectedId(*snareWirelessNoteMenuValue);
    midiNotesChoosingPage.snareWirelessRoundNoteMenu.setSelectedId(*snareWirelessRoundNoteMenuValue);
    midiNotesChoosingPage.tomNoteMenu.setSelectedId(*tomNoteMenuValue);
    midiNotesChoosingPage.tomFlamNoteMenu.setSelectedId(*tomFlamNoteMenuValue);
    midiNotesChoosingPage.ftomNoteMenu.setSelectedId(*ftomNoteMenuValue);
    midiNotesChoosingPage.ftomFlamNoteMenu.setSelectedId(*ftomFlamNoteMenuValue);
    midiNotesChoosingPage.tambNoteMenu.setSelectedId(*tambNoteMenuValue);
    midiNotesChoosingPage.hhClosedNoteMenu.setSelectedId(*hhClosedNoteMenuValue);
    midiNotesChoosingPage.hhHalfNoteMenu.setSelectedId(*hhHalfNoteMenuValue);
    midiNotesChoosingPage.hhOpenNoteMenu.setSelectedId(*hhOpenNoteMenuValue);
    midiNotesChoosingPage.ridePointNoteMenu.setSelectedId(*ridePointNoteMenuValue);
    midiNotesChoosingPage.rideBellNoteMenu.setSelectedId(*rideBellNoteMenuValue);
    midiNotesChoosingPage.rideOpenNoteMenu.setSelectedId(*rideOpenNoteMenuValue);
    midiNotesChoosingPage.crashPointNoteMenu.setSelectedId(*crashPointNoteMenuValue);
    midiNotesChoosingPage.crashBellNoteMenu.setSelectedId(*crashBellNoteMenuValue);
    midiNotesChoosingPage.crashOpenNoteMenu.setSelectedId(*crashOpenNoteMenuValue);

}

HDrumsAudioProcessorEditor::~HDrumsAudioProcessorEditor()
{

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

    if (samplePackMenu.getSelectedId() == 2)
        g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    else if (samplePackMenu.getSelectedId() == 3)
        g.drawImageWithin(dryBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    else
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

}

void HDrumsAudioProcessorEditor::resized()
{
    auto halfWidth = getWidth() / 4;
    
    //openButton.setBounds(10, 10, getWidth() - 20, 30);

    samplePackMenu.setBounds(10, 10, halfWidth - 15, 20);
    curveMenu.setBounds(halfWidth + 5, 10, halfWidth - 15, 20);

    myTabbedComponent.setBounds(getWidth() / 2 + 100, 0, getWidth() / 2 - 100, getHeight());
}

void HDrumsAudioProcessorEditor::velocityCurveChanged()
{
    if (curveMenu.getSelectedId() == 2)
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
    /*audioProcessor.midiProcessor.newKickMidiNote = midiNotesChoosingPage.kickNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newSnareMidiNote = midiNotesChoosingPage.snareNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newSnareFlamMidiNote = midiNotesChoosingPage.snareFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newSnareRoundMidiNote = midiNotesChoosingPage.snareRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newSnareWirelessMidiNote = midiNotesChoosingPage.snareWirelessNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newSnareWirelessRoundMidiNote = midiNotesChoosingPage.snareWirelessRoundNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newTomMidiNote = midiNotesChoosingPage.tomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newTomFlamMidiNote = midiNotesChoosingPage.tomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newFTomMidiNote = midiNotesChoosingPage.ftomNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newFTomFlamMidiNote = midiNotesChoosingPage.ftomFlamNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newTambMidiNote = midiNotesChoosingPage.tambNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newHHClosedMidiNote = midiNotesChoosingPage.hhClosedNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newHHHalfMidiNote = midiNotesChoosingPage.hhHalfNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newHHOpenMidiNote = midiNotesChoosingPage.hhOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newRidePointMidiNote = midiNotesChoosingPage.ridePointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newRideBellMidiNote = midiNotesChoosingPage.rideBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newRideOpenMidiNote = midiNotesChoosingPage.rideOpenNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newCrashPointMidiNote = midiNotesChoosingPage.crashPointNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newCrashBellMidiNote = midiNotesChoosingPage.crashBellNoteMenu.getSelectedId();
    audioProcessor.midiProcessor.newCrashOpenMidiNote = midiNotesChoosingPage.crashOpenNoteMenu.getSelectedId();*/

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
    juce::MidiMessage message = juce::MidiMessage::noteOn(1, noteNumber, 0.92f);
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001 - 0.0);
    audioProcessor.getMidiMessageCollector().addMessageToQueue(message);
}