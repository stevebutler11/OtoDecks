#include "TwoChannelMixer.h"

TwoChannelMixer::TwoChannelMixer(DJAudioPlayer *_leftPlayer, DJAudioPlayer *_rightPlayer)
        : leftPlayer(_leftPlayer), rightPlayer(_rightPlayer) {
    addAndMakeVisible(leftDeckVolume);
    addAndMakeVisible(rightDeckVolume);
    addAndMakeVisible(crossfader);
    addAndMakeVisible(leftVolLabel);
    addAndMakeVisible(rightVolLabel);
    addAndMakeVisible(crossfaderLabel);

    leftDeckVolume.addListener(this);
    rightDeckVolume.addListener(this);
    crossfader.addListener(this);

    leftDeckVolume.setRange(0.0, 1.0);
    rightDeckVolume.setRange(0.0, 1.0);
    crossfader.setRange(-1.0, 1.0);

    leftDeckVolume.setValue(1.0);
    rightDeckVolume.setValue(1.0);
    crossfader.setValue(0.0);

    formatLabel(leftVolLabel, "VOLUME");
    formatLabel(rightVolLabel, "VOLUME");
    formatLabel(crossfaderLabel, "CROSSFADER");
}

TwoChannelMixer::~TwoChannelMixer() {}

void TwoChannelMixer::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(getLookAndFeel().findColour(juce::ListBox::ColourIds::backgroundColourId));
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 5.0f, 1.0f);
}

void TwoChannelMixer::resized() {
    auto widthSlice = getBounds().getWidth() / 8;
    auto heightSlice = getBounds().getHeight() / 7;

    leftDeckVolume.setBounds(0, heightSlice / 2, widthSlice * 3, heightSlice * 5);
    leftVolLabel.setBounds(0, (int) (heightSlice * 5.5), widthSlice * 3, heightSlice / 4);

    rightDeckVolume.setBounds(widthSlice * 5, heightSlice / 2, widthSlice * 3, heightSlice * 5);
    rightVolLabel.setBounds(widthSlice * 5, (int) (heightSlice * 5.5), widthSlice * 3, heightSlice / 4);
    crossfader.setBounds(widthSlice, (int) (heightSlice * 6), widthSlice * 6, (int) heightSlice / 2);
    crossfaderLabel.setBounds(widthSlice, (int) (heightSlice * 6.5), widthSlice * 6, heightSlice / 4);
}

void TwoChannelMixer::sliderValueChanged(Slider *slider) {
    auto val = crossfader.getValue();

    if (slider == &leftDeckVolume) {
        if (val <= 0) {
            leftPlayer->setGain(leftDeckVolume.getValue());
        } else {
            leftPlayer->setGain(leftDeckVolume.getValue() * (1 - val));
        }
    }

    if (slider == &rightDeckVolume) {
        if (val <= 0) {
            rightPlayer->setGain(rightDeckVolume.getValue() * (1 + val));
        } else {
            rightPlayer->setGain(rightDeckVolume.getValue());
        }
    }

    if (slider == &crossfader) {
        if (val <= 0) {
            rightPlayer->setGain(rightDeckVolume.getValue() * (1 + val));
            leftPlayer->setGain(leftDeckVolume.getValue());
        } else {
            leftPlayer->setGain(leftDeckVolume.getValue() * (1 - val));
            rightPlayer->setGain(rightDeckVolume.getValue());
        }
    }
}

void TwoChannelMixer::formatLabel(Label &label, std::string text) {
    Typeface::Ptr tface = Typeface::createSystemTypefaceFor(BinaryData::neuropol_otf, BinaryData::neuropol_otfSize);
    label.setText(text, juce::dontSendNotification);
    label.setFont(Font(tface).withHeight(10.0f));
    label.setColour(juce::Label::textColourId, juce::Colours::grey);
    label.setJustificationType(juce::Justification::centredBottom);
}