#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class MidiNotesChoosingPage : public juce::Component
{
public:
	
	juce::ComboBox kickNoteMenu;
	juce::ComboBox snareNoteMenu;
	juce::ComboBox snareSwirlNoteMenu;
	juce::ComboBox snareFlamNoteMenu;
	juce::ComboBox snareRoundNoteMenu;
	juce::ComboBox snareWirelessNoteMenu;
	juce::ComboBox snareWirelessRoundNoteMenu;
	juce::ComboBox snarePiccoloNoteMenu;
	juce::ComboBox snarePiccoloSwirlNoteMenu;
	juce::ComboBox tomNoteMenu;
	juce::ComboBox tomFlamNoteMenu;
	juce::ComboBox ftomNoteMenu;
	juce::ComboBox ftomFlamNoteMenu;
	juce::ComboBox hhFootNoteMenu;
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
	juce::ComboBox stackClosedNoteMenu;
	juce::ComboBox stackOpenNoteMenu;
	juce::ComboBox sticksNoteMenu;

	MyLookAndFeel myLookAndFeel;

	std::vector<juce::ComboBox*> midiNoteHiddenMenus = { &kickNoteMenu, &snareNoteMenu, &snareSwirlNoteMenu, &snareFlamNoteMenu, &snareRoundNoteMenu,
								&snareWirelessNoteMenu, &snareWirelessRoundNoteMenu, &snarePiccoloNoteMenu, &snarePiccoloSwirlNoteMenu,
								&tomNoteMenu, &tomFlamNoteMenu, &ftomNoteMenu, &ftomFlamNoteMenu,
								&hhFootNoteMenu, &hhClosedNoteMenu, &hhHalfNoteMenu, &hhOpenNoteMenu, &tambNoteMenu,
								&ridePointNoteMenu, &rideBellNoteMenu, &rideOpenNoteMenu, &crashPointNoteMenu, &crashBellNoteMenu, &crashOpenNoteMenu,
								&stackClosedNoteMenu, &stackOpenNoteMenu, &sticksNoteMenu };

	juce::ComboBox allSounds;
	juce::ComboBox soundNoteMenu;
	juce::TextButton soundButton;

	MidiNotesChoosingPage()
	{

		for (int i = 0; i < midiNoteHiddenMenus.size(); i++)
		{
			midiNoteHiddenMenus[i]->addItemList(midiNotes, 0);
			midiNoteHiddenMenus[i]->setSelectedId(defaultMidiNotes[i + 1]);
			addAndMakeVisible(midiNoteHiddenMenus[i]);
		}

		addAndMakeVisible(&allSounds);
		//allSounds.addItemList(sounds, 1);
		for (int i = 0; i < sounds2.size(); i++)
			allSounds.addItem(sounds2[i], i);
		allSounds.setJustificationType(juce::Justification::centredLeft);
		allSounds.setSelectedId(1, 1);

		addAndMakeVisible(&soundNoteMenu);
		soundNoteMenu.setJustificationType(juce::Justification::centredLeft);
		soundNoteMenu.addItemList(midiNotes, 0);
		soundNoteMenu.setSelectedId(0, 1);

		addAndMakeVisible(soundButton);
		soundButton.setButtonText("Play Sound");
		soundButton.setLookAndFeel(&myLookAndFeel);

	}

	~MidiNotesChoosingPage()
	{
		midiNoteHiddenMenus.clear();
		midiNoteHiddenMenus.shrink_to_fit();
	}

	void paint(juce::Graphics& g) override
	{
		g.setFont(18.0f);
		g.setColour(juce::Colours::black);
		g.drawFittedText("ARTICULATION", getWidth() / 8, getHeight() / 8 + 6, 4 * getWidth() / 8 - 10, getHeight() / 8, juce::Justification::centred, 1);
		g.drawFittedText("NOTE", 5 * getWidth() / 8 + 10, getHeight() / 8 + 6, 2 * getWidth() / 8 - 20, getHeight() / 8, juce::Justification::centred, 1);
	}
	void MidiNotesChoosingPage::resized() override
	{
		auto qWidth = getWidth() / 8;
		auto qHeight = getHeight() / 8;

		allSounds.setBounds(qWidth, 2 * qHeight, 4 * qWidth - 10, qHeight - 10);
		soundNoteMenu.setBounds(5 * qWidth + 10, 2 * qHeight, 2 * qWidth - 10, qHeight - 10);
		soundButton.setBounds(qWidth, 3 * qHeight + 10, 6 * qWidth, 2 * qHeight);
	}

private:

	int defaultMidiNotes[28] = { 0, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97 };

	juce::StringArray sounds = juce::StringArray("Kick", "Snare", "Snare Swirl", "Snare Flam", "Snare Round", "Snare Wireless", "Snare Wireless Round", "Piccolo", "Piccolo Swirl", 
												 "Tom", "Tom Flam", "FTom", "FTom Flam", "HH Foot", "HH Closed", "HH Half", "HH Open", "Tambourine",
												 "Ride Point", "Ride Bell", "Ride Open", "Crash Point", "Crash Bell", "Crash Open", "Stack Closed", "Stack Open", "Sticks");

	std::vector<juce::String> sounds2 = { "HDrums", "Kick", "Snare", "Snare Swirl", "Snare Flam", "Snare Round", "Snare Wireless", "Snare Wireless Round", "Piccolo", "Piccolo Swirl",
												 "Tom", "Tom Flam", "FTom", "FTom Flam", "HH Foot", "HH Closed", "HH Half", "HH Open", "Tambourine",
												 "Ride Point", "Ride Bell", "Ride Open", "Crash Point", "Crash Bell", "Crash Open", "Stack Closed", "Stack Open", "Sticks" };

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
