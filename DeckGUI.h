#ifndef GUI_APP_EXAMPLE_DECKGUI_H
#define GUI_APP_EXAMPLE_DECKGUI_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Jogwheel.h"
#include "TrackInfoDisplay.h"
#include "DeckButton.h"

/**
 * A class to represent the graphical user interface of a DJ deck
 */
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public DragAndDropTarget,
                public Timer {
public:
    /**
     * DeckGUI constructor
     * @param player instance of the DJAudioPlayer handling audio for the DJ deck
     * @param formatManagerToUse keeps a list of available audio formats, and decides which one to use to open a given file
     * @param cacheToUse used to manage multiple AudioThumbnail objects
     */
    DeckGUI(DJAudioPlayer *player,
            AudioFormatManager &formatManagerToUse,
            AudioThumbnailCache &cacheToUse);

    /**
     * DeckGUI destructor
     */
    ~DeckGUI() override;

    /**
     * Loads a file into the DJ deck
     * @param file Represents a local file or directory
     */
    void loadFile(File &file);

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

    //================ Button pure virtual functions ================

    /**
     * Called when the button is clicked
     * @param button Button pointer
     */
    void buttonClicked(Button *button) override;

    //================ Slider pure virtual functions ================

    /**
     * Called when the slider's value is changed
     * @param slider Slider pointer
     */
    void sliderValueChanged(Slider *slider) override;

    //================ FileDragAndDropTarget pure virtual functions ================

    /**
     * Callback to check whether this target is interested in the set of files being offered
     * @param files the set of (absolute) pathnames of the files that the user is dragging
     * @return true if this component wants to receive the other callbacks regarding this type of object;
     * if it returns false, no other callbacks will be made
     */
    bool isInterestedInFileDrag(const StringArray &files) override;

    /**
     * Callback to indicate that the user has dropped the files onto this component
     * @param files the set of (absolute) pathnames of the files that the user is dragging
     * @param x the mouse x position, relative to this component
     * @param y the mouse y position, relative to this component
     */
    void filesDropped(const StringArray &files, int x, int y) override;

    //================ DragAndDropTarget pure virtual functions ================

    /**
     * Callback to check whether this target is interested in the type of object being dragged
     * @param dragSourceDetails contains information about the source of the drag operation
     * @return true if this component wants to receive the other callbacks regarding this type of object;
     * if it returns false, no other callbacks will be made
     */
    bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override;

    /**
     * Callback to indicate that the user has dropped something onto this component
     * @param dragSourceDetails contains information about the source of the drag operation
     */
    void itemDropped(const SourceDetails &dragSourceDetails) override;

    //================ Timer pure virtual functions ================

    /**
     * The user-defined callback routine that actually gets called periodically
     */
    void timerCallback() override;

private:

    /**
     * sets the correct formatting for the labels on the deck
     * @param label Label instance to be formatted
     * @param text Text to be set on the label
     */
    void formatLabel(Label &label, std::string text);

    // custom deck buttons to control playback of audio on DJ deck
    DeckButton playPauseButton{"", Colour::fromString("#FF00CC00"), true};
    DeckButton cueButton{"CUE", Colour::fromString("#FFE67300")};

    // slider to control the tempo of the track being played on the deck
    Slider tempoSlider{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};

    // label for the tempo slider
    Label tempoLabel;

    // shared pointer for the tempo value of the audio on the deck
    std::shared_ptr<double> tempoVal = std::make_shared<double>(1.0);

    // pointer to the instance of the DJAudioPlayer handling audio for the DJ deck
    DJAudioPlayer *player;

    // Component to quickly control the tempo of the track, aids the DJ in beat matching
    Jogwheel jogWheel{player, tempoVal};

    // Creates a dialog box to choose a file or directory to load or save
    FileChooser fChooser{"Select a file..."};

    // Component to display the information of the current track on the deck
    TrackInfoDisplay trackInfoDisplay;

    // Component to display the Waveform of the current track on the deck
    WaveformDisplay waveformDisplay;

    // constant for the rate the timer callback fires
    const int TIMER_INTERVAL = 100;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

#endif //GUI_APP_EXAMPLE_DECKGUI_H
