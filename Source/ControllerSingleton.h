/*
  ==============================================================================

    ControllerSingleton.h
    Created: 25 Jun 2019 1:09:29pm
    Author:  expert239

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ControllerSingleton
{
public:

    //==========================================================================
    ControllerSingleton();
    ~ControllerSingleton();
    //==========================================================================
    static void init(std::vector<bool> bla, bool basicp__visualizeWholeScale, bool basicP__visualizeWithColours, bool chords__visualizeWithColours);
    //GRAPHICS
    static int fps;
    static int barsPerScreen;
    static bool dropShadows;
    //beatsperbar
    static int bpb;
    //beatsperminute
    static int bpm;
    static float timePerBarMs;
    
    static int nrOfVisualizedKeys;
    static int nrPoints;
    static Colour backgroundColor;
    static Colour pointsColor;

    
    //VisualizationMode
    static bool keyBoardMode;
    //PitchVisualisation
    static bool snapPitchToGrid;
    
    //ChordVisualisation
    static bool chords_visualizeAsDots;
    static bool chords_visualizeAsKeys;
    static bool * chords_visuArray;
    static bool chords_visualizeWithColours;
    static bool chords_fadeOutHorizontal;
    
    //BasicPianoVisualisation
    static bool basicp_highlightBasicPiano;
    static bool basicp_visualizeWholeScale;
    static bool basicP_visualizeWithColours;
    //==========================================================================
    //BASICCONTROL
    static bool isPlaying;
    static bool isLooping;
    
    
private:

    //==========================================================================
    
    //==========================================================================
    
};
