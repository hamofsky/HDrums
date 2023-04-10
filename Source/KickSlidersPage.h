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

	bool muteStateBeforeFirstSolo[4] = { false, false, false, false };
	bool soloAlreadyEngaged = false;

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
		kickCloseSlider.setBounds(15, 40, 70, getHeight() - 104);
		kickOHSlider.setBounds(115, 40, 70, getHeight() - 104);
		kickRoomSlider.setBounds(215, 40, 70, getHeight() - 104);
		kickBleedSlider.setBounds(315, 40, 70, getHeight() - 104);

		int buttonsSize = 50;

		kickCloseSolo.setBounds(20, getHeight() - 60, buttonsSize, buttonsSize);
		kickOHSolo.setBounds(120, getHeight() - 60, buttonsSize, buttonsSize);
		kickRoomSolo.setBounds(220, getHeight() - 60, buttonsSize, buttonsSize);
		kickBleedSolo.setBounds(320, getHeight() - 60, buttonsSize, buttonsSize);
		kickCloseMute.setBounds(57, getHeight() - 60, buttonsSize, buttonsSize);
		kickOHMute.setBounds(157, getHeight() - 60, buttonsSize, buttonsSize);
		kickRoomMute.setBounds(257, getHeight() - 60, buttonsSize, buttonsSize);
		kickBleedMute.setBounds(357, getHeight() - 60, buttonsSize, buttonsSize);
	}

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KickSlidersPage)
};
