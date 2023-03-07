#include "TwoChannelMixer.h"

TwoChannelMixer::TwoChannelMixer(DJAudioPlayer* _leftPlayer, DJAudioPlayer* _rightPlayer)
                                : leftPlayer(_leftPlayer), rightPlayer(_rightPlayer)
{
    addAndMakeVisible(leftDeckVolume);
    addAndMakeVisible(rightDeckVolume);
    addAndMakeVisible(crossfader);

    leftDeckVolume.addListener(this);
    rightDeckVolume.addListener(this);
    crossfader.addListener(this);

    leftDeckVolume.setRange(0.0, 1.0);
    rightDeckVolume.setRange(0.0, 1.0);
    crossfader.setRange(-1.0, 1.0);

    leftDeckVolume.setValue(1.0);
    rightDeckVolume.setValue(1.0);
    crossfader.setValue(0.0);
}

TwoChannelMixer::~TwoChannelMixer()
{

}

void TwoChannelMixer::paint(Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(getLookAndFeel().findColour (juce::ListBox::ColourIds::backgroundColourId));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 5.0f, 1.0f);
}

void TwoChannelMixer::resized()
{
    auto widthSlice = getBounds().getWidth() / 8;
    auto heightSlice = getBounds().getHeight() / 7;

    leftDeckVolume.setBounds(0, heightSlice / 2, widthSlice * 3, heightSlice * 5);
    rightDeckVolume.setBounds(widthSlice * 5, heightSlice / 2, widthSlice * 3, heightSlice * 5);
    crossfader.setBounds(widthSlice, heightSlice * 6, widthSlice * 6, heightSlice);
}

void TwoChannelMixer::sliderValueChanged(Slider *slider)
{
    auto val = crossfader.getValue();

    if (slider == &leftDeckVolume)
    {
        if (val <= 0)
        {
            leftPlayer->setGain(leftDeckVolume.getValue());
        }
        else
        {
            leftPlayer->setGain(leftDeckVolume.getValue() * (1 - val));
        }
    }

    if (slider == &rightDeckVolume)
    {
        if (val <= 0)
        {
            rightPlayer->setGain(rightDeckVolume.getValue() * (1 + val));
        }
        else
        {
            rightPlayer->setGain(rightDeckVolume.getValue());
        }
    }

    if (slider == &crossfader)
    {
        if (val <= 0)
        {
            // set right deck to rightDeckVolume value
            rightPlayer->setGain(rightDeckVolume.getValue() * (1 + val));
            // set left deck to leftDeckVolume * 1 - crossFader.getValue()
            leftPlayer->setGain(leftDeckVolume.getValue());
        }
        else
        {
            // set left deck to leftDeckVolume value
            leftPlayer->setGain(leftDeckVolume.getValue() * (1 - val));
            // set right deck to rightDeckVolume * crossFader.getValue()
            rightPlayer->setGain(rightDeckVolume.getValue());
        }
    }
}