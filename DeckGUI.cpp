#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse
                 ) : player(_player),
                     waveformDisplay(formatManagerToUse, cacheToUse) // pass cstr args directly to wavfrmDisp
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);

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

    startTimer(TIMER_INTERVAL);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::loadFile(File& file)
{
    player->loadFile(file);
    //TODO: change waveform to load from file rather than URL
    waveformDisplay.loadURL(URL{file});
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
    int rowH = getHeight()/8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    posSlider.setBounds(0, rowH*2, getWidth(), rowH);
    volumeSlider.setBounds(0, rowH*3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH*4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH*5, getWidth(), rowH*2);
    loadButton.setBounds(0, rowH*7, getWidth(), rowH);
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
            loadFile(chosenFile);
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

bool DeckGUI::isInterestedInFileDrag(const StringArray &files)
{
    return true;
}

void DeckGUI::filesDropped(const StringArray &files, int x, int y)
{
    if (files.size() == 1)
    {
        auto file = File{files[0]};
        //TODO include more file types?
        if (file.getFileExtension() == ".mp3")
        {
            loadFile(file);
        }
        else
        {
            std::cout << "incorrect file type" << std::endl;
        }
    }
    else
    {
        std::cout << "too many files" << std::endl;
    }
}

void DeckGUI::timerCallback()
{
    //TODO: potentially change setposrel and getposrel to actual seconds rather than relative
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}