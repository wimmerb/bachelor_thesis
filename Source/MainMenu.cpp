/*
  ==============================================================================

    MainMenu.cpp
    Created: 7 Aug 2019 12:42:50pm
    Author:  expert239

  ==============================================================================
*/

#include "MainMenu.h"

MainMenu::MainMenu()
{
    
    Array<File> songDirectories = f.findChildFiles(File::findDirectories, false);
    for(int i = 0; i < songDirectories.size(); i++){
        File tmp = songDirectories[i];
        songBox.addItem(tmp.getFileName(), i+1);
    }
    songBox.addListener(this);
    addAndMakeVisible (songBox);
    addAndMakeVisible (play);
    addAndMakeVisible (modify);
    play.onClick = [this]{  std::cout << "play";
                            informParent("SwitchToGameView");};
}

MainMenu::~MainMenu()
{
}

//==============================================================================
void MainMenu::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    auto bounds = getLocalBounds();
    g.drawText (mainMessage, bounds.removeFromTop(100), Justification::centred, true);
}

void MainMenu::resized()
{
    auto bounds = getLocalBounds();
    bounds.reduce(40, 100);
    songBox.setBounds(bounds.removeFromTop(30));
    play.setBounds(bounds.removeFromTop(bounds.getHeight()/2.0f).reduced(0, 30));
    modify.setBounds(bounds.reduced(0, 30));
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

//==============================================================================
void MainMenu::comboBoxChanged(ComboBox * boxThatHasChanged){
    
    mainMessage = "Chosen: "+boxThatHasChanged->getItemText(boxThatHasChanged->getSelectedItemIndex());
    File songFolder = f.getChildFile("./"+boxThatHasChanged->getItemText(boxThatHasChanged->getSelectedItemIndex()));
    mainMessage = "Chosen: "+songFolder.getFileName();
    Array<File> a = songFolder.findChildFiles(File::findFiles, false, "*.json");
    File songJson;
    if(!a.isEmpty()){
        songJson = a[0];
    }
    var bla = JSON::parse(songJson);
    
    String name = bla.getProperty("name", var());
    int bpm = bla.getProperty("bpm", var());
    int bpb = bla.getProperty("bpb", var());
    std::cout << name << ":" << bpm << ":" << bpb << "\n";
    if (auto chordsArray = bla.getProperty("chords", var()).getArray())
        for (auto& chord : *chordsArray){
            String base = chord.getProperty("base",var());
            String chordType = chord.getProperty("chordtype",var());
            String scale = chord.getProperty("scale",var());
            float lengthInBars = chord.getProperty("length_in_bars",var());
            std::cout << base << ":" << chordType << ":" << scale << ":" << lengthInBars << "\n";
        }
    
    repaint();
}

