#ifndef GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
#define GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
#include <JuceHeader.h>
class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    //==============================================================================

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================

    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPositionRelative(double pos);

    void start();
    void stop();

private:
    juce::AudioFormatManager& formatManager;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    void setPosition(double posInSecs);
};
#endif //GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
