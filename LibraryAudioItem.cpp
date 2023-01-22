#include "LibraryAudioItem.h"

LibraryAudioItem::LibraryAudioItem(File& _file, std::string& _fileName, double _duration, std::string& _extension
                                    ) :file(_file), fileName(_fileName), duration(_duration), extension(_extension)
{

}

LibraryAudioItem::~LibraryAudioItem()
{

}

void LibraryAudioItem::setKey(std::string& _key)
{
    key = _key;
}

void LibraryAudioItem::setBPM(double _BPM)
{
    BPM = _BPM;
}

File LibraryAudioItem::getFile()
{
    return file;
}

std::string LibraryAudioItem::getFileName() const
{
    return fileName;
}

double LibraryAudioItem::getDuration() const
{
    return duration;
}

std::string LibraryAudioItem::getDurationFormatted() const
{
    int mins = duration / 60;
    int remaining_secs = std::fmod(duration, 60);

    return std::to_string(mins) + ":" + std::to_string(remaining_secs) + "s";
}

std::string LibraryAudioItem::getExtension() const
{
    return extension;
}

std::string LibraryAudioItem::getKey() const
{
    return key;
}

double LibraryAudioItem::getBPM() const
{
    return BPM;
}