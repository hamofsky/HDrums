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
	juce::TextButton snareRoundButton;
	juce::TextButton snareWirelessButton;
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
	juce::ComboBox snareRoundNoteMenu;
	juce::ComboBox snareWirelessNoteMenu;
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
		kickNoteMenu.addItemList(midiNotes, 0);
		kickNoteMenu.setSelectedId(defaultMidiNotes[0]);

		addAndMakeVisible(snareButton);
		snareButton.setButtonText("Snare");
		addAndMakeVisible(&snareNoteMenu);
		snareNoteMenu.setJustificationType(juce::Justification::centredLeft);
		snareNoteMenu.addItemList(midiNotes, 0);
		snareNoteMenu.setSelectedId(defaultMidiNotes[1]);

		addAndMakeVisible(snareFlamButton);
		snareFlamButton.setButtonText("Snare Flam");
		addAndMakeVisible(&snareFlamNoteMenu);
		snareFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		snareFlamNoteMenu.addItemList(midiNotes, 0);
		snareFlamNoteMenu.setSelectedId(defaultMidiNotes[2]);

		addAndMakeVisible(snareRoundButton);
		snareRoundButton.setButtonText("Snare Round");
		addAndMakeVisible(&snareRoundNoteMenu);
		snareRoundNoteMenu.setJustificationType(juce::Justification::centredLeft);
		snareRoundNoteMenu.addItemList(midiNotes, 0);
		snareRoundNoteMenu.setSelectedId(defaultMidiNotes[3]);

		addAndMakeVisible(snareWirelessButton);
		snareWirelessButton.setButtonText("Snare Wireless");
		addAndMakeVisible(&snareWirelessNoteMenu);
		snareWirelessNoteMenu.setJustificationType(juce::Justification::centredLeft);
		snareWirelessNoteMenu.addItemList(midiNotes, 0);
		snareWirelessNoteMenu.setSelectedId(defaultMidiNotes[4]);

		addAndMakeVisible(snareWirelessRoundButton);
		snareWirelessRoundButton.setButtonText("Snare Round Wireless");
		addAndMakeVisible(&snareWirelessRoundNoteMenu);
		snareWirelessRoundNoteMenu.setJustificationType(juce::Justification::centredLeft);
		snareWirelessRoundNoteMenu.addItemList(midiNotes, 0);
		snareWirelessRoundNoteMenu.setSelectedId(defaultMidiNotes[5]);

		addAndMakeVisible(tomButton);
		tomButton.setButtonText("Tom");
		addAndMakeVisible(&tomNoteMenu);
		tomNoteMenu.setJustificationType(juce::Justification::centredLeft);
		tomNoteMenu.addItemList(midiNotes, 0);
		tomNoteMenu.setSelectedId(defaultMidiNotes[6]);

		addAndMakeVisible(tomFlamButton);
		tomFlamButton.setButtonText("Tom Flam");
		addAndMakeVisible(&tomFlamNoteMenu);
		tomFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		tomFlamNoteMenu.addItemList(midiNotes, 0);
		tomFlamNoteMenu.setSelectedId(defaultMidiNotes[7]);

		addAndMakeVisible(ftomButton);
		ftomButton.setButtonText("FTom");
		addAndMakeVisible(&ftomNoteMenu);
		ftomNoteMenu.setJustificationType(juce::Justification::centredLeft);
		ftomNoteMenu.addItemList(midiNotes, 0);
		ftomNoteMenu.setSelectedId(defaultMidiNotes[8]);

		addAndMakeVisible(ftomFlamButton);
		ftomFlamButton.setButtonText("FTom Flam");
		addAndMakeVisible(&ftomFlamNoteMenu);
		ftomFlamNoteMenu.setJustificationType(juce::Justification::centredLeft);
		ftomFlamNoteMenu.addItemList(midiNotes, 0);
		ftomFlamNoteMenu.setSelectedId(defaultMidiNotes[9]);

		addAndMakeVisible(tambButton);
		tambButton.setButtonText("Tambourine");
		addAndMakeVisible(&tambNoteMenu);
		tambNoteMenu.setJustificationType(juce::Justification::centredLeft);
		tambNoteMenu.addItemList(midiNotes, 0);
		tambNoteMenu.setSelectedId(defaultMidiNotes[10]);

		addAndMakeVisible(hhClosedButton);
		hhClosedButton.setButtonText("HH Closed");
		addAndMakeVisible(&hhClosedNoteMenu);
		hhClosedNoteMenu.setJustificationType(juce::Justification::centredLeft);
		hhClosedNoteMenu.addItemList(midiNotes, 0);
		hhClosedNoteMenu.setSelectedId(defaultMidiNotes[11]);

		addAndMakeVisible(hhHalfButton);
		hhHalfButton.setButtonText("HH Half");
		addAndMakeVisible(&hhHalfNoteMenu);
		hhHalfNoteMenu.setJustificationType(juce::Justification::centredLeft);
		hhHalfNoteMenu.addItemList(midiNotes, 0);
		hhHalfNoteMenu.setSelectedId(defaultMidiNotes[12]);

		addAndMakeVisible(hhOpenButton);
		hhOpenButton.setButtonText("HH Open");
		addAndMakeVisible(&hhOpenNoteMenu);
		hhOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		hhOpenNoteMenu.addItemList(midiNotes, 0);
		hhOpenNoteMenu.setSelectedId(defaultMidiNotes[13]);

		addAndMakeVisible(ridePointButton);
		ridePointButton.setButtonText("Ride Point");
		addAndMakeVisible(&ridePointNoteMenu);
		ridePointNoteMenu.setJustificationType(juce::Justification::centredLeft);
		ridePointNoteMenu.addItemList(midiNotes, 0);
		ridePointNoteMenu.setSelectedId(defaultMidiNotes[14]);

		addAndMakeVisible(rideBellButton);
		rideBellButton.setButtonText("Ride Bell");
		addAndMakeVisible(&rideBellNoteMenu);
		rideBellNoteMenu.setJustificationType(juce::Justification::centredLeft);
		rideBellNoteMenu.addItemList(midiNotes, 0);
		rideBellNoteMenu.setSelectedId(defaultMidiNotes[15]);

		addAndMakeVisible(rideOpenButton);
		rideOpenButton.setButtonText("Ride Open");
		addAndMakeVisible(&rideOpenNoteMenu);
		rideOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		rideOpenNoteMenu.addItemList(midiNotes, 0);
		rideOpenNoteMenu.setSelectedId(defaultMidiNotes[16]);

		addAndMakeVisible(crashPointButton);
		crashPointButton.setButtonText("Crash Point");
		addAndMakeVisible(&crashPointNoteMenu);
		crashPointNoteMenu.setJustificationType(juce::Justification::centredLeft);
		crashPointNoteMenu.addItemList(midiNotes, 0);
		crashPointNoteMenu.setSelectedId(defaultMidiNotes[17]);

		addAndMakeVisible(crashBellButton);
		crashBellButton.setButtonText("Crash Bell");
		addAndMakeVisible(&crashBellNoteMenu);
		crashBellNoteMenu.setJustificationType(juce::Justification::centredLeft);
		crashBellNoteMenu.addItemList(midiNotes, 0);
		crashBellNoteMenu.setSelectedId(defaultMidiNotes[18]);

		addAndMakeVisible(crashOpenButton);
		crashOpenButton.setButtonText("Crash Open");
		addAndMakeVisible(&crashOpenNoteMenu);
		crashOpenNoteMenu.setJustificationType(juce::Justification::centredLeft);
		crashOpenNoteMenu.addItemList(midiNotes, 0);
		crashOpenNoteMenu.setSelectedId(defaultMidiNotes[19]);

	}

	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.setFont(15.0f);
	}
	void MidiNotesChoosingPage::resized() override
	{
		auto qWidth = getWidth() / 4;
		auto deltaHeight = getHeight() / 10;
		kickButton.setBounds(10, 8, qWidth - 12.5, deltaHeight - 5);
		snareButton.setBounds(10, deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareFlamButton.setBounds(10, 2 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareRoundButton.setBounds(10, 3 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
		snareWirelessButton.setBounds(10, 4 * deltaHeight + 7, qWidth - 12.5, deltaHeight - 5);
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

	int defaultMidiNotes[20] = { 71, 72, 73, 74, 75, 76, 78, 79, 80, 81, 83, 85, 86, 87, 89, 90, 91, 93, 94, 95 };

	juce::StringArray midiNotes = juce::StringArray("0 C-2", "1 C#-2", "2 D-2", "3 D#-2", "4 E-2", "5 F-2", "6 F#-2", "7 G-2", "8 G#-2", "9 A-2", "10 A#-2", "11 B-2",
													"12 C-1", "13 C#-1", "14 D-1", "15 D#-1", "16 E-1", "17 F-1", "18 F#-1", "19 G-1", "20 G#-1", "21 A-1", "22 A#-1", "23 B-1",
													"24 C0", "25 C#0", "26 D0", "27 D#0", " 28 E0", "29 F0", "30 F#0", " 31 G0", "32 G#0", "33 A0", "34 A#0", "35 B0",
													"36 C1", "37 C#1", "38 D1", "39 D#1", "40 E1", "41 F1", "42 F#1", "43 G1", "44 G#1", "45 A1", "46 A#1", "47 B1",
													"48 C2", "49 C#2", "50 D2", "51 D#2", "52 E2", "53 F2", "54 F#2", "55 G2", "56 G#2", "57 A2", "58 A#2", "59 B2",
													"60 C3", "61 C#3", "62 D3", "63 D#3", "64 E3", "65 F3", "66 F#3", "67 G3", "68 G#3", "69 A3", "70 A#3", "71 B3",
													"72 C4", "73 C#4", "74 D4", "75 D#4", "76 E4", "77 F4", "78 F#4", "79 G4", "80 G#4", "81 A4", "82 A#4", "83 B4",
													"84 C5", "85 C#5", "86 D5", "87 D#5", "88 E5", "89 F5", "90 F#5", "91 G5", "92 G#5", "93 A5", "94 A#5", "95 B5",
													"96 C6", "97 C#6", "98 D6", "99 D#6", "100 E6", "101 F6", "102 F#6", "103 G6", "104 G#6", "105 A6", "106 A#6", "107 B6",
													"108 C7", "109 C#7", "110 D7", "111 D#7", "112 E7", "113 F7", "114 F#7", "115 G7", "116 G#7", "117 A7", "118 A#7", "119 B7",
													"120 C8", "121 C#8", "122 D8", "123 D#8", "124 E8", "125 F8", "126 F#8", "127 G8");

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiNotesChoosingPage)
};
