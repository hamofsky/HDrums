#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"

#pragma once

class SnareSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
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

	SnareSlidersPage()
	{
		snareTopCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareTopCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareTopCloseSlider.setRange(-48.0f, 10.0f);
		snareTopCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		snareTopCloseSlider.setNumDecimalPlacesToDisplay(1);
		snareTopCloseSlider.setLookAndFeel(&myLookAndFeel);
		snareTopCloseSlider.setValue(snareTopCloseSlider.getValue());
		addAndMakeVisible(&snareTopCloseSlider);
		addAndMakeVisible(snareTopCloseSliderLabel);
		snareTopCloseSliderLabel.setText("Top", juce::dontSendNotification);
		snareTopCloseSliderLabel.setJustificationType(juce::Justification::centred);
		snareTopCloseSliderLabel.attachToComponent(&snareTopCloseSlider, false);

		snareBotCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareBotCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareBotCloseSlider.setRange(-48.0f, 10.0f);
		snareBotCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		snareBotCloseSlider.setNumDecimalPlacesToDisplay(1);
		snareBotCloseSlider.setLookAndFeel(&myLookAndFeel);
		snareBotCloseSlider.setValue(snareBotCloseSlider.getValue());
		addAndMakeVisible(&snareBotCloseSlider);
		addAndMakeVisible(snareBotCloseSliderLabel);
		snareBotCloseSliderLabel.setText("Bottom", juce::dontSendNotification);
		snareBotCloseSliderLabel.setJustificationType(juce::Justification::centred);
		snareBotCloseSliderLabel.attachToComponent(&snareBotCloseSlider, false);

		snareOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareOHSlider.setRange(-48.0f, 10.0f);
		snareOHSlider.setDoubleClickReturnValue(true, 0.0f);
		snareOHSlider.setNumDecimalPlacesToDisplay(1);
		snareOHSlider.setLookAndFeel(&myLookAndFeel);
		snareOHSlider.setValue(snareOHSlider.getValue());
		addAndMakeVisible(&snareOHSlider);
		addAndMakeVisible(snareOHSliderLabel);
		snareOHSliderLabel.setText("OH", juce::dontSendNotification);
		snareOHSliderLabel.setJustificationType(juce::Justification::centred);
		snareOHSliderLabel.attachToComponent(&snareOHSlider, false);

		snareRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareRoomSlider.setRange(-48.0f, 10.0f);
		snareRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		snareRoomSlider.setNumDecimalPlacesToDisplay(1);
		snareRoomSlider.setLookAndFeel(&myLookAndFeel);
		snareRoomSlider.setValue(snareRoomSlider.getValue());
		addAndMakeVisible(&snareRoomSlider);
		addAndMakeVisible(snareRoomSliderLabel);
		snareRoomSliderLabel.setText("Room", juce::dontSendNotification);
		snareRoomSliderLabel.setJustificationType(juce::Justification::centred);
		snareRoomSliderLabel.attachToComponent(&snareRoomSlider, false);

		snareBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		snareBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		snareBleedSlider.setRange(-48.0f, 10.0f);
		snareBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		snareBleedSlider.setNumDecimalPlacesToDisplay(1);
		snareBleedSlider.setLookAndFeel(&myLookAndFeel);
		snareBleedSlider.setValue(snareBleedSlider.getValue());
		addAndMakeVisible(&snareBleedSlider);
		addAndMakeVisible(snareBleedSliderLabel);
		snareBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		snareBleedSliderLabel.setJustificationType(juce::Justification::centred);
		snareBleedSliderLabel.attachToComponent(&snareBleedSlider, false);
	}

	void SnareSlidersPage::resized() override
	{
		snareTopCloseSlider.setBounds(10, 50, 70, getHeight() - 100);
		snareBotCloseSlider.setBounds(85, 50, 70, getHeight() - 100);
		snareOHSlider.setBounds(162, 50, 70, getHeight() - 100);
		snareRoomSlider.setBounds(240, 50, 70, getHeight() - 100);
		snareBleedSlider.setBounds(315, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SnareSlidersPage)
};