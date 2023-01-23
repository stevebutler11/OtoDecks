#ifndef GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
#define GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H

#include <JuceHeader.h>
#include <string>
#include <vector>

class LibraryAudioItem
{
public:
    LibraryAudioItem(File& file, std::string& fileName, double duration, std::string& extension,
                     std::string _key = "", double _bpm = 0.0);
    ~LibraryAudioItem();

    void setKey(std::string& key);
    void setBPM(double bpm);
    File getFile();
    std::string getFileName() const;
    double getDuration() const;
    std::string getDurationFormatted() const;
    std::string getExtension() const;
    std::string getKey() const;
    double getBPM() const;
private:
    File file;
    std::string fileName;
    double duration{0.0};
    std::string extension;
    //TODO: enum for key?
    std::string key;
    double BPM;
};

#endif //GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
