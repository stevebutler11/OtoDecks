#ifndef GUI_APP_EXAMPLE_JOGWHEEL_H
#define GUI_APP_EXAMPLE_JOGWHEEL_H

#include "JuceHeader.h"
#include "DJAudioPlayer.h"
#include "JogwheelLookAndFeel.h"

/**
 * A class to represent the jog wheel of a DJ deck. These are commonplace on real DJ decks, and aid the user in quickly
 * changing the tempo of the track
 */
class Jogwheel : public Component,
                 public Slider::Listener,
                 public Timer {
public:

    /**
     * Jogwheel constructor
     * @param player handles the audio functionality of the DJ deck
     * @param tempoVal value of the audio track tempo
     */
    explicit Jogwheel(DJAudioPlayer *player, std::shared_ptr<double> &tempoVal);

    /**
     * Jogwheel destructor
     */
    ~Jogwheel() override;

    //================ Component pure virtual functions ================

    /**
     * Components can override this method to draw their content
     * @param g the graphics context that must be used to do the drawing operations
     */
    void paint(Graphics &g) override;

    /**
     * Called when this component's size has been changed
     */
    void resized() override;

    //================ Slider:Listener pure virtual functions ================

    /**
     * Called when the slider's value is changed
     * @param slider Slider pointer
     */
    void sliderValueChanged(Slider *slider) override;

    //================ Slider::Listener virtual functions ================

    /**
     * Called when the slider is about to be dragged
     * @param slider A slider control for changing a value
     */
    void sliderDragStarted(Slider *slider) override;

    /**
     * Called after a drag operation has finished
     * @param slider A slider control for changing a value
     */
    void sliderDragEnded(Slider *slider) override;

    //================ Timer pure virtual functions ================

    /**
     * called periodically, in this we gradually reduce the displacement value until it meets the pitch value
     * of the deck
     */
    void timerCallback() override;

private:

    // handles the audio functionality of the DJ deck
    DJAudioPlayer *player;

    // custom LookAndFeelV4 class for the jog wheel
    JogwheelLookAndFeel jogwheelLookAndFeel;

    // rotary slider representing the jog wheel
    Slider jogWheel{Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::NoTextBox};

    // shared pointer to the value of the audio track tempo
    std::shared_ptr<double> tempoVal;

    // value to represent where the mouse is pressed down on the jogwheel
    double mouseDownStartValue = NAN;

    // value to help track the rotation count of the rotary slider
    // this is so when the slider is moved from 0 -> 1 or 1 -> 0, the tempo doesn't change the opposite way
    double prevValue{0.0};

    // how far the slider has been moved whilst pressed down
    double displacementValue{0.0};

    // number of rotations of the rotary slider whilst pressed down
    int rotationCount{0};
};

#endif //GUI_APP_EXAMPLE_JOGWHEEL_H
