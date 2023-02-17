#ifndef GUI_APP_EXAMPLE_DECKGUI_H
#define GUI_APP_EXAMPLE_DECKGUI_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Jogwheel.h"

class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public DragAndDropTarget,
                public juce::Timer
{
public:
    explicit DeckGUI(DJAudioPlayer* player,
                     AudioFormatManager &formatManagerToUse,
                     AudioThumbnailCache &cacheToUse);
    ~DeckGUI() override;

    void loadFile(File& file);

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

    //================ DragAndDropTarget pure virtual functions ================
    bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override;
    void itemDropped(const SourceDetails &dragSourceDetails) override;

    //================ Timer pure virtual functions ================
    void timerCallback() override;
private:
    juce::TextButton playPauseButton{"PLAY/PAUSE"};
//    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};

    juce::Slider volumeSlider;
    juce::Slider speedSlider{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};
    std::shared_ptr<double> pitchVal = std::make_shared<double>(1.0);

    DJAudioPlayer* player;

    Jogwheel jogWheel{player, pitchVal};

    juce::FileChooser fChooser{"Select a file..."};

    WaveformDisplay waveformDisplay;

    int TIMER_INTERVAL = 100;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

#endif //GUI_APP_EXAMPLE_DECKGUI_H
