#ifndef GUI_APP_EXAMPLE_DECKLOADER_H
#define GUI_APP_EXAMPLE_DECKLOADER_H

#include <JuceHeader.h>
#include "DeckGUI.h"

class DeckLoader
{
public:
    DeckLoader(DeckGUI* leftDeck, DeckGUI* rightDeck);
    ~DeckLoader();
    void loadLeft(File& file);
    void loadRight(File& file);
private:
    DeckGUI* leftDeck;
    DeckGUI* rightDeck;
};
#endif //GUI_APP_EXAMPLE_DECKLOADER_H
