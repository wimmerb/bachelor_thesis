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
        basicPianoVisualizeTransparent.setToggleState(ControllerSingleton::basicP_visualizeTransparent, NotificationType::dontSendNotification);
        chordsVisualize.setToggleState(ControllerSingleton::chords_Visualize, NotificationType::dontSendNotification);
        chordsVisualizeAsDots.setToggleState(ControllerSingleton::chords_visualizeAsDots, NotificationType::dontSendNotification);
        chordsVisualizeAsKeys.setToggleState(ControllerSingleton::chords_visualizeAsKeys, NotificationType::dontSendNotification);
        chordsVisualizeGuideline.setToggleState(ControllerSingleton::chords_visualizeGuidelines, NotificationType::dontSendNotification);
        chordsFadeOutHorizontal.setToggleState(ControllerSingleton::chords_BlockMovement, NotificationType::dontSendNotification);
        dropShadows.setToggleState(ControllerSingleton::dropShadows, NotificationType::dontSendNotification);
        keyBoardMode.setToggleState(ControllerSingleton::keyBoardMode, NotificationType::dontSendNotification);
        pitchVisualize.setToggleState(ControllerSingleton::pitch_Visualize, NotificationType::dontSendNotification);
        pitchVisualizeGraph.setToggleState(ControllerSingleton::pitch_visualizeGraph, NotificationType::dontSendNotification);
        pitchVisualizeBubbles.setToggleState(ControllerSingleton::pitch_visualizeBubble, NotificationType::dontSendNotification);
        pitchVisualizeKeys.setToggleState(ControllerSingleton::pitch_visualizeKeys, NotificationType::dontSendNotification);
        pitchTrackUseMPM.setToggleState(ControllerSingleton::pitchTrack_useMPM, NotificationType::dontSendNotification);
        pitchTrackUseDywa.setToggleState(ControllerSingleton::pitchTrack_useDywa, NotificationType::dontSendNotification);
        pitchFollow.setToggleState(ControllerSingleton::pitch_follow, NotificationType::dontSendNotification);
        pitchWrapAround.setToggleState(ControllerSingleton::pitch_wrapAround, NotificationType::dontSendNotification);
        
        barsPerScreen.setSliderStyle(Slider::LinearHorizontal);
        basicPianoScreenPortion.setSliderStyle(Slider::LinearHorizontal);
        
        barsPerScreen.setTextBoxStyle(Slider::NoTextBox, true, 40, 40);
        basicPianoScreenPortion.setTextBoxStyle(Slider::NoTextBox, true, 40, 40);
        
        barsPerScreen.setValue(ControllerSingleton::barsPerScreen);
        basicPianoScreenPortion.setValue(ControllerSingleton::basicp_ScreenPortion);
        
        addAndMakeVisible(highlightBasicPiano);
        addAndMakeVisible(basicPianoVisualizeWholeScale);
        //addAndMakeVisible(basicPianoVisualizeWithColours);
        addAndMakeVisible(basicPianoVisualizeTransparent);
        //addAndMakeVisible(basicPianoScreenPortion);
        addAndMakeVisible(chordsVisualize);
        addAndMakeVisible(chordsVisualizeAsDots);
        addAndMakeVisible(chordsVisualizeAsKeys);
        addAndMakeVisible(chordsFadeOutHorizontal);
        addAndMakeVisible(chordsVisualizeGuideline);
        addAndMakeVisible(dropShadows);
        addAndMakeVisible(keyBoardMode);
        addAndMakeVisible(barsPerScreen);
        addAndMakeVisible(pitchVisualize);
        addAndMakeVisible(pitchVisualizeGraph);
        addAndMakeVisible(pitchVisualizeBubbles);
        addAndMakeVisible(pitchVisualizeKeys);
        addAndMakeVisible(pitchTrackUseMPM);
        addAndMakeVisible(pitchTrackUseDywa);
        addAndMakeVisible(pitchFollow);
        addAndMakeVisible(pitchWrapAround);
        
        highlightBasicPiano.onClick = [this]{ControllerSingleton::basicp_highlightBasicPiano = highlightBasicPiano.getToggleState();};
        basicPianoVisualizeWholeScale.onClick = [this]{ControllerSingleton::basicp_visualizeWholeScale = basicPianoVisualizeWholeScale.getToggleState();};
        basicPianoVisualizeWithColours.onClick = [this]{ControllerSingleton::basicP_visualizeWithColours = basicPianoVisualizeWithColours.getToggleState();};
        basicPianoVisualizeTransparent.onClick = [this]{ControllerSingleton::basicP_visualizeTransparent = basicPianoVisualizeTransparent.getToggleState();};
        chordsVisualize.onClick = [this]{ControllerSingleton::chords_Visualize = chordsVisualize.getToggleState();};
        chordsVisualizeAsDots.onClick = [this]{ControllerSingleton::chords_visualizeAsDots = chordsVisualizeAsDots.getToggleState();};
        chordsVisualizeAsKeys.onClick = [this]{ControllerSingleton::chords_visualizeAsKeys = chordsVisualizeAsKeys.getToggleState();};
        chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_BlockMovement = chordsFadeOutHorizontal.getToggleState();};
        chordsVisualizeGuideline.onClick = [this]{ControllerSingleton::chords_visualizeGuidelines = chordsVisualizeGuideline.getToggleState();};
        dropShadows.onClick = [this]{ControllerSingleton::dropShadows = dropShadows.getToggleState();};
        keyBoardMode.onClick = [this]{ControllerSingleton::keyBoardMode = keyBoardMode.getToggleState();};
        pitchVisualize.onClick = [this]{ControllerSingleton::pitch_Visualize = pitchVisualize.getToggleState();};
        pitchVisualizeGraph.onClick = [this]{ControllerSingleton::pitch_visualizeGraph = pitchVisualizeGraph.getToggleState();};
        pitchVisualizeBubbles.onClick = [this]{ControllerSingleton::pitch_visualizeBubble = pitchVisualizeBubbles.getToggleState();};
        pitchVisualizeKeys.onClick = [this]{ControllerSingleton::pitch_visualizeKeys = pitchVisualizeKeys.getToggleState();};
        pitchTrackUseMPM.onClick = [this]{ControllerSingleton::pitchTrack_useMPM = pitchTrackUseMPM.getToggleState();};
        pitchTrackUseDywa.onClick = [this]{ControllerSingleton::pitchTrack_useDywa = pitchTrackUseDywa.getToggleState();};
        pitchFollow.onClick = [this]{ControllerSingleton::pitch_follow = pitchFollow.getToggleState();};
        pitchWrapAround.onClick = [this]{ControllerSingleton::pitch_wrapAround = pitchWrapAround.getToggleState();};
        
        barsPerScreen.setRange(1.0, 3.0, 1.0);
        barsPerScreen.onValueChange = [this]{ControllerSingleton::barsPerScreen = std::round(barsPerScreen.getValue());};
        basicPianoScreenPortion.setRange(0.1,1.0);
        basicPianoScreenPortion.onValueChange = [this]{ControllerSingleton::basicp_ScreenPortion = (float)basicPianoScreenPortion.getValue();};
        
        //chordsVisualizeAsDots.setRadioGroupId(1000);
        //chordsVisualizeAsKeys.setRadioGroupId(1000);
        
        pitchVisualizeGraph.setRadioGroupId(1001);
        pitchVisualizeBubbles.setRadioGroupId(1001);
        pitchVisualizeKeys.setRadioGroupId(1001);
        
        pitchTrackUseDywa.setRadioGroupId(1002);
        pitchTrackUseMPM.setRadioGroupId(1002);
        
        pitchFollow.setRadioGroupId(1003);
        pitchWrapAround.setRadioGroupId(1003);
        
};

