/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "oled.h"
#include <iostream>
//==============================================================================

unsigned char buffer[512];
bool shouldDrawScreen = false;

VocodecAudioProcessorEditor::VocodecAudioProcessorEditor (VocodecAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p),
constrain(new ComponentBoundsConstrainer()),
resizer(new ResizableCornerComponent (this, constrain.get()))
{
    panel = Drawable::createFromImageData(BinaryData::panel_svg, BinaryData::panel_svgSize);
    
    screenImage = std::make_unique<Image>(Image::PixelFormat::RGB, 128, 32, false);
    screen.setImage(*screenImage);
    screen.setImagePlacement(RectanglePlacement::centred);
    addAndMakeVisible(screen);
    
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
    }
    buttons[0]->setClickingTogglesState(true);
    
    for (int i = 0; i < (int) VocodecLightNil; i++)
    {
        lights.add(new VocodecLight("", Colours::grey, cLightColours[i]));
        addAndMakeVisible(lights[i]);
    }
    lightStates[VocodecLightIn1Meter] = true;
    lightStates[VocodecLightIn2Meter] = true;
    lightStates[VocodecLightOut1Meter] = true;
    lightStates[VocodecLightOut2Meter] = true;
    
    addAndMakeVisible(menu);
    menu.setLookAndFeel(&vocodecLAF);
    menu.setAlpha(0.0f);
    menu.addItem("VOCODER", 1);
    menu.addItem("VOCODERCH", 2);
    menu.addItem("PITCHSHIFT", 3);
    menu.addItem("AUTOTUNE", 4);
    menu.addItem("HARMONIZE", 5);
    menu.addItem("SAMPLERBUTTONPRESS", 6);
    menu.addItem("SAMPLERKEYBOARD", 7);
    menu.addItem("AUTOSAMPlER", 8);
    menu.addItem("DISTORTION", 9);
    menu.addItem("WAVEFOLDER", 10);
    menu.addItem("BITCRUSHER", 11);
    menu.addItem("DELAY", 12);
    menu.addItem("REVERB", 13);
    menu.addItem("REVERB2", 14);
    menu.addItem("LIVINGSTRING", 15);
    menu.addItem("LIVINGSTRINGSYNTH", 16);
    menu.addItem("CLASSICSYNTH", 17);
    menu.addItem("RHODES", 18);
    menu.setColour(ComboBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    menu.setColour(ComboBox::ColourIds::textColourId, Colours::white);
    menu.setColour(ComboBox::ColourIds::buttonColourId, Colours::black);
    menu.setColour(ComboBox::ColourIds::arrowColourId, Colours::white);
    menu.setColour(ComboBox::ColourIds::outlineColourId, Colours::transparentWhite);
    menu.setJustificationType(Justification::centred);
    menu.setSelectedId(1, dontSendNotification);
    menu.onChange = [this] { presetChanged(); };

    setSize(600, 716);
    
    constrain->setFixedAspectRatio(600.0f / 716.0f);
    
    addAndMakeVisible(*resizer);
    resizer->setAlwaysOnTop(true);
    
    vocodec::OLED_writePreset();
    
    startTimerHz(30);
}

VocodecAudioProcessorEditor::~VocodecAudioProcessorEditor()
{
    menu.setLookAndFeel(nullptr);
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

    g.setFont (15.0f);

    g.setColour(Colours::white);
    g.drawFittedText(paramName, Rectangle<int>(175,80,150,50), Justification::centred, 1);

    juce::Font mainComponentFont(Font::getDefaultSansSerifFontName(), 20.0f, juce::Font::bold | juce::Font::italic);
    g.setColour(Colours::gold);

    g.setFont(60.0f);
    g.setColour(Colours::gold);
}

void VocodecAudioProcessorEditor::resized()
{
    int width = getWidth();
    int height = getHeight();
    screen.setBounds(width*0.38f, height*0.1f, width*0.28f, height*0.1f);
    
    menu.setBounds(screen.getBounds().toFloat().reduced(width*0.002f)
                   .removeFromTop(screen.getHeight()*0.5f).toNearestInt());
    
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
    
    lights[VocodecLightUSB]         ->setBounds(493*s, 252*s, bigLightSize);
    lights[VocodecLight1]           ->setBounds(502*s, 296*s, bigLightSize);
    lights[VocodecLight2]           ->setBounds(539*s, 296*s, bigLightSize);
    lights[VocodecLightA]           ->setBounds(510*s, 356*s, bigLightSize);
    lights[VocodecLightB]           ->setBounds(510*s, 415*s, bigLightSize);
    lights[VocodecLightC]           ->setBounds(303*s, 493*s, bigLightSize);
    lights[VocodecLightEdit]        ->setBounds(422*s, 50*s,  bigLightSize);
    lights[VocodecLightIn1Meter]    ->setBounds(25*s,  398*s, smallLightSize);
    lights[VocodecLightIn1Clip]     ->setBounds(45*s,  398*s, smallLightSize);
    lights[VocodecLightIn2Meter]    ->setBounds(25*s,  530*s, smallLightSize);
    lights[VocodecLightIn2Clip]     ->setBounds(45*s,  530*s, smallLightSize);
    lights[VocodecLightOut1Meter]   ->setBounds(538*s, 620*s, smallLightSize);
    lights[VocodecLightOut1Clip]    ->setBounds(558*s, 620*s, smallLightSize);
    lights[VocodecLightOut2Meter]   ->setBounds(538*s, 503*s, smallLightSize);
    lights[VocodecLightOut2Clip]    ->setBounds(558*s, 503*s, smallLightSize);
    
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
    vocodec::ADC_values[whichKnob] = (uint16_t) (sliderValue * TWO_TO_10) << 6;
    
    if (whichKnob == 5) {
        *processor.dryWetMix = sliderValue;
    }
    else
    {
        int whichParam = (vocodec::knobPage * KNOB_PAGE_SIZE) + whichKnob;
        
        vocodec::presetKnobValues[vocodec::currentPreset][whichParam] = sliderValue;
        
        int paramId = (vocodec::currentPreset * NUM_PRESET_KNOB_VALUES) + whichParam;
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
        vocodec::buttonValues[whichButton] = button->getToggleState();
    }
    else vocodec::buttonValues[whichButton] = (button->getState() == Button::ButtonState::buttonDown) ? 1 : 0;
}

