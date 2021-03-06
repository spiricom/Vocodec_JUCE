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
screen(p),
chooser("Select a .wav file to load...", {}, "*.wav")
{
    panel = Drawable::createFromImageData(BinaryData::panel_svg, BinaryData::panel_svgSize);
    
    setWantsKeyboardFocus(true);
    
    addAndMakeVisible(oversamplingMenu);
    oversamplingMenu.setLookAndFeel(&vocodecLAF);
    oversamplingMenu.addItem("1", 1);
    oversamplingMenu.addItem("2", 2);
    oversamplingMenu.addItem("4", 3);
    oversamplingMenu.addItem("8", 4);
    oversamplingMenu.addItem("16", 5);
//    oversamplingMenu.addItem("32", 6);
//    oversamplingMenu.addItem("64", 7);
    oversamplingMenu.setJustificationType(Justification::centred);
    oversamplingMenu.setSelectedId(1, dontSendNotification);
    oversamplingMenu.onChange = [this] {
        processor.oversamplingRatio = exp2(oversamplingMenu.getSelectedId()-1);
    };
    
    Typeface::Ptr tp = Typeface::createSystemTypefaceFor(BinaryData::EuphemiaCAS_ttf,
                                                         BinaryData::EuphemiaCAS_ttfSize);
    euphemia = Font(tp);
    euphemia.setItalic(true);
    
    oversamplingLabel.setText("OVERSAMPLING", dontSendNotification);
    oversamplingLabel.setFont(euphemia);
    oversamplingLabel.setJustificationType(Justification::centredTop);
    oversamplingLabel.setLookAndFeel(&vocodecLAF);
    addAndMakeVisible(oversamplingLabel);
    
    addAndMakeVisible(screen);
    screen.setOpaque(true);
    screen.onChange = [this] { presetChanged(); };
    
    for (int i = 0; i < NUM_KNOBS; i++) {
        //        knobs.add(new DrawableImage());
        dials.add(new Slider());
        addAndMakeVisible(dials[i]);
        //        addAndMakeVisible(knobs[i]);
        dials[i]->setLookAndFeel(&vocodecLAF);
        dials[i]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        dials[i]->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        dials[i]->addListener(this);
        dials[i]->setRange(0., 1.);
        dials[i]->setOpaque(true);
        
        dialLabels.add(new Label());
        //        dialLabels[i]->setMultiLine(true);
        //        dialLabels[i]->setReadOnly(true);
        dialLabels[i]->setFont(euphemia);
        //        dialLabels[i]->setInterceptsMouseClicks(false, false);
        dialLabels[i]->setJustificationType(Justification::centredTop);
        //        dialLabels[i]->setBorder(BorderSize<int>(-3, 0, 0, 0));
        dialLabels[i]->setLookAndFeel(&vocodecLAF);
        addAndMakeVisible(dialLabels[i]);
    }
    dials[0]->setRange(0., 4.);
    dials[0]->setSkewFactorFromMidPoint(1.0f);
    dials[0]->setDoubleClickReturnValue(true, 1.0f);
    dialLabels[0]->setJustificationType(Justification::topLeft);
    dialLabels[0]->setText("INPUT\nGAIN", dontSendNotification);
    dialLabels[4]->setJustificationType(Justification::topRight);
    
    gainLabel.setText(String(processor.inputGain->get(), 2, false), dontSendNotification);
    addAndMakeVisible(gainLabel);
    
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
        lights.add(new VocodecLight("", darkergrey, cLightColours[i]));
        addAndMakeVisible(lights[i]);
        lights[i]->setOpaque(true);
    }
    processor.vcd.lightStates[vocodec::VocodecLightIn1Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightIn2Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightOut1Meter] = true;
    processor.vcd.lightStates[vocodec::VocodecLightOut2Meter] = true;
    
    setSize(600 * processor.editorScale, 716 * processor.editorScale);
    
    constrain->setFixedAspectRatio(600.0f / 716.0f);
    
    addAndMakeVisible(*resizer);
    resizer->setAlwaysOnTop(true);
    
    versionLabel.setText("v" + String(ProjectInfo::versionString), dontSendNotification);
    versionLabel.setColour(Label::ColourIds::textColourId, Colours::lightgrey);
    addAndMakeVisible(versionLabel);
    
    vocodec::OLED_writePreset(&processor.vcd);
    
    currentKnobPreset = processor.vcd.currentPreset;
    
    startTimerHz(30);
}

