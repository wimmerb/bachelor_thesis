/*
  ==============================================================================

    GameMenu.cpp
    Created: 7 Aug 2019 12:43:12pm
    Author:  expert239

  ==============================================================================
*/

#include "GameMenu.h"

GameMenu::GameMenu()
{
    Colour x = Colours::cyan.interpolatedWith(Colours::darkblue, 0.45f);
    burgerButton.setColours ( x,
                             x.interpolatedWith(Colours::lightgrey, 0.3f),
                             x.interpolatedWith(Colours::lightgrey, 0.6f));
    
    playPauseButton.setColours ( x,
                                x.interpolatedWith(Colours::lightgrey, 0.3f),
                                x.interpolatedWith(Colours::lightgrey, 0.6f));
    
    stopButton.setColours ( x,
                                x.interpolatedWith(Colours::lightgrey, 0.3f),
                                x.interpolatedWith(Colours::lightgrey, 0.6f));
    
    //burgerButton.setOutline(Colours::grey, 0.5f);
    //playPauseButton.setOutline(Colours::grey, 0.5f);
    
    addAndMakeVisible(bla);
    bla.onClick = [this]{informParent("Back");};
    
    static const unsigned char burgerMenuPathData[]
    = { 110,109,0,0,192,65,0,0,192,64,108,0,0,0,0,0,0,192,64,108,0,0,0,0,0,0,0,64,108,0,0,192,65,0,0,0,64,108,0,0,192,65,0,0,192,64,99,109,0,0,192,65,0,0,32,65,108,0,0,0,0,0,0,32,65,108,0,0,0,0,0,0,96,65,108,0,0,192,65,0,0,96,65,108,0,0,192,65,0,0,32,65,99,109,
        0,0,192,65,0,0,144,65,108,0,0,0,0,0,0,144,65,108,0,0,0,0,0,0,176,65,108,0,0,192,65,0,0,176,65,108,0,0,192,65,0,0,144,65,99,101,0,0 };
    static const unsigned char playPathData[] = { 110,109,121,233,22,66,92,15,164,67,98,219,249,31,66,33,176,164,67,244,253,41,66,0,0,165,67,0,0,52,66,0,0,165,67,98,80,13,63,66,0,0,165,67,135,22,74,66,86,158,164,67,205,204,83,66,41,220,163,67,108,154,121,146,67,148,184,49,67,98,2,171,148,67,226,250,
        46,67,0,0,150,67,74,44,42,67,0,0,150,67,66,0,37,67,98,0,0,150,67,58,212,31,67,2,171,148,67,162,5,27,67,154,121,146,67,240,71,24,67,108,205,204,83,66,133,235,17,64,98,205,76,65,66,128,106,28,191,238,252,41,66,248,83,67,191,121,233,22,66,215,163,240,63,
        98,4,214,3,66,156,196,144,64,0,0,240,65,131,192,24,65,0,0,240,65,0,0,112,65,108,0,0,240,65,0,128,157,67,98,0,0,240,65,252,57,160,67,4,214,3,66,238,188,162,67,121,233,22,66,92,15,164,67,99,101,0,0 };
    
    static const unsigned char pausePathData[] = { 110,109,31,133,99,65,246,168,54,66,108,31,133,99,65,146,173,103,67,98,31,133,99,65,84,115,128,67,176,114,247,65,68,171,138,67,33,48,78,66,68,171,138,67,98,123,84,144,66,68,171,138,67,162,197,177,66,52,115,128,67,162,197,177,66,146,173,103,67,108,162,
        197,177,66,246,168,54,66,98,162,197,177,66,203,161,163,65,123,84,144,66,0,16,3,60,33,48,78,66,0,16,3,60,98,176,114,247,65,0,0,0,0,31,133,99,65,203,161,163,65,31,133,99,65,246,168,54,66,99,109,174,199,97,67,0,0,0,0,98,127,42,77,67,0,0,0,0,123,116,60,67,
        104,145,163,65,123,116,60,67,197,160,54,66,108,123,116,60,67,133,171,103,67,98,123,116,60,67,78,114,128,67,127,42,77,67,55,169,138,67,174,199,97,67,55,169,138,67,98,221,100,118,67,55,169,138,67,27,143,131,67,45,114,128,67,27,143,131,67,132,171,103,67,
        108,27,143,131,67,246,168,54,66,98,244,141,131,67,203,161,163,65,221,100,118,67,0,0,0,0,174,199,97,67,0,0,0,0,99,101,0,0 };
    
    static const unsigned char stopPathData[] = { 110,109,0,0,0,0,0,0,0,0,98,0,0,0,0,66,96,13,192,125,63,229,191,0,0,128,192,0,0,128,192,0,0,128,192,108,0,0,0,194,0,0,128,192,98,4,214,8,194,0,0,128,192,0,0,16,194,66,96,13,192,0,0,16,194,0,0,0,0,108,0,0,16,194,0,0,224,65,98,0,0,16,194,8,172,241,65,4,
        214,8,194,0,0,0,66,0,0,0,194,0,0,0,66,108,0,0,128,192,0,0,0,66,98,124,63,229,191,0,0,0,66,0,0,0,0,8,172,241,65,0,0,0,0,0,0,224,65,108,0,0,0,0,0,0,0,0,99,101,0,0 };
    
    
    Path p;
    p.loadPathFromData (playPathData, sizeof (playPathData));
    playPauseButton.setShape (p, true, true, true);
    
    p.clear();
    p.loadPathFromData (burgerMenuPathData, sizeof (burgerMenuPathData));
    burgerButton.setShape (p, true, true, true);
    
    p.clear();
    p.loadPathFromData(stopPathData, sizeof (stopPathData));
    stopButton.setShape(p, true, true, true);
    
    burgerButton.onClick = [this] {informParent("Burger");};
    playPauseButton.onClick = [this] {  Path p;
                                        isPlaying = !isPlaying;
                                        if(!isPlaying){
                                            p.loadPathFromData (playPathData, sizeof (playPathData));
                                            informParent("Pause");
                                        }
                                        else{
                                            p.loadPathFromData (pausePathData, sizeof (pausePathData));
                                            informParent("Play");
                                        }
                                        playPauseButton.setShape (p, true, true, true);
                                        resized();
                                        };
    stopButton.onClick = [this] {
                                    if(isPlaying){
                                        playPauseButton.onClick();
//                                        informParent("Pause");
//                                        isPlaying = !isPlaying;
//                                        Path p;
//                                        p.loadPathFromData (playPathData, sizeof (playPathData));
//                                        playPauseButton.setShape (p, true, true, true);
//                                        resized();
                                    }
                                    informParent("Stop");
                                };
    
    addAndMakeVisible (burgerButton);
    addAndMakeVisible (playPauseButton);
    addAndMakeVisible (stopButton);
    
}

GameMenu::~GameMenu()
{
}

//==============================================================================
void GameMenu::paint (Graphics& g)
{
}

void GameMenu::resized()
{
    auto bounds = getLocalBounds();
    //bla.setBounds(bounds.removeFromTop(200).reduced(100,100));
    burgerButton.setBounds(bounds.removeFromRight(40).withTrimmedRight(8).withTrimmedLeft(8));
    stopButton.setBounds(bounds.removeFromRight(40).withTrimmedRight(10).withTrimmedLeft(10));
    playPauseButton.setBounds(bounds.removeFromRight(40).withTrimmedRight(10).withTrimmedLeft(10));
    //burgerButton.setBounds(bounds.removeFromRight(bounds.getWidth()/1.8f).reduced(15,10));
    //playPauseButton.setBounds(bounds.reduced(15,10));
}


