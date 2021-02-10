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
#include "GameMenu.h"
#include <time.h>
#include <list>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class VisuMaster   : public AnimatedAppComponent //, public OpenGLRenderer
{
public:
    //==============================================================================
    VisuMaster();
    ~VisuMaster();
    
    //==============================================================================
    void mouseDrag(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;
    void mouseDown(const MouseEvent &event) override;
    void mouseMove(const MouseEvent &event) override;
    std::function<void(const String & s)> informParent;



private:
    //==============================================================================
    // Your private member variables go here...
    
    float currMouseY;
    Image backgroundImage;
    
    //std::unique_ptr<SidePanel> sidePanel;
    std::unique_ptr<VisuSidePanel> visuSidePanel;
    GameMenu gameMenu {};
    void receiveFromGameMenu(const String & s);
    
    float visu_lowerBound;
    float visu_range;

    std::vector<Chord> * chordVector;
    
    ChordVisualisation * chordVisualizer;
    
    void update() override;
    void paint(Graphics &g) override;
    void ppaint(Graphics &g);
    void resized() override;

    void createBackGroundSpace(Graphics &g);
    void createNoteText(float visu_lB, float visu_r, Graphics& g, float height, float width);

    void reAdjustWindow(float p, float timeSinceLastFrameMs);
    float currScreenSpeed = 0.0f;
    int maxScreenSpeed = 40;
    float virtScreenBorder = 0.2f;
    float screenAcceleration = 0.55f;
    
    
//    void renderOpenGL() override;
    #if JUCE_IOS
    OpenGLContext openGLContext;
    #endif
//    void newOpenGLContextCreated() override;
//    void openGLContextClosing() override;
    



    static double now_ms();

    //systimes
    double a = 0.0;
    double b = 0.0;

    void displayTiming();

    void setEnterTime();

    void setExitTime();
    
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisuMaster)
};
