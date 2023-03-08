#include "DeckButton.h"

DeckButton::DeckButton(const std::string& buttonName, const Colour& _outerGlowColour)
                        : Button(buttonName), outerGlowColour(_outerGlowColour)
{

}

void DeckButton::paintButton(juce::Graphics& g, bool isMouseOver, bool isButtonDown)
{
    auto buttonColour = getLookAndFeel().findColour(juce::TextButton::buttonColourId);
    auto buttonBounds = getLocalBounds().toFloat().reduced(1.0f);
    auto diameter = buttonBounds.getHeight() > buttonBounds.getWidth() ?
                    buttonBounds.getWidth() : buttonBounds.getHeight();
    g.setColour(buttonColour);
    g.fillEllipse(
            buttonBounds.getCentreX() - diameter/2,
            buttonBounds.getCentreY() - diameter/2,
            diameter,
            diameter);

    g.setFont(10.0f);

    if (isMouseOver || isButtonDown)
    {
        g.setColour(outerGlowColour);
        g.drawEllipse(
                buttonBounds.getCentreX() - diameter/2,
                buttonBounds.getCentreY() - diameter/2,
                diameter,
                diameter,
                1.0f);
        g.setColour(findColour(TextButton::ColourIds::textColourOnId));
        g.drawText(this->getButtonText(), buttonBounds, Justification::centred);
    }
    else
    {
        g.setColour(findColour(TextButton::ColourIds::textColourOffId));
        g.drawText(this->getButtonText(), buttonBounds, Justification::centred);
    }
}