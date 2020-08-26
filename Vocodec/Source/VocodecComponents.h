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
    
    void setBounds (float x, float y, float w, float h);
    void setBounds (Rectangle<float> newBounds);
    
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
class VocodecLight : public Component,
public SettableTooltipClient
{
public:
    
    VocodecLight(const String& name,
                 Colour normalColour,
                 Colour onColour);
    ~VocodecLight() override;
    
    void setBounds (float x, float y, float d);
    void setBounds (Rectangle<float> newBounds);
    
    void setState (bool state);
    void setBrightness (float newBrightness);
    
    void paint (Graphics &g) override;
    
private:
    
    Colour normalColour, onColour;
    bool isOn;
    float brightness;
    float lightSize;
    
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecScreen)
};

//==============================================================================

class VocodecLookAndFeel : public LookAndFeel_V4
{
public:
    VocodecLookAndFeel()
    {
        setColour(ComboBox::backgroundColourId, Colours::black);
        setColour(ComboBox::textColourId, Colours::white);
        setColour(ComboBox::buttonColourId, Colours::black);
        setColour(ComboBox::outlineColourId, Colours::white);
        setColour(ComboBox::arrowColourId, Colours::white);
        
        setColour(PopupMenu::backgroundColourId, Colours::black);
        setColour(PopupMenu::textColourId, Colours::white);
    }
    
    ~VocodecLookAndFeel()
    {
    }
    
    Font getPopupMenuFont (void) override
    {
        Typeface::Ptr tp = Typeface::createSystemTypefaceFor(BinaryData::EuphemiaCAS_ttf,
                                                             BinaryData::EuphemiaCAS_ttfSize);
        Font font (tp);
        
        return Font(tp);
    }
    
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        Array<Colour> colours{ Colour(117, 117, 117), Colour(136, 136, 137), Colour(140, 139, 139), Colour(168, 167, 167), Colour(166, 163, 163), Colour(208, 208, 208), Colour(207, 207, 207) };
        //auto colorOne = Colour(117, 117, 117);
        
        Path p;
        auto pointerLength = fmax(radius * 0.33f, 3.0f);
        auto pointerThickness = pointerLength > 3.0f ? 2.0f : 1.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
        g.setColour(Colours::dimgrey);
        
        float b = fmin(fmax(rw * 0.05f, 1.0f), 2.0f);
        g.fillEllipse(rx - b, ry - b, rw + b*2, rw + b*3);
        g.setColour(Colours::white);
        g.fillEllipse(rx, ry, rw, rw);
        g.setColour(Colours::black);
        g.fillPath(p);
    }
    
    void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
                            const bool isSeparator, const bool isActive,
                            const bool isHighlighted, const bool isTicked,
                            const bool hasSubMenu, const String& text,
                            const String& shortcutKeyText,
                            const Drawable* icon, const Colour* const textColourToUse) override
    {
        if (isSeparator)
        {
            auto r  = area.reduced (5, 0);
            r.removeFromTop (roundToInt ((r.getHeight() * 0.5f) - 0.5f));
            
            g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.3f));
            g.fillRect (r.removeFromTop (1));
        }
        else
        {
            auto textColour = (textColourToUse == nullptr ? findColour (PopupMenu::textColourId)
                               : *textColourToUse);
            
            auto r  = area.reduced (1);
            
            if (isHighlighted && isActive)
            {
                g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
                g.fillRect (r);
                
                g.setColour (findColour (PopupMenu::highlightedTextColourId));
            }
            else
            {
                g.setColour (textColour.withMultipliedAlpha (isActive ? 1.0f : 0.5f));
            }
            
            r.reduce (jmin (5, area.getWidth() / 20), 0);
            
            auto font = getPopupMenuFont();
            
            const auto maxFontHeight = r.getHeight() / 1.2f;
            
            if (font.getHeight() > maxFontHeight)
                font.setHeight (maxFontHeight);
            
            g.setFont (font);
            
            auto iconArea = r.removeFromRight (roundToInt (maxFontHeight)).toFloat();
            
            if (icon != nullptr)
            {
                icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
            }
            else if (isTicked)
            {
                const auto tick = getTickShape (1.0f);
                g.fillPath (tick, tick.getTransformToScaleToFit (iconArea.reduced (iconArea.getWidth() / 5, 0).toFloat(), true));
            }
            
            if (hasSubMenu)
            {
                const auto arrowH = 0.6f * getPopupMenuFont().getAscent();
                
                const auto x = (float) r.removeFromRight ((int) arrowH).getX();
                const auto halfH = (float) r.getCentreY();
                
                Path path;
                path.startNewSubPath (x, halfH - arrowH * 0.5f);
                path.lineTo (x + arrowH * 0.6f, halfH);
                path.lineTo (x, halfH + arrowH * 0.5f);
                
                g.strokePath (path, PathStrokeType (2.0f));
            }
            
            r.removeFromRight (3);
            g.drawFittedText (text, r, Justification::centredLeft, 1);
            
            if (shortcutKeyText.isNotEmpty())
            {
                auto f2 = font;
                f2.setHeight (f2.getHeight() * 0.75f);
                f2.setHorizontalScale (0.95f);
                g.setFont (f2);
                g.drawText (shortcutKeyText, r, Justification::centredLeft, true);
            }
        }
    }
};

