#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"

#pragma once

class MainSlidersPage : public juce::Component
{
public:
	MyLookAndFeel myLookAndFeel;
	juce::Slider closeSlider;
	juce::Slider OHSlider;
	juce::Slider roomSlider;
	juce::Slider bleedSlider;
	juce::Label closeSliderLabel;
	juce::Label OHSliderLabel;
	juce::Label roomSliderLabel;
	juce::Label bleedSliderLabel;

	MainSlidersPage()
	{
		closeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		closeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		closeSlider.setRange(-48.0f, 10.0f);
		closeSlider.setDoubleClickReturnValue(true, 0.0f);
		closeSlider.setValue(closeSlider.getValue());
		closeSlider.setLookAndFeel(&myLookAndFeel);
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

	void MainSlidersPage::resized() override
	{
		closeSlider.setBounds(15, 50, 70, getHeight() - 100);
		OHSlider.setBounds(115, 50, 70, getHeight() - 100);
		roomSlider.setBounds(215, 50, 70, getHeight() - 100);
		bleedSlider.setBounds(315, 50, 70, getHeight() - 100);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainSlidersPage)
};