#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager &_formatManager) : formatManager(_formatManager) {
    startTimer(1);
}

DJAudioPlayer::~DJAudioPlayer() {

}

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

//    if (bufferToFill.buffer->getNumChannels() == 2)
//    {
//        auto* leftChannelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
//        auto* rightChannelData = bufferToFill.buffer->getReadPointer (1, bufferToFill.startSample);
//        for (auto i = 0; i < bufferToFill.numSamples; ++i)
//        {
//            pushNextEnergyIntoQueue(leftChannelData[i], rightChannelData[i]);
//        }
//    }
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
    //TODO: implement exception here instead of printed line
    if (gain < 0.0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain should be between 0.0 and 1.0\n";
    } else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) {
    //TODO: implement exception here instead of printed line
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
    //TODO: implement exception here instead of printed line
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

    //TODO: throw divide by zero error?
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

//void DJAudioPlayer::pushNextEnergyIntoQueue(float leftSample, float rightSample)
//{
//    // if instantSample is full
//    if (instantSampleIndex == DJAudioPlayer::instantSampleSize)
//    {
//        //  calc energy
//        float instantEnergy{0.0f};
//
//        for (auto i{0u}; i < DJAudioPlayer::instantSampleSize; i++)
//        {
//            instantEnergy += (instantSampleFifoLeft[i] * instantSampleFifoLeft[i]) + (instantSampleFifoRight[i] * instantSampleFifoRight[i]);
//        }
//
//        // push to queue
//        previousEnergiesQueue.push_back(instantEnergy);
//
//        // if queue is full
//        if (previousEnergiesQueue.size() == previousEnergiesSize)
//        {
//            // calc average energy
//            float avgEnergy{0.0f};
//            for (auto const& energy : previousEnergiesQueue)
//            {
//                avgEnergy += energy;
//            }
//            avgEnergy /= previousEnergiesSize;
//
//            // calc the variance
//            float varianceEnergy{0.0f};
//            for (auto const& energy : previousEnergiesQueue)
//            {
//                varianceEnergy += (energy - avgEnergy) * (energy - avgEnergy);
//            }
//            varianceEnergy /= previousEnergiesSize;
//
//            // calculate constant
//            float C = (-0.0025714f * varianceEnergy) + 1.5142857f; // something not right here
//
//            // if instant energy larger than avgEnergy * constant C, then a beat has been detected
//            if (instantEnergy > avgEnergy * C)
//            {
//                DBG(millis << ", " << instantEnergy);
//            }
//
//            // remove last energy
//            previousEnergiesQueue.pop_front();
//        }
//
//        // clear array
//        zeromem (instantSampleFifoLeft, sizeof (instantSampleFifoLeft));
//        zeromem (instantSampleFifoRight, sizeof (instantSampleFifoRight));
//        //  set index back to zero
//        instantSampleIndex = 0;
//    }
//
//    // add channel data to fifos
//    instantSampleFifoLeft[instantSampleIndex] = leftSample;
//    instantSampleFifoRight[instantSampleIndex] = rightSample;
//    instantSampleIndex++;
//}

void DJAudioPlayer::timerCallback() {
//    millis++;
}