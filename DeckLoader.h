#ifndef GUI_APP_EXAMPLE_DECKLOADER_H
#define GUI_APP_EXAMPLE_DECKLOADER_H

#include <JuceHeader.h>
#include "DeckGUI.h"

/**
 * A class to aid with the loading of audio to each deck from the LibraryComponent
 */
class DeckLoader {
public:

    /**
     * DeckLoader constructor
     * @param leftDeck a pointer to the left DJ deck in the application
     * @param rightDeck a pointer to the right DJ deck in the application
     */
    DeckLoader(DeckGUI *leftDeck, DeckGUI *rightDeck);

    /**
     * DeckLoader destructor
     */
    ~DeckLoader();

    /**
     * Loads a File into the left DJ deck
     * @param file Represents a local file or directory
     */
    void loadLeft(File &file);

    /**
     * Loads a File into the right DJ deck
     * @param file Represents a local file or directory
     */
    void loadRight(File &file);

private:

    // a pointer to the left DJ deck in the application
    DeckGUI *leftDeck;

    // a pointer to the right DJ deck in the application
    DeckGUI *rightDeck;
};

#endif //GUI_APP_EXAMPLE_DECKLOADER_H