VisuSidePanel::~VisuSidePanel(){};

void VisuSidePanel::resized(){
    SidePanel::resized();
    auto bounds = getLocalBounds().removeFromRight(280);
    bounds.removeFromTop(50).removeFromLeft(50);
    dropShadows.setBounds(bounds.removeFromTop(40));
    keyBoardMode.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    highlightBasicPiano.setBounds(bounds.removeFromTop(40));
    //basicPianoVisualizeWithColours.setBounds(bounds.removeFromTop(40));
    
    basicPianoVisualizeTransparent.setBounds(bounds.removeFromTop(40));
    //basicPianoScreenPortion.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    chordsVisualize.setBounds(bounds.removeFromTop(40));
    chordsVisualizeAsDots.setBounds(bounds.removeFromTop(40));
    chordsVisualizeAsKeys.setBounds(bounds.removeFromTop(40));
    chordsFadeOutHorizontal.setBounds(bounds.removeFromTop(40));
    basicPianoVisualizeWholeScale.setBounds(bounds.removeFromTop(40));
    chordsVisualizeGuideline.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);
    pitchVisualize.setBounds(bounds.removeFromTop(40));
    pitchVisualizeGraph.setBounds(bounds.removeFromTop(40));
    pitchVisualizeBubbles.setBounds(bounds.removeFromTop(40));
    pitchVisualizeKeys.setBounds(bounds.removeFromTop(40));
    pitchFollow.setBounds(bounds.removeFromTop(40));
    pitchWrapAround.setBounds(bounds.removeFromTop(40));
    //bounds.removeFromTop(40);
    barsPerScreen.setBounds(bounds.removeFromTop(40));
    //bounds.removeFromTop(40);
    pitchTrackUseDywa.setBounds(bounds.removeFromTop(40));
    pitchTrackUseMPM.setBounds(bounds.removeFromTop(40));
}
/*
 chordsFadeOutHorizontal.setToggleState(ControllerSingleton::chords_fadeOutHorizontal, NotificationType::dontSendNotification);
 addAndMakeVisible(chordsFadeOutHorizontal);
 chordsFadeOutHorizontal.onClick = [this]{ControllerSingleton::chords_fadeOutHorizontal = chordsFadeOutHorizontal.getToggleState();};
*/
