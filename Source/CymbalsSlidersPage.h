#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

#pragma once

class CymbalsSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
	MyLookAndFeelSolo myLookAndFeelSolo;
	juce::Slider hhCloseSlider;
	juce::Slider cymbalsOHSlider;
	juce::Slider cymbalsRoomSlider;
	juce::Slider cymbalsBleedSlider;
	juce::Label hhCloseSliderLabel;
	juce::Label cymbalsOHSliderLabel;
	juce::Label cymbalsRoomSliderLabel;
	juce::Label cymbalsBleedSliderLabel;
	float sliderMinValue = -36.0f;
	float sliderMaxValue = 12.0f;

	MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;

	juce::ToggleButton hhCloseSolo;
	juce::ToggleButton cymbalsOHSolo;
	juce::ToggleButton cymbalsRoomSolo;
	juce::ToggleButton cymbalsBleedSolo;
	std::vector<juce::ToggleButton*> cymbalsSoloButtons = { &hhCloseSolo, &cymbalsOHSolo, &cymbalsRoomSolo, &cymbalsBleedSolo };

	juce::ToggleButton hhCloseMute;
	juce::ToggleButton cymbalsOHMute;
	juce::ToggleButton cymbalsRoomMute;
	juce::ToggleButton cymbalsBleedMute;
	std::vector<juce::ToggleButton*> cymbalsMuteButtons = { &hhCloseMute, &cymbalsOHMute, &cymbalsRoomMute, &cymbalsBleedMute };

	CymbalsSlidersPage()
	{
		hhCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		hhCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		hhCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		hhCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		hhCloseSlider.setLookAndFeel(&myLookAndFeel);
		hhCloseSlider.setValue(hhCloseSlider.getValue());
		addAndMakeVisible(&hhCloseSlider);
		addAndMakeVisible(hhCloseSliderLabel);
		hhCloseSliderLabel.setText("HH", juce::dontSendNotification);
		hhCloseSliderLabel.setJustificationType(juce::Justification::centred);
		hhCloseSliderLabel.attachToComponent(&hhCloseSlider, false);

		cymbalsOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsOHSlider.setRange(sliderMinValue, sliderMaxValue);
		cymbalsOHSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsOHSlider.setLookAndFeel(&myLookAndFeel);
		cymbalsOHSlider.setValue(cymbalsOHSlider.getValue());
		addAndMakeVisible(&cymbalsOHSlider);
		addAndMakeVisible(cymbalsOHSliderLabel);
		cymbalsOHSliderLabel.setText("OH", juce::dontSendNotification);
		cymbalsOHSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsOHSliderLabel.attachToComponent(&cymbalsOHSlider, false);

		cymbalsRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsRoomSlider.setRange(sliderMinValue, sliderMaxValue);
		cymbalsRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsRoomSlider.setLookAndFeel(&myLookAndFeel);
		cymbalsRoomSlider.setValue(cymbalsRoomSlider.getValue());
		addAndMakeVisible(&cymbalsRoomSlider);
		addAndMakeVisible(cymbalsRoomSliderLabel);
		cymbalsRoomSliderLabel.setText("Room", juce::dontSendNotification);
		cymbalsRoomSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsRoomSliderLabel.attachToComponent(&cymbalsRoomSlider, false);

		cymbalsBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsBleedSlider.setRange(sliderMinValue, sliderMaxValue);
		cymbalsBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsBleedSlider.setLookAndFeel(&myLookAndFeel);
		cymbalsBleedSlider.setValue(cymbalsBleedSlider.getValue());
		addAndMakeVisible(&cymbalsBleedSlider);
		addAndMakeVisible(cymbalsBleedSliderLabel);
		cymbalsBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		cymbalsBleedSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsBleedSliderLabel.attachToComponent(&cymbalsBleedSlider, false);

		for (int i = 0; i < cymbalsSoloButtons.size(); i++)
		{
			addAndMakeVisible(cymbalsSoloButtons[i]);
			cymbalsSoloButtons[i]->setLookAndFeel(&myLookAndFeelSolo);
			cymbalsSoloButtons[i]->setToggleState(cymbalsSoloButtons[i]->getToggleState(), true);

			addAndMakeVisible(cymbalsMuteButtons[i]);
			cymbalsMuteButtons[i]->setLookAndFeel(&myLookAndFeel);
			cymbalsMuteButtons[i]->setToggleState(cymbalsMuteButtons[i]->getToggleState(), true);
		}
	}

	CymbalsSlidersPage::~CymbalsSlidersPage()
	{
		cymbalsMuteButtons.clear();
		cymbalsSoloButtons.clear();
		cymbalsMuteButtons.shrink_to_fit();
		cymbalsSoloButtons.shrink_to_fit();
	}

	void CymbalsSlidersPage::resized() override
	{
		int sliderWidth = 70;
		int sliderHeight = getHeight() - 90;
		hhCloseSlider.setBounds(15, 40, sliderWidth, sliderHeight);
		cymbalsOHSlider.setBounds(115, 40, sliderWidth, sliderHeight);
		cymbalsRoomSlider.setBounds(215, 40, sliderWidth, sliderHeight);
		cymbalsBleedSlider.setBounds(315, 40, sliderWidth, sliderHeight);

		int buttonsSize = 32;
		int buttonsPositionY = sliderHeight + 45;
		hhCloseSolo.setBounds(15, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsOHSolo.setBounds(115, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsRoomSolo.setBounds(215, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsBleedSolo.setBounds(315, buttonsPositionY, buttonsSize, buttonsSize);

		hhCloseMute.setBounds(53, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsOHMute.setBounds(153, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsRoomMute.setBounds(253, buttonsPositionY, buttonsSize, buttonsSize);
		cymbalsBleedMute.setBounds(353, buttonsPositionY, buttonsSize, buttonsSize);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CymbalsSlidersPage)
};