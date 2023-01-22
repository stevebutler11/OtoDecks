#ifndef GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
#define GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "LibraryAudioItem.h"

class LibraryComponent : public juce::Component,
                         public TableListBoxModel,
                         public Button::Listener
{
public:

    explicit LibraryComponent(juce::AudioFormatManager& _formatManager);
    ~LibraryComponent() override;

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
    void addFileToLibrary(File& file);
    juce::FileChooser fChooser{"Select file(s)...", File(), "*.mp3"};
    juce::AudioFormatManager& formatManager;
    TableListBox tableComponent;
    std::vector<LibraryAudioItem> libraryItems;
    juce::TextButton addItemsButton{"+ ADD TO LIBRARY"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};


#endif //GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
