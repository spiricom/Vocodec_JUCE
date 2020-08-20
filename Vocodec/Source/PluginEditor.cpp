/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
using namespace std;
//==============================================================================

VocodecAudioProcessorEditor* editor;
bool lightStates[NUM_LIGHTS];
bool shouldRepaint = false;

VocodecAudioProcessorEditor::VocodecAudioProcessorEditor (VocodecAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    
    //logo = Drawable::createFromImageData(BinaryData::snyderphonicswhitelogo_svg, BinaryData::snyderphonicswhitelogo_svgSize);
    //sideThingy = Drawable::createFromImageData(BinaryData::logo_large_svg, BinaryData::logo_large_svgSize);
    panel = Drawable::createFromImageData(BinaryData::panel_svg, BinaryData::panel_svgSize);
    //addAndMakeVisible(*logo);
    //addAndMakeVisible(*sideThingy);
    addAndMakeVisible(*panel);
    
    for (int i = 0; i < NUM_KNOBS; i++) {
        //        knobs.add(new DrawableImage());
        dials.add(new Slider());
        addAndMakeVisible(dials[i]);
        //        addAndMakeVisible(knobs[i]);
        dials[i]->setLookAndFeel(&knobOne);
        dials[i]->setSliderStyle(Slider::RotaryVerticalDrag);
        dials[i]->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(dials[i]);
        dials[i]->addListener(this);
        dials[i]->setRange(0, 1);
    }
    dials[6]->setValue(1);
    //    for (int i = 0; i < NUM_LIGHTS; i++) {
    //        lightStates[i] = false;
    //        lights.add(new DrawableImage());
    //        addAndMakeVisible(lights[i]);
    //    }
    
    Path path;
    path.addEllipse(0, 0, 30, 30);
    
    
    for (int i = 0; i < NUM_BUTTONS; i++) {
        buttons.add(new ShapeButton("", Colours::lightgrey, Colours::grey, Colours::darkgrey));
        buttons[i]->setShape(path, true, true, true);
        addAndMakeVisible(buttons[i]);
        buttons[i]->addListener(this);
    }
    buttons[0]->setClickingTogglesState(true);
    //buttons[0]->setTriggeredOnMouseDown(true);
    //buttons[0]->onClick = [this] { buttonFunction(0); };
    //buttons[1]->onClick = [this] { buttonFunction(1); };
    //buttons[2]->onClick = [this] { buttonFunction(2); };
    //buttons[3]->onClick = [this] { buttonFunction(3); };
    //buttons[4]->onClick = [this] { buttonFunction(4); };
    
    setSize(600, 712);
    
    addAndMakeVisible(menu);
    menu.addItem("Vocoder", 1);
    menu.addItem("VocoderCh", 2);
    menu.addItem("Pitchshift", 3);
    menu.addItem("AutotuneMono", 4);
    menu.addItem("AutotunePoly", 5);
    menu.addItem("SamplerButtonPress", 6);
    menu.addItem("SamplerKeyboard", 7);
    menu.addItem("SamplerAutoGrab", 8);
    menu.addItem("Distortion", 9);
    menu.addItem("Wavefolder", 10);
    menu.addItem("BitCrusher", 11);
    menu.addItem("Delay", 12);
    menu.addItem("Reverb", 13);
    menu.addItem("Reverb 2", 14);
    menu.addItem("LivingString", 15);
    menu.addItem("LivingStringSynth", 16);
    menu.addItem("ClassicSynth", 17);
    menu.addItem("Rhodes", 18);
    menu.setColour(ComboBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    menu.setColour(ComboBox::ColourIds::textColourId, Colours::white);
    menu.setColour(ComboBox::ColourIds::buttonColourId, Colours::black);
    menu.setColour(ComboBox::ColourIds::arrowColourId, Colours::white);
    menu.setColour(ComboBox::ColourIds::outlineColourId, Colours::transparentWhite);
    menu.setJustificationType(Justification::centred);
    menu.setSelectedId(1, dontSendNotification);
    menu.onChange = [this] { presetChanged(); };
    
    addAndMakeVisible(pageLabel);
    pageLabel.setText("P" + String(vocodec::knobPage + 1), dontSendNotification);
    
    //logo->setBounds(Rectangle<int>(110, 10, 75, 75));
    //sideThingy->setSize(1000, 700);
    //sideThingy->setBounds(Rectangle<int>(-230, 230, 700, 1000));
    panel->setBounds(Rectangle<int>(5, 10, 1000, 1000));
    
    startTimerHz(30);
    
    editor = this;
}

VocodecAudioProcessorEditor::~VocodecAudioProcessorEditor()
{
    for (int i = 0; i < NUM_KNOBS; i++)
        dials[i]->setLookAndFeel(nullptr);
    
    editor = nullptr;
}

//==============================================================================
void VocodecAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setGradientFill(ColourGradient(Colour(30, 30, 30), juce::Point<float>(0,0), Colour(10, 10, 10), juce::Point<float>(0, 712), false));
    
    g.fillRect(0, 0, 600, 712);
    
    g.setFont (15.0f);
    //    g.drawImageAt(baseline, 0, 0);
    
    g.setColour(Colours::white);
    g.drawFittedText(paramName, Rectangle<int>(175,80,150,50), Justification::centred, 1);
    //    knobs[0]->setBounds(0, 3, getWidth(), getHeight());
    
    juce::Font mainComponentFont(Font::getDefaultSansSerifFontName(), 20.0f, juce::Font::bold | juce::Font::italic);
    g.setColour(Colours::gold);
    /*g.drawFittedText("EDIT", Rectangle<int>(455, 70, 40, 15), Justification::left, 1);
     g.drawFittedText("USB", Rectangle<int>(557, 217, 30, 15), Justification::left, 1);
     g.drawFittedText("Dry/Wet", Rectangle<int>(380, 590, 75, 15), Justification::left, 1);
     g.drawFittedText("1", Rectangle<int>(190, 290, 10, 20), Justification::left, 1);
     g.drawFittedText("2", Rectangle<int>(405, 290, 10, 20), Justification::left, 1);
     g.drawFittedText("3", Rectangle<int>(270, 420, 10, 20), Justification::left, 1);
     g.drawFittedText("4", Rectangle<int>(470, 420, 10, 20), Justification::left, 1);
     g.drawFittedText("5", Rectangle<int>(200, 580, 10, 20), Justification::left, 1);
     g.drawFittedText("A", Rectangle<int>(573, 360, 10, 20), Justification::left, 1);
     g.drawFittedText("B", Rectangle<int>(573, 420, 10, 20), Justification::left, 1);
     g.drawFittedText("C", Rectangle<int>(306, 557, 10, 20), Justification::left, 1);
     g.drawFittedText("D", Rectangle<int>(190, 650, 10, 20), Justification::left, 1);
     g.drawFittedText("E", Rectangle<int>(250, 650, 10, 20), Justification::left, 1);*/
    
    
    //g.drawLine(Line<float>(Point<float>(400, 722), Point<float>(612, 687)), 5);
    //g.drawLine(Line<float>(Point<float>(550, 722), Point<float>(610, 662)), 5);
    
    g.setFont(60.0f);
    g.setColour(Colours::gold);
    //g.drawFittedText("V O C O", Rectangle<int>(0, 400, 75, 300), Justification::left, 7);
    //g.drawFittedText("D E C", Rectangle<int>(0, 640, 350, 100), Justification::left, 1);
    
    // USB
    g.setColour(juce::Colours::darkgreen);
    g.fillEllipse(493, 252, 22, 22);
    g.setGradientFill(ColourGradient(Colours::lightgreen, juce::Point<float>(504, 263), Colours::transparentWhite, juce::Point<float>(493, 252), true));
    g.fillEllipse(489, 248, 30, 30);
    // 1
    
    g.setColour(Colours::darkred);
    g.fillEllipse(502, 296, 22, 22);
    if (lightStates[8]) {
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(513, 307), Colours::transparentWhite, juce::Point<float>(502, 296), true));
        g.fillEllipse(497, 292, 30, 30);
    }
    // 2
    
    g.setColour(Colours::darkgreen);
    g.fillEllipse(539, 296, 22, 22);
    if (lightStates[9]) {
        g.setGradientFill(ColourGradient(Colours::lightgreen, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
        g.fillEllipse(535, 292, 30, 30);
    }
    // A
    
    // Trying this out, since it's technically more accurate to the hardware look
    g.setColour(Colours::white.withAlpha(0.5f));
    g.fillEllipse(510, 357, 22, 22);
    if (lightStates[0]) {
        g.setGradientFill(ColourGradient(Colours::gold, juce::Point<float>(521, 368), Colours::transparentWhite, juce::Point<float>(510, 357), true));
        g.fillEllipse(506, 353, 30, 30);
    }
    // B
    
    g.setColour(juce::Colours::darkgreen);
    g.fillEllipse(510, 414, 22, 22);
    if (lightStates[1]) {
        g.setGradientFill(ColourGradient(Colours::lightgreen, juce::Point<float>(521, 425), Colours::transparentWhite, juce::Point<float>(510, 414), true));
        g.fillEllipse(506, 410, 30, 30);
    }
    // C
    
    g.setColour(juce::Colours::darkgreen);
    g.fillEllipse(303, 493, 22, 22);
    if (lightStates[2]) {
        g.setGradientFill(ColourGradient(Colours::lightgreen, juce::Point<float>(314, 504), Colours::transparentWhite, juce::Point<float>(303, 493), true));
        g.fillEllipse(299, 489, 30, 30);
    }
    
    // EDIT
    g.setColour(juce::Colours::darkred);
    g.fillEllipse(421, 50, 22, 22);
    if (lightStates[6]) {
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(432, 61), Colours::transparentWhite, juce::Point<float>(421, 50), true));
        g.fillEllipse(417, 46, 30, 30);
    }
    
    // In1Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(15, 398, 10, 10);
    float inOne;
    inOne = atodb(processor.audioInput[0]);
    inOne = LEAF_clip(-120.0f, inOne, 0.0f);
    inOne = ( (inOne + 120.0f) / 120.0f ) * 8.0f;
    g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(21, 404), Colours::transparentWhite, juce::Point<float>(10 - inOne + 11.0f, 393 - inOne + 11.0f), true));
    g.fillEllipse(10, 393, 20, 20);
    
    
    // In1Red
    g.setColour(Colours::darkred);
    g.fillEllipse(35, 398, 10, 10);
    if(processor.audioInput[0] >= 0.999f){
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(41, 404), Colours::transparentWhite, juce::Point<float>(30, 393), true));
        g.fillEllipse(30, 393, 20, 20);
    }
    
    
    // In2Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(15, 530, 10, 10);
    float inTwo;
    inTwo = atodb(processor.audioInput[1]);
    inTwo = LEAF_clip(-120.0f, inTwo, 0.0f);
    inTwo = ( (inTwo + 120.0f) / 120.0f ) * 8.0f;
    g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(21, 536), Colours::transparentWhite, juce::Point<float>(10 - inTwo + 11.0f, 525 - inTwo + 11.0f), true));
    g.fillEllipse(10, 525, 20, 20);
    
    
    // In2Red
    g.setColour(Colours::darkred);
    g.fillEllipse(35, 530, 10, 10);
    if(processor.audioInput[1] >= 0.999f){
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(41, 536), Colours::transparentWhite, juce::Point<float>(30, 525), true));
        g.fillEllipse(30, 525, 20, 20);
    }
    
    
    
    // Out1Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(550, 632, 10, 10);
    float outOne;
    outOne = atodb(processor.audioOutput[0]);
    outOne = LEAF_clip(-120.0f, outOne, 0.0f);
    outOne = ( (outOne + 120.0f) / 120.0f ) * 8.0f;
    g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(556, 641), Colours::transparentWhite, juce::Point<float>(545 - outOne + 11.0f, 630 - outOne + 11.0f), true));
    g.fillEllipse(545, 627, 20, 20);
    
    
    // Out1Red
    g.setColour(Colours::darkred);
    g.fillEllipse(570, 632, 10, 10);
    if(processor.audioOutput[0] >= 0.999f){
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(576, 638), Colours::transparentWhite, juce::Point<float>(565, 627), true));
        g.fillEllipse(565, 627, 20, 20);
    }
    
    
    // Out2Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(550, 515, 10, 10);
    float outTwo;
    outTwo = atodb(processor.audioOutput[1]);
    outTwo = LEAF_clip(-120.0f, outTwo, 0.0f);
    outTwo = ( (outTwo + 120.0f) / 120.0f ) * 8.0f;
    g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(556, 521), Colours::transparentWhite, juce::Point<float>(545 - outTwo + 11.0f, 510 - outTwo + 11.0f), true));
    g.fillEllipse(545, 510, 20, 20);
    
    
    //Out2Red
    g.setColour(Colours::darkred);
    g.fillEllipse(570, 515, 10, 10);
    if(processor.audioOutput[1] >= 0.999f){
        g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(576, 521), Colours::transparentWhite, juce::Point<float>(565, 510), true));
        g.fillEllipse(565, 510, 20, 20);
    }
}

