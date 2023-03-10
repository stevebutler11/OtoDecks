#ifndef GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H
#define GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H

#include <JuceHeader.h>

/**
 * Overrides the LookAndFeel_V4 class to create a custom theme for the application
 */
class CustomLookAndFeel : public LookAndFeel_V4 {
public:

    /**
     * CustomLookAndFeel constructor
     */
    CustomLookAndFeel();

    /**
     * CustomLookAndFeel destructor
     */
    ~CustomLookAndFeel() override;

    //================ LookAndFeel_V4 override functions ================

    /**
     * Overrides the function to draw linear sliders
     * @param g JUCE Graphics instance
     * @param x x pos of linear slider
     * @param y y pos of linear slider
     * @param width width of linear slider
     * @param height height of linear slider
     * @param sliderPos starting position of the slider
     * @param minSliderPos lowest value of slider
     * @param maxSliderPos highest value of slider
     * @param style style of the slider
     * @param slider reference to the slider itself
     */
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos,
                          float maxSliderPos, const Slider::SliderStyle style, Slider &slider) override;

private:
};

#endif //GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H
