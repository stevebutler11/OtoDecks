#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(DJAudioPlayer *_player,
                                 AudioFormatManager &formatManagerToUse,
                                 AudioThumbnailCache &cacheToUse
) : player(_player), audioThumbnail(
        1000,
        formatManagerToUse,
        cacheToUse), fileLoaded(false), position(0.0) {
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay() {}

void WaveformDisplay::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ListBox::ColourIds::backgroundColourId));

    if (fileLoaded) {
        auto cg = ColourGradient(Colour::fromString("FFC75450"),
                                 0.0, 0.0,
                                 Colour::fromString("FFC75450"),
                                 0.0,
                                 getLocalBounds().getHeight(),
                                 false);

        cg.addColour(0.5, Colour::fromString("FF3592C4"));
        g.setGradientFill(cg);

        auto scrollableThumbnailArea = Rectangle<int>{
                (int) -(zoomFactor * leftWidthOffset),
                0,
                (int) (getLocalBounds().getWidth() + (zoomFactor * rightWidthOffset) + (zoomFactor * leftWidthOffset)),
                getHeight()};

        audioThumbnail.drawChannel(
                g,
                scrollableThumbnailArea,
                0,
                audioThumbnail.getTotalLength(),
                0,
                1.0f);

        // draw cue mark
        g.setColour(juce::Colours::blueviolet);

        auto cueMap = WaveformDisplay::map(
                cuePosition * getLocalBounds().getWidth(),
                0,
                getLocalBounds().getWidth(),
                scrollableThumbnailArea.getX(),
                scrollableThumbnailArea.getX() + scrollableThumbnailArea.getWidth());

        g.fillRect(cueMap, 0, 1, getLocalBounds().getHeight());

        // draw current position
        if (!std::isnan(position)) {
            g.setColour(juce::Colours::lightgreen);

            auto posMap = WaveformDisplay::map(
                    position * getLocalBounds().getWidth(),
                    0,
                    getLocalBounds().getWidth(),
                    scrollableThumbnailArea.getX(),
                    scrollableThumbnailArea.getX() + scrollableThumbnailArea.getWidth());

            g.fillRect(posMap, 0, 1, getLocalBounds().getHeight());
        }
    }
}

void WaveformDisplay::resized() {

}

void WaveformDisplay::loadURL(const URL &audioURL) {
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
    if (!fileLoaded) {
        std::cout << "WaveformDisplay::loadURL load error" << std::endl;
    }
}

void WaveformDisplay::setPositionRelative(double pos) {
    if (position != pos) {
        position = pos;
        repaint();
    }
}

double WaveformDisplay::getCuePositionRelative() const {
    return cuePosition;
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source) {
    repaint();
}

void WaveformDisplay::mouseDown(const MouseEvent &event) {
    auto trackWidthRatio = getTrackWidthRatio();

    // setting cue position
    if (event.mods.isShiftDown()) {
        cuePosition = trackWidthRatio;
        repaint();
    }
        // setting play position
    else {
        player->setPositionRelative(trackWidthRatio);
    }
}

void WaveformDisplay::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    if (event.mods.isShiftDown()) {
        zoomFactor = (zoomFactor + (wheel.deltaY * 80) > 1) ? zoomFactor + (wheel.deltaY * 80) : 1.0;
        auto mouseWidthRatio = getMouseWidthRatio();
        leftWidthOffset = mouseWidthRatio;
        rightWidthOffset = 1 - mouseWidthRatio;
        repaint();
    }
}

double WaveformDisplay::getMouseWidthRatio() {
    auto mouseXY = getMouseXYRelative();
    auto mouseWidthRatio = (double) mouseXY.getX() / (double) this->getWidth();
    return mouseWidthRatio;
}

double WaveformDisplay::getTrackWidthRatio() {
    return (getMouseWidthRatio() * getLocalBounds().getWidth() + (zoomFactor * leftWidthOffset)) /
           ((getLocalBounds().getWidth() + (zoomFactor * rightWidthOffset) + (zoomFactor * leftWidthOffset)));
}

double WaveformDisplay::map(double x, double lowCurrent, double highCurrent, double lowTarget, double highTarget) {
    auto ratio = (x - lowCurrent) / (highCurrent - lowCurrent);
    return ratio * (highTarget - lowTarget) + lowTarget;
}