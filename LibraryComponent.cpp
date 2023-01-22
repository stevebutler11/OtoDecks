#include "LibraryComponent.h"

LibraryComponent::LibraryComponent(AudioFormatManager& _formatManager, DeckLoader& _deckLoader
                            ) : formatManager(_formatManager), deckloader(_deckLoader)
{
    addAndMakeVisible(addItemsButton);
    addAndMakeVisible(tableComponent);

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
}

LibraryComponent::~LibraryComponent()
{

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
    addItemsButton.setBounds(getWidth()/2, 0, getWidth()/2, heightSplit);
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