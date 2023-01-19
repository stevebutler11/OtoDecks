#ifndef GUI_APP_EXAMPLE_DECKGUI_H
#define GUI_APP_EXAMPLE_DECKGUI_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget
{
public:
    explicit DeckGUI(DJAudioPlayer* player,
                     AudioFormatManager &formatManagerToUse,
                     AudioThumbnailCache &cacheToUse);
    ~DeckGUI() override;

    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ Button pure virtual functions ================
    void buttonClicked(Button *) override;

    //================ Slider pure virtual functions ================
    void sliderValueChanged(Slider *slider) override;

    //================ FileDragAndDropTarget pure virtual functions ================
    bool isInterestedInFileDrag(const StringArray &files) override;
    void filesDropped(const StringArray &files, int x, int y) override;
private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};

    juce::Slider volumeSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJAudioPlayer* player;

    juce::FileChooser fChooser{"Select a file..."};

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

#endif //GUI_APP_EXAMPLE_DECKGUI_H
