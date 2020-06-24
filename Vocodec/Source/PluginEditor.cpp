/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VocodecAudioProcessorEditor::VocodecAudioProcessorEditor (VocodecAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	baseline = ImageCache::getFromMemory(BinaryData::Default_png, BinaryData::Default_pngSize);

	for (int i = 0; i < NUM_KNOBS; i++) {
		knobs.add(new DrawableImage());
		addAndMakeVisible(knobs[i]);
	}
	for (int i = 0; i < NUM_LIGHTS; i++) {
		lights.add(new DrawableImage());
		addAndMakeVisible(lights[i]);
	}


	for (int i = 0; i < NUM_BUTTONS; i++) {
		buttons.add(new ImageButton());
		addAndMakeVisible(buttons[i]);
	}
	buttons[0]->setTriggeredOnMouseDown(true);
	buttons[0]->onClick = [this] { buttonFunction(0); };
	buttons[1]->onClick = [this] { buttonFunction(1); };
	buttons[2]->onClick = [this] { buttonFunction(2); };
	buttons[3]->onClick = [this] { buttonFunction(3); };
	buttons[4]->onClick = [this] { buttonFunction(4); };

	knobs[0]->setImage(ImageCache::getFromMemory(BinaryData::mic_png, BinaryData::mic_pngSize));
	knobs[1]->setImage(ImageCache::getFromMemory(BinaryData::_1_png, BinaryData::_1_pngSize));
	knobs[2]->setImage(ImageCache::getFromMemory(BinaryData::_2_png, BinaryData::_2_pngSize));
	knobs[3]->setImage(ImageCache::getFromMemory(BinaryData::_3_png, BinaryData::_3_pngSize));
	knobs[4]->setImage(ImageCache::getFromMemory(BinaryData::_4_png, BinaryData::_4_pngSize));
	knobs[5]->setImage(ImageCache::getFromMemory(BinaryData::_5_png, BinaryData::_5_pngSize));
	knobs[6]->setImage(ImageCache::getFromMemory(BinaryData::wet_png, BinaryData::wet_pngSize));
	lights[0]->setImage(ImageCache::getFromMemory(BinaryData::A_png, BinaryData::A_pngSize));
	lights[1]->setImage(ImageCache::getFromMemory(BinaryData::B_png, BinaryData::B_pngSize));
	lights[2]->setImage(ImageCache::getFromMemory(BinaryData::C_png, BinaryData::C_pngSize));
	lights[3]->setImage(ImageCache::getFromMemory(BinaryData::In1_png, BinaryData::In1_pngSize));
	lights[4]->setImage(ImageCache::getFromMemory(BinaryData::In2_png, BinaryData::In2_pngSize));
	lights[5]->setImage(ImageCache::getFromMemory(BinaryData::Out1_png, BinaryData::Out1_pngSize));
	lights[6]->setImage(ImageCache::getFromMemory(BinaryData::Out2_png, BinaryData::Out2_pngSize));

	Image upA = ImageCache::getFromMemory(BinaryData::A_1_png, BinaryData::A_1_pngSize);
	Image upB = ImageCache::getFromMemory(BinaryData::B_2_png, BinaryData::B_2_pngSize);
	Image downB = ImageCache::getFromMemory(BinaryData::Boff_png, BinaryData::Boff_pngSize);
	Image upC = ImageCache::getFromMemory(BinaryData::C_1_png, BinaryData::C_1_pngSize);
	Image upD = ImageCache::getFromMemory(BinaryData::D_png, BinaryData::D_pngSize);
	Image upE = ImageCache::getFromMemory(BinaryData::E_png, BinaryData::E_pngSize);
	Image upEdit = ImageCache::getFromMemory(BinaryData::edit_png, BinaryData::edit_pngSize);
	Image upUp = ImageCache::getFromMemory(BinaryData::UP_png, BinaryData::UP_pngSize);
	Image upDown = ImageCache::getFromMemory(BinaryData::Down_png, BinaryData::Down_pngSize);
	Image upLeft = ImageCache::getFromMemory(BinaryData::Left_png, BinaryData::Left_pngSize);
	Image upRight = ImageCache::getFromMemory(BinaryData::Right_png, BinaryData::Right_pngSize);

	Image blank = ImageCache::getFromMemory(BinaryData::blank_png, BinaryData::blank_pngSize);
	
	
	buttons[0]->setImages(false, false, true, upA, 1, Colours::transparentBlack, upA, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[1]->setImages(false, false, true, upB, 1, Colours::transparentBlack, upB, 1, Colours::transparentBlack, downB, 1, Colours::transparentBlack, 0.5);
	buttons[2]->setImages(false, false, true, upC, 1, Colours::transparentBlack, upC, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[3]->setImages(false, false, true, upD, 1, Colours::transparentBlack, upD, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[4]->setImages(false, false, true, upE, 1, Colours::transparentBlack, upE, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[5]->setImages(false, false, true, upEdit, 1, Colours::transparentBlack, upEdit, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[6]->setImages(false, false, true, upUp, 1, Colours::transparentBlack, upUp, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[7]->setImages(false, false, true, upDown, 1, Colours::transparentBlack, upDown, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[8]->setImages(false, false, true, upLeft, 1, Colours::transparentBlack, upLeft, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);
	buttons[9]->setImages(false, false, true, upRight, 1, Colours::transparentBlack, upRight, 1, Colours::transparentBlack, blank, 1, Colours::transparentBlack, 0.5);

	setSize(baseline.getWidth(), baseline.getHeight());

	dial1.setLookAndFeel(&knobOne);
	dial1.setSliderStyle(Slider::Rotary);
	dial1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial1);
	dial1.addListener(this);

	dial2.setLookAndFeel(&knobTwo);
	dial2.setSliderStyle(Slider::Rotary);
	dial2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial2);
	dial2.addListener(this);

	dial3.setLookAndFeel(&knobThree);
	dial3.setSliderStyle(Slider::Rotary);
	dial3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial3);
	dial3.addListener(this);

	dial4.setLookAndFeel(&knobFour);
	dial4.setSliderStyle(Slider::Rotary);
	dial4.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial4);
	dial4.addListener(this);

	dial5.setLookAndFeel(&knobFive);
	dial5.setSliderStyle(Slider::Rotary);
	dial5.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial5);
	dial5.addListener(this);

	dial6.setLookAndFeel(&knobSix);
	dial6.setSliderStyle(Slider::Rotary);
	dial6.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial6);
	dial6.addListener(this);

	dial7.setLookAndFeel(&knobSeven);
	dial7.setSliderStyle(Slider::Rotary);
	dial7.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(dial7);
	dial7.addListener(this);


	addAndMakeVisible(menu);
	menu.addItem("PRESET 1", 1);
	menu.addItem("PRESET 2", 2);
	menu.addItem("PRESET 3", 3);
	menu.addItem("PRESET 4", 4);
	Colour translucent(0.0f, 0.0f, 0.0f, 0.65f);
	menu.setColour(ComboBox::ColourIds::backgroundColourId, translucent);
	menu.setColour(ComboBox::ColourIds::textColourId, Colours::blue);
	menu.setColour(ComboBox::ColourIds::buttonColourId, Colours::black);
	menu.setColour(ComboBox::ColourIds::outlineColourId, Colours::transparentWhite);
	menu.setJustificationType(Justification::centred);
	menu.setSelectedId(1);
}

VocodecAudioProcessorEditor::~VocodecAudioProcessorEditor()
{
	
}

//==============================================================================
void VocodecAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	g.drawImageAt(baseline,0, 0);
	knobs[0]->setBounds(0, 3, getWidth(), getHeight());
}

