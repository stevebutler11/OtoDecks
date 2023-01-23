#include <algorithm>
#include "LibraryComponent.h"
#include "XmlParser.h"

LibraryComponent::LibraryComponent(AudioFormatManager& _formatManager, DeckLoader& _deckLoader
                            ) : formatManager(_formatManager), deckloader(_deckLoader)
{
    addAndMakeVisible(addItemsButton);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible (inputText);

    inputText.setText ("Search filenames...", juce::dontSendNotification);
    inputText.setEditable(true, false, true);
    inputText.onTextChange = [this] {
        // TODO: eventually filter the libraryItems list with inputText.getText().toLowerCase(), though this may mean
        //  copying library items and then removing, whilst keeping original array
    };

    addItemsButton.addListener(this);

    tableComponent.getHeader().addColumn("Track Title", 1, 300);
    tableComponent.getHeader().addColumn("Duration", 2, 80);
    tableComponent.getHeader().addColumn("Extension", 3, 80);
    tableComponent.getHeader().addColumn("Key", 4, 80);
    tableComponent.getHeader().addColumn("BPM", 5, 80);
    tableComponent.getHeader().addColumn("Load To Left Deck", 6, 150);
    tableComponent.getHeader().addColumn("Load To Right Deck", 7, 150);
    tableComponent.getHeader().addColumn("Remove", 8, 80);

    tableComponent.setModel(this);

    // try load persistent data
    loadXmlFile();
}

LibraryComponent::~LibraryComponent()
{
    saveToXmlFile();
}

void LibraryComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(Colours::white);
    g.setFont(14.0f);
    g.drawText("LibraryComponent",
               getLocalBounds(),
               Justification::centred,
               true);
}

void LibraryComponent::resized()
{
    auto heightSplit = getHeight() / 8;
    auto widthSplit = getWidth()/4;
    inputText.setBounds(0, 0, 3 * widthSplit, heightSplit);
    addItemsButton.setBounds(3 * widthSplit, 0, widthSplit, heightSplit);
    tableComponent.setBounds(0, heightSplit, getWidth(), heightSplit * 7);
}

int LibraryComponent::getNumRows()
{
    return libraryItems.size();
}

void LibraryComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

void LibraryComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    switch (columnId)
    {
        case 1:
            g.drawText(libraryItems[rowNumber].getFileName(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredLeft,
                       true);
            break;
        case 2:
            g.drawText(libraryItems[rowNumber].getDurationFormatted(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredRight,
                       true);
            break;
        case 3:
            g.drawText(libraryItems[rowNumber].getExtension(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredRight,
                       true);
            break;
        case 4:
            g.drawText(libraryItems[rowNumber].getKey(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredRight,
                       true);
            break;
        case 5:
            g.drawText(String {libraryItems[rowNumber].getBPM()},
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredRight,
                       true);
            break;
    }

}

Component* LibraryComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                                     Component *existingComponentToUpdate)
{
    switch (columnId)
    {
        case 6:
            if (existingComponentToUpdate == nullptr)
            {
                auto* leftDeckBtn = new TextButton{"Load To Left Deck"};
                leftDeckBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                leftDeckBtn->setComponentID(id);

                existingComponentToUpdate = leftDeckBtn;
            }
            break;
        case 7:
            if (existingComponentToUpdate == nullptr)
            {
                auto* rightDeckBtn = new TextButton{"Load To Right Deck"};
                rightDeckBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                rightDeckBtn->setComponentID(id);

                existingComponentToUpdate = rightDeckBtn;
            }
            break;
        case 8:
            // if the component hasn't been created yet
            if (existingComponentToUpdate == nullptr)
            {
                auto* textBtn = new TextButton{"Remove"};
                textBtn->addListener(this);

                String id{std::to_string(rowNumber)};
                textBtn->setComponentID(id);

                existingComponentToUpdate = textBtn;
            }
            break;
    }
    return existingComponentToUpdate;
}

void LibraryComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    // TODO: tidy this up,
    // potentially create enum class on LibraryAudioItem for column headings -> column data?
    // then create a map of int (enum val), int (isForwards) -> comparator function?

    switch (newSortColumnId)
    {
        case 1:
            if (isForwards)
            {
                std::sort(libraryItems.begin(), libraryItems.end(),[](
                        const LibraryAudioItem& a,
                        const LibraryAudioItem& b
                        ){return a.getFileName() < b.getFileName();});
                break;
            }
            std::sort(libraryItems.begin(), libraryItems.end(),[](
                    const LibraryAudioItem& a,
                    const LibraryAudioItem& b
            ){return a.getFileName() > b.getFileName();});
            break;
        case 2:
            if (isForwards)
            {
                std::sort(libraryItems.begin(), libraryItems.end(),[](
                        const LibraryAudioItem& a,
                        const LibraryAudioItem& b
                ){return a.getDuration() < b.getDuration();});
                break;
            }
            std::sort(libraryItems.begin(), libraryItems.end(),[](
                    const LibraryAudioItem& a,
                    const LibraryAudioItem& b
            ){return a.getDuration() > b.getDuration();});
            break;
        case 3:
            if (isForwards)
            {
                std::sort(libraryItems.begin(), libraryItems.end(),[](
                        const LibraryAudioItem& a,
                        const LibraryAudioItem& b
                ){return a.getExtension() < b.getExtension();});
                break;
            }
            std::sort(libraryItems.begin(), libraryItems.end(),[](
                    const LibraryAudioItem& a,
                    const LibraryAudioItem& b
            ){return a.getExtension() > b.getExtension();});
            break;
        case 4:
            if (isForwards)
            {
                std::sort(libraryItems.begin(), libraryItems.end(),[](
                        const LibraryAudioItem& a,
                        const LibraryAudioItem& b
                ){return a.getKey() < b.getKey();});
                break;
            }
            std::sort(libraryItems.begin(), libraryItems.end(),[](
                    const LibraryAudioItem& a,
                    const LibraryAudioItem& b
            ){return a.getKey() > b.getKey();});
            break;
        case 5:
            if (isForwards)
            {
                std::sort(libraryItems.begin(), libraryItems.end(),[](
                        const LibraryAudioItem& a,
                        const LibraryAudioItem& b
                ){return a.getBPM() < b.getBPM();});
                break;
            }
            std::sort(libraryItems.begin(), libraryItems.end(),[](
                    const LibraryAudioItem& a,
                    const LibraryAudioItem& b
            ){return a.getBPM() > b.getBPM();});
            break;
    }
}

void LibraryComponent::buttonClicked(Button* button)
{
    if (button == &addItemsButton)
    {
        fChooser.launchAsync(FileBrowserComponent::canSelectMultipleItems, [this](const FileChooser& chooser)
        {
            auto chosenFiles = chooser.getResults();

            for (auto& file : chosenFiles)
            {
                // try to add the file to the current audio library collection
                try
                {
                    addFileToLibrary(file);
                }
                //TODO: show message on screen? maybe using NativeMessageBox?
                catch (const std::exception& e)
                {
                    std::cout << "LibraryComponent::buttonClicked: " << e.what() << std::endl;
                }
            }
            // refresh the table data to update on screen
            this->tableComponent.updateContent();
        });
    }
    else
    {
        auto rowIndex = std::stoi(button->getComponentID().toStdString());

        if (button->getButtonText() == "Remove")
        {
            // erase takes an iterator as an arg so offset from the beginning by rowIndex amt
            libraryItems.erase(libraryItems.begin() + rowIndex);
            // refresh the table data to update on screen
            this->tableComponent.updateContent();
        }
        else if (button->getButtonText() == "Load To Left Deck")
        {
            auto fl = libraryItems[rowIndex].getFile();
            deckloader.loadLeft(fl);
        }
        else if (button->getButtonText() == "Load To Right Deck")
        {
            auto fl = libraryItems[rowIndex].getFile();
            deckloader.loadRight(fl);
        }
    }
}

bool LibraryComponent::isInterestedInFileDrag(const StringArray &files)
{
    return true;
}

void LibraryComponent::filesDropped(const StringArray &files, int x, int y)
{
    for (auto const& fl : files)
    {
        auto file = File{fl};
        //TODO include more file types?
        if (file.getFileExtension() == ".mp3")
        {
            // try to add the file to the current audio library collection
            try
            {
                addFileToLibrary(file);
            }
                //TODO: show message on screen? maybe using NativeMessageBox?
            catch (const std::exception& e)
            {
                std::cout << "LibraryComponent::filesDropped: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "incorrect file type" << std::endl;
        }
    }
    tableComponent.updateContent();
}

void LibraryComponent::addFileToLibrary(File& file)
{
    // try to create LibraryAudioItem from file
    auto* reader = formatManager.createReaderFor(file);
    auto duration = reader->lengthInSamples / reader->sampleRate;

    // delete reader as memory has been allocated for it above
    delete reader;

    auto fileName = file.getFileName().toStdString();
    auto ext = file.getFileExtension().toStdString();

    // since lai is created with make_unique, it is deleted with the current scope
    auto lai = std::make_unique<LibraryAudioItem>(
            LibraryAudioItem{file, fileName, duration, ext});

    // append to libraryItems
    libraryItems.push_back(*lai);
}

void LibraryComponent::loadXmlFile()
{
    if (xmlFile.existsAsFile())
    {
        try
        {
            XmlParser::loadXmlFile(xmlFile, libraryItems);
        }
        catch (std::runtime_error& e)
        {
            //TODO: maybe push message to screen?
            std::cout << e.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "problem loading xml file data" << std::endl;
        }
    }
}

void LibraryComponent::saveToXmlFile()
{
    // if file already exists, .create() does nothing to it
    Result result = xmlFile.create();
    if (result.wasOk())
    {
        try
        {
            XmlParser::saveXmlFile(xmlFile, libraryItems);
        }
        catch (...)
        {
            std::cout << "error saving xml file" << std::endl;
        }
    }
    else
    {
        std::cout << "failed to create xml file, due to: " + result.getErrorMessage().toStdString() << std::endl;
    }
}