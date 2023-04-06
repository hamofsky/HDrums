#pragma once

class MyLookAndFeel : public juce::LookAndFeel_V4
{
	public:
		void drawLinearSliderThumb(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sliderStyle, juce::Slider &slider) override
		{
			if (sliderStyle == juce::Slider::SliderStyle::LinearVertical)
			{
				juce::Rectangle<float> sliderThumbArea(x, y, width, height / 10);
				g.setColour(juce::Colours::red);
				g.drawRect(sliderThumbArea);
				g.fillRect(sliderThumbArea);
			}
		}

		void drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sliderStyle, juce::Slider& slider) override
		{
			juce::Rectangle<float> sliderBackgroundArea(x, y, width, height);
			g.setColour(juce::Colours::black);
			g.drawRect(sliderBackgroundArea);
			g.fillRect(sliderBackgroundArea);
		}
};