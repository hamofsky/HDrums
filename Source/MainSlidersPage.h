#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyLookAndFeel.h"
#include "MuteAndSoloButtonsFunctionality.h"

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
	float sliderMinValue = -36.0f;
	float sliderMaxValue = 12.0f;

	MuteAndSoloButtonsFunctionality muteAndSoloButtonsFunctionality;

	juce::ToggleButton closeSolo;
	juce::ToggleButton OHSolo;
	juce::ToggleButton roomSolo;
	juce::ToggleButton bleedSolo;
	std::vector<juce::ToggleButton*> soloButtons = { &closeSolo, &OHSolo, &roomSolo, &bleedSolo };

	juce::ToggleButton closeMute;
	juce::ToggleButton OHMute;
	juce::ToggleButton roomMute;
	juce::ToggleButton bleedMute;
	std::vector<juce::ToggleButton*> muteButtons = { &closeMute, &OHMute, &roomMute, &bleedMute };
	
	bool muteStateBeforeFirstSolo[4] = { false, false, false, false };
	bool soloAlreadyEngaged = false;

	MainSlidersPage()
	{
		closeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		closeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		closeSlider.setRange(sliderMinValue, sliderMaxValue);
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
		OHSlider.setRange(sliderMinValue, sliderMaxValue);
		OHSlider.setDoubleClickReturnValue(true, 0.0f);
		OHSlider.setValue(OHSlider.getValue());
		OHSlider.setLookAndFeel(&myLookAndFeel);
		addAndMakeVisible(&OHSlider);
		addAndMakeVisible(OHSliderLabel);
		OHSliderLabel.setText("OH", juce::dontSendNotification);
		OHSliderLabel.setJustificationType(juce::Justification::centred);
		OHSliderLabel.attachToComponent(&OHSlider, false);

		roomSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		roomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		roomSlider.setRange(sliderMinValue, sliderMaxValue);
		roomSlider.setDoubleClickReturnValue(true, 0.0f);
		roomSlider.setLookAndFeel(&myLookAndFeel);
		roomSlider.setValue(roomSlider.getValue());
		addAndMakeVisible(&roomSlider);
		addAndMakeVisible(roomSliderLabel);
		roomSliderLabel.setText("Room", juce::dontSendNotification);
		roomSliderLabel.setJustificationType(juce::Justification::centred);
		roomSliderLabel.attachToComponent(&roomSlider, false);

		bleedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		bleedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
		bleedSlider.setRange(sliderMinValue, sliderMaxValue);
		bleedSlider.setDoubleClickReturnValue(true, 0.0f);
		bleedSlider.setLookAndFeel(&myLookAndFeel);
		bleedSlider.setValue(bleedSlider.getValue());
		addAndMakeVisible(&bleedSlider);
		addAndMakeVisible(bleedSliderLabel);
		bleedSliderLabel.setText("Bleed", juce::dontSendNotification);
		bleedSliderLabel.setJustificationType(juce::Justification::centred);
		bleedSliderLabel.attachToComponent(&bleedSlider, false);

		for (int i = 0; i < soloButtons.size(); i++)
		{
			addAndMakeVisible(soloButtons[i]);
			soloButtons[i]->setToggleState(soloButtons[i]->getToggleState(), true);
			//soloButtons[i]->onStateChange = [this] { soloStateChanged(i); };
			addAndMakeVisible(muteButtons[i]);
			muteButtons[i]->setToggleState(muteButtons[i]->getToggleState(), true);

			muteStateBeforeFirstSolo[i] = muteButtons[i]->getToggleState();

			if (soloButtons[i]->getToggleState())
			{
				soloAlreadyEngaged = true;
			}
		}
		soloButtons[0]->onClick = [this] { soloStateChanged(0); };
		soloButtons[1]->onClick = [this] { soloStateChanged(1); };
		soloButtons[2]->onClick = [this] { soloStateChanged(2); };
		soloButtons[3]->onClick = [this] { soloStateChanged(3); };
	}

	MainSlidersPage::~MainSlidersPage()
	{
		muteButtons.clear();
		soloButtons.clear();
		muteButtons.shrink_to_fit();
		soloButtons.shrink_to_fit();
	}

	void MainSlidersPage::resized() override
	{
		closeSlider.setBounds(15, 40, 70, getHeight() - 110);
		OHSlider.setBounds(115, 40, 70, getHeight() - 110);
		roomSlider.setBounds(215, 40, 70, getHeight() - 110);
		bleedSlider.setBounds(315, 40, 70, getHeight() - 110);

		closeSolo.setBounds(20, getHeight() - 50, 30, 30);
		OHSolo.setBounds(120, getHeight() - 50, 30, 30);
		roomSolo.setBounds(220, getHeight() - 50, 30, 30);
		bleedSolo.setBounds(320, getHeight() - 50, 30, 30);

		closeMute.setBounds(60, getHeight() - 50, 30, 30);
		OHMute.setBounds(160, getHeight() - 50, 30, 30);
		roomMute.setBounds(260, getHeight() - 50, 30, 30);
		bleedMute.setBounds(360, getHeight() - 50, 30, 30);
	}

	void soloStateChanged(int soloButtonId)
	{
		// solo clicked for the first time
		if (soloButtons[soloButtonId]->getToggleState() && !soloAlreadyEngaged)
		{
			muteAndSoloButtonsFunctionality.muteButtonsWhenSoloFirstTime(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
			soloAlreadyEngaged = true;
			muteAndSoloButtonsFunctionality.unsoloButtonsWhenSolo(soloButtonId, soloButtons);
		}
		// solo clicked for the n-th time
		else if (soloButtons[soloButtonId]->getToggleState() && soloAlreadyEngaged)
		{
			muteAndSoloButtonsFunctionality.muteButtonsWhenSoloAgain(soloButtonId, soloButtons, muteButtons, muteStateBeforeFirstSolo);
			muteAndSoloButtonsFunctionality.unsoloButtonsWhenSolo(soloButtonId, soloButtons);
		}
		// solo unclicked
		else if (!soloButtons[soloButtonId]->getToggleState())
		{
			muteAndSoloButtonsFunctionality.unmuteButtonsWhenSolo(muteButtons, muteStateBeforeFirstSolo);
			soloAlreadyEngaged = false;
		}
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainSlidersPage)
};