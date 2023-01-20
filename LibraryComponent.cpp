#include "LibraryComponent.h"

LibraryComponent::LibraryComponent()
{
    trackTitles.emplace_back("Track 1");
    trackTitles.emplace_back("Track 2");
    trackTitles.emplace_back("Track 3");
    trackTitles.emplace_back("Track 4");
    trackTitles.emplace_back("Track 5");
    trackTitles.emplace_back("Track 6");

    addAndMakeVisible(tableComponent);

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
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int LibraryComponent::getNumRows()
{
    return trackTitles.size();
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
    g.drawText(trackTitles[rowNumber],
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
    auto rowIndex = std::stoi(button->getComponentID().toStdString());
    std::cout << trackTitles[rowIndex] << " clicked" << std::endl;
}