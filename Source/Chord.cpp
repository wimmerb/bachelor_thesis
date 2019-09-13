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


Chord::Chord(String base, String chordType, String scale, float lengthInBars){
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

void Chord::updatePosition(float samplePositionOfSong){
    if(ControllerSingleton::chords_BlockMovement){
        std::vector<Chord>::iterator it;
        for (it = chordVector->begin(); it != chordVector->end(); ++it){
            if(it->beginsAtSampleCount < samplePositionOfSong && it->endsAtSampleCount > samplePositionOfSong){
                float progress = (samplePositionOfSong-it->beginsAtSampleCount) / (it->endsAtSampleCount - it->beginsAtSampleCount);
                float range = it->endsAtSampleCount - it->beginsAtSampleCount;
                progress = std::pow(progress, 10.0);
                samplePositionOfSong = it->beginsAtSampleCount + range*progress;
                //samplePositionOfSong = it->beginsAtSampleCount;
            }
        }
    }
    
    positionX = (beginsAtSampleCount-samplePositionOfSong)/SharedResources::samplerate*1000.0f/ControllerSingleton::timePerBarMs;//TODO timePerBar handeln!!!
    if(samplePositionOfSong > endsAtSampleCount){
        positionX += totalLengthOfSongInBars;
    }
    if(SharedResources::countIn){
        if(positionX <= 0.0f && positionX > -1.0f){
            positionX += totalLengthOfSongInBars;
        }
    }
    std::cout << "=======INIT=========\n";
    std::cout << "baseName " << baseName << "\n";
    std::cout << "chordName " << chordName << "\n";
    std::cout << "positionX " << positionX << "\n";
    std::cout << "lengthInBars " << lengthInBars << "\n";
    std::cout << "beginsAtSampleCount " << beginsAtSampleCount << "\n";
    std::cout << "endsAtSampleCount " << endsAtSampleCount << "\n";
    std::cout << "=======INIT=========\n";
    
//    positionX -= (timeDeltaMs/ControllerSingleton::timePerBarMs);//*(float)ControllerSingleton::isPlaying;
//    if(positionX <= -lengthInBars){
//        positionX += totalLengthOfSongInBars;
//    }
}

int Chord::IdCount = 0;

std::vector<std::tuple<int, int, int>> Chord::getGuideLines(int func){
    std::vector<std::tuple<int, int, int>> tmp;
    for(int i = 0; i < guideLines.size(); i++){
        if (std::get<0>(guideLines[i]) == func)
            tmp.push_back(guideLines[i]);
    }
    return tmp;
}
//==============================================================================

String Chord::toString(){
    return "ImAChord";
}

//==============================================================================
void Chord::initFunctionForNote(String scaleName, String chordName){

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
    std::cout << "TOTALLENGTH" << overallLength << "\n";
}
void Chord::initGuidelines(){
    Chord nextChord = acquireNext();
    //HIER WÄRE ES AUCH GUT, IM NACHHINEIN - wohl besser im Nachhinein - ODER WÄHRENDDESSEN FÜR JEDES ZIEL DAS MINIMUM ZU WÄHLEN
    //Argument dagegen: so denkt der Spieler nicht...
    for (int i = 0; i < 12; i++){
        if(functionForNote[i] == FUNC_3 || functionForNote[i] == FUNC_7){
            for (int j = -4; j <=4; j++){
                int k = (i+j+12)%12;
                int nextChordFunc = nextChord.functionForNote[k];
                if(nextChordFunc == FUNC_3 || nextChordFunc == FUNC_7){
                    if(guideLines.size()==0)
                        guideLines.push_back(std::tuple<int,int,int>(i, j, k));
                    else{
                        if(std::get<0>(guideLines[guideLines.size()-1]) == i){
                            if(std::abs(std::get<1>(guideLines[guideLines.size()-1])) > std::abs(j)){
                                while(std::get<0>(guideLines[guideLines.size()-1]) == i){
                                    guideLines.pop_back();
                                }
                                std::cout << "INITGUIDE" << "1." << std::get<1>(guideLines[0]) << "2." << j;
                                guideLines.push_back(std::tuple<int,int,int>(i, j, k));
                            }
                            else{
                                if(!(std::abs(std::get<1>(guideLines[guideLines.size()-1])) < std::abs(j)))
                                    guideLines.push_back(std::tuple<int,int,int>(i, j, k));
                            }
                            std::tuple<int,int,int> bla (1,2,3);
                        }
                        else
                            guideLines.push_back(std::tuple<int,int,int>(i, j, k));
                    }
//                    std::cout << baseName << chordName<< "::   " << "I:" << i << "   J:" << j << "       ::"<< nextChord.baseName+nextChord.chordName << "\n";
                }
                
            }
        }
    }
    //removing "from right to left"
    for(int i = 0; i < 12; i++){
        std::vector<std::tuple<int, int, int>> tmpLines;
        for (auto & x : guideLines){
            if(std::get<2>(x) == i)
                tmpLines.push_back(x);
        }
        int min = 13;
        for (auto & x : tmpLines){
            int valRightNow = std::abs(std::get<1>(x));
            if (valRightNow < min)
                min = valRightNow;
        }
        
        for (auto & x : tmpLines){
            int valRightNow = std::abs(std::get<1>(x));
            if (valRightNow > min)
                std::remove(guideLines.begin(), guideLines.end(), x);
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
