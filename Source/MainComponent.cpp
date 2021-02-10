/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "SharedResources.h"

//==============================================================================
MainComponent::MainComponent()
{
    mainMenu.reset(new MainMenu());
    mainMenu->addActionListener(this);
    addAndMakeVisible(mainMenu.get());
    setSize(200*2*1.5f, 320*2*1.5f);
    mainMenu->informParent = [this](const String & s){handleInformation(s);};
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::resized(){
    auto bounds = getLocalBounds();
    if(mainMenu)
        mainMenu->setBounds(bounds);
    if(visuMaster)
        visuMaster->setBounds(bounds);
}
void MainComponent::paint(Graphics& g){}

void MainComponent::handleInformation(const String & s){
    if( s == "SwitchToGameView"){
        removeChildComponent(mainMenu.get()); //hier fehlt evtl mainMenu delete
        SharedResources::init();
        analyser.reset(new AnalyserComponent);
        visuMaster.reset(new VisuMaster());
        
        visuMaster->informParent = [this](const String & s){analyser->receiveControls(s);};
        addAndMakeVisible(visuMaster.get());
        resized();
    }
}


void MainComponent::actionListenerCallback(const String & message){
    std::cout << "bla";
}
