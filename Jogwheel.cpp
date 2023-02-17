#include "Jogwheel.h"

Jogwheel::Jogwheel(DJAudioPlayer* _player, std::shared_ptr<double>& _pitchVal) : player(_player), pitchVal(_pitchVal)
{
    jogWheel.setRotaryParameters(0.0f, MathConstants<float>::pi * 2.0f, false);
    jogWheel.setRange(0.0, 1.0);
    jogWheel.addListener(this);
    addAndMakeVisible(jogWheel);

    startTimer(100);
}

Jogwheel::~Jogwheel()
{

}


void Jogwheel::paint(Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Jogwheel::resized()
{
    jogWheel.setBounds(0, 0, getWidth(), getHeight());
}

void Jogwheel::sliderValueChanged(Slider* slider)
{
    if (slider == &jogWheel)
    {
        if (std::isnan(mouseDownStartValue))
        {
            mouseDownStartValue = slider->getValue() + rotationCount;
        }

        if (!std::isnan(mouseDownStartValue))
        {
            // workaround to deal with the rotary slider coming back around
            if (slider->getValue() <= 0.1 && prevValue >= 0.9)
            {
                ++rotationCount;
            }
            else if (prevValue <= 0.1 && slider->getValue() >= 0.9)
            {
                --rotationCount;
            }
            displacementValue = ((slider->getValue() + rotationCount) - mouseDownStartValue);
            prevValue = slider->getValue();
        }

    }
}

void Jogwheel::sliderDragStarted(Slider* slider)
{
}

void Jogwheel::sliderDragEnded (Slider* slider)
{
    mouseDownStartValue = NAN;
}

void Jogwheel::timerCallback()
{
    if (displacementValue == 0.0)
    {
        return;
    }
    else if (displacementValue <= 0.05 && displacementValue >= -0.05)
    {
        displacementValue = 0.0;
    }
    else
    {
        displacementValue /= 1.2;
    }
    player->setSpeed(*pitchVal + displacementValue);
}