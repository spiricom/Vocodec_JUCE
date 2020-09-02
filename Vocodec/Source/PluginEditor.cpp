/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "oled.h"
#include "ui.h"
#include <iostream>
//==============================================================================

VocodecAudioProcessorEditor::VocodecAudioProcessorEditor (VocodecAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p),
constrain(new ComponentBoundsConstrainer()),
resizer(new ResizableCornerComponent (this, constrain.get())),
screen(p)
{
    panel = Drawable::createFromImageData(BinaryData::panel_svg, BinaryData::panel_svgSize);
    
    addAndMakeVisible(screen);
    screen.setOpaque(true);
    screen.onChange = [this] { presetChanged(); };
    
    for (int i = 0; i < NUM_KNOBS; i++) {
        //        knobs.add(new DrawableImage());
        dials.add(new Slider());
        addAndMakeVisible(dials[i]);
        //        addAndMakeVisible(knobs[i]);
        dials[i]->setLookAndFeel(&vocodecLAF);
        dials[i]->setSliderStyle(Slider::Rotary);
        dials[i]->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(dials[i]);
        dials[i]->addListener(this);
        dials[i]->setRange(0, 1);
        dials[i]->setOpaque(true);
    }
    dials[6]->setValue(1);
    
    Path path;
    path.addEllipse(0, 0, 30, 30);
    
    
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons.add(new VocodecButton("", Colours::white, Colours::grey.brighter(), Colours::darkgrey));
        buttons[i]->setShape(path, true, true, true);
        addAndMakeVisible(buttons[i]);
        buttons[i]->addListener(this);
        buttons[i]->setOpaque(true);
    }
    buttons[0]->setClickingTogglesState(true);
    
    for (int i = 0; i < (int) vocodec::VocodecLightNil; i++)
    {
        lights.add(new VocodecLight("", Colours::grey, cLightColours[i]));
        addAndMakeVisible(lights[i]);
        lights[i]->setOpaque(true);
    }
    processor.vcd.lightStates[vocodec::VocodecLightIn1Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightIn2Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightOut1Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightOut2Meter] = true;

    setSize(600, 716);
    
    constrain->setFixedAspectRatio(600.0f / 716.0f);
    
    addAndMakeVisible(*resizer);
    resizer->setAlwaysOnTop(true);
    
    vocodec::OLED_writePreset(&processor.vcd);
    
    currentKnobPreset = processor.vcd.currentPreset;
    
    startTimerHz(30);
}

VocodecAudioProcessorEditor::~VocodecAudioProcessorEditor()
{
    for (int i = 0; i < NUM_KNOBS; i++)
        dials[i]->setLookAndFeel(nullptr);
}

//==============================================================================
void VocodecAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setGradientFill(ColourGradient(Colour(25, 25, 25), juce::Point<float>(0,0), Colour(10, 10, 10), juce::Point<float>(0, getHeight()), false));

    g.fillRect(0, 0, getWidth(), getHeight());
    
    Rectangle<float> panelArea = getLocalBounds().toFloat();
    panelArea.reduce(getWidth()*0.025f, getHeight()*0.01f);
    panelArea.removeFromBottom(getHeight()*0.03f);
    panel->drawWithin(g, panelArea, RectanglePlacement::centred, 1.0f);
}

