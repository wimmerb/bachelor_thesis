/*
  ==============================================================================

    VisuSidePanel.cpp
    Created: 1 Aug 2019 4:53:40pm
    Author:  expert239

  ==============================================================================
*/

#include "VisuSidePanel.h"


VisuSidePanel::VisuSidePanel(StringRef title, int width, bool positionOnLeft)
    : SidePanel(title, width, positionOnLeft) {
    
        highlightBasicPiano.setToggleState(ControllerSingleton::basicp_highlightBasicPiano, NotificationType::dontSendNotification);
        basicPianoVisualizeWholeScale.setToggleState(ControllerSingleton::basicp_visualizeWholeScale, NotificationType::dontSendNotification);
        basicPianoVisualizeWithColours.setToggleState(ControllerSingleton::basicP_visualizeWithColours, NotificationType::dontSendNotification);
        chordsVisualizeAsDots.setToggleState(ControllerSingleton::chords_visualizeAsDots, NotificationType::dontSendNotification);
        chordsVisualizeAsKeys.setToggleState(ControllerSingleton::chords_visualizeAsKeys, NotificationType::dontSendNotification);
        keyBoardMode.setToggleState(ControllerSingleton::keyBoardMode, NotificationType::dontSendNotification);
        
        barsPerScreen.setSliderStyle(Slider::LinearHorizontal);
        
        barsPerScreen.setTextBoxStyle(Slider::NoTextBox, true, 40, 40);
        chordsFadeOutHorizontal.setToggleState(ControllerSingleton::chords_fadeOutHorizontal, NotificationType::dontSendNotification);
        barsPerScreen.setValue(ControllerSingleton::barsPerScreen);
        
        addAndMakeVisible(highlightBasicPiano);
        addAndMakeVisible(basicPianoVisualizeWholeScale);
        addAndMakeVisible(basicPianoVisualizeWithColours);
        addAndMakeVisible(chordsVisualizeAsDots);
        addAndMakeVisible(chordsVisualizeAsKeys);
        addAndMakeVisible(chordsFadeOutHorizontal);
        addAndMakeVisible(keyBoardMode);
        addAndMakeVisible(barsPerScreen);
        
        highlightBasicPiano.onClick = [this]{ControllerSingleton::basicp_highlightBasicPiano = highlightBasicPiano.getToggleState();};
        basicPianoVisualizeWholeScale.onClick = [this]{ControllerSingleton::basicp_visualizeWholeScale = basicPianoVisualizeWholeScale.getToggleState();};
        basicPianoVisualizeWithColours.onClick = [this]{ControllerSingleton::basicP_visualizeWithColours = basicPianoVisualizeWithColours.getToggleState();};
        chordsVisualizeAsDots.onClick = [this]{ControllerSingleton::chords_visualizeAsDots = chordsVisualizeAsDots.getToggleState();};
        chordsVisualizeAsKeys.onClick = [this]{ControllerSingleton::chords_visualizeAsKeys = chordsVisualizeAsKeys.getToggleState();};
        chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_fadeOutHorizontal = chordsFadeOutHorizontal.getToggleState();};
        keyBoardMode.onClick = [this]{ControllerSingleton::keyBoardMode = keyBoardMode.getToggleState();};
        
        barsPerScreen.setRange(2.0, 10.0, 1.0);
        barsPerScreen.onValueChange = [this]{ControllerSingleton::barsPerScreen = std::round(barsPerScreen.getValue());};
        
        
        
        chordsVisualizeAsDots.setRadioGroupId(1000);
        chordsVisualizeAsKeys.setRadioGroupId(1000);
    
    
        
    
};

VisuSidePanel::~VisuSidePanel(){};

void VisuSidePanel::resized(){
    SidePanel::resized();
    auto bounds = getLocalBounds().removeFromRight(280);
    bounds.removeFromTop(50).removeFromLeft(50);
    highlightBasicPiano.setBounds(bounds.removeFromTop(40));
    basicPianoVisualizeWithColours.setBounds(bounds.removeFromTop(40));
    basicPianoVisualizeWholeScale.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    chordsVisualizeAsDots.setBounds(bounds.removeFromTop(40));
    chordsVisualizeAsKeys.setBounds(bounds.removeFromTop(40));
    chordsFadeOutHorizontal.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    keyBoardMode.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    barsPerScreen.setBounds(bounds.removeFromTop(40));
}
/*
 chordsFadeOutHorizontal.setToggleState(ControllerSingleton::chords_fadeOutHorizontal, NotificationType::dontSendNotification);
 addAndMakeVisible(chordsFadeOutHorizontal);
 chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_fadeOutHorizontal = chordsFadeOutHorizontal.getToggleState();};
*/
