#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager &_formatManager) : formatManager(_formatManager) {}

DJAudioPlayer::~DJAudioPlayer() {}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);
    resampleSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    resampleSource.releaseResources();
    transportSource.releaseResources();
}

void DJAudioPlayer::loadFile(const File &file) {
    auto *reader = formatManager.createReaderFor(file);

    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource
                (new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(),
                                  0,
                                  nullptr,
                                  reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0.0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain should be between 0.0 and 1.0\n";
    } else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0.0 || ratio > 100.0) {
        std::cout << "DJAudioPlayer::setSpeed should be between 0.0 and 100.0\n";
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs) {
    if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) {
        std::cout << "DJAudioPlayer::setPosition should be between 0.0 and the length of the track in seconds\n";
    } else {
        transportSource.setPosition(posInSecs);
    }
}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0.0 || pos > 1.0) {
        std::cout << "DJAudioPlayer::setPositionRelative should be between 0.0 and 1.0\n";
    } else {
        const double relativePos = transportSource.getLengthInSeconds() * pos;
        setPosition(relativePos);
    }
}

double DJAudioPlayer::getPositionRelative() {
    double currentPosInSecs = transportSource.getCurrentPosition();
    double lengthInSecs = transportSource.getLengthInSeconds();

    if (lengthInSecs == 0.0) {
        return 0.0;
    }

    return currentPosInSecs / lengthInSecs;
}

void DJAudioPlayer::start() {
    transportSource.start();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

bool DJAudioPlayer::isPlaying() {
    return transportSource.isPlaying();
}