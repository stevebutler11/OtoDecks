#ifndef GUI_APP_EXAMPLE_DECKBUTTON_H
#define GUI_APP_EXAMPLE_DECKBUTTON_H

#include <JuceHeader.h>

/**
 * Overrides the JUCE button class to create a button more suited to the DJ Deck
 */
class DeckButton : public Button {
public:

    /**
     * DeckButton constructor
     * @param buttonName the text of the button
     * @param outerGlowColour JUCE colour to set the outer glow to
     * @param isPlayButton boolean representing if this button is of the 'play/pause' variety
     */
    DeckButton(const std::string &buttonName, const Colour &outerGlowColour, bool isPlayButton = false);

    /**
     * DeckButton destructor
     */
    ~DeckButton() override = default;

private:

    //================ Button override functions ================

    /**
     * Override funtion that paints the button's contents
     * @param g reference to the JUCE Graphics instance
     * @param isMouseOver boolean representing whether the mouse is hovering over the button
     * @param isButtonDown boolean representing whether the button is down
     */
    void paintButton(juce::Graphics &g, bool isMouseOver, bool isButtonDown) override;

    // JUCE Colour to set the outer glow to
    Colour outerGlowColour;

    // boolean representing if this button is of the 'play/pause' variety
    bool isPlayButton;
};

#endif //GUI_APP_EXAMPLE_DECKBUTTON_H
