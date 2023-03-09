#ifndef GUI_APP_EXAMPLE_DECKGUI_H
#define GUI_APP_EXAMPLE_DECKGUI_H

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Jogwheel.h"
#include "TrackInfoDisplay.h"
#include "DeckButton.h"

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

    void formatLabel(Label& label, std::string text);

    DeckButton playPauseButton{"", Colour::fromString("#FF00CC00"), true};
    DeckButton cueButton{"CUE", Colour::fromString("#FFE67300")};

    juce::Slider tempoSlider{Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox};
    Label tempoLabel;
    std::shared_ptr<double> tempoVal = std::make_shared<double>(1.0);

    DJAudioPlayer* player;

    Jogwheel jogWheel{player, tempoVal};

    juce::FileChooser fChooser{"Select a file..."};

    TrackInfoDisplay trackInfoDisplay;
    WaveformDisplay waveformDisplay;

    int TIMER_INTERVAL = 100;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};

#endif //GUI_APP_EXAMPLE_DECKGUI_H
