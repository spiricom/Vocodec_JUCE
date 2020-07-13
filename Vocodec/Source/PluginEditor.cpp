/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

bool lightStates[NUM_LIGHTS];

VocodecAudioProcessorEditor::VocodecAudioProcessorEditor (VocodecAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    baseline = ImageCache::getFromMemory(BinaryData::Default_png, BinaryData::Default_pngSize);

	vocodec::initModeNames();

	for (int i = 0; i < NUM_KNOBS; i++) {
//        knobs.add(new DrawableImage());
		dials.add(new Slider());
		addAndMakeVisible(dials[i]);
//        addAndMakeVisible(knobs[i]);
		dials[i]->setLookAndFeel(&knobOne);
		dials[i]->setSliderStyle(Slider::Rotary);
        dials[i]->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		addAndMakeVisible(dials[i]);
		dials[i]->addListener(this);
		dials[i]->setRange(0, 1);
	}
    
//    for (int i = 0; i < NUM_LIGHTS; i++) {
//        lightStates[i] = false;
//        lights.add(new DrawableImage());
//        addAndMakeVisible(lights[i]);
//    }

	Path path;
	path.addEllipse(0, 0, 30, 30);


	for (int i = 0; i < NUM_BUTTONS; i++) {
        buttons.add(new ShapeButton("", Colours::ivory, Colours::lightgrey, Colours::grey));
		buttons[i]->setShape(path, true, true, true);
		addAndMakeVisible(buttons[i]);
		buttons[i]->addListener(this);
	}
	//buttons[0]->setTriggeredOnMouseDown(true);
	//buttons[0]->onClick = [this] { buttonFunction(0); };
	//buttons[1]->onClick = [this] { buttonFunction(1); };
	//buttons[2]->onClick = [this] { buttonFunction(2); };
	//buttons[3]->onClick = [this] { buttonFunction(3); };
	//buttons[4]->onClick = [this] { buttonFunction(4); };

//    knobs[0]->setImage(ImageCache::getFromMemory(BinaryData::mic_png, BinaryData::mic_pngSize));
//    knobs[1]->setImage(ImageCache::getFromMemory(BinaryData::_1_png, BinaryData::_1_pngSize));
//    knobs[2]->setImage(ImageCache::getFromMemory(BinaryData::_2_png, BinaryData::_2_pngSize));
//    knobs[3]->setImage(ImageCache::getFromMemory(BinaryData::_3_png, BinaryData::_3_pngSize));
//    knobs[4]->setImage(ImageCache::getFromMemory(BinaryData::_4_png, BinaryData::_4_pngSize));
//    knobs[5]->setImage(ImageCache::getFromMemory(BinaryData::_5_png, BinaryData::_5_pngSize));
//    knobs[6]->setImage(ImageCache::getFromMemory(BinaryData::wet_png, BinaryData::wet_pngSize));
    
//    lights[0]->setImage(ImageCache::getFromMemory(BinaryData::A_png, BinaryData::A_pngSize));
//    lights[1]->setImage(ImageCache::getFromMemory(BinaryData::B_png, BinaryData::B_pngSize));
//    lights[2]->setImage(ImageCache::getFromMemory(BinaryData::C_png, BinaryData::C_pngSize));
//    lights[3]->setImage(ImageCache::getFromMemory(BinaryData::In1_png, BinaryData::In1_pngSize));
//    lights[4]->setImage(ImageCache::getFromMemory(BinaryData::In2_png, BinaryData::In2_pngSize));
//    lights[5]->setImage(ImageCache::getFromMemory(BinaryData::Out1_png, BinaryData::Out1_pngSize));
//    lights[6]->setImage(ImageCache::getFromMemory(BinaryData::Out2_png, BinaryData::Out2_pngSize));
//    lights[7]->setImage(ImageCache::getFromMemory(BinaryData::_1light_png, BinaryData::_1light_pngSize));
//    lights[8]->setImage(ImageCache::getFromMemory(BinaryData::_2light_png, BinaryData::_2light_pngSize));
//    lights[9]->setImage(ImageCache::getFromMemory(BinaryData::_3light_png, BinaryData::_3light_pngSize));

//    Image upA = ImageCache::getFromMemory(BinaryData::A_1_png, BinaryData::A_1_pngSize);
//    Image upB = ImageCache::getFromMemory(BinaryData::B_2_png, BinaryData::B_2_pngSize);
//    Image downB = ImageCache::getFromMemory(BinaryData::Boff_png, BinaryData::Boff_pngSize);
//    Image upC = ImageCache::getFromMemory(BinaryData::C_1_png, BinaryData::C_1_pngSize);
//    Image upD = ImageCache::getFromMemory(BinaryData::D_png, BinaryData::D_pngSize);
//    Image upE = ImageCache::getFromMemory(BinaryData::E_png, BinaryData::E_pngSize);
//    Image upEdit = ImageCache::getFromMemory(BinaryData::edit_png, BinaryData::edit_pngSize);
//    Image upUp = ImageCache::getFromMemory(BinaryData::UP_png, BinaryData::UP_pngSize);
//    Image upDown = ImageCache::getFromMemory(BinaryData::Down_png, BinaryData::Down_pngSize);
//    Image upLeft = ImageCache::getFromMemory(BinaryData::Left_png, BinaryData::Left_pngSize);
//    Image upRight = ImageCache::getFromMemory(BinaryData::Right_png, BinaryData::Right_pngSize);
//
//    Image blank = ImageCache::getFromMemory(BinaryData::blank_png, BinaryData::blank_pngSize);

//    buttons[vocodec::ButtonA]->setImages(false, false, true, upA, 1, Colours::transparentBlack, upA, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonB]->setImages(false, false, true, upB, 1, Colours::transparentBlack, upB, 1, Colours::transparentBlack, downB, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonC]->setImages(false, false, true, upC, 1, Colours::transparentBlack, upC, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonD]->setImages(false, false, true, upD, 1, Colours::transparentBlack, upD, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonE]->setImages(false, false, true, upE, 1, Colours::transparentBlack, upE, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonEdit]->setImages(false, false, true, upEdit, 1, Colours::transparentBlack, upEdit, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonUp]->setImages(false, false, true, upUp, 1, Colours::transparentBlack, upUp, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonDown]->setImages(false, false, true, upDown, 1, Colours::transparentBlack, upDown, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonLeft]->setImages(false, false, true, upLeft, 1, Colours::transparentBlack, upLeft, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
//    buttons[vocodec::ButtonRight]->setImages(false, false, true, upRight, 1, Colours::transparentBlack, upRight, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);

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
	Colour translucent(0.0f, 0.0f, 0.0f, 0.65f);
	menu.setColour(ComboBox::ColourIds::backgroundColourId, translucent);
	menu.setColour(ComboBox::ColourIds::textColourId, Colours::blue);
	menu.setColour(ComboBox::ColourIds::buttonColourId, Colours::black);
	menu.setColour(ComboBox::ColourIds::outlineColourId, Colours::transparentWhite);
	menu.setJustificationType(Justification::centred);
    menu.setSelectedId(1, dontSendNotification);
    menu.onChange = [this] { presetChanged(); };
    
    startTimerHz(10);
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
    g.fillAll (Colours::black);

    g.setFont (15.0f);
//    g.drawImageAt(baseline, 0, 0);
	Colour translucent(0.0f, 0.0f, 0.0f, 0.50f);
	g.setColour(translucent);
	g.fillRect(Rectangle<int>(175, 80, 150, 35));
	g.setColour(Colours::blue);
	g.drawFittedText(paramName, Rectangle<int>(175,80,150,50), Justification::centred, 1);
//    knobs[0]->setBounds(0, 3, getWidth(), getHeight());
	// USB
	g.setColour(juce::Colours::green);
	g.fillEllipse(493, 252, 22, 22);
	// 1
	if (lightStates[8]) {
		g.setColour(juce::Colours::red);
	}
	else {
		g.setColour(Colours::darkgrey);
	}
	g.fillEllipse(502, 296, 22, 22);
	// 2
	if (lightStates[9]) {
		g.setColour(juce::Colours::green);
	}
	else {
		g.setColour(Colours::darkgrey);
	}
	g.fillEllipse(539, 296, 22, 22);
	// A
	if (lightStates[0]) {
		g.setColour(juce::Colours::yellow);
	}
	else {
		g.setColour(Colours::darkgrey);
	}
	g.fillEllipse(510, 357, 22, 22);
	// B
	if (lightStates[1]) {
		g.setColour(juce::Colours::green);
	}
	else {
		g.setColour(Colours::darkgrey);
	}
	g.fillEllipse(510, 414, 22, 22);
	// C
	if (lightStates[3]) {
		g.setColour(juce::Colours::green);
	}
	else {
		g.setColour(Colours::darkgrey);
	}
	g.fillEllipse(303, 493, 22, 22);
	// EDIT
	g.setColour(juce::Colours::green);
	g.fillEllipse(421, 50, 22, 22);
}

