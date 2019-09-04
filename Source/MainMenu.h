/*
  ==============================================================================

    MainMenu.h
    Created: 7 Aug 2019 12:42:50pm
    Author:  expert239

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainMenu   : public Component, private ComboBox::Listener , public ActionBroadcaster
{
public:
    //==============================================================================
    MainMenu();
    ~MainMenu();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    std::function<void(const String & s)> informParent;
private:
    //==============================================================================
    // Your private member variables go here...
    //File f {"/Users/expert239/Desktop/bachelor_thesis/SongFolders"};
    File f;
    ComboBox songBox;
    TextButton play {"Play"}, modify {"modify Song"};
    String mainMessage {"Choose a Song"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenu)
};
