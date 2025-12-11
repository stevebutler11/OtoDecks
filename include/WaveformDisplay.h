#ifndef GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H
#define GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/**
 * A class to display the waveform of the audio track on the DJ deck
 */
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener {
public:

    /**
     * WaveformDisplay constructor
     * @param player handles the audio functionality of the DJ deck
     * @param formatManagerToUse keeps a list of available audio formats, and decides which one to use to open a given file
     * @param cacheToUse used to manage multiple AudioThumbnail objects
     */
    WaveformDisplay(DJAudioPlayer *player,
                    AudioFormatManager &formatManagerToUse,
                    AudioThumbnailCache &cacheToUse);

    /**
     * WaveformDisplay destructor
     */
    ~WaveformDisplay() override;

    /**
     * Loads the given URL into the audioThumbnail
     * @param audioURL Represents a URL
     */
    void loadURL(const URL &audioURL);

    /**
     * set the relative position of the playhead
     * @param pos relative position
     */
    void setPositionRelative(double pos);

    /**
     * gets the relative cue position set on the waveform of the track
     * @return relative position of the cue
     */
    double getCuePositionRelative() const;

    //================ Component override functions ================

    /**
     * Called when a mouse button is pressed
     * @param event Contains position and status information about a mouse event
     */
    void mouseDown(const MouseEvent &event) override;

    /**
     * Called when the mouse-wheel is moved
     * @param event Contains position and status information about a mouse event
     * @param wheel Contains status information about a mouse wheel event
     */
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

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

    //================ ChangeListener pure virtual functions ================

    /**
     * implement this method to receive the callback
     * @param source the ChangeBroadcaster that triggered the callback
     */
    void changeListenerCallback(ChangeBroadcaster *source) override;

private:

    /**
     * Gets the ratio: current mouse X position / component width
     * @return mouse width ratio
     */
    double getMouseWidthRatio();

    /**
     * Gets the track width ratio
     * @return track width ratio
     */
    double getTrackWidthRatio();

    /**
     * performs a linear mathematical map of a value from one range to another
     * @param x value to map
     * @param lowCurrent lower value of current range
     * @param highCurrent higher value of current range
     * @param lowTarget lower value of the range intended to map to
     * @param highTarget higher value of the range intended to map to
     * @return mapped value
     */
    static double map(double x, double lowCurrent, double highCurrent, double lowTarget, double highTarget);

    // handles the audio functionality of a DJ deck
    DJAudioPlayer *player;

    // keeps a list of available audio formats, and decides which one to use to open a given file
    AudioThumbnail audioThumbnail;

    // boolean representing whether the file has loaded
    bool fileLoaded;

    // current track position
    double position{0.0};

    // current cue position
    double cuePosition{0.0};

    // fator to multiply by when zoom is enabled
    double zoomFactor{0.0};

    // the amount to offset the waveform from the left when zooming
    double leftWidthOffset{0.0};

    // the amount to offset the waveform from the right when zooming
    double rightWidthOffset{0.0};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};

#endif //GUI_APP_EXAMPLE_WAVEFORMDISPLAY_H
