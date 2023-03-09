#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
//#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "LibraryComponent.h"
#include "DeckLoader.h"
#include "CustomLookAndFeel.h"
#include "TwoChannelMixer.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public AudioAppComponent,
                      public DragAndDropContainer
{
public:

    /**
     * MainComponent constructor
     */
    MainComponent();

    /**
     * MainComponent destructor
     */
    ~MainComponent() override;

    //================ AudioAppComponent pure virtual functions ================

    /**
     * Tells the source to prepare for playing
     * @param samplesPerBlockExpected the number of samples that the source will be expected to supply
     * @param sampleRate the sample rate that the output will be used at
     */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    /**
     * Called repeatedly to fetch subsequent blocks of audio data
     * @param bufferToFill
     */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;

    /**
     * Allows the source to release anything it no longer needs after playback has stopped
     */
    void releaseResources() override;

    //================ Component pure virtual functions ================

    /**
     * Components can override this method to draw their content
     * @param g the graphics context that must be used to do the drawing operations
     */
    void paint (Graphics& g) override;

    /**
     * Called when this component's size has been changed
     */
    void resized() override;

private:
    // Custom implementation of the Look&FeelV4 class
    CustomLookAndFeel customLookAndFeel;

    // A class for keeping a list of available audio formats
    AudioFormatManager formatManager;

    // Used to manage multiple AudioThumbnail objects
    AudioThumbnailCache thumbnailCache{100};

    // Handles the audio for a dj deck
    DJAudioPlayer player1{formatManager};

    // Class to represent a DJ deck
    DeckGUI deckGUI1{&player1, formatManager, thumbnailCache};

    // Handles the audio for a dj deck
    DJAudioPlayer player2{formatManager};

    // Class to represent a DJ deck
    DeckGUI deckGUI2{&player2, formatManager, thumbnailCache};

    // Instance of a class that represents a two channel mixer in the application
    TwoChannelMixer twoChannelMixer{&player1, &player2};

    // Mixes together the output of a set of other AudioSources
    MixerAudioSource mixerSource;

    // Aids the loading of audio to each deck from the library
    DeckLoader deckLoader{&deckGUI1, &deckGUI2};

    // Represents the music library, to store & manage audio tracks
    LibraryComponent libraryComponent{formatManager, deckLoader};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
