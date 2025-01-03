#include <algorithm>
#include "LibraryComponent.h"
#include "XmlParser.h"

LibraryComponent::LibraryComponent(AudioFormatManager &_formatManager, DeckLoader &_deckLoader
) : formatManager(_formatManager), deckloader(_deckLoader) {
    addAndMakeVisible(addItemsButton);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(searchComponent);

    addItemsButton.addListener(this);
    searchComponent.addChangeListener(this);

    tableComponent.getHeader().addColumn("Track Title", 1, 300);
    tableComponent.getHeader().addColumn("Duration", 2, 80);
    tableComponent.getHeader().addColumn("Extension", 3, 80);
    tableComponent.getHeader().addColumn("Load To Left Deck", 6, 150);
    tableComponent.getHeader().addColumn("Load To Right Deck", 7, 150);
    tableComponent.getHeader().addColumn("Remove", 8, 80);

    tableComponent.setModel(this);

    // try load persistent data
    loadXmlFile();
}

LibraryComponent::~LibraryComponent() {
    // attempt to persist the library contents before the component is destroyed
    saveToXmlFile();
    tableComponent.setModel(nullptr);
}

void LibraryComponent::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void LibraryComponent::resized() {
    // flexbox for the top row (search bar and add items button)
    FlexBox searchBarFb;
    searchBarFb.flexWrap = FlexBox::Wrap::noWrap;
    searchBarFb.justifyContent = FlexBox::JustifyContent::center;
    searchBarFb.alignContent = FlexBox::AlignContent::center;

    searchBarFb.items.addArray({
                                       FlexItem(searchComponent).withFlex(1).withMargin(FlexItem::Margin(0, 5, 0, 0)),
                                       FlexItem(addItemsButton).withFlex(1).withMaxWidth(150)
                               });

    // flexbox for the whole library component
    FlexBox libraryFb;
    libraryFb.flexWrap = FlexBox::Wrap::noWrap;
    libraryFb.justifyContent = FlexBox::JustifyContent::center;
    libraryFb.alignContent = FlexBox::AlignContent::center;
    libraryFb.flexDirection = FlexBox::Direction::column;

    libraryFb.items.addArray({
                                     FlexItem(searchBarFb).withMinHeight(30).withMaxHeight(40).withMargin(
                                             FlexItem::Margin(10, 10, 0, 10)),
                                     FlexItem(tableComponent).withFlex(10).withMargin(10)
                             });

    libraryFb.performLayout(getLocalBounds().toFloat());
}

int LibraryComponent::getNumRows() {
    return libraryItems->size();
}

void LibraryComponent::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(Colour::fromString("FFBD8E3E"));
    } else {
        g.fillAll(Colours::darkgrey);
    }
}

void LibraryComponent::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.setColour(getLookAndFeel().findColour(ListBox::ColourIds::backgroundColourId));
    switch (columnId) {
        case 1:
            g.drawText((*libraryItems)[rowNumber].getFileName(), 2, 0, width - 4, height,
                       Justification::centredLeft, true);
            break;
        case 2:
            g.drawText((*libraryItems)[rowNumber].getDurationFormatted(), 2, 0, width - 4, height,
                       Justification::centredRight, true);
            break;
        case 3:
            g.drawText((*libraryItems)[rowNumber].getExtension(), 2, 0, width - 4, height,
                       Justification::centredRight, true);
            break;
    }

}

Component *LibraryComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                                     Component *existingComponentToUpdate) {
    switch (columnId) {
        case 6:
            if (existingComponentToUpdate == nullptr) {
                auto *leftDeckBtn = new TextButton{"Load To Left Deck"};
                leftDeckBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                leftDeckBtn->setComponentID(id);

                existingComponentToUpdate = leftDeckBtn;
            }
            break;
        case 7:
            if (existingComponentToUpdate == nullptr) {
                auto *rightDeckBtn = new TextButton{"Load To Right Deck"};
                rightDeckBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                rightDeckBtn->setComponentID(id);

                existingComponentToUpdate = rightDeckBtn;
            }
            break;
        case 8:
            // if the component hasn't been created yet
            if (existingComponentToUpdate == nullptr) {
                auto *textBtn = new TextButton{"Remove"};
                textBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                textBtn->setComponentID(id);

                existingComponentToUpdate = textBtn;
            }
            break;
    }
    return existingComponentToUpdate;
}

