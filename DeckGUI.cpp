#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse
                 ) : player(_player),
                     waveformDisplay(_player, formatManagerToUse, cacheToUse) // pass cstr args directly to wavfrmDisp
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(jogWheel);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volumeSlider.addListener(this);
    speedSlider.addListener(this);

    volumeSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.92, 1.08);

    volumeSlider.setValue(1.0);
    speedSlider.setValue(1.0);

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

//    g.setColour(juce::Colours::white);
//    g.setFont(14.0f);
//    g.drawText("DeckGUI", getLocalBounds(), juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    int rowH = getHeight()/8;
    int colW = getWidth()/5;

    waveformDisplay.setBounds(colW, 0, colW * 3, rowH);
    volumeSlider.setBounds(colW, rowH * 2, colW * 3, rowH/2);

    playButton.setBounds(0, rowH * 7, colW, rowH);
    stopButton.setBounds(0, rowH * 6, colW, rowH);

    speedSlider.setBounds(colW * 4, rowH*2, colW, rowH * 6);
    jogWheel.setBounds(colW, rowH * 3, colW * 3, rowH * 5);

//    loadButton.setBounds(0, rowH*7, getWidth(), rowH);
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
        *pitchVal = speedSlider.getValue();
        player->setSpeed(speedSlider.getValue());
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

bool DeckGUI::isInterestedInDragSource(const SourceDetails &dragSourceDetails)
{
    return true;
}

void DeckGUI::itemDropped(const SourceDetails &dragSourceDetails)
{
    auto file = File{dragSourceDetails.description.toString()};
    if (file.existsAsFile())
    {
        //TODO: check if mp3?
        loadFile(file);
    }
    repaint();
}

void DeckGUI::timerCallback()
{
    //TODO: potentially change setposrel and getposrel to actual seconds rather than relative
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}