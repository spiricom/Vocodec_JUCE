/*
  ==============================================================================

    VocodecComponents.cpp
    Created: 20 Aug 2020 4:43:30pm
    Author:  Matthew Wang

  ==============================================================================
*/

#include "VocodecComponents.h"

VocodecButton::VocodecButton (const String& t, Colour n, Colour o, Colour d)
: Button (t),
normalColour   (n), overColour   (o), downColour   (d),
normalColourOn (n), overColourOn (o), downColourOn (d),
useOnColours(false),
maintainShapeProportions (false),
outlineWidth (0.0f)
{
}

VocodecButton::~VocodecButton() {}

void VocodecButton::setColours (Colour newNormalColour, Colour newOverColour, Colour newDownColour)
{
    normalColour = newNormalColour;
    overColour   = newOverColour;
    downColour   = newDownColour;
}

void VocodecButton::setOnColours (Colour newNormalColourOn, Colour newOverColourOn, Colour newDownColourOn)
{
    normalColourOn = newNormalColourOn;
    overColourOn   = newOverColourOn;
    downColourOn   = newDownColourOn;
}

void VocodecButton::shouldUseOnColours (bool shouldUse)
{
    useOnColours = shouldUse;
}

void VocodecButton::setOutline (Colour newOutlineColour, const float newOutlineWidth)
{
    outlineColour = newOutlineColour;
    outlineWidth = newOutlineWidth;
}

void VocodecButton::setBorderSize (BorderSize<int> newBorder)
{
    border = newBorder;
}

void VocodecButton::setBounds (float x, float y, float w, float h)
{
    Rectangle<float> bounds (x, y, w, h);
    Component::setBounds(bounds.toNearestInt());
}

void VocodecButton::setBounds (Rectangle<float> newBounds)
{
    Component::setBounds(newBounds.toNearestInt());
}

void VocodecButton::setShape (const Path& newShape,
                            const bool resizeNowToFitThisShape,
                            const bool maintainShapeProportions_,
                            const bool hasShadow)
{
    shape = newShape;
    maintainShapeProportions = maintainShapeProportions_;
    
    shadow.setShadowProperties (DropShadow (Colours::black.withAlpha (0.5f), 3, Point<int>()));
    setComponentEffect (hasShadow ? &shadow : nullptr);
    
    if (resizeNowToFitThisShape)
    {
        auto newBounds = shape.getBounds();
        
        if (hasShadow)
            newBounds = newBounds.expanded (4.0f);
        
        shape.applyTransform (AffineTransform::translation (-newBounds.getX(),
                                                            -newBounds.getY()));
        
        setSize (1 + (int) (newBounds.getWidth()  + outlineWidth) + border.getLeftAndRight(),
                 1 + (int) (newBounds.getHeight() + outlineWidth) + border.getTopAndBottom());
    }
    
    repaint();
}

void VocodecButton::paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setGradientFill(ColourGradient(Colour(25, 25, 25), juce::Point<float>(-getX(),-getY()), Colour(10, 10, 10), juce::Point<float>(-getX(), getParentHeight()-getY()), false));
    g.fillRect(getLocalBounds());
    
    if (! isEnabled())
    {
        shouldDrawButtonAsHighlighted = false;
        shouldDrawButtonAsDown = false;
    }
    
    auto r = border.subtractedFrom (getLocalBounds())
    .toFloat()
    .reduced (outlineWidth * 0.5f);

    if (shouldDrawButtonAsDown)
    {
        const float sizeReductionWhenPressed = 0.04f;
        
        r = r.reduced (sizeReductionWhenPressed * r.getWidth(),
                       sizeReductionWhenPressed * r.getHeight());
    }
    
    auto trans = shape.getTransformToScaleToFit (r, maintainShapeProportions);
    
    if      (shouldDrawButtonAsDown)        g.setColour (getToggleState() && useOnColours ? downColourOn   : downColour);
    else if (shouldDrawButtonAsHighlighted) g.setColour (getToggleState() && useOnColours ? overColourOn   : overColour);
    else                                    g.setColour (getToggleState() && useOnColours ? normalColourOn : normalColour);
    
    g.fillPath (shape, trans);
    
    if (outlineWidth > 0.0f)
    {
        g.setColour (outlineColour);
        g.strokePath (shape, PathStrokeType (outlineWidth), trans);
    }
}



