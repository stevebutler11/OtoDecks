#ifndef GUI_APP_EXAMPLE_TRACKINFODISPLAY_H
#define GUI_APP_EXAMPLE_TRACKINFODISPLAY_H

#include <JuceHeader.h>

/**
 * A class to display the track information on the DJ deck
 */
class TrackInfoDisplay : public Component, Timer {
public:

    /**
     * TrackInfoDisplay constructor
     */
    TrackInfoDisplay();

    /**
     * TrackInfoDisplay destructor
     */
    ~TrackInfoDisplay() override;

    /**
     * Sets the track detail text to scroll across the screen
     * @param trackText the track detail text
     */
    void setText(std::string trackText);

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

    //================ Timer pure virtual functions ================

    /**
     * The user-defined callback routine that actually gets called periodically
     */
    void timerCallback() override;

private:

    /**
     * pads the string of text with the correct amount of whitespace for the current TrackInfoDisplay width so that it
     * scrolls off of the screen smoothly
     */
    void padDisplayText();

    // The initial text (this is **NOT** adjusted for screen whitespace)
    std::string displayText{"File not loaded..."};

    // The current width of the text to be displayed (pre-padding)
    float displayTextWidth{0};

    // The width of a single whitespace character
    float whitespaceCharWidth{0};

    // The text to be displayed on screen (this is the text adjusted for screen whitespace)
    std::string paddedText{displayText};
};

#endif //GUI_APP_EXAMPLE_TRACKINFODISPLAY_H
