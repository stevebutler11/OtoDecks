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

std::string LibraryAudioItem::getFileName() const
{
    return fileName;
}