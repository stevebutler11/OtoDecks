#ifndef GUI_APP_EXAMPLE_XMLPARSER_H
#define GUI_APP_EXAMPLE_XMLPARSER_H

#include <JuceHeader.h>
#include "LibraryAudioItem.h"

/**
 * A class that helps parse XML, with the aim to facilitate persistence of audio file data when the application closes
 * and re-opens
 */
class XmlParser {
public:

    /**
     * static function that attempts to load data from an xml file
     * @param xmlFile JUCE File that should have extension .xml
     * @param container reference to a vector that will store LibraryAudioItems for the parsed data
     */
    static void loadXmlFile(const File &xmlFile, std::vector<LibraryAudioItem> &container);

    /**
     * static function that attempts to save data to an xml file
     * @param xmlFile JUCE File with extension .xml
     * @param container reference to a vector that should have LibraryAudioItems in it to store
     */
    static void saveXmlFile(const File &xmlFile, std::vector<LibraryAudioItem> &libraryItems);

    /**
     * xml tag identifiers
     */
    inline static const Identifier LIBRARY_AUDIO_ITEMS_TAG = "LIBRARY_AUDIO_ITEMS";
    inline static const Identifier LIBRARY_AUDIO_ITEM_TAG = "LIBRARY_AUDIO_ITEM";
    inline static const Identifier FULL_FILEPATH_TAG{"FULL_FILEPATH"};
    inline static const Identifier FILENAME_TAG = "FILENAME";
    inline static const Identifier DURATION_TAG = "DURATION";
    inline static const Identifier EXTENSION_TAG = "EXTENSION";
    inline static const Identifier KEY_TAG = "KEY";
    inline static const Identifier BPM_TAG = "BPM";

    // absolute path for the users' music folder
    inline static const std::string USERS_MUSIC_DIRECTORY = File::getSpecialLocation(
            File::SpecialLocationType::userMusicDirectory).getFullPathName().toStdString();
    // file path for our xml file for audio data persistence
    inline static const std::string PERSISTENT_DATA_FILEPATH = USERS_MUSIC_DIRECTORY + "/libraryItems.xml";
};

#endif //GUI_APP_EXAMPLE_XMLPARSER_H
