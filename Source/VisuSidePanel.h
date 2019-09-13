/*
  ==============================================================================

    VisuSidePanel.h
    Created: 1 Aug 2019 4:53:40pm
    Author:  expert239

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ControllerSingleton.h"

class VisuSidePanel : public SidePanel {
public:
    VisuSidePanel(StringRef title, int width, bool positionOnLeft);
    ~VisuSidePanel();
private:
    ToggleButton highlightBasicPiano {"highlightBasicPiano"};
    ToggleButton basicPianoVisualizeWholeScale {"Chord Notes Only"};
    ToggleButton basicPianoVisualizeWithColours {"basicPianoVisualizeWithColours"};
    ToggleButton basicPianoVisualizeTransparent {"Show Scale On Piano"};
    Slider basicPianoScreenPortion;
    
    ToggleButton chordsVisualize {"chordsVisualize"};
    ToggleButton chordsVisualizeAsDots {"Show Chords as Dots"};
    ToggleButton chordsVisualizeAsKeys {"Show Chords as Bars"};
    ToggleButton chordsFadeOutHorizontal {"Move Chords in Blocks"};
    ToggleButton chordsVisualizeGuideline {"Show Guideline"};
    ToggleButton chordsShowScale {"Show Scale"};

    ToggleButton pitchVisualize {"Show Current Pitch:"};
    ToggleButton pitchVisualizeGraph {"As Graph"};
    ToggleButton pitchVisualizeBubbles {"As Bubbles"};
    ToggleButton pitchVisualizeKeys {"As Marked Keys"};
    
    ToggleButton pitchTrackUseMPM {"MacLeod Pitch Tracker"};
    ToggleButton pitchTrackUseDywa {"Dynamic Wavelet Pitch Tracker"};
    
    ToggleButton pitchFollow {"Follow Pitch with Screen"};
    ToggleButton pitchWrapAround {"Transpose Pitch to Fit"};
    
    ToggleButton dropShadows {"Drop Shadows - !Slower Performance!"};
    ToggleButton keyBoardMode {"Keyboard Mode - !Slower Performance!"};
    
    
    
    Slider barsPerScreen;
    
    void resized() override;
};