void VocodecAudioProcessorEditor::resized()
{

//	for (int i = 1; i < NUM_KNOBS; i++) {
////        knobs[i]->setBounds(0, 1, getWidth(), getHeight());
//	}
//	for (int i = 0; i < NUM_LIGHTS; i++) {
////        lights[i]->setBounds(0, 1, getWidth(), getHeight());
//	}


    Rectangle<int> area = getBounds();
    area.removeFromRight(area.getWidth() * 0.5);
    float h = area.getHeight() * 0.1f;
	buttons[vocodec::ButtonA]->setBounds(Rectangle<int>(540, 353, 30, 30));
	buttons[vocodec::ButtonB]->setBounds(Rectangle<int>(540, 412, 30, 30));
	buttons[vocodec::ButtonC]->setBounds(Rectangle<int>(300, 523, 30, 30));
	buttons[vocodec::ButtonD]->setBounds(Rectangle<int>(181, 618, 30, 30));
	buttons[vocodec::ButtonE]->setBounds(Rectangle<int>(238, 618, 30, 30));
	buttons[vocodec::ButtonEdit]->setBounds(Rectangle<int>(419, 88, 30, 30));

    

	dials[0]->setBounds(90, 60, 57, 57);
	
	dials[1]->setBounds(175, 205, 57, 57);
	dials[2]->setBounds(385, 205, 57, 57);

	dials[3]->setBounds(250, 345, 57, 57);

	dials[4]->setBounds(445, 345, 57, 57);

	dials[5]->setBounds(175, 500, 57, 57);

	dials[6]->setBounds(380, 500, 57, 57);

	menu.setBounds(175, 50, 150, 50);

}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	if (slider == dials[0]) {
		if (sliderOpacity[0] == 0) {
			sliderOpacity[0] = 1;
//            knobs[0]->setOpacity(sliderOpacity[0]);
		}
		else
		{
			sliderOpacity[0] = 0;
//            knobs[0]->setOpacity(sliderOpacity[0]);
		}
	}
	if (slider == dials[1]) {
		vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 0)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 0)]);
		paramName += " " + String(vocodec::displayValues[vocodec::knobPage * 5 + 0]);
		if (sliderOpacity[1] == 0) {
			sliderOpacity[1] = 1;
//            knobs[1]->setOpacity(sliderOpacity[1]);
		}
		else
		{
			sliderOpacity[1] = 0;
//            knobs[1]->setOpacity(sliderOpacity[1]);
		}
		
	}
	if (slider == dials[2]) {
		vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 1)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId() - 1][(vocodec::knobPage * 5 + 1)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 1]);
		if (sliderOpacity[2] == 0) {
			sliderOpacity[2] = 1;
//            knobs[2]->setOpacity(sliderOpacity[2]);
		}
		else
		{
			sliderOpacity[2] = 0;
//            knobs[2]->setOpacity(sliderOpacity[2]);
		}
	}
	if (slider == dials[3]) {
		vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 2)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 2)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 2]);
		if (sliderOpacity[3] == 0) {
			sliderOpacity[3] = 1;
//            knobs[3]->setOpacity(sliderOpacity[3]);
		}
		else
		{
			sliderOpacity[3] = 0;
//            knobs[3]->setOpacity(sliderOpacity[3]);
		}
	}
	if (slider == dials[4]) {
		vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 3)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId() - 1][(vocodec::knobPage * 5 + 3)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 3]);
		if (sliderOpacity[4] == 0) {
			sliderOpacity[4] = 1;
//            knobs[4]->setOpacity(sliderOpacity[4]);
		}
		else
		{
			sliderOpacity[4] = 0;
//            knobs[4]->setOpacity(sliderOpacity[4]);
		}
	}
	if (slider == dials[5]) {
		vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 4)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 4)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 4]);
		if (sliderOpacity[5] == 0) {
			sliderOpacity[5] = 1;
//            knobs[5]->setOpacity(sliderOpacity[5]);
		}
		else
		{
			sliderOpacity[5] = 0;
//            knobs[5]->setOpacity(sliderOpacity[5]);
		}
	}
	if (slider == dials[6]) {
		if (sliderOpacity[6] == 0) {
			sliderOpacity[6] = 1;
//            knobs[6]->setOpacity(sliderOpacity[6]);
		}
		else
		{
			sliderOpacity[6] = 0;
//            knobs[6]->setOpacity(sliderOpacity[6]);
		}
	}
		//for (int i = 0; i < NUM_LIGHTS; i++) {
		//	lights[i]->setAlpha(slider->getValue() / 10.0f);
		//}
}

