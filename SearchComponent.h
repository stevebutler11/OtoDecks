#ifndef GUI_APP_EXAMPLE_SEARCHCOMPONENT_H
#define GUI_APP_EXAMPLE_SEARCHCOMPONENT_H

#include <vector>
#include <string>
#include <memory>
#include "JuceHeader.h"
#include "LibraryAudioItem.h"

class SearchComponent : public Component,
                        public ChangeBroadcaster
{
public:
    explicit SearchComponent(std::shared_ptr<std::vector<LibraryAudioItem>>& _libItems);
    ~SearchComponent() override;

    //================ Component pure virtual functions ================
    void paint(Graphics& g) override;
    void resized() override;

private:
    void search();
    void clear();
    Label searchBar;
    std::shared_ptr<std::vector<LibraryAudioItem>> libraryItems;
    std::shared_ptr<std::vector<LibraryAudioItem>> filteredItems = std::make_shared<std::vector<LibraryAudioItem>>();
};
#endif //GUI_APP_EXAMPLE_SEARCHCOMPONENT_H
