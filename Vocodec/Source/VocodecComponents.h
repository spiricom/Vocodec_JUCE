/*
  ==============================================================================

    VocodecComponents.h
    Created: 20 Aug 2020 4:43:30pm
    Author:  Matthew Wang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
// Copy of juce::ShapeButton in case we want to change/add things
class VocodecButton  : public Button
{
public:
    
    VocodecButton (const String& name,
                 Colour normalColour,
                 Colour overColour,
                 Colour downColour);
    
    /** Destructor. */
    ~VocodecButton() override;
    
    void setShape (const Path& newShape,
                   bool resizeNowToFitThisShape,
                   bool maintainShapeProportions,
                   bool hasDropShadow);
    
    void setColours (Colour normalColour,
                     Colour overColour,
                     Colour downColour);
    
    
    void setOnColours (Colour normalColourOn,
                       Colour overColourOn,
                       Colour downColourOn);
    
    void shouldUseOnColours (bool shouldUse);
    
    void setOutline (Colour outlineColour, float outlineStrokeWidth);

    void setBorderSize (BorderSize<int> border);
    
    void paintButton (Graphics&, bool, bool) override;
    
private:
    
    Colour normalColour,   overColour,   downColour,
    normalColourOn, overColourOn, downColourOn, outlineColour;
    bool useOnColours;
    DropShadowEffect shadow;
    Path shape;
    BorderSize<int> border;
    bool maintainShapeProportions;
    float outlineWidth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecButton)
};

//==============================================================================
class VocodecLight : public Component
{
public:
    
    VocodecLight(const String& name,
                 Colour normalColour,
                 Colour onColour);
    ~VocodecLight() override;
    
    void setBounds (int x, int y, int d);
    void setBounds (Rectangle<int> newBounds);
    
    void setState (bool state);
    void setBrightness (float newBrightness);
    
    void paint (Graphics &g) override;

private:
    
    Colour normalColour, onColour;
    bool isOn;
    float brightness;
    int lightSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecLight)
};

//==============================================================================
class VocodecScreen : public Component
{
public:
    
    VocodecScreen(const String& name,
                  Colour backgroundColour,
                  Colour textColour,
                  Font font);
    ~VocodecScreen() override;
    
    void paint (Graphics &g) override;
    
    
    
private:
    
    ComboBox presetCB;
    Label pageLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecScreen)
};
