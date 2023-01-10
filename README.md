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

