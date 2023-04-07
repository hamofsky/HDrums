#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"

#pragma once

class TomsSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
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
	}

	void TomsSlidersPage::resized() override
	{
		tomCloseSlider.setBounds(10, 50, 70, getHeight() - 100);
		ftomCloseSlider.setBounds(85, 50, 70, getHeight() - 100);
		tomsOHSlider.setBounds(162, 50, 70, getHeight() - 100);
		tomsRoomSlider.setBounds(240, 50, 70, getHeight() - 100);
		tomsBleedSlider.setBounds(315, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TomsSlidersPage)
};