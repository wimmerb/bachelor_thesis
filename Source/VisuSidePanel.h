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
    ToggleButton basicPianoVisualizeWholeScale {"basicPianoVisualizeWholeScale"};
    ToggleButton basicPianoVisualizeWithColours {"basicPianoVisualizeWithColours"};
    ToggleButton basicPianoVisualizeTransparent {"basicPianoVisualizeTransparent"};
    Slider basicPianoScreenPortion;
    
    ToggleButton chordsVisualize {"chordsVisualize"};
    ToggleButton chordsVisualizeAsDots {"chordsVisualizeAsDots"};
    ToggleButton chordsVisualizeAsKeys {"chordsVisualizeAsKeys"};
    ToggleButton chordsFadeOutHorizontal {"chordsFadeOutHorizontal"};
    ToggleButton chordsVisualizeGuideline {"chordsVisualizeGuideline"};

    ToggleButton pitchVisualize {"pitchVisualize"};
    ToggleButton pitchVisualizeGraph {"pitchVisualizeGraph"};
    ToggleButton pitchVisualizeBubbles {"pitchVisualizeBubbles"};
    ToggleButton pitchVisualizeKeys {"pitchVisualizeKeys"};
    
    ToggleButton dropShadows {"dropShadows"};
    ToggleButton keyBoardMode {"keyBoardMode"};
    
    Slider barsPerScreen;
    
    void resized() override;
};
