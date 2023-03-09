#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1000, 800);

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

    customLookAndFeel.setDefaultSansSerifTypeface(
            Typeface::createSystemTypefaceFor(
                    BinaryData::LatoLight_ttf,
                    BinaryData::LatoLight_ttfSize));
    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(twoChannelMixer);
    addAndMakeVisible(libraryComponent);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();

    LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    FlexBox decksFb;
    decksFb.flexWrap = juce::FlexBox::Wrap::noWrap;
    decksFb.justifyContent = juce::FlexBox::JustifyContent::center;
    decksFb.alignContent = juce::FlexBox::AlignContent::center;

    decksFb.items.addArray({
        FlexItem(deckGUI1).withMinWidth(100).withMinHeight(100).withFlex((2)).withMargin(FlexItem::Margin(10)),
        FlexItem(twoChannelMixer).withMinWidth(50).withMinHeight(50).withFlex((1)).withMargin(FlexItem::Margin(10)),
        FlexItem(deckGUI2).withMinWidth(100).withMinHeight(100).withFlex((2)).withMargin(FlexItem::Margin(10))
    });

    FlexBox outerFb;
    outerFb.flexWrap = juce::FlexBox::Wrap::noWrap;
    outerFb.justifyContent = juce::FlexBox::JustifyContent::center;
    outerFb.alignContent = juce::FlexBox::AlignContent::center;
    outerFb.flexDirection = FlexBox::Direction::column;

    outerFb.items.addArray({
        FlexItem(decksFb).withWidth((float) getLocalBounds().getWidth()).withFlex(2),
        FlexItem(libraryComponent).withFlex(1),
    });

    outerFb.performLayout (getLocalBounds().toFloat());
}

