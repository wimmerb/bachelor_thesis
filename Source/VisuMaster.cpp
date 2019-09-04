/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "VisuMaster.h"
#include <math.h>
#include <tgmath.h>
#include "ControllerSingleton.h"
#include "SharedResources.h"


//==============================================================================




VisuMaster::VisuMaster(){
    
    addAndMakeVisible(gameMenu);
    gameMenu.informParent = [this](const String & s){receiveFromGameMenu(s);};
    
    visuSidePanel.reset(new VisuSidePanel("Visualisation-Settings", 300, false));
    addAndMakeVisible(*visuSidePanel);
    // Make sure you set the size of the component after
    // you add any child components.
    
    //Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	//int x = r.getWidth();
	//int y = r.getHeight();



    //setSize (x/3.0f, y);

    //setBounds (getScreenX(),getScreenY(),x,y);
    
    //addMouseListener(this, false);

    ControllerSingleton::init(std::vector<bool>{true,true,true,true,false,false,false,//1,3,5,7,9,11,13
                                                true,//Regular->wholescale for chords
                                                false//Avoid
                                                },
            true, //basicpWholeScale
            false, //basicpColours
            true); //chordsColours


    currMouseY = getHeight()/2.0f;
    
    openGLContext.attachTo (*this);
    
    openGLContext.setComponentPaintingEnabled(true);

    setFramesPerSecond(ControllerSingleton::fps);

    
    points = new Points(ControllerSingleton::nrPoints, (float) getHeight(), (float) getWidth()/ControllerSingleton::barsPerScreen, 15.0f, 1.0f);

    if(ControllerSingleton::chordVector == nullptr){
        chordVector = new std::vector<Chord>();
        chordVector->push_back(Chord("F", "maj7", "Major", 1.0f));
        chordVector->push_back(Chord("D", "7b9", "HM5", 1.0f));
        chordVector->push_back(Chord("G", "m7", "Dorian", 1.0f));
        chordVector->push_back(Chord("C", "7", "Mixolydian", 1.0f));
    }
    else{
        chordVector = ControllerSingleton::chordVector;
    }
    Chord::initFromChordVector(chordVector);
    chordVisualizer = new ChordVisualisation();
    
    visu_lowerBound = 1.0f+1.0f/12.0f*3.0f-1.0f/12.0f/2.0f;
    visu_range = (float)ControllerSingleton::nrOfVisualizedKeys/12.0f;

    setEnterTime();
    
    //File f = File("/Users/expert239/Desktop/wallpaperbro.jpeg");
    
    backgroundImage = ImageFileFormat::loadFrom(BinaryData::VISU_wallpaperbro_jpeg, (size_t) BinaryData::VISU_wallpaperbro_jpegSize);
    
    //backgroundImage = ImageFileFormat::loadFrom(f);
    
    
    
    
    
    
}

VisuMaster::~VisuMaster()
{
    // This shuts down the GL system and stops the rendering calls.
    //shutdownOpenGL();
    openGLContext.detach();
}

void VisuMaster::receiveFromGameMenu(const String & s){
    std::cout << "received" << s;
    if(s == "Burger"){
        visuSidePanel->showOrHide (true);
        return;
    }
    informParent(s);
}

//==============================================================================
void VisuMaster::update(){
    //UPDATE******************UPDATE
    {
        
        //IDEE: bilde reihe ab currentChord und mache das ganze NUR von der aktuellen Sampleposition abhängig.
        std::vector<Chord>::iterator it;
        for (it = chordVector->begin(); it != chordVector->end(); ++it){
            //it->updatePosition(samplePositionOfSong);
            it->updatePosition(SharedResources::samplesPositionOfSong);
        }
        float pitch = SharedResources::trackedPitch;
        if(ControllerSingleton::snapPitchToGrid){
            pitch = std::floor(pitch)+(round(fmod(pitch, 1.0f)*12.0f))/12.0f;
        }
        
        
        points->followY(pitch);
    }
    //reAdjustWindow(pitch, timeSinceLastFrameMs);
    //UPDATE******************UPDATE
}

