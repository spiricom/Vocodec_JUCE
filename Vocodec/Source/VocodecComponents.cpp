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
    if (! isEnabled())
    {
        shouldDrawButtonAsHighlighted = false;
        shouldDrawButtonAsDown = false;
    }
    
    auto r = border.subtractedFrom (getLocalBounds())
    .toFloat()
    .reduced (outlineWidth * 0.5f);
    
    if (getComponentEffect() != nullptr)
        r = r.reduced (2.0f);
    
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
lightSize(4)
{
    setPaintingIsUnclipped(true);
}

VocodecLight::~VocodecLight()
{
}

void VocodecLight::setBounds (int x, int y, int d)
{
    Rectangle<int> bounds (x, y, d, d);
    Component::setBounds(bounds.expanded(lightSize, lightSize));
}

void VocodecLight::setBounds (Rectangle<int> newBounds)
{
    Component::setBounds(newBounds.expanded(lightSize, lightSize));
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
    Rectangle<float> area = getLocalBounds().toFloat();
    Rectangle<float> innerArea = area.reduced(lightSize, lightSize);
    g.setColour(normalColour);
    g.fillEllipse(innerArea);
    
    if (isOn)
    {
        float r = innerArea.getWidth() * 0.5f * (1.0f - brightness);
        g.setGradientFill(ColourGradient(onColour, innerArea.getCentre(), onColour.withAlpha(0.0f),
                                         juce::Point<float>(area.getCentreX(), area.getY() + r),
                                         true));
        g.fillEllipse(area);
    }
}
