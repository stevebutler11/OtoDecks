#ifndef GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H
#define GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener
{
public:
    WaveformDisplay(DJAudioPlayer* player,
                    AudioFormatManager &formatManagerToUse,
                    AudioThumbnailCache &cacheToUse);
    ~WaveformDisplay() override;

    void loadURL(URL audioURL);

    /**
     * set the relative position of the playhead
     * @param pos
     */
    void setPositionRelative(double pos);

    /**
     * gets the relative cue position set on the waveform of the track
     * @return
     */
    double getCuePositionRelative();

    //================ Component functions ================
    void mouseDown(const MouseEvent &event) override;
    void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) override;
    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ ChangeListener pure virtual functions ================
    void changeListenerCallback(ChangeBroadcaster *source) override;

private:

    double getMouseWidthRatio();

    DJAudioPlayer* player;
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position{0.0};
    double cuePosition{0.0};
    double audioZoomOffset{0.0};
    double leftWidthOffset{0.0};
    double rightWidthOffset{0.0};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};

#endif //GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H
