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
    
    addAndMakeVisible(arrowBtn);
    arrowBtn.onClick = [&] { visuSidePanel->showOrHide (true); };
    
    visuSidePanel.reset(new VisuSidePanel("Visualisation-Settings", 300, false));
    addAndMakeVisible(*visuSidePanel);
    // Make sure you set the size of the component after
    // you add any child components.
    
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	int x = r.getWidth();
	int y = r.getHeight();



    setSize (x/3.0f, y);

    setBounds (getScreenX(),getScreenY(),x,y);
    
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

    chordVector = new std::vector<Chord>();
    chordVector->push_back(Chord("F", "▲7", "Major", 1.0f));
    chordVector->push_back(Chord("D", "7b9", "HM5", 1.0f));
    chordVector->push_back(Chord("G", "m7", "Dorian", 1.0f));
    chordVector->push_back(Chord("C", "7", "Mixolydian", 1.0f));
    Chord::initFromChordVector(chordVector);
    chordVisualizer = new ChordVisualisation();
    
    visu_lowerBound = 0.5f;
    visu_range = (float)ControllerSingleton::nrOfVisualizedKeys/12.0f;

    setEnterTime();
    
    File f = File("/Users/expert239/Desktop/wallpaperbro.jpeg");
    
    backgroundImage = ImageFileFormat::loadFrom(f);
    
    
    
    
    
    
}

VisuMaster::~VisuMaster()
{
    // This shuts down the GL system and stops the rendering calls.
    //shutdownOpenGL();
    openGLContext.detach();
}

//==============================================================================
void VisuMaster::paint (Graphics& g)
{
//    setExitTime();
//    double timeSinceLastFrameMs = b-a;
//    displayTiming();
//    setEnterTime();

    int samplePositionOfSong = SharedResources::samplesPositionOfSong;
    //IDEE: UPDATE und dann RENDER -> Objekte haben eigene Koordinaten?


    //UPDATE******************UPDATE


    //reposition chords;
    int bpm = 120;
    float timePerBar  = 60000.0f/((float)bpm)*4;
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
    //UPDATE******************UPDATE

    //reAdjustWindow(pitch, timeSinceLastFrameMs);


    //RENDER******************RENDER
    setEnterTime();
    //g.drawImageAt(backgroundImage, 0,0);
    //createBackGroundSpace(g);
    


    
    chordVisualizer->visualizeBackgroundPiano(visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());
    
    
    if(ControllerSingleton::dropShadows){
        DropShadow * bla = new DropShadow(Colour::fromRGBA(0,0,0,120), 20, Point<int>(-10,0));
        bla -> drawForRectangle(g, *(new Rectangle<int>(getWidth()/ControllerSingleton::barsPerScreen, 0, 1, getHeight())));
    }
    

    int indexOfLastChord = 0;
    for(int i = 0; i < chordVector->size(); i++){
        if(chordVisualizer->isCurrentChord((*(chordVector))[i])){
            indexOfLastChord = ((i-1)+chordVector->size())%chordVector->size();
            break;
        }
    }
    
    for(int i = indexOfLastChord; i < indexOfLastChord+chordVector->size(); i++){
        chordVisualizer->visualize((*(chordVector))[i%chordVector->size()], visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth(), 1);
    }
    
    
    chordVisualizer->visualizeBasicPiano(visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());
    
    
    for(int i = indexOfLastChord; i < indexOfLastChord+chordVector->size(); i++) {
        chordVisualizer->visualize((*(chordVector))[i % chordVector->size()], visu_lowerBound, visu_range, g, (float) getHeight(), (float) getWidth(), 0);
    }
    
    /*
    chordVisualizer->visualize(*chord, visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());//nrVisualizedKeys wegmachen
    chordVisualizer->visualize(*chord2, visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());
    chordVisualizer->visualize(*chord3, visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());*/



    //createNoteText(visu_lowerBound, visu_range, g, (float)getHeight(), (float)getWidth());
    
    //renderNoteHistory
    
    Path path = Path();
    //std::cout << "PATH\n";
    int pitchHistoryIndex = SharedResources::pitchHistoryIndex;
    int samplePositionOfFirst = 0;
    float y = 0.0f;
    float x = 0.0f;
    float oldy = 0.0f;
    float oldx = 0.0f;
    for(int i = 0; i < SharedResources::pitchHistorySize; i++){
        std::pair<double, int> tmpDot = SharedResources::pitchHistory[(pitchHistoryIndex-i+SharedResources::pitchHistorySize)%SharedResources::pitchHistorySize];
        if(i==0){
            samplePositionOfFirst = tmpDot.second;
        }
        if(tmpDot.first == 0.0f)
            continue;
        y = ((visu_lowerBound+visu_range)-tmpDot.first)/visu_range*getHeight();
        int second = tmpDot.second>samplePositionOfFirst?tmpDot.second-SharedResources::sampleCountOfSong:tmpDot.second;
        x = ((float)(second-samplePositionOfFirst))/(float)SharedResources::samplerate*1000.0f/(float)ControllerSingleton::timePerBarMs; //-> now Position in Bars
        if(x < -1.0f)
            break;
        //std::cout << "second:" << second << "\n";
        //std::cout << "X:" << x << "\n";
        //std::cout << "Y:" << y << "\n";
        x = (x+1.0f)/4.0f * getWidth();
        if(i == 0 || std::abs(y-oldy) > 0.1f*getHeight()){
            path.startNewSubPath(x,y);
        }

        else{
            path.lineTo(x,y);
        }
        oldy = y;
        oldx = x;
    }
    //std::cout << "PATHEND\n";
    g.setColour(ControllerSingleton::pointsColor);
    //g.strokePath(path, PathStrokeType (getHeight()/ControllerSingleton::nrOfVisualizedKeys/8.0f*std::sqrt((float)getWidth()/(float)getHeight())));
    //renderdots
    //g.setColour(ControllerSingleton::pointsColor);
    //points->visualize(visu_lowerBound, visu_range, getHeight(), g);
    setExitTime();
    displayTiming();
    
    //RENDER******************RENDER
    /*
    setExitTime();
    displayTiming();
    setEnterTime();
     */
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
    //visuSidePanel->showOrHide(false);
    arrowBtn.setBounds(getWidth() - 20-10,10,20,20);
    //points->resize();
    // This is called when the OpenGLComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
}

void VisuMaster::update(){}


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

    g.setColour(Colours::black);
    for (int i = lowestKeyNr; i <= highestKeyNr; i++){
        int func = (i+9)%12;

        float h = height/ControllerSingleton::nrOfVisualizedKeys*2.0f;
        float y = ((visu_lB+visu_r - (base+(float) i / 12.0f))/visu_r*height)-0.5f*h;
        //float y = ((visu_lB+visu_r - (base+(float) i / (float)nrVisualizedKeys))/visu_r*height)-0.5f*h;
        String s = "none";
        switch(func){
            case 0:
                s = "C";
                break;
            case 2:
                s = "D";
                break;
            case 4:
                s = "E";
                break;
            case 5:
                s = "F";
                break;
            case 7:
                s = "G";
                break;
            case 9:
                s = "A";
                break;
            case 11:
                s = "B";
                break;
        }
        if(s != "none"){
            g.drawText(s, 0.0f, y, width/ControllerSingleton::barsPerScreen*0.95f, h, Justification::right);
        }

    }


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
