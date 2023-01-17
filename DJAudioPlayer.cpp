#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer()
{

}

DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    formatManager.registerBasicFormats();
    transportSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);
    resampleSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(
            URL::InputStreamOptions(URL::ParameterHandling::inAddress)));

    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource
                (new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(),
                                   0,
                                   nullptr,
                                   reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
void DJAudioPlayer::setGain(double gain)
{
    //TODO: implement exception here instead of printed line
    if (gain < 0.0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain should be between 0.0 and 1.0\n";
    } else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
    //TODO: implement exception here instead of printed line
    if (ratio < 0.0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed should be between 0.0 and 100.0\n";
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    //TODO: implement exception here instead of printed line
    if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds())
    {
        std::cout << "DJAudioPlayer::setPosition should be between 0.0 and the length of the track in seconds\n";
    }
    else
    {
        transportSource.setPosition(posInSecs);
    }
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    //TODO: implement exception here instead of printed line
    if (pos < 0.0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative should be between 0.0 and 1.0\n";
    } else {
        const double relativePos = transportSource.getLengthInSeconds() * pos;
        setPosition(relativePos);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}