void VocodecAudioProcessorEditor::resized()
{
	for (int i = 1; i < NUM_KNOBS; i++) {
		knobs[i]->setBounds(0, 1, getWidth(), getHeight());
	}
	for (int i = 0; i < NUM_LIGHTS; i++) {
		lights[i]->setBounds(0, 1, getWidth(), getHeight());
	}
	for (int i = 0; i < NUM_BUTTONS; i++) {
		buttons[i]->setBounds(0, 1, getWidth(), getHeight());
	}

	dial1.setBounds(110, 18, 52, 61);
	
	dial2.setBounds(160, 106, 52, 68);
	dial3.setBounds(316, 113, 52, 66);

	dial4.setBounds(210, 210, 54, 68);

	dial5.setBounds(363, 210, 54, 68);

	dial6.setBounds(155, 325, 57, 68);

	dial7.setBounds(318, 326, 57, 68);

	menu.setBounds(175, 50, 150, 50);

}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	if (slider == &dial1) {
		if (sliderOpacity[0] == 0) {
			sliderOpacity[0] = 1;
			knobs[0]->setOpacity(sliderOpacity[0]);
		}
		else
		{
			sliderOpacity[0] = 0;
			knobs[0]->setOpacity(sliderOpacity[0]);
		}
	}
	if (slider == &dial2) {
		if (sliderOpacity[1] == 0) {
			sliderOpacity[1] = 1;
			knobs[1]->setOpacity(sliderOpacity[1]);
		}
		else
		{
			sliderOpacity[1] = 0;
			knobs[1]->setOpacity(sliderOpacity[1]);
		}
	}
	if (slider == &dial3) {
		if (sliderOpacity[2] == 0) {
			sliderOpacity[2] = 1;
			knobs[2]->setOpacity(sliderOpacity[2]);
		}
		else
		{
			sliderOpacity[2] = 0;
			knobs[2]->setOpacity(sliderOpacity[2]);
		}
	}
	if (slider == &dial4) {
		if (sliderOpacity[3] == 0) {
			sliderOpacity[3] = 1;
			knobs[3]->setOpacity(sliderOpacity[3]);
		}
		else
		{
			sliderOpacity[3] = 0;
			knobs[3]->setOpacity(sliderOpacity[3]);
		}
	}
	if (slider == &dial5) {
		if (sliderOpacity[4] == 0) {
			sliderOpacity[4] = 1;
			knobs[4]->setOpacity(sliderOpacity[4]);
		}
		else
		{
			sliderOpacity[4] = 0;
			knobs[4]->setOpacity(sliderOpacity[4]);
		}
	}
	if (slider == &dial6) {
		if (sliderOpacity[5] == 0) {
			sliderOpacity[5] = 1;
			knobs[5]->setOpacity(sliderOpacity[5]);
		}
		else
		{
			sliderOpacity[5] = 0;
			knobs[5]->setOpacity(sliderOpacity[5]);
		}
	}
	if (slider == &dial7) {
		if (sliderOpacity[6] == 0) {
			sliderOpacity[6] = 1;
			knobs[6]->setOpacity(sliderOpacity[6]);
		}
		else
		{
			sliderOpacity[6] = 0;
			knobs[6]->setOpacity(sliderOpacity[6]);
		}
	}
		//for (int i = 0; i < NUM_LIGHTS; i++) {
		//	lights[i]->setAlpha(slider->getValue() / 10.0f);
		//}
}

void VocodecAudioProcessorEditor::buttonFunction(int i) {
		if (lights[i]->getOpacity() == 0) {
			lights[i]->setOpacity(1);
		}
		else {
			lights[i]->setOpacity(0);
		}
}


void setLED_A(int onOFF){
   // lights[0]->setOpacity();
}

void setLED_B(int onOFF){
   // lights[1]->setOpacity();
    
}

void setLED_C(int onOFF){
   // lights[2]->setOpacity();
}

void setLED_1(int onOFF){
    
}

void setLED_2(int onOFF){
    
}

void setLED_Edit(int onOFF){

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
