#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class KickSlidersPage : public juce::Component
{
public:
	juce::Slider kickCloseSlider;
	juce::Label kickCloseSliderLabel;
	juce::Slider kickOHSlider;
	juce::Label kickOHSliderLabel;
	juce::Slider kickRoomSlider;
	juce::Label kickRoomSliderLabel;
	juce::Slider kickBleedSlider;
	juce::Label kickBleedSliderLabel;

	KickSlidersPage()
	{
		kickCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickCloseSlider.setRange(-48.0f, 10.0f);
		kickCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		kickCloseSlider.setValue(kickCloseSlider.getValue());
		addAndMakeVisible(&kickCloseSlider);
		addAndMakeVisible(kickCloseSliderLabel);
		kickCloseSliderLabel.setText("Close", juce::dontSendNotification);
		kickCloseSliderLabel.setJustificationType(juce::Justification::centred);
		kickCloseSliderLabel.attachToComponent(&kickCloseSlider, false);

		kickOHSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickOHSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickOHSlider.setRange(-48.0f, 10.0f);
		kickOHSlider.setDoubleClickReturnValue(true, 0.0f);
		kickOHSlider.setValue(kickOHSlider.getValue());
		addAndMakeVisible(&kickOHSlider);
		addAndMakeVisible(kickOHSliderLabel);
		kickOHSliderLabel.setText("OH", juce::dontSendNotification);
		kickOHSliderLabel.setJustificationType(juce::Justification::centred);
		kickOHSliderLabel.attachToComponent(&kickOHSlider, false);

		kickRoomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickRoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickRoomSlider.setRange(-48.0f, 10.0f);
		kickRoomSlider.setDoubleClickReturnValue(true, 0.0f);
		kickRoomSlider.setValue(kickRoomSlider.getValue());
		addAndMakeVisible(&kickRoomSlider);
		addAndMakeVisible(kickRoomSliderLabel);
		kickRoomSliderLabel.setText("Room", juce::dontSendNotification);
		kickRoomSliderLabel.setJustificationType(juce::Justification::centred);
		kickRoomSliderLabel.attachToComponent(&kickRoomSlider, false);

		kickBleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickBleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickBleedSlider.setRange(-48.0f, 10.0f);
		kickBleedSlider.setDoubleClickReturnValue(true, 0.0f);
		kickBleedSlider.setValue(kickBleedSlider.getValue());
		addAndMakeVisible(&kickBleedSlider);
		addAndMakeVisible(kickBleedSliderLabel);
		kickBleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		kickBleedSliderLabel.setJustificationType(juce::Justification::centred);
		kickBleedSliderLabel.attachToComponent(&kickBleedSlider, false);
	}
	
	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.setFont(15.0f);
		//g.drawFittedText("Kick Sliders Page", getLocalBounds(), juce::Justification::centred, 1);
	}
	void KickSlidersPage::resized() override
	{
		kickCloseSlider.setBounds(60, 50, 70, getHeight() - 100);
		kickOHSlider.setBounds(170, 50, 70, getHeight() - 100);
		kickRoomSlider.setBounds(280, 50, 70, getHeight() - 100);
		kickBleedSlider.setBounds(390, 50, 70, getHeight() - 100);
	}

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KickSlidersPage)
};