void VisuMaster::paint(Graphics& g){
    setExitTime();
    displayTiming();
    setEnterTime();
    
    
    if(!ControllerSingleton::keyBoardMode)
        ppaint(g);
    else{
        Image i (Image(Image::ARGB, getHeight()*2, getWidth()*2, true));
        Graphics graphics (i);
        graphics.addTransform(AffineTransform().verticalFlip(getWidth()*2));
        ppaint(graphics);
        //g.addTransform(AffineTransform().rotated(-0.5f*std::atan(1)*4));
        g.drawImageTransformed(i, AffineTransform().scaled(0.5f,0.5f).rotated(-0.5f*std::atan(1)*4).translated(0, getHeight()));
        //g.drawImageAt(i, 0, 0);
    }
    
}
void VisuMaster::ppaint (Graphics& g){
//    setExitTime();
//    double timeSinceLastFrameMs = b-a;
//    displayTiming();
//    setEnterTime();
    //g.addTransform(AffineTransform().rotated(0.5f*atan(1)*4.0f));
    int height = getHeight();
    int width = getWidth();
    if(ControllerSingleton::keyBoardMode){
        //g.addTransform(AffineTransform().verticalFlip(getHeight()).rotated(-0.5f*std::atan(1)*4).translated(0, getHeight()));
        width = getHeight()*2;
        height = getWidth()*2;
    }
    


    //RENDER******************RENDER
    {
        g.setTiledImageFill(backgroundImage, 0, 0, 1.0f);
        g.fillAll(Colours::grey);
        //g.drawImageAt(backgroundImage, width/ControllerSingleton::barsPerScreen,0);
        //createBackGroundSpace(g);
        


        
        chordVisualizer->visualizeBackgroundPiano(visu_lowerBound, visu_range, g, (float)height, (float)width);
        
        int indexOfLastChord = 0;
        for(int i = 0; i < chordVector->size(); i++){
            if(chordVisualizer->isCurrentChord((*(chordVector))[i])){
                indexOfLastChord = ((i-1)+(int)chordVector->size())%chordVector->size();
                break;
            }
        }
        Chord wrapAroundChord = (*(chordVector))[indexOfLastChord];
        wrapAroundChord.positionX -= Chord::totalLengthOfSongInBars;
        
        {   //Guidelines
            for(int i = indexOfLastChord; i < indexOfLastChord+chordVector->size(); i++){
                chordVisualizer->visualize((*(chordVector))[i%chordVector->size()], visu_lowerBound, visu_range, g, (float)height, (float)width, 0.5f);
            }
            chordVisualizer->visualize(wrapAroundChord, visu_lowerBound, visu_range, g, (float)height, (float)width, 0.5f);
        }
        
        {   //Keys
            for(int i = indexOfLastChord; i < indexOfLastChord+chordVector->size(); i++){
                chordVisualizer->visualize((*(chordVector))[i%chordVector->size()], visu_lowerBound, visu_range, g, (float)height, (float)width, 0.0f);
            }
        }
        
        
        
        
        g.setColour(Colours::black);//TODO WTF
        //g.fillAll(Colours::grey);
        g.drawImage(backgroundImage, Rectangle<float>(0, 0, width*ControllerSingleton::basicp_ScreenPortion, height));
        chordVisualizer->visualizeBasicPiano(visu_lowerBound, visu_range, g, (float)height, (float)width);
        
        
        {   //Dots
            for(int i = indexOfLastChord; i < indexOfLastChord+chordVector->size(); i++) {
                chordVisualizer->visualize((*(chordVector))[i % chordVector->size()], visu_lowerBound, visu_range, g, (float) height, (float) width, 1.0f);
            }
        }
    
    }
}


