#include "DeckButton.h"

DeckButton::DeckButton(const std::string &buttonName, const Colour &_outerGlowColour, bool _isPlayButton)
        : Button(buttonName), outerGlowColour(_outerGlowColour), isPlayButton(_isPlayButton) {

}

void DeckButton::paintButton(juce::Graphics &g, bool isMouseOver, bool isButtonDown) {
    auto buttonColour = getLookAndFeel().findColour(juce::TextButton::buttonColourId);
    auto buttonBounds = getLocalBounds().toFloat().reduced(1.0f);
    auto diameter = buttonBounds.getHeight() > buttonBounds.getWidth() ?
                    buttonBounds.getWidth() : buttonBounds.getHeight();
    g.setColour(buttonColour);
    g.fillEllipse(
            buttonBounds.getCentreX() - diameter / 2,
            buttonBounds.getCentreY() - diameter / 2,
            diameter,
            diameter);

    // scale font with button size
    g.setFont(diameter / 4);

    if (isMouseOver || isButtonDown) {
        g.setColour(outerGlowColour);
        g.drawEllipse(
                buttonBounds.getCentreX() - diameter / 2,
                buttonBounds.getCentreY() - diameter / 2,
                diameter,
                diameter,
                1.0f);
        g.setColour(findColour(TextButton::ColourIds::textColourOnId));
        if (isPlayButton) {
            Path playSymbol;
            playSymbol.addTriangle(
                    buttonBounds.getCentreX() - diameter / 8, buttonBounds.getCentreY() - diameter / 12,
                    buttonBounds.getCentreX(), buttonBounds.getCentreY(),
                    buttonBounds.getCentreX() - diameter / 8, buttonBounds.getCentreY() + diameter / 12);
            g.fillPath(playSymbol);

            g.fillRect(Rectangle<float>(
                    buttonBounds.getCentreX(),
                    buttonBounds.getCentreY() - diameter / 12,
                    diameter / 24,
                    diameter / 6));

            g.fillRect(Rectangle<float>(
                    buttonBounds.getCentreX() + diameter / 12,
                    buttonBounds.getCentreY() - diameter / 12,
                    diameter / 24,
                    diameter / 6));
        } else {
            g.drawText(this->getButtonText(), buttonBounds, Justification::centred);
        }
    } else {
        g.setColour(findColour(TextButton::ColourIds::textColourOffId));
        if (isPlayButton) {
            Path playSymbol;
            playSymbol.addTriangle(
                    buttonBounds.getCentreX() - diameter / 8, buttonBounds.getCentreY() - diameter / 12,
                    buttonBounds.getCentreX(), buttonBounds.getCentreY(),
                    buttonBounds.getCentreX() - diameter / 8, buttonBounds.getCentreY() + diameter / 12);
            g.fillPath(playSymbol);

            g.fillRect(Rectangle<float>(
                    buttonBounds.getCentreX(),
                    buttonBounds.getCentreY() - diameter / 12,
                    diameter / 24,
                    diameter / 6));

            g.fillRect(Rectangle<float>(
                    buttonBounds.getCentreX() + diameter / 12,
                    buttonBounds.getCentreY() - diameter / 12,
                    diameter / 24,
                    diameter / 6));

        } else {
            g.drawText(this->getButtonText(), buttonBounds, Justification::centred);
        }
    }
}