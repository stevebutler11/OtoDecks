#include "DeckGUI.h"



DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse
                 ) : player(_player),
                     waveformDisplay(_player, formatManagerToUse, cacheToUse) // pass cstr args directly to wavfrmDisp
{
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(cueButton);
    addAndMakeVisible(tempoSlider);
    addAndMakeVisible(jogWheel);
    addAndMakeVisible(trackInfoDisplay);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(tempoLabel);

    playPauseButton.addListener(this);
    cueButton.addListener(this);
    tempoSlider.addListener(this);

    tempoSlider.setRange(0.92, 1.08);
    tempoSlider.setValue(1.0);

    formatLabel(tempoLabel, "TEMPO +/- 8%");

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
}

void DeckGUI::resized()
{
    int rowH = getHeight()/12;
    int colW = getWidth()/5;

    trackInfoDisplay.setBounds(0, 0, colW*5, rowH);
    waveformDisplay.setBounds(0, rowH, colW*5, rowH*2);

    cueButton.setBounds(0, rowH * 8, colW, rowH*2);
    playPauseButton.setBounds(0, rowH * 10, colW, rowH*2);

    tempoSlider.setBounds(colW * 4, rowH*3, colW, (int) (rowH * 8.5));
    tempoLabel.setBounds(colW * 4, rowH*11, colW, rowH);
    jogWheel.setBounds(colW, rowH * 3, colW * 3, rowH * 9);
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
    if (slider == &tempoSlider)
    {
        *tempoVal = tempoSlider.getValue();
        player->setSpeed(tempoSlider.getValue());
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

void DeckGUI::formatLabel(Label& label, std::string text)
{
    Typeface::Ptr tface = Typeface::createSystemTypefaceFor(BinaryData::neuropol_otf, BinaryData::neuropol_otfSize);
    label.setText (text, juce::dontSendNotification);
    label.setFont(Font(tface).withHeight(10.0f));
    label.setColour (juce::Label::textColourId, juce::Colours::grey);
    label.setJustificationType (juce::Justification::centredBottom);
}