void VocodecAudioProcessorEditor::buttonClicked(Button*button)
{
    
}

void VocodecAudioProcessorEditor::buttonStateChanged(Button *button) {
    if (button->getState() == Button::ButtonState::buttonNormal) {
		if (button == buttons[0])
            vocodec::buttonActionsSFX[0][vocodec::ActionRelease] = true;
		if (button == buttons[1])
			vocodec::buttonActionsSFX[1][vocodec::ActionRelease] = true;
		if (button == buttons[2])
			vocodec::buttonActionsSFX[2][vocodec::ActionRelease] = true;
		if (button == buttons[3])
			vocodec::buttonActionsSFX[3][vocodec::ActionRelease] = true;
		if (button == buttons[4])
			vocodec::buttonActionsSFX[4][vocodec::ActionRelease] = true;
		if (button == buttons[5])
			vocodec::buttonActionsSFX[5][vocodec::ActionRelease] = true;
		if (button == buttons[6])
			vocodec::buttonActionsSFX[6][vocodec::ActionRelease] = true;
		if (button == buttons[7])
			vocodec::buttonActionsSFX[7][vocodec::ActionRelease] = true;
		if (button == buttons[8])
			vocodec::buttonActionsSFX[8][vocodec::ActionRelease] = true;
		if (button == buttons[9])
			vocodec::buttonActionsSFX[9][vocodec::ActionRelease] = true;
	}
    else if (button->getState() == Button::ButtonState::buttonOver) {
        
    }
    else if (button->getState() == Button::ButtonState::buttonDown) {
        if (button == buttons[0])
            vocodec::buttonActionsSFX[0][vocodec::ActionPress] = true;
        if (button == buttons[1])
            vocodec::buttonActionsSFX[1][vocodec::ActionPress] = true;
        if (button == buttons[2])
            vocodec::buttonActionsSFX[2][vocodec::ActionPress] = true;
        if (button == buttons[3])
            vocodec::buttonActionsSFX[3][vocodec::ActionPress] = true;
        if (button == buttons[4])
            vocodec::buttonActionsSFX[4][vocodec::ActionPress] = true;
        if (button == buttons[5])
            vocodec::buttonActionsSFX[5][vocodec::ActionPress] = true;
        if (button == buttons[6])
            vocodec::buttonActionsSFX[6][vocodec::ActionPress] = true;
        if (button == buttons[7])
            vocodec::buttonActionsSFX[7][vocodec::ActionPress] = true;
        if (button == buttons[8])
            vocodec::buttonActionsSFX[8][vocodec::ActionPress] = true;
        if (button == buttons[9])
            vocodec::buttonActionsSFX[9][vocodec::ActionPress] = true;
    }
}

void VocodecAudioProcessorEditor::timerCallback()
{
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
//        lights[i]->setOpacity(lightStates[i]);
    }
    
    repaint();
}

void setLED_A(int onOFF)
{
    lightStates[0] = (bool) onOFF;
}

void setLED_B(int onOFF)
{
	lightStates[1] = (bool) onOFF;
}

void setLED_C(int onOFF)
{
	lightStates[2] = (bool) onOFF;
}

void setLED_1(int onOFF)
{
	lightStates[8] = (bool) onOFF;
}

void setLED_2(int onOFF)
{
	lightStates[9] = (bool) onOFF;
}

void setLED_Edit(int onOFF)
{
	//lightStates[] = (bool) onOFF;
}

void OLED_process(void)
{
    
}

void OLED_writePreset(void)
{
    
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


void VocodecAudioProcessorEditor::presetChanged(){
    
	processor.loading = true;
    
    processor.prevPresetNumber = processor.presetNumber;
    
    processor.presetNumber = menu.getSelectedId();
}
