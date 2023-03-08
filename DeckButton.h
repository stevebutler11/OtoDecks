#ifndef GUI_APP_EXAMPLE_DECKBUTTON_H
#define GUI_APP_EXAMPLE_DECKBUTTON_H

#include <JuceHeader.h>

class DeckButton : public Button
{
public:
    DeckButton(const std::string& buttonName, const Colour& outerGlowColour);
    ~DeckButton() override = default;

private:
    void paintButton(juce::Graphics& g, bool isMouseOver, bool isButtonDown) override;
    Colour outerGlowColour;
};

#endif //GUI_APP_EXAMPLE_DECKBUTTON_H
