#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class HHSlidersPage : public juce::Component
{
public:
	/*juce::Slider hhCloseSlider;
	juce::Slider tambCloseSlider;
	juce::Slider hhOHSlider;
	juce::Slider hhRoomSlider;
	juce::Slider hhBleedSlider;
	juce::Label hhCloseSliderLabel;
	juce::Label tambCloseSliderLabel;
	juce::Label hhOHSliderLabel;
	juce::Label hhRoomSliderLabel;
	juce::Label hhBleedSliderLabel;*/

	juce::Slider closeSlider;
	juce::Slider OHSlider;
	juce::Slider roomSlider;
	juce::Slider bleedSlider;
	juce::Label closeSliderLabel;
	juce::Label OHSliderLabel;
	juce::Label roomSliderLabel;
	juce::Label bleedSliderLabel;

	HHSlidersPage()
	{
		/*hhCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
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
		hhBleedSliderLabel.attachToComponent(&hhBleedSlider, false);*/

		closeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		closeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		closeSlider.setRange(-48.0f, 10.0f);
		closeSlider.setDoubleClickReturnValue(true, 0.0f);
		closeSlider.setValue(closeSlider.getValue());
		addAndMakeVisible(&closeSlider);
		addAndMakeVisible(closeSliderLabel);
		closeSliderLabel.setText("Close", juce::dontSendNotification);
		closeSliderLabel.setJustificationType(juce::Justification::centred);
		closeSliderLabel.attachToComponent(&closeSlider, false);

		OHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		OHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		OHSlider.setRange(-48.0f, 10.0f);
		OHSlider.setDoubleClickReturnValue(true, 0.0f);
		OHSlider.setValue(OHSlider.getValue());
		addAndMakeVisible(&OHSlider);
		addAndMakeVisible(OHSliderLabel);
		OHSliderLabel.setText("OH", juce::dontSendNotification);
		OHSliderLabel.setJustificationType(juce::Justification::centred);
		OHSliderLabel.attachToComponent(&OHSlider, false);

		roomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		roomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		roomSlider.setRange(-48.0f, 10.0f);
		roomSlider.setDoubleClickReturnValue(true, 0.0f);
		roomSlider.setValue(roomSlider.getValue());
		addAndMakeVisible(&roomSlider);
		addAndMakeVisible(roomSliderLabel);
		roomSliderLabel.setText("Room", juce::dontSendNotification);
		roomSliderLabel.setJustificationType(juce::Justification::centred);
		roomSliderLabel.attachToComponent(&roomSlider, false);

		bleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		bleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		bleedSlider.setRange(-48.0f, 10.0f);
		bleedSlider.setDoubleClickReturnValue(true, 0.0f);
		bleedSlider.setValue(bleedSlider.getValue());
		addAndMakeVisible(&bleedSlider);
		addAndMakeVisible(bleedSliderLabel);
		bleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		bleedSliderLabel.setJustificationType(juce::Justification::centred);
		bleedSliderLabel.attachToComponent(&bleedSlider, false);
	}

	void HHSlidersPage::resized() override
	{
		/*hhCloseSlider.setBounds(30, 50, 70, getHeight() - 100);
		tambCloseSlider.setBounds(120, 50, 70, getHeight() - 100);
		hhOHSlider.setBounds(210, 50, 70, getHeight() - 100);
		hhRoomSlider.setBounds(300, 50, 70, getHeight() - 100);
		hhBleedSlider.setBounds(390, 50, 70, getHeight() - 100);*/

		closeSlider.setBounds(30, 50, 70, getHeight() - 100);
		OHSlider.setBounds(210, 50, 70, getHeight() - 100);
		roomSlider.setBounds(300, 50, 70, getHeight() - 100);
		bleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HHSlidersPage)
};