#ifndef GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H
#define GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H

#include "CustomLookAndFeel.h"

class JogwheelLookAndFeel : public CustomLookAndFeel {
public:
    JogwheelLookAndFeel();
    ~JogwheelLookAndFeel();
private:
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
};

#endif //GUI_APP_EXAMPLE_JOGWHEELLOOKANDFEEL_H
