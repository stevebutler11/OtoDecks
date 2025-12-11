#include "DeckLoader.h"

DeckLoader::DeckLoader(DeckGUI *_leftDeck, DeckGUI *_rightDeck) : leftDeck(_leftDeck), rightDeck(_rightDeck) {}

DeckLoader::~DeckLoader() {}

void DeckLoader::loadLeft(File &file) {
    leftDeck->loadFile(file);
}

void DeckLoader::loadRight(File &file) {
    rightDeck->loadFile(file);
}
