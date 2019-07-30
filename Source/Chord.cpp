/*
  ==============================================================================

    Chord.cpp
    Created: 14 Jun 2019 3:27:20pm
    Author:  expert239

  ==============================================================================
*/

#include "Chord.h"
#include <math.h>
#include <tgmath.h>
#include <optional>
#include "ControllerSingleton.h"
#include "SharedResources.h"

//==============================================================================


Chord::Chord(std::string base, std::string chordType, std::string scale, float lengthInBars){
    this->baseName = base;
    this->chordName = chordType;
    this->scaleName = scale;
    this->base = baseToInt.at(base);
    this->initFunctionForNote(scaleName, chordName);
    positionX = 0.0f;
    this->lengthInBars = lengthInBars;
    /*
    chordColoring = &(chordToColoring.at(chordType));
    scaleDegrees = &(scaleNameToDegrees.at(scale));


    initColours();*/
}

Chord::~Chord(){
}

void Chord::updatePosition(int samplePositionOfSong){
    positionX = (beginsAtSampleCount-samplePositionOfSong)/SharedResources::samplerate*1000.0f/ControllerSingleton::timePerBarMs;
    if(samplePositionOfSong > endsAtSampleCount){
        positionX += totalLengthOfSongInBars;
    }
//    positionX -= (timeDeltaMs/ControllerSingleton::timePerBarMs);//*(float)ControllerSingleton::isPlaying;
//    if(positionX <= -lengthInBars){
//        positionX += totalLengthOfSongInBars;
//    }
}
//==============================================================================

String Chord::toString(){
    return "ImAChord";
}

//==============================================================================
void Chord::initFunctionForNote(std::string scaleName, std::string chordName){

    for(int i = 0; i < 12; i++){
        functionForNote[(i+base)%12] = scaleNameToFunctions.at(scaleName)[i];
    }

    //TODO für SUS-AKKORDE nochmal extra


}


//==============================================================================

float Chord::totalLengthOfSongInBars;

std::vector<Chord> * Chord::chordVector;
void Chord::initFromChordVector(std::vector<Chord> * cv){
    //TODO: wait for Analyser to be initialised
    chordVector = cv;
    float overallLength = 0.0f;
    std::vector<Chord>::iterator it;
    for (it = chordVector->begin(); it != chordVector->end(); ++it){
        it->beginsAtSampleCount = overallLength*ControllerSingleton::bpb/ControllerSingleton::bpm*60.0f*SharedResources::samplerate;
        //it->positionX = overallLength;
        overallLength += it->lengthInBars;
        it->endsAtSampleCount = overallLength*ControllerSingleton::bpb/ControllerSingleton::bpm*60.0f*SharedResources::samplerate;
    }
    totalLengthOfSongInBars = overallLength;
    //if totalLengthOfSongInBars*bpb/bpm*60*samplerateofsong != samplesizeofsong -> FAIL
}
/*
const std::map<const std::string, const std::vector<int>> scaleNameToDegrees;
    const std::map<const std::string, const int> baseToInt;
    std::vector<int> scaleDegrees;
    int base;
    float lengthInBars;
    float position;
*/
