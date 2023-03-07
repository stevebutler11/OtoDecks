#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse
                 ) : player(_player),
                     waveformDisplay(_player, formatManagerToUse, cacheToUse) // pass cstr args directly to wavfrmDisp
{
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(cueButton);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(trackInfoDisplay);
    addAndMakeVisible(waveformDisplay);

    playPauseButton.addListener(this);
    cueButton.addListener(this);
    speedSlider.addListener(this);

    speedSlider.setRange(0.92, 1.08);
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
    trackInfoDisplay.setText(file.getFileName().toStdString());
}

void DeckGUI::paint(Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour(juce::Colours::grey);
//    g.drawRect(getLocalBounds(), 1);
}

void DeckGUI::resized()
{
    int rowH = getHeight()/8;
    int colW = getWidth()/5;

    trackInfoDisplay.setBounds(0, 0, colW*5, rowH/2);
    waveformDisplay.setBounds(0, rowH/2, colW*5, rowH);

    cueButton.setBounds(0, rowH * 6, colW, rowH);
    playPauseButton.setBounds(0, rowH * 7, colW, rowH);

    speedSlider.setBounds(colW * 4, rowH*2, colW, rowH * 6);
    jogWheel.setBounds(colW, rowH * 3, colW * 3, rowH * 5);
}

void DeckGUI::buttonClicked(Button *button)
{
    if (button == &playPauseButton)
    {
        player->isPlaying() ? player->stop() : player->start();
    }
    if (button == &cueButton)
    {
        player->setPositionRelative(waveformDisplay.getCuePositionRelative());
        player->start();
    }
}

void DeckGUI::sliderValueChanged(Slider *slider)
{
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
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}