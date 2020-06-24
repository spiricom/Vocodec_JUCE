/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
void setLED_A(int onOFF);
void setLED_B(int onOFF);
void setLED_C(int onOFF);
void setLED_1(int onOFF);
void setLED_2(int onOFF);
void setLED_Edit(int onOFF);


class OtherLookAndFeel : public LookAndFeel_V4
{
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		auto radius = jmin(width / 2, height / 2) - 4.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;
		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		Array<Colour> colours{ Colour(117, 117, 117), Colour(136, 136, 137), Colour(140, 139, 139), Colour(168, 167, 167), Colour(166, 163, 163), Colour(208, 208, 208), Colour(207, 207, 207) };
		//auto colorOne = Colour(117, 117, 117);


			Path p;
			auto pointerLength = radius * 0.33f;
			auto pointerThickness = 2.0f;
			p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
			p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
			g.setColour(Colours::black);
			g.fillPath(p);
	}

};
class VocodecAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener
{
public:
    VocodecAudioProcessorEditor (VocodecAudioProcessor&);
	~VocodecAudioProcessorEditor();
	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override;
	void buttonFunction(int i);

private:
	#define NUM_KNOBS 7
	#define NUM_LIGHTS 7
	#define NUM_BUTTONS 10

	Image baseline;
	Array<DrawableImage*> knobs;
	Array<DrawableImage*> lights;
	OtherLookAndFeel knobOne;
	OtherLookAndFeel knobTwo;
	OtherLookAndFeel knobThree;
	OtherLookAndFeel knobFour;
	OtherLookAndFeel knobFive;
	OtherLookAndFeel knobSix;
	OtherLookAndFeel knobSeven;

	Slider dial1;
	Slider dial2;
	Slider dial3;
	Slider dial4;
	Slider dial5;
	Slider dial6;
	Slider dial7;

	Array<ImageButton*> buttons;

	ComboBox menu;


	int sliderOpacity[7];

    VocodecAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessorEditor)
};