VocodecLight::VocodecLight(const String& name, Colour normalColour, Colour onColour) :
Component(name),
normalColour(normalColour),
onColour(onColour),
isOn(false),
brightness(1.0f),
lightSize(5.0f)
{
    setPaintingIsUnclipped(true);
}

VocodecLight::~VocodecLight()
{
}

void VocodecLight::setBounds (float x, float y, float d)
{
    Rectangle<float> newBounds (x, y, d, d);
    setBounds(newBounds);
}

void VocodecLight::setBounds (Rectangle<float> newBounds)
{
    lightSize = newBounds.getWidth() * 0.25f;
    Component::setBounds(newBounds.expanded(lightSize, lightSize).toNearestInt());
}

void VocodecLight::setState (bool state)
{
    if (state == isOn) return;
    isOn = state;
    repaint();
}

void VocodecLight::setBrightness (float newBrightness)
{
    if (newBrightness == brightness) return;
    brightness = newBrightness;

    repaint();
}

void VocodecLight::paint (Graphics &g)
{
    g.setGradientFill(ColourGradient(Colour(25, 25, 25), juce::Point<float>(-getX(),-getY()), Colour(10, 10, 10), juce::Point<float>(-getX(), getParentHeight()-getY()), false));
    g.fillRect(getLocalBounds());
    
    Rectangle<float> area = getLocalBounds().toFloat();
    Rectangle<float> innerArea = area.reduced(lightSize, lightSize);
    g.setColour(normalColour.interpolatedWith(onColour, isOn ? (brightness * 0.5f) : 0.0f));
    g.fillEllipse(innerArea);
    
    if (isOn)
    {
        float r = area.getWidth() * 0.5f * (1.0f - brightness);
        g.setGradientFill(ColourGradient(onColour, innerArea.getCentre(), onColour.withAlpha(0.0f),
                                         juce::Point<float>(area.getCentreX(), area.getY() + r),
                                         true));
        g.fillEllipse(area);
    }
}





VocodecScreen::VocodecScreen(VocodecAudioProcessor& p) :
Component("VocodecScreen"),
processor(p)
{
    screenImage = std::make_unique<Image>(Image::PixelFormat::RGB, 128, 32, false);
    screen.setImage(*screenImage);
    screen.setImagePlacement(RectanglePlacement::centred);
    addAndMakeVisible(screen);

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
    menu.onChange = [this] { onChange(); };
}

VocodecScreen::~VocodecScreen()
{
    menu.setLookAndFeel(nullptr);
}

void VocodecScreen::setBounds (float x, float y, float w, float h)
{
    Rectangle<float> newBounds (x, y, w, h);
    setBounds(newBounds);
}

void VocodecScreen::setBounds (Rectangle<float> newBounds)
{
    Component::setBounds(newBounds.toNearestInt());
    
    int width = getParentWidth();
    int height = getParentHeight();
    
    Rectangle<float> area = getLocalBounds().toFloat();
    area.removeFromTop(height*0.003f);
    area.reduce(width*0.023f, height*0.011f);
    
    screen.setBounds(area.toNearestInt());
    menu.setBounds(area.removeFromTop(area.getHeight()*0.5f).toNearestInt());
}

void VocodecScreen::paint (Graphics &g)
{
    g.setGradientFill(ColourGradient(Colour(25, 25, 25), juce::Point<float>(-getX(),-getY()), Colour(10, 10, 10), juce::Point<float>(-getX(), getParentHeight()-getY()), false));
    g.fillRect(getLocalBounds());
    
    int width = getParentWidth();
    int height = getParentHeight();
    Rectangle<float> area = getLocalBounds().toFloat();
    
    g.setColour(Colours::dimgrey);
    g.fillRect(area.toNearestInt());
    g.setColour(Colours::black);
    area.removeFromTop(height*0.003f);
    g.fillRect(area.reduced(width*0.003f, height*0.001f).toNearestInt());
}

void VocodecScreen::timerCallback()
{
    const Image::BitmapData screenBitmap (*screenImage, Image::BitmapData::writeOnly);
    bool screenChanged;
    for (int x = 0; x < 128; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            bool set = (processor.vcd.buffer[x + ((y/8) * 128)] >> (y&7)) & 1;
            Colour colour = set ? Colours::white : Colour(10, 10, 10);
            if (screenBitmap.getPixelColour(x, y) != colour)
            {
                screenBitmap.setPixelColour(x, y, colour);
                screenChanged = true;
            }
        }
    }
    if (screenChanged) screen.repaint();
}

ComboBox* VocodecScreen::getMenu()
{
    return &menu;
}

