/*
  ==============================================================================

    ControllerSingleton.cpp
    Created: 25 Jun 2019 1:09:29pm
    Author:  expert239

  ==============================================================================
*/

#include "ControllerSingleton.h"
#include "Chord.h"

ControllerSingleton::ControllerSingleton(){}
ControllerSingleton::~ControllerSingleton(){}



void ControllerSingleton::init(std::vector<bool> bla, bool basicp__visualizeWholeScale, bool basicP__visualizeWithColours, bool chords__visualizeWithColours){
    backgroundColor = Colours::darkgrey.interpolatedWith(Colours::darkblue, 0.5f);
    pointsColor = Colours::turquoise;

    for(int i = 0; i < 9; i++){
        chords_visuArray[i] = bla[i];
    }
    basicp_visualizeWholeScale = basicp__visualizeWholeScale;
    basicP_visualizeWithColours = basicP__visualizeWithColours;
    chords_visualizeWithColours = chords__visualizeWithColours;
}

int ControllerSingleton::fps = 60;

int ControllerSingleton::barsPerScreen = 4;
bool ControllerSingleton::dropShadows = true;
//TODO beatsperbar, bpm, timeperbarMs, fps sollten eher in Model/SharedResources
//beatsperbar
int ControllerSingleton::bpb = 4;
//beatsperminute
int ControllerSingleton::bpm = 90;
float ControllerSingleton::timePerBarMs = 60000.0f/((float)bpm)*(float)bpb;

int ControllerSingleton::nrOfVisualizedKeys = 24;
int ControllerSingleton::nrPoints = 30;
Colour ControllerSingleton::backgroundColor = Colours::darkgrey.interpolatedWith(Colours::darkblue, 0.2f);
Colour ControllerSingleton::pointsColor = Colours::turquoise;


//VisualizationMode
bool ControllerSingleton::keyBoardMode = false;

//PitchVisualisation
bool ControllerSingleton::snapPitchToGrid = true;

//ChordVisualisation
bool * ControllerSingleton::chords_visuArray = new bool [9]{true,true,true,true,false,false,false,true,false};
bool ControllerSingleton::chords_visualizeAsDots = true;
bool ControllerSingleton::chords_visualizeAsKeys = false;
bool ControllerSingleton::chords_visualizeWithColours = true;
bool ControllerSingleton::chords_fadeOutHorizontal = false;
bool ControllerSingleton::chords_visualizeGuidelines = true;

//BasicPianoVisualisation
bool ControllerSingleton::basicp_highlightBasicPiano = true;
bool ControllerSingleton::basicp_visualizeWholeScale = true;
bool ControllerSingleton::basicP_visualizeWithColours = true;
//==========================================================================
//BASICCONTROL
bool ControllerSingleton::isPlaying = false;
bool ControllerSingleton::isLooping = true;
