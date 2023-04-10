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
	}

	void CymbalsSlidersPage::resized() override
	{
		hhCloseSlider.setBounds(15, 50, 70, getHeight() - 100);
		cymbalsOHSlider.setBounds(115, 50, 70, getHeight() - 100);
		cymbalsRoomSlider.setBounds(215, 50, 70, getHeight() - 100);
		cymbalsBleedSlider.setBounds(315, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CymbalsSlidersPage)
};