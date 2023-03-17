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
	juce::TextButton hhBellButton;
	juce::TextButton hhClosedButton;
	juce::TextButton hhHalfButton;
	juce::TextButton hhOpenButton;
	juce::TextButton tambButton;
	juce::TextButton ridePointButton;
	juce::TextButton rideHalfButton;
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
	juce::ComboBox hhBellNoteMenu;
	juce::ComboBox hhClosedNoteMenu;
	juce::ComboBox hhHalfNoteMenu;
	juce::ComboBox hhOpenNoteMenu;
	juce::ComboBox tambNoteMenu;
	juce::ComboBox ridePointNoteMenu;
	juce::ComboBox rideHalfNoteMenu;
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
		kickNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			kickNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		kickNoteMenu.setSelectedId(57);    // default MIDI note for kick
		
		addAndMakeVisible(snareButton);
		snareButton.setButtonText("Snare");
		addAndMakeVisible(&snareNoteMenu);
		snareNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			snareNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareNoteMenu.setSelectedId(60);    // default MIDI note for snare

		addAndMakeVisible(snareFlamButton);
		snareFlamButton.setButtonText("Snare Flam");
		addAndMakeVisible(&snareFlamNoteMenu);
		snareFlamNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			snareFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareFlamNoteMenu.setSelectedId(61);    // default MIDI note for snareFlam

		addAndMakeVisible(snareWirelessButton);
		snareWirelessButton.setButtonText("Snare Wireless");
		addAndMakeVisible(&snareWirelessNoteMenu);
		snareWirelessNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			snareWirelessNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareWirelessNoteMenu.setSelectedId(62);    // default MIDI note for snareWireless

		addAndMakeVisible(snareRoundButton);
		snareRoundButton.setButtonText("Snare Round");
		addAndMakeVisible(&snareRoundNoteMenu);
		snareRoundNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			snareRoundNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareRoundNoteMenu.setSelectedId(63);    // default MIDI note for snareRound

		addAndMakeVisible(snareWirelessRoundButton);
		snareWirelessRoundButton.setButtonText("Snare Round Wireless");
		addAndMakeVisible(&snareWirelessRoundNoteMenu);
		snareWirelessRoundNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			snareWirelessRoundNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		snareWirelessRoundNoteMenu.setSelectedId(64);    // default MIDI note for snareWirelessRound

		addAndMakeVisible(tomButton);
		tomButton.setButtonText("Tom");
		addAndMakeVisible(&tomNoteMenu);
		tomNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			tomNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tomNoteMenu.setSelectedId(66);    // default MIDI note for tom

		addAndMakeVisible(tomFlamButton);
		tomFlamButton.setButtonText("Tom Flam");
		addAndMakeVisible(&tomFlamNoteMenu);
		tomFlamNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			tomFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tomFlamNoteMenu.setSelectedId(67);    // default MIDI note for tomFlam

		addAndMakeVisible(ftomButton);
		ftomButton.setButtonText("FTom");
		addAndMakeVisible(&ftomNoteMenu);
		ftomNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			ftomNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ftomNoteMenu.setSelectedId(68);    // default MIDI note for ftom

		addAndMakeVisible(ftomFlamButton);
		ftomFlamButton.setButtonText("FTom Flam");
		addAndMakeVisible(&ftomFlamNoteMenu);
		ftomFlamNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			ftomFlamNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ftomFlamNoteMenu.setSelectedId(69);    // default MIDI note for ftomFlam

		addAndMakeVisible(hhBellButton);
		hhBellButton.setButtonText("HH Bell");
		addAndMakeVisible(&hhBellNoteMenu);
		hhBellNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			hhBellNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhBellNoteMenu.setSelectedId(71);    // default MIDI note for hhBell

		addAndMakeVisible(hhClosedButton);
		hhClosedButton.setButtonText("HH Closed");
		addAndMakeVisible(&hhClosedNoteMenu);
		hhClosedNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			hhClosedNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhClosedNoteMenu.setSelectedId(72);    // default MIDI note for hhClosed

		addAndMakeVisible(hhHalfButton);
		hhHalfButton.setButtonText("HH Half");
		addAndMakeVisible(&hhHalfNoteMenu);
		hhHalfNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			hhHalfNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhHalfNoteMenu.setSelectedId(73);    // default MIDI note for hhHalf

		addAndMakeVisible(hhOpenButton);
		hhOpenButton.setButtonText("HH Open");
		addAndMakeVisible(&hhOpenNoteMenu);
		hhOpenNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			hhOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		hhOpenNoteMenu.setSelectedId(74);    // default MIDI note for hhOpen

		addAndMakeVisible(tambButton);
		tambButton.setButtonText("Tambourine");
		addAndMakeVisible(&tambNoteMenu);
		tambNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			tambNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		tambNoteMenu.setSelectedId(90);    // default MIDI note for tamb

		addAndMakeVisible(ridePointButton);
		ridePointButton.setButtonText("Ride Piont");
		addAndMakeVisible(&ridePointNoteMenu);
		ridePointNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			ridePointNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		ridePointNoteMenu.setSelectedId(76);    // default MIDI note for ridePoint

		addAndMakeVisible(rideHalfButton);
		rideHalfButton.setButtonText("Ride Half");
		addAndMakeVisible(&rideHalfNoteMenu);
		rideHalfNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			rideHalfNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		rideHalfNoteMenu.setSelectedId(77);    // default MIDI note for rideHalf

		addAndMakeVisible(rideBellButton);
		rideBellButton.setButtonText("Ride Bell");
		addAndMakeVisible(&rideBellNoteMenu);
		rideBellNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			rideBellNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		rideBellNoteMenu.setSelectedId(78);    // default MIDI note for rideBell

		addAndMakeVisible(rideOpenButton);
		rideOpenButton.setButtonText("Ride Open");
		addAndMakeVisible(&rideOpenNoteMenu);
		rideOpenNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			rideOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		rideOpenNoteMenu.setSelectedId(79);    // default MIDI note for rideOpen

		addAndMakeVisible(crashPointButton);
		crashPointButton.setButtonText("Crash Point");
		addAndMakeVisible(&crashPointNoteMenu);
		crashPointNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			crashPointNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashPointNoteMenu.setSelectedId(81);    // default MIDI note for crashPoint

		addAndMakeVisible(crashBellButton);
		crashBellButton.setButtonText("Crash Bell");
		addAndMakeVisible(&crashBellNoteMenu);
		crashBellNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			crashBellNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashBellNoteMenu.setSelectedId(82);    // default MIDI note for crashBell

		addAndMakeVisible(crashOpenButton);
		crashOpenButton.setButtonText("Crash Open");
		addAndMakeVisible(&crashOpenNoteMenu);
		crashOpenNoteMenu.setJustificationType(juce::Justification::centred);
		for (int i = 1; i < 128; i++)
			crashOpenNoteMenu.addItem(juce::String(i) + " (" + midiNotes[i] + ")", i);
		crashOpenNoteMenu.setSelectedId(83);    // default MIDI note for crashOpen

	}

	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.setFont(15.0f);
		g.drawFittedText("MIDI Notes Page", getLocalBounds(), juce::Justification::centred, 1);
	}
	void MidiNotesChoosingPage::resized() override
	{
		// 22 guziczki
		auto qWidth = getWidth() / 4;
		kickButton.setBounds(10, 10, qWidth - 12.5, 20);
		kickNoteMenu.setBounds(qWidth + 2.5, 10, qWidth - 7.5, 20);
		snareButton.setBounds(10, 40, qWidth - 12.5, 20);
		snareNoteMenu.setBounds(qWidth + 2.5, 40, qWidth - 7.5, 20);
		snareFlamButton.setBounds(10, 70, qWidth - 12.5, 20);
		snareFlamNoteMenu.setBounds(qWidth + 2.5, 70, qWidth - 7.5, 20);
	}

private:

	juce::String midiNotes[128] = { "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
									"C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
									"C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
									"C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
									"C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A4", "B4",
									"C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
									"C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
									"C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
									"C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "A#8", "B8",
									"C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "A#9", "B9",
									"C10", "C#10", "D10", "D#10", "E10", "F10", "F#10", "G10" };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiNotesChoosingPage)
};
