#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"
#include "MidiProcessor.h"

HDrumsAudioProcessorEditor::HDrumsAudioProcessorEditor(HDrumsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)//, openButton("Browse for directory")
{
    setSize(500, 400);

    addAndMakeVisible(kickDrumButton);
    kickDrumButton.setButtonText("Kick Drum");
    kickDrumButton.onClick = [this] { playMidiNote(kickNoteMenu.getSelectedId()); };
    addAndMakeVisible(&kickNoteMenu);
    kickNoteMenu.setJustificationType(juce::Justification::centred);
    for (int i = 1; i < 128; i++)
        kickNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
    kickNoteMenu.onChange = [this] { samplePackMenuChanged(); };
    kickNoteMenu.setSelectedId(57);    // default MIDI note for snare

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

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0f, 10.0f);
    gainSlider.setValue(gainSlider.getValue());
    addAndMakeVisible(&gainSlider);
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Volume", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);

    OHgainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    OHgainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    OHgainSlider.setRange(-48.0f, 10.0f);
    OHgainSlider.setValue(OHgainSlider.getValue());
    addAndMakeVisible(&OHgainSlider);
    addAndMakeVisible(OHgainLabel);
    OHgainLabel.setText("OH", juce::dontSendNotification);
    OHgainLabel.setJustificationType(juce::Justification::centred);
    OHgainLabel.attachToComponent(&OHgainSlider, false);

    RoomGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    RoomGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    RoomGainSlider.setRange(-48.0f, 10.0f);
    RoomGainSlider.setValue(RoomGainSlider.getValue());
    addAndMakeVisible(&RoomGainSlider);
    addAndMakeVisible(RoomGainLabel);
    RoomGainLabel.setText("Room", juce::dontSendNotification);
    RoomGainLabel.setJustificationType(juce::Justification::centred);
    RoomGainLabel.attachToComponent(&RoomGainSlider, false);

    addAndMakeVisible(&samplePackMenu);
    samplePackMenu.setJustificationType(juce::Justification::centred);
    samplePackMenu.addItem("Acoustic Drum Kit", 1);
    samplePackMenu.addItem("Electronic Drum Kit", 2);
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

//juce::String NewProjectAudioProcessorEditor::loadDirectory()
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

    /*g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);*/
}

void HDrumsAudioProcessorEditor::resized()
{
    auto halfWidth = getWidth() / 2;
    auto qWidth = getWidth() / 4;
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
    samplePackMenu.setBounds(10, 10, halfWidth - 15, 20);
    curveMenu.setBounds(halfWidth + 5, 10, halfWidth - 15, 20);
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