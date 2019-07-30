/*
  ==============================================================================

    Points.h
    Created: 3 Jun 2019 4:51:48pm
    Author:  expert239

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Points
{
public:

    //==========================================================================
    Points(int num, float h, float w, float maxDiam, float minDiam);
    ~Points();
    //==========================================================================
    std::pair<Point<float>, float> * getDots();
    int getNumDots();
    void followY(float y);
    void visualize(float lowerBound, float range, float h, Graphics& g);
    void resize(float h, float w, float maxDiam, float minDiam);
    void resize(float h, float w);
    //==========================================================================
    
private:

    //==========================================================================
    float height;
    float width;
    int numberOfDots;
    std::pair<Point<float>, float> * myDots;
    //==========================================================================
    
};