void VocodecAudioProcessorEditor::resized()
{
    int width = getWidth();
    int height = getHeight();
    
    screen.setBounds(width*0.347f, height*0.096f, width*0.306f, height*0.105f);
    
    float s = width / 600.0f;
    
    const float buttonSize = 24.0f*s;
    const float knobSize = 57.0f*s;
    const float bigLightSize = 23.0f*s;
    const float smallLightSize = 15.0f*s;
    
    buttons[vocodec::ButtonA]       ->setBounds(543*s, 356*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonB]       ->setBounds(543*s, 415*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonC]       ->setBounds(303*s, 526*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonD]       ->setBounds(184*s, 621*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonE]       ->setBounds(241*s, 621*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonEdit]    ->setBounds(422*s, 91*s,  buttonSize, buttonSize);
    buttons[vocodec::ButtonLeft]    ->setBounds(441*s, 145*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonRight]   ->setBounds(531*s, 145*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonUp]      ->setBounds(485*s, 121*s, buttonSize, buttonSize);
    buttons[vocodec::ButtonDown]    ->setBounds(485*s, 177*s, buttonSize, buttonSize);
    
    lights[vocodec::VocodecLightUSB]         ->setBounds(493*s, 252*s, bigLightSize);
    lights[vocodec::VocodecLight1]           ->setBounds(502*s, 296*s, bigLightSize);
    lights[vocodec::VocodecLight2]           ->setBounds(539*s, 296*s, bigLightSize);
    lights[vocodec::VocodecLightA]           ->setBounds(510*s, 356*s, bigLightSize);
    lights[vocodec::VocodecLightB]           ->setBounds(510*s, 415*s, bigLightSize);
    lights[vocodec::VocodecLightC]           ->setBounds(303*s, 493*s, bigLightSize);
    lights[vocodec::VocodecLightEdit]        ->setBounds(422*s, 50*s,  bigLightSize);
    lights[vocodec::VocodecLightIn1Meter]    ->setBounds(25*s,  398*s, smallLightSize);
    lights[vocodec::VocodecLightIn1Clip]     ->setBounds(45*s,  398*s, smallLightSize);
    lights[vocodec::VocodecLightIn2Meter]    ->setBounds(25*s,  530*s, smallLightSize);
    lights[vocodec::VocodecLightIn2Clip]     ->setBounds(45*s,  530*s, smallLightSize);
    lights[vocodec::VocodecLightOut1Meter]   ->setBounds(538*s, 620*s, smallLightSize);
    lights[vocodec::VocodecLightOut1Clip]    ->setBounds(558*s, 620*s, smallLightSize);
    lights[vocodec::VocodecLightOut2Meter]   ->setBounds(538*s, 503*s, smallLightSize);
    lights[vocodec::VocodecLightOut2Clip]    ->setBounds(558*s, 503*s, smallLightSize);
    
    dials[1]                        ->setBounds(175*s, 205*s, knobSize, knobSize);
    dials[2]                        ->setBounds(385*s, 205*s, knobSize, knobSize);
    dials[3]                        ->setBounds(250*s, 345*s, knobSize, knobSize);
    dials[4]                        ->setBounds(445*s, 345*s, knobSize, knobSize);
    dials[5]                        ->setBounds(175*s, 500*s, knobSize, knobSize);
    dials[6]                        ->setBounds(380*s, 500*s, knobSize, knobSize);
    
    float r = 600.0f / 716.0f;
    constrain->setSizeLimits(200, 200/r, 800*r, 800);
    resizer->setBounds(getWidth()-16, getHeight()-16, 16, 16);
}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == nullptr) return;
    
    int whichKnob = dials.indexOf(slider) - 1;
    if (whichKnob < 0) return;
    
    float sliderValue;
    sliderValue = slider->getValue();
    
    // Set ADC_values so that we can take advantage of hardware UI internals
    (*processor.vcd.ADC_values)[whichKnob] = (uint16_t) (sliderValue * TWO_TO_10) << 6;
    sliderActive[whichKnob] = true;
    
    if (whichKnob == 5) {
        *processor.dryWetMix = sliderValue;
    }
    else
    {
        int whichParam = (processor.vcd.knobPage * KNOB_PAGE_SIZE) + whichKnob;
        
        processor.vcd.presetKnobValues[processor.vcd.currentPreset][whichParam] = sliderValue;
        
        int paramId = (processor.vcd.currentPreset * NUM_PRESET_KNOB_VALUES) + whichParam;
        *processor.pluginParams[paramId] = sliderValue;
    }
}

void VocodecAudioProcessorEditor::buttonClicked(Button*button)
{
}