VocodecAudioProcessorEditor::~VocodecAudioProcessorEditor()
{
    for (int i = 0; i < NUM_KNOBS; i++)
    {
        dials[i]->setLookAndFeel(nullptr);
        dialLabels[i]->setLookAndFeel(nullptr);
    }
    oversamplingMenu.setLookAndFeel(nullptr);
    oversamplingLabel.setLookAndFeel(nullptr);
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
    
    g.fillRect(getWidth() * 0.25f, getHeight() * 0.25f, getWidth() * 0.6f, getHeight() * 0.5f);
    g.fillRect(getWidth() * 0.25f, getHeight() * 0.75f, getWidth() * 0.2f, getHeight() * 0.15f);
}

void VocodecAudioProcessorEditor::resized()
{
    int width = getWidth();
    int height = getHeight();
    
    screen.setBounds(width*0.347f, height*0.096f, width*0.306f, height*0.105f);
    
    float s = width / 600.0f;
    
    processor.editorScale = s;
    
    const float buttonSize = 24.0f*s;
    const float knobSize = 57.0f*s;
    const float bigLightSize = 23.0f*s;
    const float smallLightSize = 15.0f*s;
    const float labelWidth = 130.0f*s;
    const float labelHeight = 20.0f*s;
    
    oversamplingMenu.setBounds(378*s, 621*s, 72.0f*s, 24.0f*s);
    oversamplingLabel.setBounds(332*s, 656*s, 164.0f*s, 50.0f*s);
    oversamplingLabel.setFont(euphemia.withHeight(height * 0.025f));
    
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
    
    dials[0]                        ->setBounds(85*s, 60*s, knobSize, knobSize);
    dials[1]                        ->setBounds(175*s, 205*s, knobSize, knobSize);
    dials[2]                        ->setBounds(385*s, 205*s, knobSize, knobSize);
    dials[3]                        ->setBounds(250*s, 345*s, knobSize, knobSize);
    dials[4]                        ->setBounds(445*s, 345*s, knobSize, knobSize);
    dials[5]                        ->setBounds(175*s, 500*s, knobSize, knobSize);
    dials[6]                        ->setBounds(380*s, 500*s, knobSize, knobSize);
    
    dialLabels[0]                   ->setBounds(40*s, 110*s, 100*s, 50*s);
    //    dialLabels[1]                   ->setBounds(138*s, 185*s, labelWidth, labelHeight);
    //    dialLabels[2]                   ->setBounds(348*s, 185*s, labelWidth, labelHeight);
    //    dialLabels[3]                   ->setBounds(213*s, 325*s, labelWidth, labelHeight);
    //    dialLabels[4]                   ->setBounds(408*s, 325*s, labelWidth, labelHeight);
    //    dialLabels[5]                   ->setBounds(138*s, 480*s, labelWidth, labelHeight);
    //    dialLabels[6]                   ->setBounds(343*s, 480*s, labelWidth, labelHeight);
    dialLabels[1]                   ->setBounds(138*s, 270*s, labelWidth, labelHeight);
    dialLabels[2]                   ->setBounds(348*s, 270*s, labelWidth, labelHeight);
    dialLabels[3]                   ->setBounds(213*s, 410*s, labelWidth, labelHeight);
    dialLabels[4]                   ->setBounds(373*s, 410*s, labelWidth, labelHeight);
    dialLabels[5]                   ->setBounds(138*s, 570*s, labelWidth, labelHeight);
    dialLabels[6]                   ->setBounds(343*s, 570*s, labelWidth, labelHeight);
    
    for (auto label : dialLabels)
        label->setFont(euphemia.withHeight(height * 0.027f));
    
    gainLabel.setBounds(95*s, 120*s, 80*s, 25*s);
    gainLabel.setFont(euphemia.withHeight(height * 0.025f));
    
    versionLabel.setBounds(0, height * 0.97f, width * 0.2f, height * 0.03f);
    versionLabel.setFont(euphemia.withHeight(height * 0.025f));
    
    float r = 600.0f / 716.0f;
    constrain->setSizeLimits(200, 200/r, 800*r, 800);
    resizer->setBounds(getWidth()-16, getHeight()-16, 16, 16);
}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == nullptr) return;
    
    float sliderValue;
    sliderValue = slider->getValue();
    
    int whichKnob = dials.indexOf(slider) - 1;
    if (whichKnob < 0)
    {
        *processor.inputGain = sliderValue;
        return;
    }
    
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
        if (processor.pluginParams.contains(paramId))
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
    oversamplingMenu.setSelectedId(log2(processor.oversamplingRatio)+1);
    
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
        if (i < 5)
        {
            int whichParam = (processor.vcd.knobPage * KNOB_PAGE_SIZE) + i;
            int paramId = (processor.vcd.currentPreset * NUM_PRESET_KNOB_VALUES) + whichParam;
            if (processor.pluginParams.contains(paramId))
            {
                String name = processor.pluginParams[paramId]->getName(50).fromFirstOccurrenceOf("_", false, false).replace("_", " ");
                dialLabels[i+1]->setText(name, dontSendNotification);
            }
            else dialLabels[i+1]->setText("", dontSendNotification);
        }
    }
    
    gainLabel.setText(String(processor.inputGain->get(), 2, false), dontSendNotification);
    
    screen.timerCallback();
    
    if (processor.vcd.attemptFileLoad)
    {
        processor.vcd.attemptFileLoad = 0;
        loadWav();
    }
    
}

