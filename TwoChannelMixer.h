#ifndef GUI_APP_EXAMPLE_TWOCHANNELMIXER_H
#define GUI_APP_EXAMPLE_TWOCHANNELMIXER_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class TwoChannelMixer : public Component,
                        public Slider::Listener
{
public:
    TwoChannelMixer(DJAudioPlayer* leftPlayer, DJAudioPlayer* rightPlayer);
    ~TwoChannelMixer() override;

    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ Slider pure virtual functions ================
    void sliderValueChanged(Slider *slider) override;

private:

    static void formatLabel(Label& label, std::string text);

    DJAudioPlayer* leftPlayer;
    DJAudioPlayer* rightPlayer;
    Slider leftDeckVolume{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};
    Slider rightDeckVolume{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};
    Slider crossfader{Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::NoTextBox};
    Label leftVolLabel, rightVolLabel;
    Label crossfaderLabel;
};
#endif //GUI_APP_EXAMPLE_TWOCHANNELMIXER_H
