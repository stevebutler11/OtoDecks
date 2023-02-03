#include "SearchComponent.h"

SearchComponent::SearchComponent(std::shared_ptr<std::vector<LibraryAudioItem>>& _libItems) : libraryItems(_libItems)
{
    addAndMakeVisible(searchBar);

    searchBar.setText ("Search filenames...", juce::dontSendNotification);
    searchBar.setEditable(true, false, true);
    searchBar.onTextChange = [this] {
        if (searchBar.getText() == "")
        {
            clear();
        }
        else
        {
            search();
        }
    };
}

SearchComponent::~SearchComponent()
{

}

void SearchComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void SearchComponent::resized()
{
    searchBar.setBounds(0, 0, getWidth(), getHeight());
}

void SearchComponent::search()
{
    // if there already exists a search, clear it
    if (!filteredItems->empty())
    {
        clear();
    }

    auto searchString = searchBar.getText().toLowerCase().toStdString();

    // filter items (place them in the filteredItems vector)
    std::copy_if(
            begin(*libraryItems),
            end(*libraryItems),
            std::back_inserter(*filteredItems),
            [searchString](auto const& item){
                auto fileName = std::string{item.getFileName()};
                std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
                return (fileName.find(searchString) != std::string::npos);
            });

    // swap the libraryItems pointer to the filteredItems pointer
    libraryItems->swap(*filteredItems);
    // notify listeners
    sendChangeMessage();
}

void SearchComponent::clear()
{
    if (!filteredItems->empty())
    {
        // swap the libraryItems pointer back
        filteredItems->swap(*libraryItems);
        filteredItems->clear();
        // notify listeners
        sendChangeMessage();
    }
}