void VocodecAudioProcessorEditor::resized()
{
    
    //    for (int i = 1; i < NUM_KNOBS; i++) {
    ////        knobs[i]->setBounds(0, 1, getWidth(), getHeight());
    //    }
    //    for (int i = 0; i < NUM_LIGHTS; i++) {
    ////        lights[i]->setBounds(0, 1, getWidth(), getHeight());
    //    }
    
    buttons[vocodec::ButtonA]->setBounds(Rectangle<int>(540, 353, 30, 30));
    buttons[vocodec::ButtonB]->setBounds(Rectangle<int>(540, 412, 30, 30));
    buttons[vocodec::ButtonC]->setBounds(Rectangle<int>(300, 523, 30, 30));
    buttons[vocodec::ButtonD]->setBounds(Rectangle<int>(181, 618, 30, 30));
    buttons[vocodec::ButtonE]->setBounds(Rectangle<int>(238, 618, 30, 30));
    buttons[vocodec::ButtonEdit]->setBounds(Rectangle<int>(419, 88, 30, 30));
    buttons[vocodec::ButtonLeft]->setBounds(Rectangle<int>(438, 142, 30, 30));
    buttons[vocodec::ButtonRight]->setBounds(Rectangle<int>(528, 142, 30, 30));
    buttons[vocodec::ButtonUp]->setBounds(Rectangle<int>(482, 118, 30, 30));
    buttons[vocodec::ButtonDown]->setBounds(Rectangle<int>(482, 174, 30, 30));
    
    dials[1]->setBounds(175, 205, 57, 57);
    
    dials[2]->setBounds(385, 205, 57, 57);
    
    dials[3]->setBounds(250, 345, 57, 57);
    
    dials[4]->setBounds(445, 345, 57, 57);
    
    dials[5]->setBounds(175, 500, 57, 57);
    
    dials[6]->setBounds(380, 500, 57, 57);
    
    menu.setBounds(175, 50, 150, 50);
    
    pageLabel.setBounds(menu.getRight(), menu.getY(), 150, 50);
}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == nullptr) return;
    
    if (slider == dials[6]) {
        processor.interpVal = slider->getValue();
    }
    else
    {
        float sliderValue;
        sliderValue = slider->getValue();
        
        int whichKnob = dials.indexOf(slider) - 1;
        if (whichKnob < 0) return;
        int whichParam = (vocodec::knobPage * KNOB_PAGE_SIZE) + whichKnob;
        
        vocodec::displayValues[whichParam] =
        vocodec::presetKnobValues[vocodec::currentPreset][whichParam] = sliderValue;
        
        paramName = String(vocodec::knobParamNames[vocodec::currentPreset][whichParam]) + " ";
        paramName += String(vocodec::displayValues[whichParam], 3);
        
        *processor.pluginParams[whichParam] = sliderValue;
    }
    
    repaint();
}

