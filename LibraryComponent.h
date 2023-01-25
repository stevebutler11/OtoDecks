#ifndef GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
#define GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "LibraryAudioItem.h"
#include "DeckLoader.h"
#include "XmlParser.h"

class LibraryComponent : public Component,
                         public TableListBoxModel,
                         public Button::Listener,
                         public FileDragAndDropTarget
{
public:

    LibraryComponent(juce::AudioFormatManager& _formatManager, DeckLoader& deckLoader);
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
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;
    var getDragSourceDescription(const SparseSet< int > &rowsToDescribe) override;

    //================ Button::Listener pure virtual functions ================
    void buttonClicked(Button* button) override;

    //================ FileDragAndDropTarget pure virtual functions ================
    bool isInterestedInFileDrag(const StringArray &files) override;
    void filesDropped(const StringArray &files, int x, int y) override;

private:
    void addFileToLibrary(File& file);
    void loadXmlFile();
    void saveToXmlFile();
    FileChooser fChooser{"Select file(s)...", File(), "*.mp3"};
    AudioFormatManager& formatManager;
    DeckLoader deckloader;
    TableListBox tableComponent;
    std::vector<LibraryAudioItem> libraryItems;
    TextButton addItemsButton{"+ ADD TO LIBRARY"};
    File xmlFile = File(XmlParser::PERSISTENT_DATA_FILEPATH);
    Label inputText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};


#endif //GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
