/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainMenu.h"
#include "VisuMaster.h"
#include "AnalyserComponent.h"
#include "ControllerSingleton.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component, public ActionListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void resized() override;
    void paint (Graphics&) override;
    //==============================================================================
    void handleInformation(const String & s);
    
    void actionListenerCallback(const String & message) override;
    
private:
    std::unique_ptr<VisuMaster> visuMaster;
    std::unique_ptr<AnalyserComponent> analyser;
    std::unique_ptr<MainMenu> mainMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
