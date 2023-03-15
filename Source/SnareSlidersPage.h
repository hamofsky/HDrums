#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class SnareSlidersPage : public juce::Component
{
public:
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
		snareBleedSlider.setValue(snareBleedSlider.getValue());
		addAndMakeVisible(&snareBleedSlider);
		addAndMakeVisible(snareBleedSliderLabel);
		snareBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		snareBleedSliderLabel.setJustificationType(juce::Justification::centred);
		snareBleedSliderLabel.attachToComponent(&snareBleedSlider, false);
	}

	void SnareSlidersPage::resized() override
	{
		snareTopCloseSlider.setBounds(30, 50, 70, getHeight() - 100);
		snareBotCloseSlider.setBounds(120, 50, 70, getHeight() - 100);
		snareOHSlider.setBounds(210, 50, 70, getHeight() - 100);
		snareRoomSlider.setBounds(300, 50, 70, getHeight() - 100);
		snareBleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SnareSlidersPage)
};