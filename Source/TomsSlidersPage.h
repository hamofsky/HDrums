#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

#pragma once

class TomsSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
	MyLookAndFeelSolo myLookAndFeelSolo;
	juce::Slider tomCloseSlider;
	juce::Slider ftomCloseSlider;
	juce::Slider tomsOHSlider;
	juce::Slider tomsRoomSlider;
	juce::Slider tomsBleedSlider;
	juce::Label tomCloseSliderLabel;
	juce::Label ftomCloseSliderLabel;
	juce::Label tomsOHSliderLabel;
	juce::Label tomsRoomSliderLabel;
	juce::Label tomsBleedSliderLabel;
	float sliderMinValue = -36.0f;
	float sliderMaxValue = 12.0f;

	MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;

	juce::ToggleButton tomCloseSolo;
	juce::ToggleButton ftomCloseSolo;
	juce::ToggleButton tomsOHSolo;
	juce::ToggleButton tomsRoomSolo;
	juce::ToggleButton tomsBleedSolo;
	std::vector<juce::ToggleButton*> tomsSoloButtons = { &tomCloseSolo, &ftomCloseSolo, &tomsOHSolo, &tomsRoomSolo, &tomsBleedSolo };

	juce::ToggleButton tomCloseMute;
	juce::ToggleButton ftomCloseMute;
	juce::ToggleButton tomsOHMute;
	juce::ToggleButton tomsRoomMute;
	juce::ToggleButton tomsBleedMute;
	std::vector<juce::ToggleButton*> tomsMuteButtons = { &tomCloseMute, &ftomCloseMute, &tomsOHMute, &tomsRoomMute, &tomsBleedMute };

	TomsSlidersPage()
	{
		tomCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		tomCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		tomCloseSlider.setLookAndFeel(&myLookAndFeel);
		tomCloseSlider.setValue(tomCloseSlider.getValue());
		addAndMakeVisible(&tomCloseSlider);
		addAndMakeVisible(tomCloseSliderLabel);
		tomCloseSliderLabel.setText("Tom", juce::dontSendNotification);
		tomCloseSliderLabel.setJustificationType(juce::Justification::centred);
		tomCloseSliderLabel.attachToComponent(&tomCloseSlider, false);

		ftomCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		ftomCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		ftomCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		ftomCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		ftomCloseSlider.setLookAndFeel(&myLookAndFeel);
		ftomCloseSlider.setValue(ftomCloseSlider.getValue());
		addAndMakeVisible(&ftomCloseSlider);
		addAndMakeVisible(ftomCloseSliderLabel);
		ftomCloseSliderLabel.setText("FTom", juce::dontSendNotification);
		ftomCloseSliderLabel.setJustificationType(juce::Justification::centred);
		ftomCloseSliderLabel.attachToComponent(&ftomCloseSlider, false);

		tomsOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsOHSlider.setRange(sliderMinValue, sliderMaxValue);
		tomsOHSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsOHSlider.setLookAndFeel(&myLookAndFeel);
		tomsOHSlider.setValue(tomsOHSlider.getValue());
		addAndMakeVisible(&tomsOHSlider);
		addAndMakeVisible(tomsOHSliderLabel);
		tomsOHSliderLabel.setText("OH", juce::dontSendNotification);
		tomsOHSliderLabel.setJustificationType(juce::Justification::centred);
		tomsOHSliderLabel.attachToComponent(&tomsOHSlider, false);

		tomsRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsRoomSlider.setRange(sliderMinValue, sliderMaxValue);
		tomsRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsRoomSlider.setLookAndFeel(&myLookAndFeel);
		tomsRoomSlider.setValue(tomsRoomSlider.getValue());
		addAndMakeVisible(&tomsRoomSlider);
		addAndMakeVisible(tomsRoomSliderLabel);
		tomsRoomSliderLabel.setText("Room", juce::dontSendNotification);
		tomsRoomSliderLabel.setJustificationType(juce::Justification::centred);
		tomsRoomSliderLabel.attachToComponent(&tomsRoomSlider, false);

		tomsBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsBleedSlider.setRange(sliderMinValue, sliderMaxValue);
		tomsBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsBleedSlider.setLookAndFeel(&myLookAndFeel);
		tomsBleedSlider.setValue(tomsBleedSlider.getValue());
		addAndMakeVisible(&tomsBleedSlider);
		addAndMakeVisible(tomsBleedSliderLabel);
		tomsBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		tomsBleedSliderLabel.setJustificationType(juce::Justification::centred);
		tomsBleedSliderLabel.attachToComponent(&tomsBleedSlider, false);

		for (int i = 0; i < tomsSoloButtons.size(); i++)
		{
			addAndMakeVisible(tomsSoloButtons[i]);
			tomsSoloButtons[i]->setLookAndFeel(&myLookAndFeelSolo);
			tomsSoloButtons[i]->setToggleState(tomsSoloButtons[i]->getToggleState(), true);

			addAndMakeVisible(tomsMuteButtons[i]);
			tomsMuteButtons[i]->setLookAndFeel(&myLookAndFeel);
			tomsMuteButtons[i]->setToggleState(tomsMuteButtons[i]->getToggleState(), true);
		}
	}

	TomsSlidersPage::~TomsSlidersPage()
	{
		tomsMuteButtons.clear();
		tomsSoloButtons.clear();
		tomsMuteButtons.shrink_to_fit();
		tomsSoloButtons.shrink_to_fit();
	}

	void TomsSlidersPage::resized() override
	{
		int sliderWidth = 70;
		int sliderHeight = getHeight() - 90;
		tomCloseSlider.setBounds(10, 40, sliderWidth, sliderHeight);
		ftomCloseSlider.setBounds(85, 40, sliderWidth, sliderHeight);
		tomsOHSlider.setBounds(162, 40, sliderWidth, sliderHeight);
		tomsRoomSlider.setBounds(240, 40, sliderWidth, sliderHeight);
		tomsBleedSlider.setBounds(315, 40, sliderWidth, sliderHeight);

		int buttonsSize = 32;
		int buttonsPositionY = sliderHeight + 45;
		tomCloseSolo.setBounds(10, buttonsPositionY, buttonsSize, buttonsSize);
		ftomCloseSolo.setBounds(85, buttonsPositionY, buttonsSize, buttonsSize);
		tomsOHSolo.setBounds(162, buttonsPositionY, buttonsSize, buttonsSize);
		tomsRoomSolo.setBounds(240, buttonsPositionY, buttonsSize, buttonsSize);
		tomsBleedSolo.setBounds(315, buttonsPositionY, buttonsSize, buttonsSize);

		tomCloseMute.setBounds(48, buttonsPositionY, buttonsSize, buttonsSize);
		ftomCloseMute.setBounds(123, buttonsPositionY, buttonsSize, buttonsSize);
		tomsOHMute.setBounds(200, buttonsPositionY, buttonsSize, buttonsSize);
		tomsRoomMute.setBounds(278, buttonsPositionY, buttonsSize, buttonsSize);
		tomsBleedMute.setBounds(353, buttonsPositionY, buttonsSize, buttonsSize);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TomsSlidersPage)
};