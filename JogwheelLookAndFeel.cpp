#include "JogwheelLookAndFeel.h"

JogwheelLookAndFeel::JogwheelLookAndFeel()
{

}

JogwheelLookAndFeel::~JogwheelLookAndFeel()
{

}

void JogwheelLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                      float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;
    auto innerRadius = radius - lineW;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isMouseButtonDown())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                toAngle - 0.1f,
                                toAngle + 0.1f,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    auto cg = ColourGradient(outline,
                             bounds.getCentreX(), bounds.getCentreY(),
                             fill,
                             0.0,
                             0.0,
                             true);

    g.setGradientFill(cg);

    g.fillEllipse(bounds.getCentreX() - innerRadius, bounds.getCentreY()  - innerRadius,  innerRadius*2, innerRadius*2);
}