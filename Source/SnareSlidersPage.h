#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

#pragma once

class SnareSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
	MyLookAndFeelSolo myLookAndFeelSolo;
	juce::Slider snareTopCloseSlider;
	juce::Slider snareBotCloseSlider;
	juce::Slider snareOHSlider;
	juce::Slider snareRoomSlider;
	juce::Slider snareBleedSlider;
	juce::Label snareTopCloseSliderLabel;
	juce::Label snareBotCloseSliderLabel;
	juce::Label snareOHSliderLabel;
	juce::Label snareRoomSliderLabel;
	juce::Label snareBleedSliderLabel;
	float sliderMinValue = -36.0f;
	float sliderMaxValue = 12.0f;

	MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;

	juce::ToggleButton snareTopSolo;
	juce::ToggleButton snareBotSolo;
	juce::ToggleButton snareOHSolo;
	juce::ToggleButton snareRoomSolo;
	juce::ToggleButton snareBleedSolo;
	std::vector<juce::ToggleButton*> snareSoloButtons = { &snareTopSolo, &snareBotSolo, &snareOHSolo, &snareRoomSolo, &snareBleedSolo };

	juce::ToggleButton snareTopMute;
	juce::ToggleButton snareBotMute;
	juce::ToggleButton snareOHMute;
	juce::ToggleButton snareRoomMute;
	juce::ToggleButton snareBleedMute;
	std::vector<juce::ToggleButton*> snareMuteButtons = { &snareTopMute, &snareBotMute, &snareOHMute, &snareRoomMute, &snareBleedMute };

	SnareSlidersPage()
	{
		snareTopCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareTopCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareTopCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		snareTopCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		snareTopCloseSlider.setLookAndFeel(&myLookAndFeel);
		snareTopCloseSlider.setValue(snareTopCloseSlider.getValue());
		addAndMakeVisible(&snareTopCloseSlider);
		addAndMakeVisible(snareTopCloseSliderLabel);
		snareTopCloseSliderLabel.setText("Top", juce::dontSendNotification);
		snareTopCloseSliderLabel.setJustificationType(juce::Justification::centred);
		snareTopCloseSliderLabel.attachToComponent(&snareTopCloseSlider, false);

		snareBotCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareBotCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareBotCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		snareBotCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		snareBotCloseSlider.setLookAndFeel(&myLookAndFeel);
		snareBotCloseSlider.setValue(snareBotCloseSlider.getValue());
		addAndMakeVisible(&snareBotCloseSlider);
		addAndMakeVisible(snareBotCloseSliderLabel);
		snareBotCloseSliderLabel.setText("Bottom", juce::dontSendNotification);
		snareBotCloseSliderLabel.setJustificationType(juce::Justification::centred);
		snareBotCloseSliderLabel.attachToComponent(&snareBotCloseSlider, false);

		snareOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareOHSlider.setRange(sliderMinValue, sliderMaxValue);
		snareOHSlider.setDoubleClickReturnValue(true, 0.0f);
		snareOHSlider.setLookAndFeel(&myLookAndFeel);
		snareOHSlider.setValue(snareOHSlider.getValue());
		addAndMakeVisible(&snareOHSlider);
		addAndMakeVisible(snareOHSliderLabel);
		snareOHSliderLabel.setText("OH", juce::dontSendNotification);
		snareOHSliderLabel.setJustificationType(juce::Justification::centred);
		snareOHSliderLabel.attachToComponent(&snareOHSlider, false);

		snareRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareRoomSlider.setRange(sliderMinValue, sliderMaxValue);
		snareRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		snareRoomSlider.setLookAndFeel(&myLookAndFeel);
		snareRoomSlider.setValue(snareRoomSlider.getValue());
		addAndMakeVisible(&snareRoomSlider);
		addAndMakeVisible(snareRoomSliderLabel);
		snareRoomSliderLabel.setText("Room", juce::dontSendNotification);
		snareRoomSliderLabel.setJustificationType(juce::Justification::centred);
		snareRoomSliderLabel.attachToComponent(&snareRoomSlider, false);

		snareBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareBleedSlider.setRange(sliderMinValue, sliderMaxValue);
		snareBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		snareBleedSlider.setLookAndFeel(&myLookAndFeel);
		snareBleedSlider.setValue(snareBleedSlider.getValue());
		addAndMakeVisible(&snareBleedSlider);
		addAndMakeVisible(snareBleedSliderLabel);
		snareBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		snareBleedSliderLabel.setJustificationType(juce::Justification::centred);
		snareBleedSliderLabel.attachToComponent(&snareBleedSlider, false);

		for (int i = 0; i < snareSoloButtons.size(); i++)
		{
			addAndMakeVisible(snareSoloButtons[i]);
			snareSoloButtons[i]->setLookAndFeel(&myLookAndFeelSolo);
			//snareSoloButtons[i]->setToggleState(snareSoloButtons[i]->getToggleState(), true);

			addAndMakeVisible(snareMuteButtons[i]);
			snareMuteButtons[i]->setLookAndFeel(&myLookAndFeel);
			//snareMuteButtons[i]->setToggleState(snareMuteButtons[i]->getToggleState(), true);
		}
	}

	SnareSlidersPage::~SnareSlidersPage()
	{
		snareMuteButtons.clear();
		snareSoloButtons.clear();
		snareMuteButtons.shrink_to_fit();
		snareSoloButtons.shrink_to_fit();
	}

	void SnareSlidersPage::resized() override
	{
		int sliderWidth = 70;
		int sliderHeight = getHeight() - 90;
		snareTopCloseSlider.setBounds(10, 40, sliderWidth, sliderHeight);
		snareBotCloseSlider.setBounds(85, 40, sliderWidth, sliderHeight);
		snareOHSlider.setBounds(162, 40, sliderWidth, sliderHeight);
		snareRoomSlider.setBounds(240, 40, sliderWidth, sliderHeight);
		snareBleedSlider.setBounds(315, 40, sliderWidth, sliderHeight);
		
		int buttonsSize = 32;
		int buttonsPositionY = sliderHeight + 45;
		snareTopSolo.setBounds(10, buttonsPositionY, buttonsSize, buttonsSize);
		snareBotSolo.setBounds(85, buttonsPositionY, buttonsSize, buttonsSize);
		snareOHSolo.setBounds(162, buttonsPositionY, buttonsSize, buttonsSize);
		snareRoomSolo.setBounds(240, buttonsPositionY, buttonsSize, buttonsSize);
		snareBleedSolo.setBounds(315, buttonsPositionY, buttonsSize, buttonsSize);
		snareTopMute.setBounds(48, buttonsPositionY, buttonsSize, buttonsSize);
		snareBotMute.setBounds(123, buttonsPositionY, buttonsSize, buttonsSize);
		snareOHMute.setBounds(200, buttonsPositionY, buttonsSize, buttonsSize);
		snareRoomMute.setBounds(278, buttonsPositionY, buttonsSize, buttonsSize);
		snareBleedMute.setBounds(353, buttonsPositionY, buttonsSize, buttonsSize);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SnareSlidersPage)
};