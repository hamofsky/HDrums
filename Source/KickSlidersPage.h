#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class KickSlidersPage : public juce::Component
{
public:
	juce::Slider kickCloseSlider;
	juce::Label kickCloseSliderLabel;
	juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> kickCloseSliderValue;

	KickSlidersPage()
	{
		kickCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		kickCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		kickCloseSlider.setRange(-48.0f, 10.0f);
		kickCloseSlider.setDoubleClickReturnValue(true, 0.0f);
		kickCloseSlider.setValue(kickCloseSlider.getValue());
		addAndMakeVisible(&kickCloseSlider);
		addAndMakeVisible(kickCloseSliderLabel);
		kickCloseSliderLabel.setText("Kick Close", juce::dontSendNotification);
		kickCloseSliderLabel.setJustificationType(juce::Justification::centred);
		kickCloseSliderLabel.attachToComponent(&kickCloseSlider, false);
	}
	
	void paint(juce::Graphics& g) override
	{
		g.setColour(juce::Colours::white);
		g.setFont(15.0f);
		g.drawFittedText("Kick Sliders Page", getLocalBounds(), juce::Justification::centred, 1);
	}
	void KickSlidersPage::resized() override
	{
		kickCloseSlider.setBounds(30, 100, 80, getHeight() - 200);
	}

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KickSlidersPage)
};
