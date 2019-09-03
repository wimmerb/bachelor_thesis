/*
  ==============================================================================

    SharedResources.cpp
    Created: 29 Jul 2019 12:25:33pm
    Author:  expert239

  ==============================================================================
*/

#include "SharedResources.h"

void SharedResources::init() {
    for(int i = 0; i < pitchHistorySize; i++){
        std::cout << "beenthere";
        pitchHistory.push_back(std::pair<double, int>(0.0, 0));
    }
    pitchHistoryIndex = 0;
}
int SharedResources::samplerate = 44100; //TODO right initiation

//latest tracked pitch
double SharedResources::trackedPitch = 1.0;

//FiFo for tracked pitches
std::vector<std::pair<double,int>> SharedResources::pitchHistory;
const int SharedResources::pitchHistorySize = 2048;
int SharedResources::pitchHistoryIndex = 0;

//Delta in Samples
int SharedResources::samplesPositionOfSong = 0;
int SharedResources::sampleCountOfSong = 0;

//Functionality for CountIn
bool SharedResources::countIn = true;
