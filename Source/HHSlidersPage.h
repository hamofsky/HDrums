#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class HHSlidersPage : public juce::Component
{
public:
	juce::Slider hhCloseSlider;
	juce::Slider tambCloseSlider;
	juce::Slider hhOHSlider;
	juce::Slider hhRoomSlider;
	juce::Slider hhBleedSlider;
	juce::Label hhCloseSliderLabel;
	juce::Label tambCloseSliderLabel;
	juce::Label hhOHSliderLabel;
	juce::Label hhRoomSliderLabel;
	juce::Label hhBleedSliderLabel;

	HHSlidersPage()
	{
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

		tambCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tambCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tambCloseSlider.setRange(-48.0f, 10.0f);
		tambCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		tambCloseSlider.setValue(tambCloseSlider.getValue());
		addAndMakeVisible(&tambCloseSlider);
		addAndMakeVisible(tambCloseSliderLabel);
		tambCloseSliderLabel.setText("Tamb", juce::dontSendNotification);
		tambCloseSliderLabel.setJustificationType(juce::Justification::centred);
		tambCloseSliderLabel.attachToComponent(&tambCloseSlider, false);

		hhOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		hhOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		hhOHSlider.setRange(-48.0f, 10.0f);
		hhOHSlider.setDoubleClickReturnValue(true, 0.0f);
		hhOHSlider.setValue(hhOHSlider.getValue());
		addAndMakeVisible(&hhOHSlider);
		addAndMakeVisible(hhOHSliderLabel);
		hhOHSliderLabel.setText("OH", juce::dontSendNotification);
		hhOHSliderLabel.setJustificationType(juce::Justification::centred);
		hhOHSliderLabel.attachToComponent(&hhOHSlider, false);

		hhRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		hhRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		hhRoomSlider.setRange(-48.0f, 10.0f);
		hhRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		hhRoomSlider.setValue(hhRoomSlider.getValue());
		addAndMakeVisible(&hhRoomSlider);
		addAndMakeVisible(hhRoomSliderLabel);
		hhRoomSliderLabel.setText("Room", juce::dontSendNotification);
		hhRoomSliderLabel.setJustificationType(juce::Justification::centred);
		hhRoomSliderLabel.attachToComponent(&hhRoomSlider, false);

		hhBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		hhBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		hhBleedSlider.setRange(-48.0f, 10.0f);
		hhBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		hhBleedSlider.setValue(hhBleedSlider.getValue());
		addAndMakeVisible(&hhBleedSlider);
		addAndMakeVisible(hhBleedSliderLabel);
		hhBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		hhBleedSliderLabel.setJustificationType(juce::Justification::centred);
		hhBleedSliderLabel.attachToComponent(&hhBleedSlider, false);
	}

	void HHSlidersPage::resized() override
	{
		hhCloseSlider.setBounds(30, 50, 70, getHeight() - 100);
		tambCloseSlider.setBounds(120, 50, 70, getHeight() - 100);
		hhOHSlider.setBounds(210, 50, 70, getHeight() - 100);
		hhRoomSlider.setBounds(300, 50, 70, getHeight() - 100);
		hhBleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HHSlidersPage)
};