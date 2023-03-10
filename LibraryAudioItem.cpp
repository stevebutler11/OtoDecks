#include "LibraryAudioItem.h"

LibraryAudioItem::LibraryAudioItem(File &_file,
                                   std::string &_fileName,
                                   double _duration,
                                   std::string &_extension,
                                   std::string _key,
                                   double _bpm
) : file(_file),
    fileName(_fileName),
    duration(_duration),
    extension(_extension),
    key((std::string &) _key),
    BPM(_bpm) {}

LibraryAudioItem::~LibraryAudioItem() {

}

void LibraryAudioItem::setKey(std::string &_key) {
    key = _key;
}

void LibraryAudioItem::setBPM(double _BPM) {
    BPM = _BPM;
}

File LibraryAudioItem::getFile() {
    return file;
}

std::string LibraryAudioItem::getFileName() const {
    return fileName;
}

double LibraryAudioItem::getDuration() const {
    return duration;
}

std::string LibraryAudioItem::getDurationFormatted() const {
    auto mins = std::to_string((int) duration / 60);
    auto remaining_secs = std::to_string((int) std::fmod(duration, 60));

    mins.insert(mins.begin(), (int) 2 - mins.size(), '0');
    remaining_secs.insert(remaining_secs.begin(), (int) 2 - remaining_secs.size(), '0');

    return mins + ":" + remaining_secs + "s";
}

std::string LibraryAudioItem::getExtension() const {
    return extension;
}

std::string LibraryAudioItem::getKey() const {
    return key;
}

double LibraryAudioItem::getBPM() const {
    return BPM;
}