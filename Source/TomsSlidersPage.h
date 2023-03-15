#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class TomsSlidersPage : public juce::Component
{
public:
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

	TomsSlidersPage()
	{
		tomCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomCloseSlider.setRange(-48.0f, 10.0f);
		tomCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		tomCloseSlider.setValue(tomCloseSlider.getValue());
		addAndMakeVisible(&tomCloseSlider);
		addAndMakeVisible(tomCloseSliderLabel);
		tomCloseSliderLabel.setText("Tom", juce::dontSendNotification);
		tomCloseSliderLabel.setJustificationType(juce::Justification::centred);
		tomCloseSliderLabel.attachToComponent(&tomCloseSlider, false);

		ftomCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		ftomCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		ftomCloseSlider.setRange(-48.0f, 10.0f);
		ftomCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		ftomCloseSlider.setValue(ftomCloseSlider.getValue());
		addAndMakeVisible(&ftomCloseSlider);
		addAndMakeVisible(ftomCloseSliderLabel);
		ftomCloseSliderLabel.setText("FTom", juce::dontSendNotification);
		ftomCloseSliderLabel.setJustificationType(juce::Justification::centred);
		ftomCloseSliderLabel.attachToComponent(&ftomCloseSlider, false);

		tomsOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsOHSlider.setRange(-48.0f, 10.0f);
		tomsOHSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsOHSlider.setValue(tomsOHSlider.getValue());
		addAndMakeVisible(&tomsOHSlider);
		addAndMakeVisible(tomsOHSliderLabel);
		tomsOHSliderLabel.setText("OH", juce::dontSendNotification);
		tomsOHSliderLabel.setJustificationType(juce::Justification::centred);
		tomsOHSliderLabel.attachToComponent(&tomsOHSlider, false);

		tomsRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsRoomSlider.setRange(-48.0f, 10.0f);
		tomsRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsRoomSlider.setValue(tomsRoomSlider.getValue());
		addAndMakeVisible(&tomsRoomSlider);
		addAndMakeVisible(tomsRoomSliderLabel);
		tomsRoomSliderLabel.setText("Room", juce::dontSendNotification);
		tomsRoomSliderLabel.setJustificationType(juce::Justification::centred);
		tomsRoomSliderLabel.attachToComponent(&tomsRoomSlider, false);

		tomsBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		tomsBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		tomsBleedSlider.setRange(-48.0f, 10.0f);
		tomsBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		tomsBleedSlider.setValue(tomsBleedSlider.getValue());
		addAndMakeVisible(&tomsBleedSlider);
		addAndMakeVisible(tomsBleedSliderLabel);
		tomsBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		tomsBleedSliderLabel.setJustificationType(juce::Justification::centred);
		tomsBleedSliderLabel.attachToComponent(&tomsBleedSlider, false);
	}

	void TomsSlidersPage::resized() override
	{
		tomCloseSlider.setBounds(30, 50, 70, getHeight() - 100);
		ftomCloseSlider.setBounds(120, 50, 70, getHeight() - 100);
		tomsOHSlider.setBounds(210, 50, 70, getHeight() - 100);
		tomsRoomSlider.setBounds(300, 50, 70, getHeight() - 100);
		tomsBleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TomsSlidersPage)
};