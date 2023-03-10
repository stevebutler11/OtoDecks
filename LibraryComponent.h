#ifndef GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
#define GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "LibraryAudioItem.h"
#include "DeckLoader.h"
#include "XmlParser.h"
#include "SearchComponent.h"

/**
 * A class that represents the library portion of the DJ application.
 * The component displays audio tracks to be played, and facilitates loading to the decks and management of the files,
 * including persisting the files when the application is exited and re-started
 */
class LibraryComponent : public Component,
                         public TableListBoxModel,
                         public Button::Listener,
                         public FileDragAndDropTarget,
                         public ChangeListener {
public:

    /**
     * LibraryComponent constructor
     * @param _formatManager keeps a list of available audio formats, and decides which one to use to open a given file
     * @param deckLoader Aids the loading of audio to each deck from the library
     */
    LibraryComponent(AudioFormatManager &_formatManager, DeckLoader &deckLoader);

    /**
     * LibraryComponent destructor
     */
    ~LibraryComponent() override;

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

    //================ TableListBoxModel pure virtual functions ================

    /**
     * Return the number of rows currently in the table
     * @return the number of rows currently in the table
     */
    int getNumRows() override;

    /**
     * Draws the background behind one of the rows in the table
     * @param rowNumber the row number
     * @param width width of the row
     * @param height height of the row
     * @param rowIsSelected boolean representing whether the row is currently selected
     */
    void paintRowBackground(Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;

    /**
     * Draws one of the cells
     * @param rowNumber the row number
     * @param columnId if of the column the cell belongs to
     * @param width width of the row
     * @param height height of the row
     * @param rowIsSelected boolean representing whether the row is currently selected
     */
    void paintCell(Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    /**
     * Creates or updates a custom component to go in a cell
     * @param rowNumber the row number
     * @param columnId if of the column the cell belongs to
     * @param isRowSelected boolean representing whether the row is currently selected
     * @param existingComponentToUpdate If this is non-null, it will be a pointer to a component previously created by this method
     * @return a JUCE component
     */
    Component *refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                       Component *existingComponentToUpdate) override;

    /**
     * Re-sorts the table using the given column as the key
     * @param newSortColumnId new sort column ID
     * @param isForwards boolean denoting the direction to specify the order
     */
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;

    /**
     * Allows rows from the table to be dragged-and-dropped
     * @param rowsToDescribe Sparse set of integers representing rows selected
     * @return variant class that can be used to hold a range of primitive values
     */
    var getDragSourceDescription(const SparseSet<int> &rowsToDescribe) override;

    //================ Button::Listener pure virtual functions ================

    /**
     * Called when the button is clicked
     * @param button Button pointer
     */
    void buttonClicked(Button *button) override;

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

    //================ ChangeListener pure virtual functions ================

    /**
     * implement this method to receive the callback
     * @param source the ChangeBroadcaster that triggered the callback
     */
    void changeListenerCallback(ChangeBroadcaster *source) override;

private:

    /**
     * Add a file to the library component
     * @param file Represents a local file or directory
     */
    void addFileToLibrary(File &file);

    /**
     * Attempts to load the XML file containing files for persistence
     */
    void loadXmlFile();

    /**
     * Attempts to save library file data to an xml file for persistence
     */
    void saveToXmlFile();

    // Creates a dialog box to choose a file or directory to load or save
    FileChooser fChooser{"Select file(s)...", File(), "*.mp3"};

    // A class for keeping a list of available audio formats
    AudioFormatManager &formatManager;

    // Aids the loading of audio to each deck from the library
    DeckLoader deckloader;

    // A table of cells, using a TableHeaderComponent as its header
    TableListBox tableComponent;

    // Shared pointer to a vector of LibraryAudioItems
    std::shared_ptr<std::vector<LibraryAudioItem>> libraryItems = std::make_shared<std::vector<LibraryAudioItem>>();

    // Add items button
    TextButton addItemsButton{"+ ADD TO LIBRARY"};

    // File to be used for data persistence
    File xmlFile = File(XmlParser::PERSISTENT_DATA_FILEPATH);

    // component that implements search functionality
    SearchComponent searchComponent{libraryItems};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LibraryComponent)
};


#endif //GUI_APP_EXAMPLE_LIBRARYCOMPONENT_H
