#ifndef GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
#define GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H

#include <JuceHeader.h>
#include <string>
#include <vector>

/**
 * Class that represents an audio item within the library component
 */
class LibraryAudioItem {
public:

    /**
     * LibraryAudioItem constructor
     * @param file Represents a local file or directory
     * @param fileName the name of the file
     * @param duration duration of the track in seconds
     * @param extension file extension
     * @param _key
     * @param _bpm
     */
    LibraryAudioItem(File &file, std::string &fileName, double duration, std::string &extension,
                     std::string _key = "", double _bpm = 0.0);

    /**
     * LibraryAudioItem destructor
     */
    ~LibraryAudioItem();

    void setKey(std::string &key);

    void setBPM(double bpm);

    /**
     * Get the File of the LibraryAudioItem
     * @return JUCE File that is returned
     */
    File getFile();

    /**
     * Get the filename of the LibraryAudioItem
     * @return name of the file
     */
    std::string getFileName() const;

    /**
     * Get the duration of the LibraryAudioItem
     * @return duration in seconds
     */
    double getDuration() const;

    /**
     * Get the duration of the LibraryAudioItem as a std::string, formatted correctly
     * @return formatted duration string
     */
    std::string getDurationFormatted() const;

    /**
     * Get the extension of the LibraryAudioItem
     * @return extension
     */
    std::string getExtension() const;

    std::string getKey() const;

    double getBPM() const;

private:

    // Represents a local file or directory
    File file;

    // name of the file
    std::string fileName;

    // duration of the song in seconds
    double duration{0.0};

    // extension of the JUCE File
    std::string extension;


    std::string key;
    double BPM;
};

#endif //GUI_APP_EXAMPLE_LIBRARYAUDIOITEM_H
