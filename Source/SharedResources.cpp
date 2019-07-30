/*
  ==============================================================================

    SharedResources.cpp
    Created: 29 Jul 2019 12:25:33pm
    Author:  expert239

  ==============================================================================
*/

#include "SharedResources.h"

int SharedResources::samplerate = 44100; //TODO right initiation

//latest tracked pitch
double SharedResources::trackedPitch = 1.0;

//FiFo for tracked pitches
std::pair<double, int> * SharedResources::pitchHistory = new std::pair<double, int> [2048]{std::pair<double, int>(0.0, 0)};
int SharedResources::pitchHistorySize = 2048;
int SharedResources::pitchHistoryIndex = 0;

//Delta in Samples
int SharedResources::samplesPositionOfSong = 0;
int SharedResources::sampleCountOfSong = 0;