void VocodecAudioProcessorEditor::buttonStateChanged(Button *button)
{
    if (button == nullptr) return;
    
    // Set the button values to be checked in the audio frame (same as hardware Vocodec)
    int whichButton = buttons.indexOf(static_cast<VocodecButton*>(button));
    if (whichButton == 0) // The edit button, do toggle behavior
    {
        processor.vcd.buttonValues[whichButton] = button->getToggleState();
    }
    else if (button->getState() == Button::ButtonState::buttonDown)
    {
        processor.vcd.buttonValues[whichButton] = 1;
    }
    else processor.vcd.buttonValues[whichButton] = 0;
}

void VocodecAudioProcessorEditor::presetChanged()
{
    processor.vcd.loadingPreset = 1;
    
    int id = screen.getMenu()->getSelectedId();
    processor.vcd.currentPreset = vocodec::VocodecPresetType(id > 0 ? id - 1 : 0);
    processor.vcd.knobPage = 0;
    
    vocodec::OLED_writePreset(&processor.vcd);
    vocodec::clearButtonActions(&processor.vcd);
}

void VocodecAudioProcessorEditor::timerCallback()
{
    screen.getMenu()->setSelectedId(processor.vcd.currentPreset + 1, dontSendNotification);
    
    processor.vcd.lightStates[vocodec::VocodecLightIn1Clip] = processor.audioInput[0] >= 0.999f;
    processor.vcd.lightStates[vocodec::VocodecLightIn2Clip] = processor.audioInput[1] >= 0.999f;
    processor.vcd.lightStates[vocodec::VocodecLightOut1Clip] = processor.audioOutput[0] >= 0.999f;
    processor.vcd.lightStates[vocodec::VocodecLightOut2Clip] = processor.audioOutput[1] >= 0.999f;
    
    for (int i = 0; i < vocodec::VocodecLightNil; i++)
    {
        lights[i]->setState(processor.vcd.lightStates[i]);
    }
    
    float b = atodb(processor.audioInput[0]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[vocodec::VocodecLightIn1Meter]->setBrightness(b);
    
    b = atodb(processor.audioInput[1]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[vocodec::VocodecLightIn2Meter]->setBrightness(b);
    
    b = atodb(processor.audioOutput[0]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[vocodec::VocodecLightOut1Meter]->setBrightness(b);
    
    b = atodb(processor.audioOutput[1]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[vocodec::VocodecLightOut2Meter]->setBrightness(b);
    
    updateKnobs();
    
    if (currentKnobPreset != processor.vcd.currentPreset)
    {
        for (int i = 0; i < NUM_ADC_CHANNELS; i++)
            sliderActive[i] = false;
        currentKnobPreset = processor.vcd.currentPreset;
    }
    
    for (int i = 0; i < NUM_ADC_CHANNELS; i++)
    {
        if (sliderActive[i])
        {
            // Set ADC_values so that we can take advantage of hardware UI internals
            (*processor.vcd.ADC_values)[i] = (uint16_t) (dials[i+1]->getValue() * TWO_TO_10) << 6;
        }
    }
    
    screen.timerCallback();
}

void VocodecAudioProcessorEditor::updateKnobs()
{
    for (int i = 1; i < NUM_KNOBS - 1; ++i)
    {
        int paramId = (processor.vcd.currentPreset * NUM_PRESET_KNOB_VALUES) + (i - 1);
        if (processor.pluginParams.contains(paramId))
            if (dials[i]->getValue() != processor.pluginParams[paramId]->get())
                dials[i]->setValue(processor.pluginParams[paramId]->get(), dontSendNotification);
    }
    if (dials[6]->getValue() != processor.dryWetMix->get())
        dials[6]->setValue(processor.dryWetMix->get(), dontSendNotification);
}

namespace vocodec
{
    void setLED_A(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLightA] = (bool) onOFF; }
    void setLED_B(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLightB] = (bool) onOFF; }
    void setLED_C(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLightC] = (bool) onOFF; }
    void setLED_1(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLight1] = (bool) onOFF; }
    void setLED_2(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLight2] = (bool) onOFF; }
    void setLED_Edit(Vocodec* vcd, int onOFF) { vcd->lightStates[VocodecLightEdit] = (bool) onOFF; }
    
    void OLED_draw(Vocodec* vcd) { ; }
}
