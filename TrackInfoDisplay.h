#ifndef GUI_APP_EXAMPLE_TRACKINFODISPLAY_H
#define GUI_APP_EXAMPLE_TRACKINFODISPLAY_H

#include <JuceHeader.h>

class TrackInfoDisplay : public Component, Timer
{
public:
    TrackInfoDisplay();
    ~TrackInfoDisplay() override;

    void setText(std::string trackText);
    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ Timer pure virtual functions ================
    void timerCallback() override;
private:
    void padDisplayText();
    std::string displayText{"File not loaded..."};
    float displayTextWidth{0};
    float whitespaceCharWidth{0};
    std::string paddedText{displayText};
};
#endif //GUI_APP_EXAMPLE_TRACKINFODISPLAY_H
