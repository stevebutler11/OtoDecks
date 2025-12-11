#ifndef GUI_APP_EXAMPLE_SEARCHCOMPONENT_H
#define GUI_APP_EXAMPLE_SEARCHCOMPONENT_H

#include <vector>
#include <string>
#include <memory>
#include "JuceHeader.h"
#include "LibraryAudioItem.h"

/**
 * Component to facilitate the search function of the LibraryComponent.
 * Uses another vector to store filtered items and then swaps pointers, in the aim of being more efficient than creating
 * and destroying vectors
 */
class SearchComponent : public Component,
                        public ChangeBroadcaster {
public:

    /**
     * SearchComponent constructor
     * @param _libItems a shared pointer to a vector of LibraryAudioItems
     */
    explicit SearchComponent(std::shared_ptr<std::vector<LibraryAudioItem>> &_libItems);

    /**
     * SearchComponent destructor
     */
    ~SearchComponent() override;

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

private:

    /**
     * filters items in libraryItems and swaps pointers
     */
    void search();

    /**
     * swaps pointers back clears filteredItems
     */
    void clear();

    // search text box component
    Label searchBar;

    // a shared pointer to a vector of LibraryAudioItems (the contents of the library)
    std::shared_ptr<std::vector<LibraryAudioItem>> libraryItems;

    // a shared pointer to a filtered vector of LibraryAudioItems based on the search query
    std::shared_ptr<std::vector<LibraryAudioItem>> filteredItems = std::make_shared<std::vector<LibraryAudioItem>>();
};

#endif //GUI_APP_EXAMPLE_SEARCHCOMPONENT_H