void VocodecAudioProcessorEditor::buttonClicked(Button*button)
{
    
}

void VocodecAudioProcessorEditor::buttonStateChanged(Button *button)
{
    if (button == nullptr) return;
    
    // Set the button values to be checked in the audio frame (same as hardware Vocodec)
    int whichButton = buttons.indexOf(static_cast<ShapeButton*>(button));
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
}

void VocodecAudioProcessorEditor::timerCallback()
{
    if (shouldRepaint)
    {
        repaint();
        shouldRepaint = false;
    }
    
    pageLabel.setText("P" + String(vocodec::knobPage + 1), dontSendNotification);
}

void setLED_A(int onOFF)
{
    if (lightStates[0] == (bool) onOFF) return;
    
    lightStates[0] = (bool) onOFF;
    
    shouldRepaint = true;
}

void setLED_B(int onOFF)
{
    if (lightStates[1] == (bool) onOFF) return;
    
    lightStates[1] = (bool) onOFF;
    
    shouldRepaint = true;
}

void setLED_C(int onOFF)
{
    if (lightStates[2] == (bool) onOFF) return;
    
    lightStates[2] = (bool) onOFF;
    
    shouldRepaint = true;
}

void setLED_1(int onOFF)
{
    if (lightStates[8] == (bool) onOFF) return;
    
    lightStates[8] = (bool) onOFF;
    
    shouldRepaint = true;
}

