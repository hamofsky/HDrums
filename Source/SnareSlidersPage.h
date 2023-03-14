#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

#pragma once

class SnareSlidersPage : public HDrumsAudioProcessorEditor
{
public:
	SnareSlidersPage(HDrumsAudioProcessor&);
	~SnareSlidersPage() override;

	HDrumsAudioProcessor& audioProcessor;

	juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> snareTopCloseSliderValue;
	juce::Slider snareTopCloseSlider;
	juce::Label snareTopCloseSliderLabel;

	void paint(juce::Graphics& g) override;

	void resized() override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SnareSlidersPage)
};