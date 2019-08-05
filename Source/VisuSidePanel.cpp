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
        addAndMakeVisible(barsPerScreen);
        
        highlightBasicPiano.onClick = [this]{ControllerSingleton::basicp_highlightBasicPiano = highlightBasicPiano.getToggleState();};
        basicPianoVisualizeWholeScale.onClick = [this]{ControllerSingleton::basicp_visualizeWholeScale = basicPianoVisualizeWholeScale.getToggleState();};
        basicPianoVisualizeWithColours.onClick = [this]{ControllerSingleton::basicP_visualizeWithColours = basicPianoVisualizeWithColours.getToggleState();};
        chordsVisualizeAsDots.onClick = [this]{ControllerSingleton::chords_visualizeAsDots = chordsVisualizeAsDots.getToggleState();};
        chordsVisualizeAsKeys.onClick = [this]{ControllerSingleton::chords_visualizeAsKeys = chordsVisualizeAsKeys.getToggleState();};
        chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_fadeOutHorizontal = chordsFadeOutHorizontal.getToggleState();};
        
        barsPerScreen.setRange(2.0, 10.0, 1.0);
        barsPerScreen.onValueChange = [this]{ControllerSingleton::barsPerScreen = std::round(barsPerScreen.getValue());};
        
        
        
        chordsVisualizeAsDots.setRadioGroupId(1000);
        chordsVisualizeAsKeys.setRadioGroupId(1000);
    
    
        
    
};

VisuSidePanel::~VisuSidePanel(){};

void VisuSidePanel::resized(){
    SidePanel::resized();
    
    int x = std::round(getWidth()*0.1);
    int base = 50;
    int i = 0;
    highlightBasicPiano.setBounds(x,base+i++*40,200,40);
    basicPianoVisualizeWithColours.setBounds(x,base+i++*40,200,40);
    basicPianoVisualizeWholeScale.setBounds(x,base+i++*40,200,40);
    i++;
    chordsVisualizeAsDots.setBounds(x,base+i++*40,200,40);
    chordsVisualizeAsKeys.setBounds(x,base+i++*40,200,40);
    chordsFadeOutHorizontal.setBounds(x,base+i++*40,200,40);
    i++;
    barsPerScreen.setBounds(x,base+i++*40,200,40);
}
/*
 chordsFadeOutHorizontal.setToggleState(ControllerSingleton::chords_fadeOutHorizontal, NotificationType::dontSendNotification);
 addAndMakeVisible(chordsFadeOutHorizontal);
 chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_fadeOutHorizontal = chordsFadeOutHorizontal.getToggleState();};
*/
