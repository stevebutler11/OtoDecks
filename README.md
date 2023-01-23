# OtoDecks

### DJ application written with the JUCE framework

## Notes on getting it built the first time:
- start new proj
- add juce submodule
- copy all files from JUCE/examples/CMake/GuiApp
- replace main.cpp and CMakeFiles.txt in main folder with copied files
- edit CMakeFiles.txt to suit 
  - uncomment add_subdirectory(JUCE)
  - change proj names
  - add juce::juce_audio_utils to target_link_libraries PRIVATE

## TODO list (for use with project report later on)

### LibraryComponent
- ~~create library row data type~~
- ~~add 'add to library' functionality~~
- ~~remove button impl. on each row~~
- ~~refactor project to add a deckLoader class, to facilitate loading decks from the libraryComponent~~
- ~~impl. load buttons on each row, for left and right decks~~
- ~~add drag and drop functionality (from native file explorer to the library)~~
- ~~add sort functionality~~
  - almost finished, needs tidying
- ~~add persistence via an Xml file~~
  - ~~create XmlParser class, with static: loadXml, saveXml functions~~ 
  - ~~create importXml and exportXml functions on the LibraryComponent class~~
  - maybe check for duplicate files?
- add drag and drop functionality (from library to an individual deck)
- add search functionality

### DeckGUI
- potentially add track to library if drag and drop comes from the deckGUI itself
- 

## features to implement
- handle more filetypes than mp3
- create audioAnalysis class to impl. bpm and key finding algorithms