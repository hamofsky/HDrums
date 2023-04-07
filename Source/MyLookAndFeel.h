#pragma once

class MyLookAndFeel : public juce::LookAndFeel_V4
{
	public:
		MyLookAndFeel()
		{
			setColour(juce::Slider::thumbColourId, juce::Colours::red);
			
		}

        static void drawRectangle(juce::Graphics& g, float x, float y, float width, float height, const juce::Colour& fill, const juce::Colour& outline) noexcept
        {
            juce::Path p;
            p.addRectangle(juce::Rectangle<float> (x, y, width, height));
            g.setColour(fill);
            g.fillPath(p);

            g.setColour(outline);
            g.strokePath(p, juce::PathStrokeType(0.4f));    // size of the outline
        }


        void drawLinearSlider(juce::Graphics& g, int x, int y, int w, int h,
            float sliderPos, float minSliderPos, float maxSliderPos,
            const juce::Slider::SliderStyle style, juce::Slider& slider)
        {
            //g.fillAll(slider.findColour(juce::Slider::backgroundColourId)); // background rectangle

            if (style == juce::Slider::LinearBar)
            {
                g.setColour(slider.findColour(juce::Slider::thumbColourId));
                g.fillRect(x, y, (int)sliderPos - x, h);

                g.setColour(slider.findColour(juce::Slider::textBoxTextColourId).withMultipliedAlpha(0.8f));
                g.drawRect(x, y, (int)sliderPos - x, h);
            }
            else
            {
                g.setColour(slider.findColour(juce::Slider::trackColourId)
                    .withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.3f));

                if (slider.isHorizontal())
                {
                    g.fillRect(x, y + juce::roundToInt(h * 0.8f),
                        w, juce::roundToInt(h * 0.2f));
                }
                else
                {
                    g.fillRect(x + juce::roundToInt(w * 0.5f - juce::jmin(3.0f, w * 0.1f)), y,
                        juce::jmin(4, juce::roundToInt(w * 0.2f)), h);                             // darker rectangle in the middle (on which the slider seems to move)
                }

                float alpha = 1.0f;

                if (slider.isEnabled())
                    alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.9f;

                //const juce::Colour fill(slider.findColour(juce::Slider::thumbColourId).withAlpha(alpha));
                const juce::Colour outline(juce::Colours::black);
                const juce::Colour faderMain(juce::Colours::lightgrey);
                const juce::Colour faderDetails(juce::Colours::darkgrey);

                if (style == juce::Slider::LinearVertical || style == juce::Slider::ThreeValueVertical)
                {
                    float woutside = 30.0f;
                    float houtside = 16.0f;
                    float w3 = 29.5f;
                    float h3 = 8.0f;
                    float wmiddle = 28.0f;
                    float hmiddle = 3.0f;
                    drawRectangle(g, x + w * 0.5f - woutside * 0.5f, sliderPos - h3 - houtside - hmiddle * 0.5f, woutside, houtside, faderMain, outline);   // upper part of a slider thumbnail
                    drawRectangle(g, x + w * 0.5f - w3 * 0.5f, sliderPos - h3 - hmiddle * 0.5f, w3, h3, faderMain, outline);                                // upper-middle part of a slider thumbnail
                    drawRectangle(g, x + w * 0.5f - wmiddle * 0.5f, sliderPos - hmiddle * 0.5f, wmiddle, hmiddle, faderDetails, outline);                   // middle part of a slider thumbnail
                    drawRectangle(g, x + w * 0.5f - w3 * 0.5f, sliderPos + hmiddle * 0.5f, w3, h3, faderMain, outline);                                     // lower-middle part of a slider thumbnail
                    drawRectangle(g, x + w * 0.5f - woutside * 0.5f, sliderPos + hmiddle * 0.5f + h3, woutside, houtside, faderMain, outline);              // lower part of a slider thumbnail
                }
            }
        }

        int getSliderThumbRadius(juce::Slider&)
        {
            return 30;
        }
};