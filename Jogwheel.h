#ifndef GUI_APP_EXAMPLE_JOGWHEEL_H
#define GUI_APP_EXAMPLE_JOGWHEEL_H

#include "JuceHeader.h"
#include "DJAudioPlayer.h"
#include "JogwheelLookAndFeel.h"

class Jogwheel : public Component,
                 public Slider::Listener,
                 public Timer {
public:
    explicit Jogwheel(DJAudioPlayer* player, std::shared_ptr<double>& pitchVal);
    ~Jogwheel() override;

    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ Slider::Listener pure virtual functions ================
    void sliderValueChanged(Slider *slider) override;

    //================ Slider::Listener virtual functions ================
    void sliderDragStarted(Slider *) override;
    void sliderDragEnded (Slider *) override;

    //================ Timer pure virtual functions ================
    /**
     * called periodically, in this we gradually reduce the displacement value until it meets the pitch value
     * of the deck
     */
    void timerCallback() override;

private:
    DJAudioPlayer* player;
    JogwheelLookAndFeel jogwheelLookAndFeel;
    Slider jogWheel{Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::NoTextBox};
    std::shared_ptr<double> pitchVal;
    double mouseDownStartValue = NAN;
    double prevValue{0.0};
    double displacementValue{0.0};
    int rotationCount{0};
};

#endif //GUI_APP_EXAMPLE_JOGWHEEL_H