void VisuMaster::reAdjustWindow(float p, float timeSinceLastFrameMs){


    float target = visu_lowerBound;
    float dist = 0.0f;
    bool haveToMove = false;

    if(p > visu_range*(1.0f-virtScreenBorder)+visu_lowerBound){
        target = p-visu_range*(1.0f-virtScreenBorder);
        dist = target-visu_lowerBound;
        haveToMove = true;
    }
    if(p < visu_lowerBound+visu_range*virtScreenBorder){
        target = p-visu_range*virtScreenBorder;
        dist = target-visu_lowerBound;
        haveToMove = true;
    }
    if(!haveToMove){
        //slow to Zero!
        if(currScreenSpeed > 0){
            currScreenSpeed -= screenAcceleration*timeSinceLastFrameMs/(1000/ControllerSingleton::fps);
            currScreenSpeed = currScreenSpeed<0.0f?0.0f:currScreenSpeed;
        }
        else{
            currScreenSpeed += screenAcceleration*timeSinceLastFrameMs/(1000/ControllerSingleton::fps);
            currScreenSpeed = currScreenSpeed>0.0f?0.0f:currScreenSpeed;
        }
    }
    else{
        float Gauss = currScreenSpeed/2 * (abs(currScreenSpeed)+1)/maxScreenSpeed/12;

        if(Gauss > dist){
            currScreenSpeed = currScreenSpeed <= -1*maxScreenSpeed?currScreenSpeed:(currScreenSpeed-screenAcceleration*timeSinceLastFrameMs/(1000/ControllerSingleton::fps));
        }
        if(Gauss < dist){
            currScreenSpeed = currScreenSpeed >= maxScreenSpeed?currScreenSpeed:(currScreenSpeed+screenAcceleration*timeSinceLastFrameMs/(1000/ControllerSingleton::fps));
        }
    }



    //ALTERNATIV: ROLLE
    //float target = p - 0.5f * visu_range;


    visu_lowerBound += currScreenSpeed/maxScreenSpeed/12*timeSinceLastFrameMs/(1000/ControllerSingleton::fps);
}



void VisuMaster::resized()
{
    gameMenu.setBounds(getLocalBounds().removeFromTop(visuSidePanel->getTitleBarHeight()).removeFromRight(200));
    //visuSidePanel->showOrHide(false);
    //points->resize();
    // This is called when the OpenGLComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
}

void VisuMaster::createBackGroundSpace(Graphics &g){

    g.fillAll(ControllerSingleton::backgroundColor);

    g.setColour(Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 0.2f));
    for(int i = 0; i < getWidth(); i++){
        for(int j = 0; j < getHeight(); j++){
            if((i*(j<<(j%3)))%101 == 1){
                    g.fillRect(i,j,4,4);
            }
        }
    }

    /*
    Path spinePath;
    spinePath.startNewSubPath(0.2f*getWidth(), 0.4f*getHeight());
    spinePath.lineTo(0.4f*getWidth(), 0.4f*getHeight());
    spinePath.cubicTo(0.6f*getWidth(), 0.4f*getHeight(), 0.4f*getWidth(), 0.6f*getHeight(), 0.6f*getWidth(), 0.6f*getHeight());
    spinePath.lineTo(0.8f*getWidth(), 0.6f*getHeight());

    g.setColour(Colours::black);
    g.strokePath (spinePath, PathStrokeType (4.0f));
    */

}

void VisuMaster::createNoteText(float visu_lB, float visu_r, Graphics& g, float height, float width) {
    int lowestKeyNr = (int)std::floor(fmod(visu_lB, 1.0f)*12.0f);
    float base = std::round(visu_lB - (fmod(visu_lB, 1.0f)));
    int highestKeyNr = (int)std::ceil((visu_lB+visu_r-base)*12.0f);

    


}

//==============================================================================

void VisuMaster::renderOpenGL(){}
void VisuMaster::newOpenGLContextCreated(){}
void VisuMaster::openGLContextClosing(){}

//==============================================================================
void VisuMaster::mouseDrag(const MouseEvent& event)
{
    //if(!mouseExtd)
    currMouseY = (float)(event.getPosition().getY());
}
//==============================================================================





void VisuMaster::displayTiming(){
    //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§§§§§§displaytimingOpenGL§§§§§§§§§§§§§§\n");
    //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%lf", b-a);
    std::cout << b-a << "\n";
    //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§\n");
}

void VisuMaster::setEnterTime(){
    a = now_ms();
}

void VisuMaster::setExitTime(){
    b = now_ms();
}

double VisuMaster::now_ms(void) {

    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

}
