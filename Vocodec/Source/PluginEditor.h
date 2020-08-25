/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VocodecComponents.h"
#include "sfx.h"
#include "tunings.h"
//==============================================================================
/**
*/

#define NUM_KNOBS 7
#define NUM_LIGHTS 10
#define NUM_BUTTONS 10

extern unsigned char buffer[512];

class VocodecAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener, public Button::Listener, public Timer
{
public:
    VocodecAudioProcessorEditor (VocodecAudioProcessor&);
	~VocodecAudioProcessorEditor();
	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override;
    void presetChanged();
	void buttonClicked(juce::Button* button) override;
	void buttonStateChanged(Button *button) override;
    
    void timerCallback() override;

    OwnedArray<Slider> dials;
    
    OwnedArray<VocodecButton> buttons;
    
    OwnedArray<VocodecLight> lights;
    
    ComboBox menu;

private:
    
    VocodecAudioProcessor& processor;
    
    std::unique_ptr<ComponentBoundsConstrainer> constrain;
    std::unique_ptr<ResizableCornerComponent> resizer;

	std::unique_ptr<Drawable> logo;
	std::unique_ptr<Drawable> sideThingy;
    std::unique_ptr<Drawable> panel;
    
    ImageComponent screen;
    std::unique_ptr<Image> screenImage;

	String paramName = String("");
    Image baseline;
    
    VocodecLookAndFeel vocodecLAF;
    
	int sliderOpacity[7];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessorEditor)
};

void setLightState(VocodecLightID light, bool state);
