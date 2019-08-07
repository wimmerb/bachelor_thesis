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
    if(SharedResources::countIn){
        if(positionX <= 0.0f && positionX > -1.0f){
            positionX += totalLengthOfSongInBars;
        }
    }
//    positionX -= (timeDeltaMs/ControllerSingleton::timePerBarMs);//*(float)ControllerSingleton::isPlaying;
//    if(positionX <= -lengthInBars){
//        positionX += totalLengthOfSongInBars;
//    }
}

int Chord::IdCount = 0;

std::vector<std::pair<int, int>> Chord::getGuideLines(int func){
    std::vector<std::pair<int,int>> tmp;
    for(int i = 0; i < guideLines.size(); i++){
        if (guideLines[i].first == func)
            tmp.push_back(guideLines[i]);
    }
    return tmp;
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
    IdCount = 0;
    //TODO: wait for Analyser to be initialised
    chordVector = cv;
    float overallLength = 0.0f;
    std::vector<Chord>::iterator it;
    for (it = chordVector->begin(); it != chordVector->end(); ++it){
        it->Id = IdCount++;
        it->beginsAtSampleCount = overallLength*ControllerSingleton::bpb/ControllerSingleton::bpm*60.0f*SharedResources::samplerate;
        //it->positionX = overallLength;
        overallLength += it->lengthInBars;
        it->endsAtSampleCount = overallLength*ControllerSingleton::bpb/ControllerSingleton::bpm*60.0f*SharedResources::samplerate;
        
        
    }
    for (it = chordVector->begin(); it != chordVector->end(); ++it){
        it->initGuidelines();
    }
    
    
    totalLengthOfSongInBars = overallLength;
    //if totalLengthOfSongInBars*bpb/bpm*60*samplerateofsong != samplesizeofsong -> FAIL
}
void Chord::initGuidelines(){
    Chord nextChord = acquireNext();
    //TODO HIER WÄRE ES AUCH GUT, IM NACHHINEIN - wohl besser im Nachhinein - ODER WÄHRENDDESSEN FÜR JEDES ZIEL DAS MINIMUM ZU WÄHLEN
    for (int i = 0; i < 12; i++){
        if(functionForNote[i] == FUNC_3 || functionForNote[i] == FUNC_7){
            for (int j = -4; j <=4; j++){
                int nextChordFunc = nextChord.functionForNote[(i+j+12)%12];
                if(nextChordFunc == FUNC_3 || nextChordFunc == FUNC_7){
                    if(guideLines.size()==0)
                        guideLines.push_back(std::pair<int, int>(i, j));
                    else{
                        if(guideLines[guideLines.size()-1].first == i){
                            if(std::abs(guideLines[guideLines.size()-1].second) > std::abs(j)){
                                while(guideLines[guideLines.size()-1].first == i){
                                    guideLines.pop_back();
                                }
                                std::cout << "INITGUIDE" << "1." << guideLines[0].second << "2." << j;
                                guideLines.push_back(std::pair<int, int>(i, j));
                            }
                            else{
                                if(!(std::abs(guideLines[guideLines.size()-1].second) < std::abs(j)))
                                    guideLines.push_back(std::pair<int, int>(i, j));
                            }
                            
                        }
                        else
                            guideLines.push_back(std::pair<int, int>(i, j));
                    }
//                    std::cout << baseName << chordName<< "::   " << "I:" << i << "   J:" << j << "       ::"<< nextChord.baseName+nextChord.chordName << "\n";
                }
                
            }
        }
    }
}
//TODO remove vector POINTER....
Chord Chord::acquireNext(){
    return (*chordVector)[(Id+1)%chordVector->size()];
}
/*
const std::map<const std::string, const std::vector<int>> scaleNameToDegrees;
    const std::map<const std::string, const int> baseToInt;
    std::vector<int> scaleDegrees;
    int base;
    float lengthInBars;
    float position;
*/
