#ifndef GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H
#define GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H

#include <JuceHeader.h>

class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    //================ LookAndFeel_V4 override functions ================
    void drawLinearSlider (Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos,
                           float maxSliderPos, const Slider::SliderStyle, Slider &) override;
private:
};
#endif //GUI_APP_EXAMPLE_CUSTOMLOOKANDFEEL_H
