# OtoDecks

## Overview

![app screenshot](./assets/app_screenshot.png)

OtoDecks is a DJ software application designed for the playback and mixing of multiple audio tracks as a disk jockey would with physical DJ decks. The software is written in C++, and utilises the [JUCE](https://juce.com/) audio and GUI programming framework.


## Features

### Realistic DJ Decks
- UI of the DJ decks akin to industry standard DJ hardware
- jogwheel implemented to alter the tempo of the track on the fly
- tempo slider to alter track tempo to aid in mixing
- cue, play and pause buttons
- cue points can be set on the track by zooming into the track waveform display and setting
- scrolling track info display

### Mixer
- two channel mixer implemented
- individual volume sliders 
- crossfader slider

### Music Library
- stage tracks from local storage into the music library
- track metadata displayed on screen
- library search/filter/sort capabilities
- load tracks onto decks from the library
- library state is saved to xml file so music library is persistent

### Custom Theme
- Overrides the Juce LookAndFeel_V4 class to create a custom theme

## Building

Below are the steps to build and run (tested on ubuntu 22.04 and windows 11 WSL Ubuntu 22.04).

> [!NOTE]  
> You may be missing packages. If so, see [JUCE Dependencies on Linux](https://github.com/juce-framework/JUCE/blob/develop/docs/Linux%20Dependencies.md)

1. clone the repo
2. in the root directory, pull the juce submodule locally:

```bash
git submodule update --init --remote --recursive
```

3. build application

```bash
mkdir .build && .build
cmake ..
make
```

4. run application

```bash
./OtoDecks_artefacts/OtoDecks
```