void VocodecAudioProcessorEditor::updateKnobs()
{
    for (int i = 1; i < NUM_KNOBS - 1; ++i)
    {
        int whichParam = (processor.vcd.knobPage * KNOB_PAGE_SIZE) + (i - 1);
        int paramId = (processor.vcd.currentPreset * NUM_PRESET_KNOB_VALUES) + whichParam;
        if (processor.pluginParams.contains(paramId))
        {
            dials[i]->setAlpha(1.0f);
            dials[i]->setEnabled(true);
            if (dials[i]->getValue() != processor.pluginParams[paramId]->get())
                dials[i]->setValue(processor.pluginParams[paramId]->get(), dontSendNotification);
        }
        else
        {
            dials[i]->setAlpha(0.4f);
            dials[i]->setEnabled(false);
        }
    }
    if (dials[0]->getValue() != processor.inputGain->get())
        dials[0]->setValue(processor.inputGain->get(), dontSendNotification);
    if (dials[6]->getValue() != processor.dryWetMix->get())
        dials[6]->setValue(processor.dryWetMix->get(), dontSendNotification);
}

void VocodecAudioProcessorEditor::loadWav()
{
    chooser.launchAsync (FileBrowserComponent::canSelectMultipleItems | FileBrowserComponent::openMode
                         | FileBrowserComponent::canSelectFiles,
                         [this] (const FileChooser& chooser)
                         {
        int idx = processor.vcd.wavetableSynthParams.loadIndex;
        
        auto results = chooser.getResults();
        
        int n = 0;
        for (auto result : results)
        {
            auto* reader = processor.formatManager.createReaderFor (result);
            
            if (reader != nullptr)
            {
                std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource
                                                                          (reader, true));
                
                AudioBuffer<float> buffer = AudioBuffer<float>(reader->numChannels, int(reader->lengthInSamples));
                
                reader->read(&buffer, 0, buffer.getNumSamples(), 0, true, true);
                
                if (processor.vcd.loadedTableSizes[idx] > 0)
                {
                    mpool_free((char*)processor.vcd.loadedTables[idx], processor.vcd.largePool);
                }
                processor.vcd.loadedTables[idx] =
                (float*) mpool_alloc(sizeof(float) * buffer.getNumSamples(), processor.vcd.largePool);
                processor.vcd.loadedTableSizes[idx] = buffer.getNumSamples();
                for (int i = 0; i < processor.vcd.loadedTableSizes[idx]; ++i)
                {
                    processor.vcd.loadedTables[idx][i] = buffer.getSample(0, i);
                }
                
                processor.readerSource.reset(newSource.release());
                
                processor.wavetablePaths.set(idx, result.getFullPathName());
                processor.vcd.loadedFilePaths[idx] = (char*) processor.wavetablePaths[idx].toRawUTF8();
            }
            idx++; n++;
            if (idx >= 4) idx = 0;
            // Only load the first 4 files
            if (n >= 4) break;
        }
        processor.vcd.newWavLoaded = 1;
    });
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

