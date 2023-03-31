#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class MidiNotesChoosingPage : public juce::Component
{
public:
	
	juce::TextButton kickButton;
	juce::TextButton snareButton;
	juce::TextButton snareFlamButton;
	juce::TextButton snareWirelessButton;
	juce::TextButton snareRoundButton;
	juce::TextButton snareWirelessRoundButton;
	juce::TextButton tomButton;
	juce::TextButton tomFlamButton;
	juce::TextButton ftomButton;
	juce::TextButton ftomFlamButton;
	juce::TextButton hhClosedButton;
	juce::TextButton hhHalfButton;
	juce::TextButton hhOpenButton;
	juce::TextButton tambButton;
	juce::TextButton ridePointButton;
	juce::TextButton rideBellButton;
	juce::TextButton rideOpenButton;
	juce::TextButton crashPointButton;
	juce::TextButton crashBellButton;
	juce::TextButton crashOpenButton;
	
	juce::ComboBox kickNoteMenu;
	juce::ComboBox snareNoteMenu;
	juce::ComboBox snareFlamNoteMenu;
	juce::ComboBox snareWirelessNoteMenu;
	juce::ComboBox snareRoundNoteMenu;
	juce::ComboBox snareWirelessRoundNoteMenu;
	juce::ComboBox tomNoteMenu;
	juce::ComboBox tomFlamNoteMenu;
	juce::ComboBox ftomNoteMenu;
	juce::ComboBox ftomFlamNoteMenu;
	juce::ComboBox hhClosedNoteMenu;
	juce::ComboBox hhHalfNoteMenu;
	juce::ComboBox hhOpenNoteMenu;
	juce::ComboBox tambNoteMenu;
	juce::ComboBox ridePointNoteMenu;
	juce::ComboBox rideBellNoteMenu;
	juce::ComboBox rideOpenNoteMenu;
	juce::ComboBox crashPointNoteMenu;
	juce::ComboBox crashBellNoteMenu;
	juce::ComboBox crashOpenNoteMenu;

	MidiNotesChoosingPage()
	{
		addAndMakeVisible(kickButton);
		kickButton.setButtonText("Kick");
		addAndMakeVisible(&kickNoteMenu);
		kickNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			kickNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		kickNoteMenu.setSelectedId(59);    // default MIDI note for kick

		addAndMakeVisible(snareButton);
		snareButton.setButtonText("Snare");
		addAndMakeVisible(&snareNoteMenu);
		snareNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			snareNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareNoteMenu.setSelectedId(60);    // default MIDI note for snare

		addAndMakeVisible(snareFlamButton);
		snareFlamButton.setButtonText("Snare Flam");
		addAndMakeVisible(&snareFlamNoteMenu);
		snareFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			snareFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareFlamNoteMenu.setSelectedId(61);    // default MIDI note for snareFlam

		addAndMakeVisible(snareRoundButton);
		snareRoundButton.setButtonText("Snare Round");
		addAndMakeVisible(&snareRoundNoteMenu);
		snareRoundNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			snareRoundNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareRoundNoteMenu.setSelectedId(62);    // default MIDI note for snareRound

		addAndMakeVisible(snareWirelessButton);
		snareWirelessButton.setButtonText("Snare Wireless");
		addAndMakeVisible(&snareWirelessNoteMenu);
		snareWirelessNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			snareWirelessNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareWirelessNoteMenu.setSelectedId(63);    // default MIDI note for snareWireless

		addAndMakeVisible(snareWirelessRoundButton);
		snareWirelessRoundButton.setButtonText("Snare Round Wireless");
		addAndMakeVisible(&snareWirelessRoundNoteMenu);
		snareWirelessRoundNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			snareWirelessRoundNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareWirelessRoundNoteMenu.setSelectedId(64);    // default MIDI note for snareWirelessRound

		addAndMakeVisible(tomButton);
		tomButton.setButtonText("Tom");
		addAndMakeVisible(&tomNoteMenu);
		tomNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			tomNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tomNoteMenu.setSelectedId(66);    // default MIDI note for tom

		addAndMakeVisible(tomFlamButton);
		tomFlamButton.setButtonText("Tom Flam");
		addAndMakeVisible(&tomFlamNoteMenu);
		tomFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			tomFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tomFlamNoteMenu.setSelectedId(67);    // default MIDI note for tomFlam

		addAndMakeVisible(ftomButton);
		ftomButton.setButtonText("FTom");
		addAndMakeVisible(&ftomNoteMenu);
		ftomNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			ftomNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ftomNoteMenu.setSelectedId(68);    // default MIDI note for ftom

		addAndMakeVisible(ftomFlamButton);
		ftomFlamButton.setButtonText("FTom Flam");
		addAndMakeVisible(&ftomFlamNoteMenu);
		ftomFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			ftomFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ftomFlamNoteMenu.setSelectedId(69);    // default MIDI note for ftomFlam

		addAndMakeVisible(tambButton);
		tambButton.setButtonText("Tambourine");
		addAndMakeVisible(&tambNoteMenu);
		tambNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			tambNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tambNoteMenu.setSelectedId(71);    // default MIDI note for tamb

		addAndMakeVisible(hhClosedButton);
		hhClosedButton.setButtonText("HH Closed");
		addAndMakeVisible(&hhClosedNoteMenu);
		hhClosedNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			hhClosedNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhClosedNoteMenu.setSelectedId(73);    // default MIDI note for hhClosed

		addAndMakeVisible(hhHalfButton);
		hhHalfButton.setButtonText("HH Half");
		addAndMakeVisible(&hhHalfNoteMenu);
		hhHalfNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			hhHalfNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhHalfNoteMenu.setSelectedId(74);    // default MIDI note for hhHalf

		addAndMakeVisible(hhOpenButton);
		hhOpenButton.setButtonText("HH Open");
		addAndMakeVisible(&hhOpenNoteMenu);
		hhOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			hhOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhOpenNoteMenu.setSelectedId(75);    // default MIDI note for hhOpen

		addAndMakeVisible(ridePointButton);
		ridePointButton.setButtonText("Ride Point");
		addAndMakeVisible(&ridePointNoteMenu);
		ridePointNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			ridePointNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ridePointNoteMenu.setSelectedId(78);    // default MIDI note for ridePoint

		addAndMakeVisible(rideBellButton);
		rideBellButton.setButtonText("Ride Bell");
		addAndMakeVisible(&rideBellNoteMenu);
		rideBellNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			rideBellNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		rideBellNoteMenu.setSelectedId(79);    // default MIDI note for rideBell

		addAndMakeVisible(rideOpenButton);
		rideOpenButton.setButtonText("Ride Open");
		addAndMakeVisible(&rideOpenNoteMenu);
		rideOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			rideOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		rideOpenNoteMenu.setSelectedId(80);    // default MIDI note for rideOpen

		addAndMakeVisible(crashPointButton);
		crashPointButton.setButtonText("Crash Point");
		addAndMakeVisible(&crashPointNoteMenu);
		crashPointNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			crashPointNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashPointNoteMenu.setSelectedId(82);    // default MIDI note for crashPoint

		addAndMakeVisible(crashBellButton);
		crashBellButton.setButtonText("Crash Bell");
		addAndMakeVisible(&crashBellNoteMenu);
		crashBellNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			crashBellNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashBellNoteMenu.setSelectedId(83);    // default MIDI note for crashBell

		addAndMakeVisible(crashOpenButton);
		crashOpenButton.setButtonText("Crash Open");
		addAndMakeVisible(&crashOpenNoteMenu);
		crashOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		for (int i = 0; i < 128; i++)
			crashOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashOpenNoteMenu.setSelectedId(84);    // default MIDI note for crashOpen

	}

	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.setFont(15.0f);
		//g.drawFittedText("MIDI Notes Page", getLocalBounds(), juce::Justification::centred, 1);
	}
	void MidiNotesChoosingPage::resized() override
	{
		auto qWidth = getWidth() / 4;
		auto deltaHeight = getHeight() / 10;
		kickButton.setBounds(10, 8, qWidth - 12.5, deltaHeight - 5);
		snareButton.setBounds(10, deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareFlamButton.setBounds(10, 2 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareWirelessButton.setBounds(10, 3 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareRoundButton.setBounds(10, 4 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareWirelessRoundButton.setBounds(10, 5 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		tomButton.setBounds(10, 6 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		tomFlamButton.setBounds(10, 7 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		ftomButton.setBounds(10, 8 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		ftomFlamButton.setBounds(10, 9 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);

		tambButton.setBounds(2 * qWidth + 10, 8, qWidth - 12.5, deltaHeight - 5);
		hhClosedButton.setBounds(2 * qWidth + 10, deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		hhHalfButton.setBounds(2 * qWidth + 10, 2 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		hhOpenButton.setBounds(2 * qWidth + 10, 3 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		ridePointButton.setBounds(2 * qWidth + 10, 4 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		rideBellButton.setBounds(2 * qWidth + 10, 5 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		rideOpenButton.setBounds(2 * qWidth + 10, 6 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		crashPointButton.setBounds(2 * qWidth + 10, 7 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		crashBellButton.setBounds(2 * qWidth + 10, 8 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		crashOpenButton.setBounds(2 * qWidth + 10, 9 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		
		kickNoteMenu.setBounds(qWidth + 2.5, 8, qWidth - 7.5, deltaHeight - 5);
		snareNoteMenu.setBounds(qWidth + 2.5, deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		snareFlamNoteMenu.setBounds(qWidth + 2.5, 2 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		snareRoundNoteMenu.setBounds(qWidth + 2.5, 3 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		snareWirelessNoteMenu.setBounds(qWidth + 2.5, 4 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		snareWirelessRoundNoteMenu.setBounds(qWidth + 2.5, 5 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		tomNoteMenu.setBounds(qWidth + 2.5, 6 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		tomFlamNoteMenu.setBounds(qWidth + 2.5, 7 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		ftomNoteMenu.setBounds(qWidth + 2.5, 8 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		ftomFlamNoteMenu.setBounds(qWidth + 2.5, 9 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);

		tambNoteMenu.setBounds(3 * qWidth + 2.5, 8, qWidth - 7.5, deltaHeight - 5);
		hhClosedNoteMenu.setBounds(3 * qWidth + 2.5, deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		hhHalfNoteMenu.setBounds(3 * qWidth + 2.5, 2 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		hhOpenNoteMenu.setBounds(3 * qWidth + 2.5, 3 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		ridePointNoteMenu.setBounds(3 * qWidth + 2.5, 4 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		rideBellNoteMenu.setBounds(3 * qWidth + 2.5, 5 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		rideOpenNoteMenu.setBounds(3 * qWidth + 2.5, 6 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		crashPointNoteMenu.setBounds(3 * qWidth + 2.5, 7 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		crashBellNoteMenu.setBounds(3 * qWidth + 2.5, 8 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);
		crashOpenNoteMenu.setBounds(3 * qWidth + 2.5, 9 * deltaHeight + 7, qWidth - 7.5, deltaHeight - 5);

	}

private:

	juce::String midiNotes[128] = { "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2",
									"C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1",
									"C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
									"C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
									"C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
									"C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
									"C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
									"C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
									"C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
									"C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
									"C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8" };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiNotesChoosingPage)
};
