#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"
#include "SnareSlidersPage.h"

SnareSlidersPage::SnareSlidersPage(HDrumsAudioProcessor& p)
	: HDrumsAudioProcessorEditor(p), audioProcessor2(p)
{
	/*snareTopCloseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	snareTopCloseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
	snareTopCloseSlider.setRange(-48.0f, 10.0f);
	snareTopCloseSlider.setDoubleClickReturnValue(true, 0.0f);
	snareTopCloseSlider.setValue(snareTopCloseSlider.getValue());
	addAndMakeVisible(&snareTopCloseSlider);
	addAndMakeVisible(snareTopCloseSliderLabel);
	snareTopCloseSliderLabel.setText("SD Top", juce::dontSendNotification);
	snareTopCloseSliderLabel.setJustificationType(juce::Justification::centred);
	snareTopCloseSliderLabel.attachToComponent(&snareTopCloseSlider, false);*/
}

SnareSlidersPage::~SnareSlidersPage()
{

}

void SnareSlidersPage::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Snare Sliders Page", getLocalBounds(), juce::Justification::centred, 1);
}

void SnareSlidersPage::resized()
{
	//snareTopCloseSlider.setBounds(30, 100, 80, getHeight() - 200);
}
