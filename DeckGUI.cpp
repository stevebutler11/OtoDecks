#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volumeSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volumeSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);

    volumeSlider.setValue(1.0);
    speedSlider.setValue(1.0);
    posSlider.setValue(0.0);
}

DeckGUI::~DeckGUI()
{

}

void DeckGUI::paint(Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("DeckGUI", getLocalBounds(), juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    int rowH = getHeight()/6;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    posSlider.setBounds(0, rowH*2, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH*3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH*4, getWidth(), rowH);
    loadButton.setBounds(0, rowH*5, getWidth(), rowH);
}

void DeckGUI::buttonClicked(Button *button)
{
    if (button == &playButton)
    {
        player->start();
    }
    if (button == &stopButton)
    {
        player->stop();
    }
    if (button == &loadButton)
    {

        auto fileChooserFlags =
                FileBrowserComponent::canSelectFiles;

        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFile = chooser.getResult();
            player->loadURL(URL{chosenFile});
        });
    }
}

void DeckGUI::sliderValueChanged(Slider *slider)
{
    if (slider == &volumeSlider)
    {
        player->setGain(volumeSlider.getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(speedSlider.getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(posSlider.getValue());
    }
}
