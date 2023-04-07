#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"

#pragma once

class KickSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
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
	}

	void KickSlidersPage::resized() override
	{
		kickCloseSlider.setBounds(15, 50, 70, getHeight() - 100);
		kickOHSlider.setBounds(115, 50, 70, getHeight() - 100);
		kickRoomSlider.setBounds(215, 50, 70, getHeight() - 100);
		kickBleedSlider.setBounds(315, 50, 70, getHeight() - 100);
	}

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KickSlidersPage)
};
