#include "MainComponent.h"

MainComponent::MainComponent() {
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(1000, 800);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio)) {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
                                    [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    } else {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }

    customLookAndFeel.setDefaultSansSerifTypeface(Typeface::createSystemTypefaceFor(
            BinaryData::LatoLight_ttf, BinaryData::LatoLight_ttfSize));

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(twoChannelMixer);
    addAndMakeVisible(libraryComponent);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent() {
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) {
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    // flexbox for the main top row
    FlexBox decksFb;
    decksFb.flexWrap = FlexBox::Wrap::noWrap;
    decksFb.justifyContent = FlexBox::JustifyContent::center;
    decksFb.alignContent = FlexBox::AlignContent::center;

    decksFb.items.addArray({
                                   FlexItem(deckGUI1).withMinWidth(100).withMinHeight(100).withFlex((2)).withMargin(
                                           FlexItem::Margin(10)),
                                   FlexItem(twoChannelMixer).withMinWidth(50).withMinHeight(50).withFlex(
                                           (1)).withMargin(FlexItem::Margin(10)),
                                   FlexItem(deckGUI2).withMinWidth(100).withMinHeight(100).withFlex((2)).withMargin(
                                           FlexItem::Margin(10))
                           });

    // flexbox for the whole visible GUI
    FlexBox outerFb;
    outerFb.flexWrap = FlexBox::Wrap::noWrap;
    outerFb.justifyContent = FlexBox::JustifyContent::center;
    outerFb.alignContent = FlexBox::AlignContent::center;
    outerFb.flexDirection = FlexBox::Direction::column;

    outerFb.items.addArray({
                                   FlexItem(decksFb).withWidth((float) getLocalBounds().getWidth()).withFlex(2),
                                   FlexItem(libraryComponent).withFlex(1),
                           });

    outerFb.performLayout(getLocalBounds().toFloat());
}

