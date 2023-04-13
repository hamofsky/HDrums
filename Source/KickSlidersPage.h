#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

#pragma once

class KickSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
	MyLookAndFeelSolo myLookAndFeelSolo;
	juce::Slider kickCloseSlider;
	juce::Label kickCloseSliderLabel;
	juce::Slider kickOHSlider;
	juce::Label kickOHSliderLabel;
	juce::Slider kickRoomSlider;
	juce::Label kickRoomSliderLabel;
	juce::Slider kickBleedSlider;
	juce::Label kickBleedSliderLabel;
	float sliderMinValue = -36.0f;
	float sliderMaxValue = 12.0f;

	MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;

	juce::ToggleButton kickCloseSolo;
	juce::ToggleButton kickOHSolo;
	juce::ToggleButton kickRoomSolo;
	juce::ToggleButton kickBleedSolo;
	std::vector<juce::ToggleButton*> kickSoloButtons = { &kickCloseSolo, &kickOHSolo, &kickRoomSolo, &kickBleedSolo };

	juce::ToggleButton kickCloseMute;
	juce::ToggleButton kickOHMute;
	juce::ToggleButton kickRoomMute;
	juce::ToggleButton kickBleedMute;
	std::vector<juce::ToggleButton*> kickMuteButtons = { &kickCloseMute, &kickOHMute, &kickRoomMute, &kickBleedMute };

	KickSlidersPage()
	{
		kickCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickCloseSlider.setRange(sliderMinValue, sliderMaxValue);
		kickCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		kickCloseSlider.setLookAndFeel(&myLookAndFeel);
		kickCloseSlider.setValue(kickCloseSlider.getValue());
		addAndMakeVisible(&kickCloseSlider);
		addAndMakeVisible(kickCloseSliderLabel);
		kickCloseSliderLabel.setText("Close", juce::dontSendNotification);
		kickCloseSliderLabel.setJustificationType(juce::Justification::centred);
		kickCloseSliderLabel.attachToComponent(&kickCloseSlider, false);

		kickOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickOHSlider.setRange(sliderMinValue, sliderMaxValue);
		kickOHSlider.setDoubleClickReturnValue(true, 0.0f);
		kickOHSlider.setLookAndFeel(&myLookAndFeel);
		kickOHSlider.setValue(kickOHSlider.getValue());
		addAndMakeVisible(&kickOHSlider);
		addAndMakeVisible(kickOHSliderLabel);
		kickOHSliderLabel.setText("OH", juce::dontSendNotification);
		kickOHSliderLabel.setJustificationType(juce::Justification::centred);
		kickOHSliderLabel.attachToComponent(&kickOHSlider, false);

		kickRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickRoomSlider.setRange(sliderMinValue, sliderMaxValue);
		kickRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		kickRoomSlider.setLookAndFeel(&myLookAndFeel);
		kickRoomSlider.setValue(kickRoomSlider.getValue());
		addAndMakeVisible(&kickRoomSlider);
		addAndMakeVisible(kickRoomSliderLabel);
		kickRoomSliderLabel.setText("Room", juce::dontSendNotification);
		kickRoomSliderLabel.setJustificationType(juce::Justification::centred);
		kickRoomSliderLabel.attachToComponent(&kickRoomSlider, false);

		kickBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickBleedSlider.setRange(sliderMinValue, sliderMaxValue);
		kickBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		kickBleedSlider.setLookAndFeel(&myLookAndFeel);
		kickBleedSlider.setValue(kickBleedSlider.getValue());
		addAndMakeVisible(&kickBleedSlider);
		addAndMakeVisible(kickBleedSliderLabel);
		kickBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		kickBleedSliderLabel.setJustificationType(juce::Justification::centred);
		kickBleedSliderLabel.attachToComponent(&kickBleedSlider, false);

		for (int i = 0; i < kickSoloButtons.size(); i++)
		{
			addAndMakeVisible(kickSoloButtons[i]);
			kickSoloButtons[i]->setLookAndFeel(&myLookAndFeelSolo);
			kickSoloButtons[i]->setToggleState(kickSoloButtons[i]->getToggleState(), true);

			addAndMakeVisible(kickMuteButtons[i]);
			kickMuteButtons[i]->setLookAndFeel(&myLookAndFeel);
			kickMuteButtons[i]->setToggleState(kickMuteButtons[i]->getToggleState(), true);
		}
	}

	KickSlidersPage::~KickSlidersPage()
	{
		kickMuteButtons.clear();
		kickSoloButtons.clear();
		kickMuteButtons.shrink_to_fit();
		kickSoloButtons.shrink_to_fit();
	}

	void KickSlidersPage::resized() override
	{
		int sliderWidth = 70;
		int sliderHeight = getHeight() - 90;
		kickCloseSlider.setBounds(15, 40, sliderWidth, sliderHeight);
		kickOHSlider.setBounds(115, 40, sliderWidth, sliderHeight);
		kickRoomSlider.setBounds(215, 40, sliderWidth, sliderHeight);
		kickBleedSlider.setBounds(315, 40, sliderWidth, sliderHeight);

		int buttonsSize = 32;
		int buttonsPositionY = sliderHeight + 45;
		kickCloseSolo.setBounds(15, buttonsPositionY, buttonsSize, buttonsSize);
		kickOHSolo.setBounds(115, buttonsPositionY, buttonsSize, buttonsSize);
		kickRoomSolo.setBounds(215, buttonsPositionY, buttonsSize, buttonsSize);
		kickBleedSolo.setBounds(315, buttonsPositionY, buttonsSize, buttonsSize);

		kickCloseMute.setBounds(53, buttonsPositionY, buttonsSize, buttonsSize);
		kickOHMute.setBounds(153, buttonsPositionY, buttonsSize, buttonsSize);
		kickRoomMute.setBounds(253, buttonsPositionY, buttonsSize, buttonsSize);
		kickBleedMute.setBounds(353, buttonsPositionY, buttonsSize, buttonsSize);
	}

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KickSlidersPage)
};
