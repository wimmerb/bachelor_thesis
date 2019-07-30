/*
  ==============================================================================

    Points.cpp
    Created: 3 Jun 2019 4:51:48pm
    Author:  expert239

  ==============================================================================
*/

#include "Points.h"

//==========================================================================
Points::Points(int num, float h, float w, float maxDiam, float minDiam){
    myDots = new std::pair<Point<float>, float> [num];
    numberOfDots = num;
    resize(h, w, maxDiam, minDiam);
    followY(h/2.0f);
}
Points::~Points(){
    delete [] myDots;
}
//==========================================================================
std::pair<Point<float>, float> * Points::getDots(){
    return myDots;
}

int Points::getNumDots(){
    return numberOfDots;
}

void Points::followY(float y){
    for (int i = numberOfDots-1; i > 0; i--){
        // deprecated, diese Berechnung muss erst bei der Visualisierung passieren, TODO std::get<0>( myDots[i]).setY(y - (std::get<1>(myDots[i]))/2.0f);
        std::get<0>( myDots[i]).setY(y);
    }
}

void Points::visualize(float lowerBound, float range, float h, Graphics& g){
    for(int i = 0; i < numberOfDots; i++){
        std::pair<Point<float>, float> dot = myDots[i];
        Point<float> p = std::get<0>(dot);
        float diam = std::get<1>(dot);
        float y = (range+lowerBound-p.getY())/range * h - diam/2.0f;
        g.fillEllipse(p.getX(), y, diam, diam);
    }
}

void Points::resize(float h, float w, float maxDiam, float minDiam){
    //TODO Y per ratio anpassen??
    height = h;
    width = w;
    float rightBound = maxDiam/2.0f;
    float eqDist = (width - maxDiam)/((numberOfDots-1)>0?(numberOfDots-1):numberOfDots);
    for (int i = 0; i < numberOfDots; i++){
        
        float diam = maxDiam - (maxDiam - minDiam)/((numberOfDots-1)>0?(numberOfDots-1):numberOfDots)*i;
        std::get<1>(myDots[i]) = diam;
        
        std::get<0>(myDots[i]).setX(width - rightBound - i*eqDist - diam/2.0f);
        
    }
    
}

void Points::resize(float h, float w){
    float minDiam = std::get<1>(myDots[numberOfDots-1]);
    float maxDiam = std::get<1>(myDots[0]);
    resize(h, w, maxDiam, minDiam);
}
//==========================================================================
