#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"
#include "MidiProcessor.h"
#include "KickSlidersPage.h"
#include "SnareSlidersPage.h"
#include "TomsSlidersPage.h"
#include "HHSlidersPage.h"
#include "CymbalsSlidersPage.h"

HDrumsAudioProcessorEditor::HDrumsAudioProcessorEditor(HDrumsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), myTabbedComponent(juce::TabbedButtonBar::Orientation::TabsAtTop),
    kickSlidersPage(), snareSlidersPage(), tomsSlidersPage(), hhSlidersPage(), cymbalsSlidersPage()//, openButton("Browse for directory")
{
    setSize(1000, 400);

    addAndMakeVisible(&myTabbedComponent);
    myTabbedComponent.addTab("Kick", juce::Colours::pink.withAlpha(0.9f), &kickSlidersPage, true);
    myTabbedComponent.addTab("Snare", juce::Colours::red.withAlpha(0.6f), &snareSlidersPage, true);
    myTabbedComponent.addTab("Toms", juce::Colours::green.withAlpha(0.5f), &tomsSlidersPage, true);
    myTabbedComponent.addTab("HH", juce::Colours::blue.withAlpha(0.5f), &hhSlidersPage, true);
    myTabbedComponent.addTab("Cymbals", juce::Colours::blue.withAlpha(0.5f), &cymbalsSlidersPage, true);

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

    hhCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, HH_CLOSE_GAIN_ID, hhSlidersPage.hhCloseSlider);
    tambCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, TAMB_CLOSE_GAIN_ID, hhSlidersPage.tambCloseSlider);
    hhOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, HH_OH_GAIN_ID, hhSlidersPage.hhOHSlider);
    hhRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, HH_ROOM_GAIN_ID, hhSlidersPage.hhRoomSlider);
    hhBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, HH_BLEED_GAIN_ID, hhSlidersPage.hhBleedSlider);

    crashCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CRASH_CLOSE_GAIN_ID, cymbalsSlidersPage.crashCloseSlider);
    rideCloseSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, RIDE_CLOSE_GAIN_ID, cymbalsSlidersPage.rideCloseSlider);
    cymbalsOHSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_OH_GAIN_ID, cymbalsSlidersPage.cymbalsOHSlider);
    cymbalsRoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_ROOM_GAIN_ID, cymbalsSlidersPage.cymbalsRoomSlider);
    cymbalsBleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, CYMBALS_BLEED_GAIN_ID, cymbalsSlidersPage.cymbalsBleedSlider);

    // Buttons for triggering samples internally ========================================
    addAndMakeVisible(kickDrumButton);
    kickDrumButton.setButtonText("Kick Drum");
    kickDrumButton.onClick = [this] { playMidiNote(kickNoteMenu.getSelectedId()); };
    addAndMakeVisible(&kickNoteMenu);
    kickNoteMenu.setJustificationType(juce::Justification::centred);
    for (int i = 1; i < 128; i++)
        kickNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
    kickNoteMenu.onChange = [this] { samplePackMenuChanged(); };
    kickNoteMenu.setSelectedId(57);    // default MIDI note for kick

    addAndMakeVisible(snareDrumButton);
    snareDrumButton.setButtonText("Snare Drum");
    snareDrumButton.onClick = [this] { playMidiNote(snareNoteMenu.getSelectedId()); };
    addAndMakeVisible(&snareNoteMenu);
    snareNoteMenu.setJustificationType(juce::Justification::centred);
    for (int i = 1; i < 128; i++)
        snareNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
    snareNoteMenu.onChange = [this] { samplePackMenuChanged(); };
    snareNoteMenu.setSelectedId(60);    // default MIDI note for snare

    addAndMakeVisible(floorTomButton);
    floorTomButton.setButtonText("Floor Tom close (67)");
    floorTomButton.onClick = [this] { playMidiNote(67); };
    addAndMakeVisible(floorTomButton2);
    floorTomButton2.setButtonText("Floor Tom OH (67)");
    floorTomButton2.onClick = [this] { playMidiNote(67); };

    //addAndMakeVisible(&openButton);
    //openButton.onClick = [this] { loadDirectory(); };

    sliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, GAIN_ID, gainSlider);
    OHsliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, OH_GAIN_ID, OHgainSlider);
    RoomSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, ROOM_GAIN_ID, RoomGainSlider);
    BleedSliderValue = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, BLEED_GAIN_ID, BleedGainSlider);

    // Main sliders =======================================================
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0f, 10.0f);
    gainSlider.setDoubleClickReturnValue(true, 0.0f);
    gainSlider.setValue(gainSlider.getValue());
    addAndMakeVisible(&gainSlider);
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Close", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);

    OHgainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    OHgainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    OHgainSlider.setRange(-48.0f, 10.0f);
    OHgainSlider.setDoubleClickReturnValue(true, 0.0f);
    OHgainSlider.setValue(OHgainSlider.getValue());
    addAndMakeVisible(&OHgainSlider);
    addAndMakeVisible(OHgainLabel);
    OHgainLabel.setText("OH", juce::dontSendNotification);
    OHgainLabel.setJustificationType(juce::Justification::centred);
    OHgainLabel.attachToComponent(&OHgainSlider, false);

    RoomGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    RoomGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    RoomGainSlider.setRange(-48.0f, 10.0f);
    RoomGainSlider.setDoubleClickReturnValue(true, 0.0f);
    RoomGainSlider.setValue(RoomGainSlider.getValue());
    addAndMakeVisible(&RoomGainSlider);
    addAndMakeVisible(RoomGainLabel);
    RoomGainLabel.setText("Room", juce::dontSendNotification);
    RoomGainLabel.setJustificationType(juce::Justification::centred);
    RoomGainLabel.attachToComponent(&RoomGainSlider, false);

    BleedGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    BleedGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    BleedGainSlider.setRange(-48.0f, 10.0f);
    BleedGainSlider.setDoubleClickReturnValue(true, 0.0f);
    BleedGainSlider.setValue(BleedGainSlider.getValue());
    addAndMakeVisible(&BleedGainSlider);
    addAndMakeVisible(BleedGainLabel);
    BleedGainLabel.setText("Bleed", juce::dontSendNotification);
    BleedGainLabel.setJustificationType(juce::Justification::centred);
    BleedGainLabel.attachToComponent(&BleedGainSlider, false);

    // Menu ===========================================================
    addAndMakeVisible(&samplePackMenu);
    samplePackMenu.setJustificationType(juce::Justification::centred);
    samplePackMenu.addItem("Acoustic Drum Kit", 1);
    samplePackMenu.addItem("Electronic Drum Kit", 2);
    samplePackMenu.addItem("Dry Drum Kit", 3);
    samplePackMenu.onChange = [this] { samplePackMenuChanged(); };
    samplePackMenu.setSelectedId(1);
    
    addAndMakeVisible(&curveMenu);
    curveMenu.setJustificationType(juce::Justification::centred);
    curveMenu.addItem("Linear", 1);
    curveMenu.addItem("Logarhytmic", 2);
    curveMenu.onChange = [this] { samplePackMenuChanged(); };
    curveMenu.setSelectedId(1);

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
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void HDrumsAudioProcessorEditor::resized()
{
    auto halfWidth = getWidth() / 4;
    auto qWidth = getWidth() / 8;
    kickDrumButton.setBounds(10, 40, qWidth - 12.5, 20);
    kickNoteMenu.setBounds(qWidth + 2.5, 40, qWidth - 7.5, 20);

    snareDrumButton.setBounds(10, 70, qWidth - 12.5, 20);
    snareNoteMenu.setBounds(qWidth + 2.5, 70, qWidth - 7.5, 20);

    floorTomButton.setBounds(halfWidth + 5, 40, halfWidth - 15, 20);
    floorTomButton2.setBounds(halfWidth + 5, 70, halfWidth - 15, 20);
    
    openButton.setBounds(10, 10, getWidth() - 20, 30);
    gainSlider.setBounds(30, 140, 80, getHeight() - 200);
    OHgainSlider.setBounds(120, 140, 80, getHeight() - 200);
    RoomGainSlider.setBounds(210, 140, 80, getHeight() - 200);
    BleedGainSlider.setBounds(300, 140, 80, getHeight() - 200);

    samplePackMenu.setBounds(10, 10, halfWidth - 15, 20);
    curveMenu.setBounds(halfWidth + 5, 10, halfWidth - 15, 20);

    myTabbedComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

void HDrumsAudioProcessorEditor::samplePackMenuChanged()
{
    audioProcessor.loadSamples(samplePackMenu.getSelectedId(), curveMenu.getSelectedId(),
                                kickNoteMenu.getSelectedId(), snareNoteMenu.getSelectedId());
}

void HDrumsAudioProcessorEditor::playMidiNote(int noteNumber)
{
    juce::MidiMessage message = juce::MidiMessage::noteOn(1, noteNumber, 0.92f);
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001 - 0.0);
    audioProcessor.getMidiMessageCollector().addMessageToQueue(message);
}