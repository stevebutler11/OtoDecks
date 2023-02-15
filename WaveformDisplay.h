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

    //================ Component functions ================
    void mouseDown(const MouseEvent &event) override;
    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ ChangeListener pure virtual functions ================
    void changeListenerCallback(ChangeBroadcaster *source) override;

private:
    DJAudioPlayer* player;
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position{0.0};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};

#endif //GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H
