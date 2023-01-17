#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
//#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
#include "DJAudioPlayer.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent,
                      public Button::Listener,
                      public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    void loadURL(URL audioURL);

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    //==============================================================================
    void buttonClicked (Button *) override;
    void sliderValueChanged (Slider *slider) override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton playButton{"play"};
    juce::TextButton stopButton{"stop"};
//    juce::Slider gainSlider;
//    juce::Random random;
    bool playing;
    double gain;
//    float phase;
    double dphase;

    juce::Slider volumeGainSlider;
    juce::TextButton loadButton;
    juce::FileChooser fChooser{"Select a file..."};

    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJAudioPlayer player1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
