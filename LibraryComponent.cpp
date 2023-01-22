#include "LibraryComponent.h"

LibraryComponent::LibraryComponent(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager)
{
    addAndMakeVisible(addItemsButton);
    addAndMakeVisible(tableComponent);

    addItemsButton.addListener(this);

    tableComponent.getHeader().addColumn("Track Title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);
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
    g.drawText(libraryItems[rowNumber].getFileName(),
               2,
               0,
               width - 4,
               height,
               Justification::centredLeft,
               true);
}

Component* LibraryComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                                     Component *existingComponentToUpdate)
{
    if (columnId == 2)
    {
        // if the component hasn't been created yet
        if (existingComponentToUpdate == nullptr)
        {
            auto* textBtn = new TextButton{"PLAY"};
            textBtn->addListener(this);

            String id{std::to_string(rowNumber)};
            textBtn->setComponentID(id);

            existingComponentToUpdate = textBtn;
        }
    }
    return existingComponentToUpdate;
}

void LibraryComponent::buttonClicked(Button* button)
{
    if (button == &addItemsButton)
    {
        // get file(s)
        auto fileChooserFlags =
                FileBrowserComponent::canSelectMultipleItems;

        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFiles = chooser.getResults();

            // iterate through files
            for (auto& file : chosenFiles)
            {
                try
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
        std::cout << libraryItems[rowIndex].getFileName() << " clicked" << std::endl;
    }
}