/*
  ==============================================================================

    SharedResources.h
    Created: 29 Jul 2019 12:25:33pm
    Author:  expert239

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class SharedResources{
public:
    static int samplerate;
    
    //latest tracked pitch
    static double trackedPitch;
    
    //FiFo for tracked pitches as tuple (pitch, sampleCountinSong)
    static std::pair<double, int> * pitchHistory;
    static int pitchHistorySize;
    static int pitchHistoryIndex;
    
    //Delta in Samples
    static int samplesPositionOfSong;
    static int sampleCountOfSong;
    
    //Functionality for Counting in
    static bool countIn;
    
private:
    
};
