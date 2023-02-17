#ifndef GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
#define GUI_APP_EXAMPLE_DJAUDIOPLAYER_H

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
    explicit DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer() override;

    void loadFile(const File& file);
    void setGain(double gain);
    double getSpeed();
    void setSpeed(double ratio);
    void setPositionRelative(double pos);

    /**
     * get the relative position of the playhead
     * @return double
     */
    double getPositionRelative();

    void start();
    void stop();
    bool isPlaying();

    //================ AudioSource pure virtual functions ================

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    juce::AudioFormatManager& formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    void setPosition(double posInSecs);
};
#endif //GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
