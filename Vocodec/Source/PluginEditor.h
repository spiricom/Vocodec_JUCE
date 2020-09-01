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
//#include "ui.h"
//#include "tunings.h"
//==============================================================================
/**
*/

#define NUM_KNOBS 7
#define NUM_LIGHTS 10
#define NUM_BUTTONS 10

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
    
    void updateKnobs();

    OwnedArray<Slider> dials;
    
    OwnedArray<VocodecButton> buttons;
    
    OwnedArray<VocodecLight> lights;
    
private:
    
    VocodecAudioProcessor& processor;
    
    std::unique_ptr<ComponentBoundsConstrainer> constrain;
    std::unique_ptr<ResizableCornerComponent> resizer;

    std::unique_ptr<Drawable> panel;
    
    VocodecScreen screen;
    
    vocodec::VocodecPresetType currentKnobPreset;
    bool sliderActive[NUM_ADC_CHANNELS];
    
    VocodecLookAndFeel vocodecLAF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessorEditor)
};
