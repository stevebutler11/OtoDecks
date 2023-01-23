#ifndef GUI_APP_EXAMPLE_XMLPARSER_H
#define GUI_APP_EXAMPLE_XMLPARSER_H

#include <JuceHeader.h>
#include "LibraryAudioItem.h"

class XmlParser
{
public:
    static void loadXmlFile(const File& xmlFile, std::vector<LibraryAudioItem>& container);
    static void saveXmlFile(const File& xmlFile, std::vector<LibraryAudioItem>& libraryItems);

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

    /**
     * temporary abs file path for the data
     */
     //TODO: change this to something more appropriate
    inline static const std::string PERSISTENT_DATA_FILEPATH = "/home/steve/libraryItems.xml";
};

#endif //GUI_APP_EXAMPLE_XMLPARSER_H
