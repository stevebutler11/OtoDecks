#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(DJAudioPlayer* _player,
                                 AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse
                                 ) : player(_player), audioThumbnail(
                                         1000,
                                         formatManagerToUse,
                                         cacheToUse), fileLoaded(false), position(0.0)
{
    audioThumbnail.addChangeListener(this);
}
WaveformDisplay::~WaveformDisplay()
{

}

void WaveformDisplay::paint(Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour(ListBox::ColourIds::backgroundColourId));

    if (fileLoaded)
    {
        auto cg = ColourGradient(Colour::fromString("FFC75450"),
                       0.0, 0.0,
                       Colour::fromString("FFC75450"),
                       0.0,
                       getLocalBounds().getHeight(),
                       false);

        cg.addColour(0.5, Colour::fromString("FF3592C4"));

        g.setGradientFill(cg);

        audioThumbnail.drawChannel(
                g,
                getLocalBounds(),
                0 + (audioZoomOffset * leftWidthOffset),
                audioThumbnail.getTotalLength() - (audioZoomOffset * rightWidthOffset),
                0,
                1.0f);

        // draw cue mark
        g.setColour(juce::Colours::blueviolet);
        g.fillRect(cuePosition * getLocalBounds().getWidth(), 0, 1, getLocalBounds().getHeight());

        // draw current position
        if (!std::isnan(position))
        {
            g.setColour(juce::Colours::lightgreen);
            g.fillRect(position * getLocalBounds().getWidth(), 0, 1, getLocalBounds().getHeight());
        }
    }
    else
    {
        g.setFont(20.0f);
        g.setColour(getLookAndFeel().findColour(TextButton::ColourIds::textColourOffId));
        g.drawText("File not loaded...", getLocalBounds(), juce::Justification::centred, true);
    }
}
void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
    //TODO: change to throw error and catch in deckGUI?
    if (fileLoaded)
    {
        std::cout << "WaveformDisplay::loadURL loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "WaveformDisplay::loadURL load error" << std::endl;
    }
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (position != pos)
    {
        position = pos;
        repaint();
    }
}

double WaveformDisplay::getCuePositionRelative()
{
    return cuePosition;
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source)
{
    repaint();
}

void WaveformDisplay::mouseDown(const MouseEvent &event)
{
    auto mouseWidthRatio = getMouseWidthRatio();

    // setting cue position
    if (event.mods.isShiftDown())
    {
        cuePosition = mouseWidthRatio;
        repaint();
    }
    // setting play position
    else
    {
        player->setPositionRelative(mouseWidthRatio);
    }
}

void WaveformDisplay::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if (event.mods.isShiftDown())
    {
        auto temp = audioZoomOffset + (wheel.deltaY*30);
        audioZoomOffset = (temp > 1) ? temp : 1.0;

        auto mouseWidthRatio = getMouseWidthRatio();
        leftWidthOffset = mouseWidthRatio;
        rightWidthOffset = 1 - mouseWidthRatio;

        repaint();
    }
}

double WaveformDisplay::getMouseWidthRatio()
{
    auto mouseXY = getMouseXYRelative();
    auto mouseWidthRatio = (double) mouseXY.getX() / (double) this->getWidth();
    return mouseWidthRatio;
}