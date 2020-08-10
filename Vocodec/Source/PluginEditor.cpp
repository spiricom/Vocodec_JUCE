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

bool lightStates[NUM_LIGHTS];

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

	vocodec::initModeNames();

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
	menu.setColour(ComboBox::ColourIds::backgroundColourId, Colours::transparentWhite);
	menu.setColour(ComboBox::ColourIds::textColourId, Colours::white);
	menu.setColour(ComboBox::ColourIds::buttonColourId, Colours::black);
	menu.setColour(ComboBox::ColourIds::arrowColourId, Colours::white);
	menu.setColour(ComboBox::ColourIds::outlineColourId, Colours::transparentWhite);
	menu.setJustificationType(Justification::centred);
    menu.setSelectedId(1, dontSendNotification);
    menu.onChange = [this] { presetChanged(); };
	//logo->setBounds(Rectangle<int>(110, 10, 75, 75));
	//sideThingy->setSize(1000, 700);
	//sideThingy->setBounds(Rectangle<int>(-230, 230, 700, 1000));
	panel->setBounds(Rectangle<int>(5, 10, 1000, 1000));
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

	g.setColour(Colours::gold);
	g.fillEllipse(510, 357, 22, 22);
	if (lightStates[0]) {
		g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(521, 368), Colours::transparentWhite, juce::Point<float>(510, 357), true));
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
    float x;
    x = atodb(processor.audioInput[0]);
    x = LEAF_clip(-120.0f, x, 0.0f);
    x = ( (x + 120.0f) / 120.0f ) * 4.0f;
    g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(26, 409), Colours::transparentWhite, juce::Point<float>(15 + x, 398 + x), true));
    g.fillEllipse(11, 394, 20, 20);

    
    // In1Red
    g.setColour(Colours::darkred);
    g.fillEllipse(35, 398, 10, 10);
    
    g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
    g.fillEllipse(535, 292, 30, 30);
  
    // In2Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(539, 296, 22, 22);
    if (lightStates[9]) {
        g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
        g.fillEllipse(535, 292, 30, 30);
    }
 
     // In2Red
    g.setColour(Colours::darkred);
     g.fillEllipse(539, 296, 22, 22);
     if (lightStates[9]) {
         g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
         g.fillEllipse(535, 292, 30, 30);
     }

      // Out1Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(539, 296, 22, 22);
    if (lightStates[9]) {
        g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
        g.fillEllipse(535, 292, 30, 30);
    }
  
    // Out1Red
    g.setColour(Colours::darkred);
     g.fillEllipse(539, 296, 22, 22);
     if (lightStates[9]) {
         g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
         g.fillEllipse(535, 292, 30, 30);
     }
     
       // Out2Yellow
    g.setColour(Colours::gold);
    g.fillEllipse(539, 296, 22, 22);
    if (lightStates[9]) {
        g.setGradientFill(ColourGradient(Colours::yellow, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
        g.fillEllipse(535, 292, 30, 30);
    }
 
      //Out2Red
    g.setColour(Colours::darkred);
     g.fillEllipse(539, 296, 22, 22);
     if (lightStates[9]) {
         g.setGradientFill(ColourGradient(Colours::pink, juce::Point<float>(550, 307), Colours::transparentWhite, juce::Point<float>(539, 296), true));
         g.fillEllipse(535, 292, 30, 30);
     }
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

}

void VocodecAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	float sliderValue;
	sliderValue = slider->getValue();

	if (slider == dials[1]) {
        vocodec::presetKnobValues[processor.presetNumber - 1][(vocodec::knobPage * 5 + 0)] = sliderValue;
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 0)]);
        paramName += " ";
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 0]);
		switch (vocodec::knobPage) {
		case 0:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_volume = sliderValue;
			case 1:
				*processor.vocoderCh_volume = sliderValue;
			case 2:
				*processor.pitchShift_shift = sliderValue;
			case 3:
				*processor.autotuneMono_pickiness = sliderValue;
			case 4:
				*processor.autotunePoly_pickiness = sliderValue;
			case 5:
				*processor.samplerButtonPress_start = sliderValue;
			case 6:
				*processor.samplerKeyboard_start = sliderValue;
			case 7:
				*processor.samplerAutoGrab_threshold = sliderValue;
			case 8:
				*processor.distortion_preGain = sliderValue;
			case 9:
				*processor.wavefolder_gain = sliderValue;
			case 10:
				*processor.bitCrusher_quality = sliderValue;
			case 11:
				*processor.delay_delayL = sliderValue;
			case 12:
				*processor.reverb_size = sliderValue;
			case 13:
				*processor.reverb2_size = sliderValue;
			case 14:
				*processor.livingString_freq1 = sliderValue;
			case 15:
				*processor.livingStringSynth_pluckVol = sliderValue;
			case 16:
				// COME BACK TO CLASSIC SYNTH
				*processor.classicSynth_volume = sliderValue;
			case 17:
				*processor.rhodes_brightness = sliderValue;
			}
			case 1:
				switch (vocodec::currentPreset) {
				case 0:
					*processor.vocoder_breath = sliderValue;
				case 1:
					*processor.vocoderCh_sawToPulse = sliderValue;
				case 2:
					*processor.pitchShift_offset = sliderValue;
				case 3:
					*processor.autotuneMono_hysteresis = sliderValue;
				case 6:
					*processor.samplerKeyboard_crossFade = sliderValue;
				case 7:
					*processor.samplerAutoGrab_lenRand = sliderValue;
				case 10:
					*processor.bitCrusher_preGain = sliderValue;
				case 11:
					*processor.delay_postGain = sliderValue;
				case 14:
					*processor.livingString_prepPos = sliderValue;
				case 15:
					*processor.livingStringSynth_prepPos = sliderValue;
				case 16:
					*processor.classicSynth_attack = sliderValue;
				case 17:
					*processor.rhodes_attack = sliderValue;
				}
				case 2:
					switch (vocodec::currentPreset) {
					case 1:
						*processor.vocoderCh_bandSquish = sliderValue;
					case 14:
						*processor.livingString_freq2 = sliderValue;
					case 16:
						*processor.classicSynth_fAttack = sliderValue;
					case 17:
						*processor.rhodes_index1 = sliderValue;
					}
				case 3:
					switch (vocodec::currentPreset) {
					case 16:
						*processor.classicSynth_fAmount = sliderValue;
					case 17:
						*processor.rhodes_ratio1 = sliderValue;
					}
				case 4:
					*processor.rhodes_ratio6 = sliderValue;
				}
		}
	else if (slider == dials[2]) {
		vocodec::presetKnobValues[processor.presetNumber - 1][(vocodec::knobPage * 5 + 1)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId() - 1][(vocodec::knobPage * 5 + 1)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 1]);
		switch (vocodec::knobPage) {
		case 0:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_warp = sliderValue;
				case 1:
				*processor.vocoderCh_warp = sliderValue;
				case 2:
				*processor.pitchShift_fine = sliderValue;
				case 3:
				*processor.autotuneMono_amount = sliderValue;
				case 5:
				*processor.samplerButtonPress_length = sliderValue;
				case 6:
				*processor.samplerKeyboard_length = sliderValue;
				case 7:
				*processor.samplerAutoGrab_window = sliderValue;
				case 8:
				*processor.distortion_tilt = sliderValue;
				case 9:
				*processor.wavefolder_offset1 = sliderValue;
				case 10:
				*processor.bitCrusher_sampRatio = sliderValue;
				case 11:
				*processor.delay_delayR = sliderValue;
				case 12:
				*processor.reverb_fBLowPass = sliderValue;
				case 13:
				*processor.reverb2_lowPass = sliderValue;
				case 14:
				*processor.livingString_detune = sliderValue;
				case 15:
				*processor.livingStringSynth_pluckTone = sliderValue;
				case 16:
				*processor.classicSynth_lowPass = sliderValue;
				case 17:
				*processor.rhodes_tremDepth = sliderValue;
			}
		case 1:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_tilt = sliderValue;
			case 1:
				*processor.vocoderCh_pulseWidth = sliderValue;
			case 6:
				*processor.samplerKeyboard_velo_Sens = sliderValue;
			case 7:
				*processor.samplerAutoGrab_spdRand = sliderValue;
			case 11:
				*processor.delay_postGain1 = sliderValue;
			case 14:
				*processor.livingString_prepForce = sliderValue;
			case 15:
				*processor.livingStringSynth_prepForce = sliderValue;
			case 16:
				*processor.classicSynth_decay = sliderValue;
			case 17:
				*processor.rhodes_decay = sliderValue;
			}
		case 2:
			switch (vocodec::currentPreset) {
			case 1:
				*processor.vocoderCh_bandOff = sliderValue;
			case 14:
				*processor.livingString_freq3 = sliderValue;
			case 16: 
				*processor.classicSynth_fDecay = sliderValue;
			case 17:
				*processor.rhodes_index2 = sliderValue;
			}
		case 3:
			switch (vocodec::currentPreset) {
			case 16:
				*processor.classicSynth_sawPulse = sliderValue;
			case 17:
				*processor.rhodes_ratio2 = sliderValue;
			}
		case 4:
			*processor.rhodes_feedback = sliderValue;
		}

	}
	else if (slider == dials[3]) {
		vocodec::presetKnobValues[processor.presetNumber - 1][(vocodec::knobPage * 5 + 2)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 2)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 2]);
		switch (vocodec::knobPage) {
		case 0:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_quality = sliderValue;
				case 1:
				*processor.vocoderCh_quality = sliderValue;
				case 2:
				*processor.pitchShift_f_Amt = sliderValue;
				case 3:
				*processor.autotuneMono_speed = sliderValue;
				case 5:
				*processor.samplerButtonPress_speed = sliderValue;
				case 6:
				*processor.samplerKeyboard_speed = sliderValue;
				case 7:
				*processor.samplerAutoGrab_speed = sliderValue;
				case 8:
				*processor.distortion_midGain = sliderValue;
				case 9:
				*processor.wavefolder_offset2 = sliderValue;
				case 10:
				*processor.bitCrusher_rounding = sliderValue;
				case 11:
				*processor.delay_highPass = sliderValue;
				case 12:
				*processor.reverb_inHighPass = sliderValue;
				case 13:
				*processor.reverb2_highPass = sliderValue;
				case 14:
				*processor.livingString_decay = sliderValue;
				case 15:
				*processor.livingStringSynth_decay = sliderValue;
				case 16:
				*processor.classicSynth_keyFollow = sliderValue;
				case 17:
				*processor.rhodes_tremRate = sliderValue;
			}
		case 1:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_pulsewidth = sliderValue;
			case 1:
				*processor.vocoderCh_pulseShape = sliderValue;
			case 11:
				*processor.delay_postGain2 = sliderValue;
			case 14:
				*processor.livingString_letRing = sliderValue;
			case 15:
				*processor.livingStringSynth_letRing = sliderValue;
			case 16:
				*processor.classicSynth_sustain = sliderValue;
			case 17:
				*processor.rhodes_sustain = sliderValue;
			}
		case 2:
			switch (vocodec::currentPreset) {
			case 1:
				*processor.vocoderCh_tilt = sliderValue;
			case 14:
				*processor.livingString_freq4 = sliderValue;
			case 16:
				*processor.classicSynth_fSustain = sliderValue;
			case 17:
				*processor.rhodes_index3 = sliderValue;
			}
		case 3:
			*processor.rhodes_ratio3 = sliderValue;
		case 4:
			*processor.rhodes_tuneSnap = sliderValue;
		}
	}
	else if (slider == dials[4]) {
		vocodec::presetKnobValues[processor.presetNumber - 1][(vocodec::knobPage * 5 + 3)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId() - 1][(vocodec::knobPage * 5 + 3)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 3]);
		switch (vocodec::knobPage) {
		case 0:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_sawToPulse = sliderValue;
			case 1:
				*processor.vocoderCh_bandWidth = sliderValue;
			case 2:
				*processor.pitchShift_formant = sliderValue;
			case 3:
				*processor.autotuneMono_leapallow = sliderValue;
			case 5:
				*processor.samplerButtonPress_speedMult = sliderValue;
			case 6:
				*processor.samplerKeyboard_speedMult = sliderValue;
			case 7:
				*processor.samplerAutoGrab_crossFade = sliderValue;
			case 8:
				*processor.distortion_midFreq = sliderValue;
			case 9:
				*processor.wavefolder_postGain = sliderValue;
			case 10:
				*processor.bitCrusher_operation = sliderValue;
			case 11:
				*processor.delay_lowPass = sliderValue;
			case 12:
				*processor.reverb_inLowPass = sliderValue;
			case 13:
				*processor.reverb2_peakFreq = sliderValue;
			case 14:
				*processor.livingString_damping = sliderValue;
			case 15:
				*processor.livingStringSynth_damping = sliderValue;
			case 16:
				*processor.classicSynth_detune = sliderValue;
			case 17:
				*processor.rhodes_drive = sliderValue;
			}
		case 1:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_pulseShape = sliderValue;
			case 1:
				*processor.vocoderCh_breath = sliderValue;
			case 11:
				*processor.delay_postGain3 = sliderValue;
			case 15:
				*processor.livingStringSynth_fBLevel = sliderValue;
			case 16:
				*processor.classicSynth_release = sliderValue;
			case 17:
				*processor.rhodes_release = sliderValue;
			}
		case 2:
			switch (vocodec::currentPreset) {
			case 1:
				*processor.vocoderCh_stereo = sliderValue;
			case 14:
				*processor.livingString_freq5 = sliderValue;
			case 16:
				*processor.classicSynth_fRelease = sliderValue;
			case 17:
				*processor.rhodes_index4 = sliderValue;
			}
		case 3:
			*processor.rhodes_ratio4 = sliderValue;
		case 4:
			*processor.rhodes_randDecay = sliderValue;
		}
	}
	else if (slider == dials[5]) {
		vocodec::presetKnobValues[processor.presetNumber - 1][(vocodec::knobPage * 5 + 4)] = slider->getValue();
		paramName = String(vocodec::knobParamNames[menu.getSelectedId()-1][(vocodec::knobPage * 5 + 4)]);
		paramName += String(vocodec::displayValues[vocodec::knobPage * 5 + 4]);
		switch (vocodec::knobPage) {
		case 0:
			switch (vocodec::currentPreset) {
			case 0:
				*processor.vocoder_noiseThreshold = sliderValue;
			case 1:
				*processor.vocoderCh_noiseThreshold = sliderValue;
			case 2:
				*processor.pitchShift_range = sliderValue;
			case 3:
				*processor.autotuneMono_hysteresis = sliderValue;
			case 5:
				*processor.samplerButtonPress_crossfade = sliderValue;
			case 6:
				*processor.samplerKeyboard_loopOn = sliderValue;
			case 8:
				*processor.distortion_postGain = sliderValue;
			case 10:
				*processor.bitCrusher_postGain = sliderValue;
			case 11:
				*processor.delay_feedback = sliderValue;
			case 12:
				*processor.reverb_fBGain = sliderValue;
			case 13:
				*processor.reverb2_peakGain = sliderValue;
			case 14:
				*processor.livingString_pickPos = sliderValue;
			case 15:
				*processor.livingStringSynth_pickPos = sliderValue;
			case 16:
				*processor.classicSynth_filterQ = sliderValue;
			case 17:
				*processor.rhodes_panSpread = sliderValue;
			}
		case 1:
			switch (vocodec::currentPreset) {
			case 1:
				*processor.vocoderCh_speed = sliderValue;
			case 15:
				*processor.livingStringSynth_fBLevel = sliderValue;
			case 16:
				*processor.classicSynth_leak = sliderValue;
			case 17:
				*processor.rhodes_leak = sliderValue;
			}
		case 3:
			switch (vocodec::currentPreset) {
			case 1:
				*processor.vocoderCh_barkPull = sliderValue;
			case 14:
				*processor.livingString_freq6 = sliderValue;
			case 16:
				*processor.classicSynth_fLeak = sliderValue;
			case 17:
				*processor.rhodes_index5 = sliderValue;
			}
		case 4:
			*processor.rhodes_ratio5 = sliderValue;
		case 5:
			*processor.rhodes_randSust = sliderValue;
		}
	}
	else if (slider == dials[6]) {
		processor.interpVal = slider->getValue();
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
		if (button == buttons[3]) {
			vocodec::buttonActionsSFX[3][vocodec::ActionRelease] = true;
		}
		if (button == buttons[4]) {
			vocodec::buttonActionsSFX[4][vocodec::ActionRelease] = true;
		}
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
		if (button == buttons[0])
			vocodec::buttonActionsSFX[0][vocodec::ActionRelease] = true;
		if (button == buttons[1])
			vocodec::buttonActionsSFX[1][vocodec::ActionRelease] = true;
		if (button == buttons[2])
			vocodec::buttonActionsSFX[2][vocodec::ActionRelease] = true;
		if (button == buttons[3]) {
			vocodec::buttonActionsSFX[3][vocodec::ActionRelease] = true;
		}
		if (button == buttons[4]) {
			vocodec::buttonActionsSFX[4][vocodec::ActionRelease] = true;
		}
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
    else if (button->getState() == Button::ButtonState::buttonDown) {
        if (button == buttons[0])
            vocodec::buttonActionsSFX[0][vocodec::ActionPress] = true;
		if (button == buttons[1]) {
			//vocodec::buttonActionsSFX[1][vocodec::ActionPress] = true;
			if (processor.presetNumber > 1) {
				menu.setSelectedId(processor.presetNumber - 1, dontSendNotification);
			}
			else {
				menu.setSelectedId(18, dontSendNotification);
			}
			presetChanged();
		}
		if (button == buttons[2]) {
			//vocodec::buttonActionsSFX[2][vocodec::ActionPress] = true;
			if (processor.presetNumber < 18) {
				menu.setSelectedId(processor.presetNumber + 1, dontSendNotification);
			}
			else {
				menu.setSelectedId(1, dontSendNotification);
			}
			presetChanged();
		}
		if (button == buttons[3])
			vocodec::decrementPage();
            //vocodec::buttonActionsSFX[3][vocodec::ActionPress] = true;
		if (button == buttons[4])
			vocodec::incrementPage();
            //vocodec::buttonActionsSFX[4][vocodec::ActionPress] = true;

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
	lightStates[6] = (bool) onOFF;
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
    vocodec::currentPreset = vocodec::VocodecPresetType(processor.presetNumber - 1);
}
