/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "sfx.h"

//==============================================================================
/**
*/

#define NUM_KNOBS 7
#define NUM_LIGHTS 10
#define NUM_BUTTONS 10

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
class VocodecAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener, public Button::Listener, public Timer
{
public:
    VocodecAudioProcessorEditor (VocodecAudioProcessor&);
	~VocodecAudioProcessorEditor();
	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override;
	void buttonFunction(int i);
    void presetChanged();
	void buttonClicked(juce::Button* button) override;
	void buttonStateChanged(Button *button) override;
    
    void timerCallback() override;

private:

	String paramName = String("THIS IS A TEST");
	Image baseline;
	Array<DrawableImage*> knobs;
	OtherLookAndFeel knobOne;
	OtherLookAndFeel knobTwo;
	OtherLookAndFeel knobThree;
	OtherLookAndFeel knobFour;
	OtherLookAndFeel knobFive;
	OtherLookAndFeel knobSix;
	OtherLookAndFeel knobSeven;

	Array<DrawableImage*> lights;

	Array<Slider*> dials;

	Array<ImageButton*> buttons;

	ComboBox menu;


	int sliderOpacity[7];

    VocodecAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessorEditor)
};

typedef enum _OLEDLine
{
    FirstLine = 0,
    SecondLine,
    BothLines,
    NilLine
} OLEDLine;

void setLED_A(int onOFF);
void setLED_B(int onOFF);
void setLED_C(int onOFF);
void setLED_1(int onOFF);
void setLED_2(int onOFF);
void setLED_Edit(int onOFF);

void OLED_process(void);

void OLED_writePreset(void);

void OLED_writeEditScreen(void);

void OLED_writeKnobParameter(uint8_t whichParam);

void OLED_writeButtonAction(uint8_t whichButton, uint8_t whichAction);

void OLED_writeTuning(void);

void OLED_draw(void);

void OLEDclear(void);

void OLEDclearLine(OLEDLine line);

void OLEDwriteString(const char* myCharArray, uint8_t arrayLength, uint8_t startCursor, OLEDLine line);

void OLEDwriteLine(const char* myCharArray, uint8_t arrayLength, OLEDLine line);

void OLEDwriteInt(uint32_t myNumber, uint8_t numDigits, uint8_t startCursor, OLEDLine line);

void OLEDwriteIntLine(uint32_t myNumber, uint8_t numDigits, OLEDLine line);

void OLEDwritePitch(float midi, uint8_t startCursor, OLEDLine line, uint8_t showCents);

void OLEDwritePitchClass(float midi, uint8_t startCursor, OLEDLine line);

void OLEDwritePitchLine(float midi, OLEDLine line, uint8_t showCents);

void OLEDwriteFixedFloat(float input, uint8_t numDigits, uint8_t numDecimal, uint8_t startCursor, OLEDLine line);

void OLEDwriteFixedFloatLine(float input, uint8_t numDigits, uint8_t numDecimal, OLEDLine line);

void OLEDwriteFloat(float input, uint8_t startCursor, OLEDLine line);

void OLEDdrawFloatArray(float* input, float min, float max, uint8_t size, uint8_t offset, uint8_t startCursor, OLEDLine line);

int16_t OLEDgetCursor(void);
