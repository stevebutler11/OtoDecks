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
class MainComponent : public juce::AudioAppComponent, public DragAndDropContainer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================

    CustomLookAndFeel customLookAndFeel;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache{100};

    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbnailCache};

    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbnailCache};

    TwoChannelMixer twoChannelMixer{&player1, &player2};
    MixerAudioSource mixerSource;

    DeckLoader deckLoader{&deckGUI1, &deckGUI2};
    LibraryComponent libraryComponent{formatManager, deckLoader};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
