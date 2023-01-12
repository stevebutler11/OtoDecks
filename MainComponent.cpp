#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    formatManager.registerBasicFormats();

    URL audioURL{"file:///home/steve/Downloads/OOP tracks/tracks/aon_inspired.mp3"};
    loadURL(audioURL);

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(volumeGainSlider);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    gainSlider.addListener(this);
    gainSlider.setRange(0, 1);

    speedSlider.addListener(this);
    speedSlider.setRange(0.5, 1.5);
    speedSlider.setValue(1.0);

    volumeGainSlider.addListener(this);
    volumeGainSlider.setRange(0, 1);

    loadButton.addListener(this);
    loadButton.setButtonText("LOAD");
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    playing = false;
    gain = gainSlider.getValue();
    phase = 0;
    dphase = 0;

    transportSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);

    resampleSource.prepareToPlay(
            samplesPerBlockExpected,
            sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if(!playing)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

//    // get L and R channel pointers
//    auto* leftChannel = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//    auto* rightChannel = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
//
//    // fill both channels with random noise
//    for (auto i=0;i<bufferToFill.numSamples; ++i)
//    {
//        auto sample = fmod(phase, 1.0f);
//        phase += fmod(dphase, 0.01f);
//        dphase += 0.0000005f;
//        leftChannel[i] = sample * 0.125 * gain;
//        rightChannel[i] = sample * 0.125 * gain;
//    }

//    transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    int rowH = getHeight()/6;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    gainSlider.setBounds(0, rowH*2, getWidth(), rowH);
    volumeGainSlider.setBounds(0, rowH*3, getWidth(), rowH);
    loadButton.setBounds(0, rowH*4, getWidth(), rowH);
    speedSlider.setBounds(0, rowH*5, getWidth(), rowH);
}

void MainComponent::buttonClicked (Button *button)
{
    if (button == &playButton)
    {
        dphase = 0;
        playing = true;
        transportSource.start();
    }
    if (button == &stopButton)
    {
        playing = false;
        transportSource.stop();
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags =
                FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFile = chooser.getResult();
            loadURL(URL{chosenFile});
        });
    }
}

void MainComponent::sliderValueChanged (Slider *slider)
{
    if (slider == &gainSlider)
    {
        gain = gainSlider.getValue();
    }
    if (slider == &volumeGainSlider)
    {
        transportSource.setGain(volumeGainSlider.getValue());
    }
    if (slider == &speedSlider)
    {
        resampleSource.setResamplingRatio(speedSlider.getValue());
    }
}

void MainComponent::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(
            URL::InputStreamOptions (URL::ParameterHandling::inAddress)));

    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource
                (new AudioFormatReaderSource (reader, true));
        transportSource.setSource (newSource.get(),
                                   0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
}