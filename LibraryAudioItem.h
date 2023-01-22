#ifndef GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
#define GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H

#include <JuceHeader.h>
#include <string>
#include <vector>

class LibraryAudioItem
{
public:
    LibraryAudioItem(File& file, std::string& fileName, double duration, std::string& extension);
    ~LibraryAudioItem();

    void setKey(std::string& key);
    void setBPM(double bpm);
    [[nodiscard]] std::string getFileName() const;
private:
    File file;
    std::string fileName;
    double duration{0.0};
    std::string extension;
    //TODO: enum for key?
    std::string key{};
    double BPM{0.0};
};

#endif //GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