void LibraryComponent::sortOrderChanged(int newSortColumnId, bool isForwards) {
    switch (newSortColumnId) {
        case 1:
            if (isForwards) {
                std::sort(libraryItems->begin(), libraryItems->end(), [](
                        const LibraryAudioItem &a,
                        const LibraryAudioItem &b
                ) { return a.getFileName() < b.getFileName(); });
                break;
            }
            std::sort(libraryItems->begin(), libraryItems->end(), [](
                    const LibraryAudioItem &a,
                    const LibraryAudioItem &b
            ) { return a.getFileName() > b.getFileName(); });
            break;
        case 2:
            if (isForwards) {
                std::sort(libraryItems->begin(), libraryItems->end(), [](
                        const LibraryAudioItem &a,
                        const LibraryAudioItem &b
                ) { return a.getDuration() < b.getDuration(); });
                break;
            }
            std::sort(libraryItems->begin(), libraryItems->end(), [](
                    const LibraryAudioItem &a,
                    const LibraryAudioItem &b
            ) { return a.getDuration() > b.getDuration(); });
            break;
        case 3:
            if (isForwards) {
                std::sort(libraryItems->begin(), libraryItems->end(), [](
                        const LibraryAudioItem &a,
                        const LibraryAudioItem &b
                ) { return a.getExtension() < b.getExtension(); });
                break;
            }
            std::sort(libraryItems->begin(), libraryItems->end(), [](
                    const LibraryAudioItem &a,
                    const LibraryAudioItem &b
            ) { return a.getExtension() > b.getExtension(); });
            break;
    }
}

var LibraryComponent::getDragSourceDescription(const SparseSet<int> &rowsToDescribe) {
    // only return first row as can only load one deck at a time
    if (rowsToDescribe[0] >= 0)
        return (*libraryItems)[rowsToDescribe[0]].getFile().getFullPathName();
}

void LibraryComponent::buttonClicked(Button *button) {
    if (button == &addItemsButton) {
        fChooser.launchAsync(FileBrowserComponent::canSelectMultipleItems, [this](const FileChooser &chooser) {
            auto chosenFiles = chooser.getResults();

            for (auto &file: chosenFiles) {
                // try to add the file to the current audio library collection
                try {
                    addFileToLibrary(file);
                }
                catch (const std::exception &e) {
                    std::cout << "LibraryComponent::buttonClicked: " << e.what() << std::endl;
                }
            }
            // refresh the table data to update on screen
            this->tableComponent.updateContent();
        });
    } else {
        auto rowIndex = std::stoi(button->getComponentID().toStdString());

        if (button->getButtonText() == "Remove") {
            // erase takes an iterator as an arg so offset from the beginning by rowIndex amt
            libraryItems->erase(libraryItems->begin() + rowIndex);
            // refresh the table data to update on screen
            this->tableComponent.updateContent();
        } else if (button->getButtonText() == "Load To Left Deck") {
            auto fl = (*libraryItems)[rowIndex].getFile();
            deckloader.loadLeft(fl);
        } else if (button->getButtonText() == "Load To Right Deck") {
            auto fl = (*libraryItems)[rowIndex].getFile();
            deckloader.loadRight(fl);
        }
    }
}

bool LibraryComponent::isInterestedInFileDrag(const StringArray &files) {
    return true;
}

void LibraryComponent::filesDropped(const StringArray &files, int x, int y) {
    for (auto const &fl: files) {
        auto file = File{fl};
        if (file.hasFileExtension(".mp3")) {
            // try to add the file to the current audio library collection
            try {
                addFileToLibrary(file);
            }
            catch (const std::exception &e) {
                std::cout << "LibraryComponent::filesDropped: " << e.what() << std::endl;
            }
        } else {
            std::cout << "incorrect file type" << std::endl;
        }
    }
    tableComponent.updateContent();
}

void LibraryComponent::addFileToLibrary(File &file) {
    // if file already exists in library, return
    for (auto &item: *libraryItems) {
        if (file.getFullPathName() == item.getFile().getFullPathName())
            return;
    }

    // try to create LibraryAudioItem from file
    auto *reader = formatManager.createReaderFor(file);
    auto duration = reader->lengthInSamples / reader->sampleRate;

    // delete reader as memory has been allocated for it above
    delete reader;

    auto fileName = file.getFileName().toStdString();
    auto ext = file.getFileExtension().toStdString();

    // since libAudioItem is created with make_unique, it is deleted with the current scope
    auto libAudioItem = std::make_unique<LibraryAudioItem>(
            LibraryAudioItem{file, fileName, duration, ext});

    // append to libraryItems
    libraryItems->push_back(*libAudioItem);
}

void LibraryComponent::loadXmlFile() {
    if (xmlFile.existsAsFile()) {
        try {
            XmlParser::loadXmlFile(xmlFile, *libraryItems);
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "problem loading xml file data" << std::endl;
        }
    }
}

void LibraryComponent::saveToXmlFile() {
    // if file already exists, .create() does nothing to it
    Result result = xmlFile.create();
    if (result.wasOk()) {
        try {
            XmlParser::saveXmlFile(xmlFile, *libraryItems);
        }
        catch (...) {
            std::cout << "error saving xml file" << std::endl;
        }
    } else {
        std::cout << "failed to create xml file, due to: " + result.getErrorMessage().toStdString() << std::endl;
    }
}

void LibraryComponent::changeListenerCallback(ChangeBroadcaster *source) {
    tableComponent.updateContent();
}