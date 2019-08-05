/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Points.h"
#include "Chord.h"
#include "ChordVisualisation.h"
#include "VisuSidePanel.h"
#include <time.h>
#include <list>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class VisuMaster   : public AnimatedAppComponent, public OpenGLRenderer
{
public:
    //==============================================================================
    VisuMaster();
    ~VisuMaster();
    
    //==============================================================================
    void mouseDrag(const MouseEvent &event) override;



private:
    //==============================================================================
    // Your private member variables go here...
    
    float currMouseY;
    Image backgroundImage;
    ToggleButton highlightBasicPiano {"highlightBasicPiano"};
    ToggleButton basicPianoVisualizeWholeScale {"basicPianoVisualizeWholeScale"};
    ToggleButton basicPianoVisualizeWithColours {"basicPianoVisualizeWithColours"};
    
    ToggleButton chordsVisualizeAsDots {"chordsVisualizeAsDots"};
    ToggleButton chordsVisualizeAsKeys {"chordsVisualizeAsKeys"};
    ToggleButton chordsFadeOutHorizontal {"chordsFadeOutHorizontal"};
    
    BurgerMenuComponent burgerMenu;
    std::unique_ptr<SidePanel> sidePanel;
    ArrowButton arrowBtn {"SideBar", 0.5f, getLookAndFeel().findColour(Slider::thumbColourId)};
    std::unique_ptr<VisuSidePanel> visuSidePanel;
    
    float visu_lowerBound;
    float visu_range;

    std::vector<Chord> * chordVector;
    Points * points;
    
    ChordVisualisation * chordVisualizer;
    
    void update() override;
    void paint(Graphics &g) override;
    void resized() override;

    void createBackGroundSpace(Graphics &g);
    void createNoteText(float visu_lB, float visu_r, Graphics& g, float height, float width);

    void reAdjustWindow(float p, float timeSinceLastFrameMs);
    float currScreenSpeed = 0.0f;
    int maxScreenSpeed = 40;
    float virtScreenBorder = 0.3f;
    float screenAcceleration = 1.0f;
    
    void renderOpenGL() override;
    OpenGLContext openGLContext;
    void newOpenGLContextCreated() override;
    void openGLContextClosing() override;
    



    static double now_ms();

    //systimes
    double a = 0.0;
    double b = 0.0;

    void displayTiming();

    void setEnterTime();

    void setExitTime();
    
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisuMaster)
};
