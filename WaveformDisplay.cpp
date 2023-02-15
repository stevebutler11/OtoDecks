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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::orange);

    if (fileLoaded)
    {
        audioThumbnail.drawChannel(
                g,
                getLocalBounds(),
                0,
                audioThumbnail.getTotalLength(),
                0,
                1.0f);

        g.setColour(juce::Colours::lightgreen);

        if (!std::isnan(position))
        {
            g.fillRect(position * getLocalBounds().getWidth(), 0, 1, getLocalBounds().getHeight());
        }
    }
    else
    {
        g.setFont(20.0f);
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

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source)
{
    repaint();
}

void WaveformDisplay::mouseDown(const MouseEvent &event)
{
    auto mouseXY = getMouseXYRelative();
    auto mouseWidthRatio = (double) mouseXY.getX() / (double) this->getWidth();
    player->setPositionRelative(mouseWidthRatio);

}