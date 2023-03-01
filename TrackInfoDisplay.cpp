#include "TrackInfoDisplay.h"

#include <utility>

TrackInfoDisplay::TrackInfoDisplay()
{
    startTimer(200);
}

TrackInfoDisplay::~TrackInfoDisplay()
{

}

void TrackInfoDisplay::paint(Graphics& g)
{
    if (displayTextWidth == 0)
    {
        displayTextWidth = g.getCurrentFont().getStringWidthFloat(displayText);
        whitespaceCharWidth = g.getCurrentFont().getStringWidthFloat(" ");
        padDisplayText();
    }

    g.fillAll (getLookAndFeel().findColour(ListBox::ColourIds::backgroundColourId));
    g.setColour (juce::Colours::lightgrey);
    g.setFont (18.0f);

    g.drawText (paddedText, getLocalBounds(), juce::Justification::centredLeft, false);
}

void TrackInfoDisplay::resized()
{
    padDisplayText();
}

void TrackInfoDisplay::timerCallback()
{
    auto first_char = paddedText.front();
    paddedText = paddedText.substr(1) += first_char;
    repaint();
}

void TrackInfoDisplay::padDisplayText()
{
    paddedText = displayText;

    if (displayTextWidth > 0 && whitespaceCharWidth > 0)
    {
        // calculate how many spaces are needed to reach end of screen
        auto remainingSpace = (float) getLocalBounds().getWidth() - displayTextWidth;
        if (remainingSpace > 0)
        {
            int padNumber = remainingSpace / whitespaceCharWidth;

            // pad the text the correct amount
            for (auto i = 0; i < padNumber; ++i)
            {
                paddedText += " ";
            }
        }
    }
}

void TrackInfoDisplay::setText(std::string trackText)
{
    // strip leading & trailing whitespace
    auto startIndex = trackText.find_first_not_of(' ');
    auto endIndex = trackText.find_last_not_of(' ');
    if (startIndex != std::string::npos && endIndex != std::string::npos)
    {
        trackText = trackText.substr(startIndex, endIndex + 1);
    }

    displayText = trackText;
    padDisplayText();
}