void VocodecAudioProcessorEditor::presetChanged(){
    
    vocodec::loadingPreset = 1;
    
    int id = menu.getSelectedId();
    vocodec::previousPreset = vocodec::currentPreset;
    vocodec::currentPreset = vocodec::VocodecPresetType(id > 0 ? id - 1 : 0);
    vocodec::knobPage = 0;
    
    vocodec::OLED_writePreset();
    vocodec::clearButtonActions();
}

void VocodecAudioProcessorEditor::timerCallback()
{
    for (int i = 1; i < NUM_KNOBS - 1; ++i)
    {
        int paramId = (vocodec::currentPreset * NUM_PRESET_KNOB_VALUES) + (i - 1);
        if (processor.pluginParams.contains(paramId))
            dials[i]->setValue(processor.pluginParams[paramId]->get(), dontSendNotification);
    }
    dials[6]->setValue(processor.dryWetMix->get(), dontSendNotification);
         
    menu.setSelectedId(vocodec::currentPreset + 1, dontSendNotification);
    
    lightStates[VocodecLightIn1Clip] = processor.audioInput[0] >= 0.999f;
    lightStates[VocodecLightIn2Clip] = processor.audioInput[1] >= 0.999f;
    lightStates[VocodecLightOut1Clip] = processor.audioOutput[0] >= 0.999f;
    lightStates[VocodecLightOut2Clip] = processor.audioOutput[1] >= 0.999f;
    
    for (int i = 0; i < VocodecLightNil; i++)
    {
        lights[i]->setState(lightStates[i]);
    }
    
    float b = atodb(processor.audioInput[0]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[VocodecLightIn1Meter]->setBrightness(b);
    
    b = atodb(processor.audioInput[1]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[VocodecLightIn2Meter]->setBrightness(b);
    
    b = atodb(processor.audioOutput[0]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[VocodecLightOut1Meter]->setBrightness(b);
    
    b = atodb(processor.audioOutput[1]);
    b = LEAF_clip(MIN_METER_VOL, b, 0.0f);
    b = (b - MIN_METER_VOL) * -INV_MIN_METER_VOL;
    lights[VocodecLightOut2Meter]->setBrightness(b);
    
    for (int i = 0; i < NUM_ADC_CHANNELS; i++)
    {
        // Set ADC_values so that we can take advantage of hardware UI internals
        vocodec::ADC_values[i] = (uint16_t) (dials[i+1]->getValue() * TWO_TO_10) << 6;
    }
    
    vocodec::OLED_process();
    
    const Image::BitmapData screenBitmap (*screenImage, Image::BitmapData::writeOnly);
    bool screenChanged;
    for (int x = 0; x < 128; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            bool set = (buffer[x + ((y/8) * 128)] >> (y&7)) & 1;
            Colour colour = set ? Colours::white : Colours::black;
            if (screenBitmap.getPixelColour(x, y) != colour)
            {
                screenBitmap.setPixelColour(x, y, colour);
                screenChanged = true;
            }
        }
    }
    if (screenChanged) repaint();
}

namespace vocodec
{
    void setLED_A(int onOFF) { setLightState(VocodecLightA, (bool) onOFF); }
    void setLED_B(int onOFF) { setLightState(VocodecLightB, (bool) onOFF); }
    void setLED_C(int onOFF) { setLightState(VocodecLightC, (bool) onOFF); }
    void setLED_1(int onOFF) { setLightState(VocodecLight1, (bool) onOFF); }
    void setLED_2(int onOFF) { setLightState(VocodecLight2, (bool) onOFF); }
    void setLED_Edit(int onOFF) { setLightState(VocodecLightEdit, (bool) onOFF); }
    
    void OLED_draw(void) { ; }
}

void setLightState(VocodecLightID light, bool state)
{
    lightStates[light] = state;
}
