#ifndef GUI_APP_EXAMPLE_PLAYLISTCOMPONENT_H
#define GUI_APP_EXAMPLE_PLAYLISTCOMPONENT_H

#include <JuceHeader.h>
#include <vector>
#include <string>

class PlaylistComponent : public juce::Component,
                          public TableListBoxModel,
                          public Button::Listener
{
public:

    PlaylistComponent();
    ~PlaylistComponent() override;

    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

    //================ TableListBoxModel pure virtual functions ================
    int getNumRows() override;
    void paintRowBackground(Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                       Component *existingComponentToUpdate) override;

    //================ Button::Listener pure virtual functions ================
    void buttonClicked(Button* button) override;

private:
    TableListBox tableComponent;
    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};


#endif //GUI_APP_EXAMPLE_PLAYLISTCOMPONENT_H
