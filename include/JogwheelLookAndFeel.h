#ifndef GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H
#define GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H

#include "CustomLookAndFeel.h"

/**
 * Overrides the CustomLookAndFeel class to create a custom rotary slider graphic
 */
class JogwheelLookAndFeel : public CustomLookAndFeel {
public:

    /**
     * JogwheelLookAndFeel constructor
     */
    JogwheelLookAndFeel();

    /**
     * JogwheelLookAndFeel destructor
     */
    ~JogwheelLookAndFeel();

private:

    /**
     * Overrides the function to draw the rotary slider
     * @param g JUCE Graphics instance
     * @param x x pos of slider
     * @param y y pos of slider
     * @param width width of slider
     * @param height height of slider
     * @param sliderPos starting position of the slider
     * @param rotaryStartAngle starting angle of the slider
     * @param rotaryEndAngle end angle of the slider
     * @param slider reference to the slider itself
     */
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override;
};

#endif //GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H
