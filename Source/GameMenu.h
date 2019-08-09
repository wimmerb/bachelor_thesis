/*
  ==============================================================================

    GameMenu.h
    Created: 7 Aug 2019 12:43:12pm
    Author:  expert239

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class GameMenu   : public Component, public ActionBroadcaster
{
public:
    //==============================================================================
    GameMenu();
    ~GameMenu();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    std::function<void(const String & s)> informParent;
private:
    //==============================================================================
    TextButton bla {"Back"};
    
    ShapeButton burgerButton { "burgerButton", Colours::blue, Colours::lightgrey, Colours::white };
    ShapeButton playPauseButton { "playPauseButton", Colours::blue, Colours::lightgrey, Colours::white };
    ShapeButton stopButton { "stopButton", Colours::blue, Colours::lightgrey, Colours::white };
    
    bool isPlaying = false;
    
    // Your private member variables go here...
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GameMenu)
};