void setLED_2(int onOFF)
{
    if (lightStates[9] == (bool) onOFF) return;
    
    lightStates[9] = (bool) onOFF;
    
    shouldRepaint = true;
}

void setLED_Edit(int onOFF)
{
    if (lightStates[6] == (bool) onOFF) return;
    
    lightStates[6] = (bool) onOFF;
    
    shouldRepaint = true;
}

void OLED_process(void)
{
    
}

void OLED_writePreset(void)
{
    MessageManagerLock mml;
    editor->menu.setSelectedId(vocodec::currentPreset + 1, dontSendNotification);
}

void OLED_writeEditScreen(void)
{
    
}

void OLED_writeKnobParameter(uint8_t whichParam)
{
    
}

void OLED_writeButtonAction(uint8_t whichButton, uint8_t whichAction)
{
    
}

void OLED_writeTuning(void)
{
    
}

void OLED_draw(void)
{
    
}

void OLEDclear(void)
{
    
}

void OLEDclearLine(OLEDLine line)
{
    
}

void OLEDwriteString(const char* myCharArray, uint8_t arrayLength, uint8_t startCursor, OLEDLine line)
{
    
}

void OLEDwriteLine(const char* myCharArray, uint8_t arrayLength, OLEDLine line)
{
    
}

void OLEDwriteInt(uint32_t myNumber, uint8_t numDigits, uint8_t startCursor, OLEDLine line)
{
    
}

void OLEDwriteIntLine(uint32_t myNumber, uint8_t numDigits, OLEDLine line)
{
    
}

void OLEDwritePitch(float midi, uint8_t startCursor, OLEDLine line, uint8_t showCents)
{
    
}

void OLEDwritePitchClass(float midi, uint8_t startCursor, OLEDLine line)
{
    
}

void OLEDwritePitchLine(float midi, OLEDLine line, uint8_t showCents)
{
    
}

void OLEDwriteFixedFloat(float input, uint8_t numDigits, uint8_t numDecimal, uint8_t startCursor, OLEDLine line)
{
    
}

void OLEDwriteFixedFloatLine(float input, uint8_t numDigits, uint8_t numDecimal, OLEDLine line)
{
    
}

void OLEDwriteFloat(float input, uint8_t startCursor, OLEDLine line)
{
    
}

void OLEDdrawFloatArray(float* input, float min, float max, uint8_t size, uint8_t offset, uint8_t startCursor, OLEDLine line)
{
    
}

int16_t OLEDgetCursor(void)
{
    return 0;
}
