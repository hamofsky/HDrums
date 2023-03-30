#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class CymbalsSlidersPage : public juce::Component
{
public:
	/*juce::Slider crashCloseSlider;
	juce::Slider rideCloseSlider;*/
	juce::Slider hhCloseSlider;
	juce::Slider cymbalsOHSlider;
	juce::Slider cymbalsRoomSlider;
	juce::Slider cymbalsBleedSlider;
	/*juce::Label crashCloseSliderLabel;
	juce::Label rideCloseSliderLabel;*/
	juce::Label hhCloseSliderLabel;
	juce::Label cymbalsOHSliderLabel;
	juce::Label cymbalsRoomSliderLabel;
	juce::Label cymbalsBleedSliderLabel;

	CymbalsSlidersPage()
	{
		/*crashCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		crashCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		crashCloseSlider.setRange(-48.0f, 10.0f);
		crashCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		crashCloseSlider.setValue(crashCloseSlider.getValue());
		addAndMakeVisible(&crashCloseSlider);
		addAndMakeVisible(crashCloseSliderLabel);
		crashCloseSliderLabel.setText("Crash", juce::dontSendNotification);
		crashCloseSliderLabel.setJustificationType(juce::Justification::centred);
		crashCloseSliderLabel.attachToComponent(&crashCloseSlider, false);*/

		/*rideCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		rideCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		rideCloseSlider.setRange(-48.0f, 10.0f);
		rideCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		rideCloseSlider.setValue(rideCloseSlider.getValue());
		addAndMakeVisible(&rideCloseSlider);
		addAndMakeVisible(rideCloseSliderLabel);
		rideCloseSliderLabel.setText("Ride", juce::dontSendNotification);
		rideCloseSliderLabel.setJustificationType(juce::Justification::centred);
		rideCloseSliderLabel.attachToComponent(&rideCloseSlider, false);*/

		hhCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		hhCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		hhCloseSlider.setRange(-48.0f, 10.0f);
		hhCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		hhCloseSlider.setValue(hhCloseSlider.getValue());
		addAndMakeVisible(&hhCloseSlider);
		addAndMakeVisible(hhCloseSliderLabel);
		hhCloseSliderLabel.setText("HH", juce::dontSendNotification);
		hhCloseSliderLabel.setJustificationType(juce::Justification::centred);
		hhCloseSliderLabel.attachToComponent(&hhCloseSlider, false);

		cymbalsOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsOHSlider.setRange(-48.0f, 10.0f);
		cymbalsOHSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsOHSlider.setValue(cymbalsOHSlider.getValue());
		addAndMakeVisible(&cymbalsOHSlider);
		addAndMakeVisible(cymbalsOHSliderLabel);
		cymbalsOHSliderLabel.setText("OH", juce::dontSendNotification);
		cymbalsOHSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsOHSliderLabel.attachToComponent(&cymbalsOHSlider, false);

		cymbalsRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsRoomSlider.setRange(-48.0f, 10.0f);
		cymbalsRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsRoomSlider.setValue(cymbalsRoomSlider.getValue());
		addAndMakeVisible(&cymbalsRoomSlider);
		addAndMakeVisible(cymbalsRoomSliderLabel);
		cymbalsRoomSliderLabel.setText("Room", juce::dontSendNotification);
		cymbalsRoomSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsRoomSliderLabel.attachToComponent(&cymbalsRoomSlider, false);

		cymbalsBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		cymbalsBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		cymbalsBleedSlider.setRange(-48.0f, 10.0f);
		cymbalsBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		cymbalsBleedSlider.setValue(cymbalsBleedSlider.getValue());
		addAndMakeVisible(&cymbalsBleedSlider);
		addAndMakeVisible(cymbalsBleedSliderLabel);
		cymbalsBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		cymbalsBleedSliderLabel.setJustificationType(juce::Justification::centred);
		cymbalsBleedSliderLabel.attachToComponent(&cymbalsBleedSlider, false);
	}

	void CymbalsSlidersPage::resized() override
	{
		/*crashCloseSlider.setBounds(30, 50, 70, getHeight() - 100);
		rideCloseSlider.setBounds(120, 50, 70, getHeight() - 100);*/
		hhCloseSlider.setBounds(120, 50, 70, getHeight() - 100);
		cymbalsOHSlider.setBounds(210, 50, 70, getHeight() - 100);
		cymbalsRoomSlider.setBounds(300, 50, 70, getHeight() - 100);
		cymbalsBleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CymbalsSlidersPage)
};