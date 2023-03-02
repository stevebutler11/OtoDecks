#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
//    // midnight colour scheme
//    this->setColourScheme(LookAndFeel_V4::ColourScheme({
//        // windowBackground
//        0xff2f2f3a,
//        // widgetBackground
//        0xff191926,
//        // menuBackground
//        0xffd0d0d0,
//        // outline
//        0xff66667c,
//        // defaultText
//        0xc8ffffff,
//        // defaultFill
//        0xffd8d8d8,
//        // highlightedText
//        0xffffffff,
//        // highlightedFill
//        0xff606073,
//        // menuText
//        0xff000000
//    }));

    this->setColourScheme(LookAndFeel_V4::ColourScheme({
        // windowBackground
        0xff3C3F41,
        // widgetBackground
        0xff2B2B2B,
        // menuBackground
        0xffd0d0d0, // unchanged
        // outline
        0xff6793B3,
        // defaultText
        0xffBBBBBB,
        // defaultFill
        0xff9480C1,
        // highlightedText
        0xffffffff,
        // highlightedFill
        0x779480C1,
        // menuText
        0xffCCCCCC
    }));
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}

void CustomLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos,
                       float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), (float) y + 0.5f, sliderPos - (float) x, (float) height - 1.0f)
                                          : Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height - sliderPos)));
    }
    else
    {
        auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

        Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (slider.findColour (Slider::backgroundColourId));
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::square });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : (float) width * 0.5f,
                               slider.isHorizontal() ? (float) height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius (slider);

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
        g.setColour (slider.findColour (Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::square });

        if (! isTwoVal)
        {
            if (style == Slider::SliderStyle::LinearVertical)
            {
                auto thumbRect = Rectangle<float> (
                static_cast<float> (thumbWidth * 3),
                        static_cast<float> (thumbWidth * 2)
                ).withCentre (isThreeVal ? thumbPoint : maxPoint);

                auto cg = ColourGradient(Colour::fromString("#FF333333"),
                                         thumbRect.getX(), thumbRect.getY(),
                                         Colour::fromString("#FF333333"),
                                         thumbRect.getX(), thumbRect.getY() + thumbRect.getHeight(),
                                         false);

                cg.addColour(0.4, findColour(juce::ResizableWindow::backgroundColourId));
                cg.addColour(0.6, findColour(ListBox::ColourIds::backgroundColourId));

                g.setGradientFill(cg);
                g.fillRect(thumbRect);

                g.setColour(findColour(TextButton::ColourIds::textColourOffId));
                g.drawLine(
                        thumbRect.getX(),
                        thumbRect.getCentreY(),
                        thumbRect.getX() + (thumbWidth * 3),
                        thumbRect.getCentreY(),
                        1);
            }
            if (style == Slider::SliderStyle::LinearHorizontal)
            {
                auto thumbRect = Rectangle<float> (
                        static_cast<float> (thumbWidth * 2),
                        static_cast<float> (thumbWidth * 3)
                ).withCentre (isThreeVal ? thumbPoint : maxPoint);

                auto cg = ColourGradient(Colour::fromString("#FF333333"),
                                         thumbRect.getX(), thumbRect.getY(),
                                         Colour::fromString("#FF333333"),
                                         thumbRect.getX() + thumbRect.getWidth(), thumbRect.getY(),
                                         false);

                cg.addColour(0.4, findColour(juce::ResizableWindow::backgroundColourId));
                cg.addColour(0.6, findColour(ListBox::ColourIds::backgroundColourId));

                g.setGradientFill(cg);
                g.fillRect(thumbRect);

                g.setColour(findColour(TextButton::ColourIds::textColourOffId));
                g.drawLine(
                        thumbRect.getCentreX(),
                        thumbRect.getY(),
                        thumbRect.getCentreX(),
                        thumbRect.getY() + (thumbWidth * 3),
                        1);
            }
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin (trackWidth, (slider.isHorizontal() ? (float) height : (float) width) * 0.4f);
            auto pointerColour = slider.findColour (Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer (g, minSliderPos - sr,
                             jmax (0.0f, (float) y + (float) height * 0.5f - trackWidth * 2.0f),
                             trackWidth * 2.0f, pointerColour, 2);

                drawPointer (g, maxSliderPos - trackWidth,
                             jmin ((float) (y + height) - trackWidth * 2.0f, (float) y + (float) height * 0.5f),
                             trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer (g, jmax (0.0f, (float) x + (float) width * 0.5f - trackWidth * 2.0f),
                             minSliderPos - trackWidth,
                             trackWidth * 2.0f, pointerColour, 1);

                drawPointer (g, jmin ((float) (x + width) - trackWidth * 2.0f, (float) x + (float) width * 0.5f), maxSliderPos - sr,
                             trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
}