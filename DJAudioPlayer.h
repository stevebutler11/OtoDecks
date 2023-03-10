#ifndef GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
#define GUI_APP_EXAMPLE_DJAUDIOPLAYER_H

#include <JuceHeader.h>
#include <queue>

/**
 * A class to handle the audio functionality of a DJ deck. Works in tandem with the DeckGUI to represent a DJ deck
 * in the application
 */
class DJAudioPlayer : public AudioSource, Timer {
public:
    /**
     * DJAudioPlayer constructor
     * @param _formatManager keeps a list of available audio formats, and decides which one to use to open a given file
     */
    explicit DJAudioPlayer(AudioFormatManager &_formatManager);

    /**
     * DJAudioPlayer destructor
     */
    ~DJAudioPlayer() override;

    /**
     * Loads a file into the DJ deck
     * @param file Represents a local file or directory
     */
    void loadFile(const File &file);

    /**
     * Sets the gain (volume) of the audio track
     * @param gain double value to represent the gain. Values should be between 0.0 and 1.0
     */
    void setGain(double gain);

    /**
     * Sets the speed (tempo) of the audio track
     * @param ratio double value to represent the speed ratio of the track
     */
    void setSpeed(double ratio);

    /**
     * Sets the relative position of the track
     * @param pos double value to represent the relative position of the track. Values should be between 0.0 and 1.0
     */
    void setPositionRelative(double pos);

    /**
     * Get the relative position of the playhead
     * @return double value representing the relative position of the track. Value between 0.0 and 1.0
     */
    double getPositionRelative();

    /**
     * Start playing the audio track
     */
    void start();

    /**
     * Stop playing the audio track
     */
    void stop();

    /**
     * Returns whether the audio track is currently playing
     * @return boolean representing the play state of the audio track
     */
    bool isPlaying();

    //================ AudioSource pure virtual functions ================

    /**
     * Tells the source to prepare for playing
     * @param samplesPerBlockExpected the number of samples that the source will be expected to supply
     * @param sampleRate the sample rate that the output will be used at
     */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /**
     * Called repeatedly to fetch subsequent blocks of audio data
     * @param bufferToFill
     */
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;

    /**
     * Allows the source to release anything it no longer needs after playback has stopped
     */
    void releaseResources() override;

    //================ Timer pure virtual functions ================

    /**
     * The user-defined callback routine that actually gets called periodically
     */
    void timerCallback() override;

private:
    // A class for keeping a list of available audio formats
    AudioFormatManager &formatManager;

    // An AudioSource that takes a PositionableAudioSource and allows it to be played, stopped, started, etc
    AudioTransportSource transportSource;

    // Shared pointer to a type of AudioSource that will read from an AudioFormatReader
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    // AudioSource that takes an input source and changes its sample rate
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

//    // bpm calc
//    static const int instantSampleSize{1024};
//    static const int previousEnergiesSize{43};
//    float instantSampleFifo[instantSampleSize];
//    float instantSampleFifoLeft[instantSampleSize];
//    float instantSampleFifoRight[instantSampleSize];
//    int instantSampleIndex{0};
//    std::deque<float> previousEnergiesQueue{};
//    int millis{0};

    /**
     * Set position of the track
     * @param posInSecs position of the track in seconds, should be between 0.0 and the track length
     */
    void setPosition(double posInSecs);
//
//    //
//    void pushNextEnergyIntoQueue(float leftSample, float rightSample);
};

#endif //GUI_APP_EXAMPLE_DJAUDIOPLAYER_H
