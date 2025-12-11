#ifndef GUI_APP_EXAMPLE_TWOCHANNELMIXER_H
#define GUI_APP_EXAMPLE_TWOCHANNELMIXER_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/**
 * A class that represents a two channel mixer on a DJ deck.
 * This will be used control the volume of the two 'channels' of the DJ setup and mix the two audio sources together
 */
class TwoChannelMixer : public Component,
                        public Slider::Listener {
public:

    /**
     * TwoChannelMixer constructor
     * @param leftPlayer a pointer to the left deck's DJAudioPlayer instance
     * @param rightPlayer a pointer to the right deck's DJAudioPlayer instance
     */
    TwoChannelMixer(DJAudioPlayer *leftPlayer, DJAudioPlayer *rightPlayer);

    /**
     * TwoChannelMixer destructor
     */
    ~TwoChannelMixer() override;

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

private:

    /**
     * Applies the correct styling to the label for the channel mixer component
     * @param label the label to be styled
     * @param text the text to add to the label
     */
    static void formatLabel(Label &label, std::string text);

    // a pointer to the left deck's DJAudioPlayer instance
    DJAudioPlayer *leftPlayer;

    // a pointer to the right deck's DJAudioPlayer instance
    DJAudioPlayer *rightPlayer;

    // slider for the left deck volume
    Slider leftDeckVolume{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};

    // slider for the right deck volume
    Slider rightDeckVolume{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};

    // slider for the deck crossfader
    Slider crossfader{Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::NoTextBox};

    // Labels for the sliders
    Label leftVolLabel, rightVolLabel, crossfaderLabel;
};

#endif //GUI_APP_EXAMPLE_TWOCHANNELMIXER_H
