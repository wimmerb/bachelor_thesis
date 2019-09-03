/*
  ==============================================================================

    ChordVisualisation.cpp
    Created: 23 Jun 2019 4:06:57pm
    Author:  expert239

  ==============================================================================
*/

#include "ChordVisualisation.h"
#include "ControllerSingleton.h"
#include "SharedResources.h"

//==============================================================================

ChordVisualisation::ChordVisualisation(){}

ChordVisualisation::~ChordVisualisation(){}

//==============================================================================
//public
void ChordVisualisation::visualizeBackgroundPiano(float visu_lB, float visu_r, Graphics& g, float height, float width){



    int lowestKeyNr = (int)std::floor(fmod(visu_lB, 1.0f)*12.0f);
    float relBase = std::round(visu_lB - (fmod(visu_lB, 1.0f)));
    int highestKeyNr = (int)std::ceil((visu_lB+visu_r-relBase)*12.0f);


    for (int i = lowestKeyNr; i <= highestKeyNr; i++){
        int func = (i+9)%12;
        int isBlackKey = isBlack(func);
        float w = width;
        float h = height/ControllerSingleton::nrOfVisualizedKeys;
        float x = 0.0f;
        float y = ((visu_lB+visu_r - (relBase+(float) i /12.0f))/visu_r*height)-0.5f*h;

        Colour col = isBlackKey?Colour::fromRGBA(0,0,0,30):Colour::fromRGBA(255,255,255,30);



        g.setColour(col);
        g.fillRect(x,y,w,h);
        
        /*
        //g.setColour(colourForKeyBorder);
        //g.drawRect(x,y,w,h, thicknessForKeyBorder);*/
    }
}
void ChordVisualisation::visualizeBasicPiano(float visu_lB, float visu_r, Graphics& g, float height, float width){
    //Dropshadow
    if(ControllerSingleton::dropShadows){
        DropShadow * bla = new DropShadow(Colour::fromRGBA(0,0,0,250), 8, Point<int>(-4,0));
        bla -> drawForRectangle(g, *(new Rectangle<int>(width*ControllerSingleton::basicp_ScreenPortion, 0, 1, height)));
    }
    else{
        Path p;
        p.startNewSubPath(width*ControllerSingleton::basicp_ScreenPortion, 0);
        p.lineTo(width*ControllerSingleton::basicp_ScreenPortion, height);
        g.setColour(colourForKeyBorder);
        g.strokePath(p, PathStrokeType(thicknessForKeyBorder));
    }

    int lowestKeyNr = (int)std::floor(fmod(visu_lB, 1.0f)*12.0f);
    float relBase = std::round(visu_lB - (fmod(visu_lB, 1.0f)));
    int highestKeyNr = (int)std::ceil((visu_lB+visu_r-relBase)*12.0f);


    for (int i = lowestKeyNr; i <= highestKeyNr; i++){
        int func = (i+9+12)%12;
        int isBlackKey = isBlack(func);


        float w = width;
        float h = height/ControllerSingleton::nrOfVisualizedKeys;
        float x = 0.0f;
        float y = ((visu_lB+visu_r - (relBase+(float) i /12.0f))/visu_r*height)-0.5f*h;

        Colour col = isBlackKey?Colour::fromRGBA(0,0,0,60):Colour::fromRGBA(255,255,255,100);
        if(!ControllerSingleton::basicP_visualizeTransparent){
            col = col = isBlackKey?Colours::black:Colours::white;
        }
        

        w = ControllerSingleton::basicp_ScreenPortion*width;
        h = height/ControllerSingleton::nrOfVisualizedKeys;
        x = 0.0f;
        y = ((visu_lB+visu_r - (relBase+(float) i /12.0f))/visu_r*height);
        
        
        Chord::FunctionType funcType = currentlyPlayingNotes[func];
        if(funcType != Chord::FUNC_NAN){
            funcType = ControllerSingleton::chords_visuArray[funcType]?funcType:Chord::FUNC_REGULAR;
        }
        
        if(ControllerSingleton::basicp_highlightBasicPiano){
                    if(funcType != Chord::FUNC_NAN){
                        if(ControllerSingleton::basicp_visualizeWholeScale || funcType != Chord::FUNC_REGULAR){
                            if(ControllerSingleton::basicP_visualizeWithColours){
                                col = isBlackKey?functionTypeToColourBlackScheme.at(funcType):functionTypeToColourWhiteScheme.at(funcType);
                            }
                            else{
                                col = isBlackKey?Colours::black:Colours::white;
                            }
                        }
                    }

            
        }
        
        float pitch = (relBase+(float) i /12.0f);
        bool noteCurrentlyPlayed = std::abs(pitch - SharedResources::trackedPitch) < 1.0f/12.0f/2.0f && ControllerSingleton::pitch_visualizeKeys;

        Path p;
        Path innerPath;
        if(isBlackKey){
            float startX = x+0.4f*w;
            float startY =  y-0.5f*h;
            float endX = x+w -1.0f;
            float endY = y + 0.5*h;
            
            if(noteCurrentlyPlayed){
                startX += 4.0f;
                endX -= 4.0f;
                startY += 4.0f;
                endY -= 4.0f;
            }
            
            p.startNewSubPath(startX, startY);
            p.lineTo(endX, startY);
            p.lineTo(endX, endY);
            p.lineTo(startX, endY);
            p.closeSubPath();
            
            
            
            if(noteCurrentlyPlayed){
                startX += 5.0f;
                endX -= 5.0f;
                
                startY += 5.0f;
                endY -= 5.0f;
                innerPath.startNewSubPath(startX, startY);
                innerPath.lineTo(endX, startY);
                innerPath.lineTo(endX, endY);
                innerPath.lineTo(startX, endY);
                innerPath.closeSubPath();
            }
        }
        else{
            float heightOfWhite = h*12.0f/7.0f;
            float toTheLeft = 0.5f;
            float toTheRight = 0.5f;
            float narrowToTheRight = 0.5f;
            float narrowToTheLeft = 0.5f;
            std::map<int, int> nthWhiteKey = {
                {0,0},
                {2,1},
                {4,2},
                {5,3},
                {7,4},
                {9,5},
                {11,6},
            };
            //Left is up, right is down
            
            if(!(func == 0 || func == 4 || func == 5 || func == 11)){
                toTheLeft = 1.0f;
                toTheRight = 1.0f;
            }
            if(func == 4 || func == 11){
                toTheRight = 1.0f;
            }
            if(func == 0 || func == 5){
                toTheLeft = 1.0f;
            }
            if(func == 0 || func == 2 || func == 4){
                float desiredHeight = 5.0f/3.0f;
                float currentHeight = toTheLeft + toTheRight;
                float discrepancy = std::abs(desiredHeight-currentHeight);
                switch(func){
                    case 0:
                        toTheLeft += discrepancy;
                        break;
                    case 2:
                        toTheLeft -= 0.5*discrepancy;
                        toTheRight -= 0.5*discrepancy;
                        break;
                    case 4:
                        toTheRight += discrepancy;
                        break;
                }
            }
            if(func == 5 || func == 7 || func == 9 || func == 11){
                float desiredHeight = 7.0f/4.0f;
                float currentHeight = toTheLeft + toTheRight;
                float discrepancy = std::abs(desiredHeight-currentHeight);
                switch(func){
                    case 5:
                        toTheLeft += discrepancy;
                        break;
                    case 7:
                        toTheRight -= discrepancy;
                        break;
                    case 9:
                        toTheLeft -= discrepancy;
                        break;
                    case 11:
                        toTheRight += discrepancy;
                        break;
                }
            }
            float startX = x                            +1.0f;
            float middleX = x+0.4f*w                    -1.0f;
            float endX = x+w                            -1.0f;
            float leftOuterY = y-toTheLeft*h            +1.0f;
            float leftInnerY = y-narrowToTheLeft*h      +1.0f;
            float rightInnerY = y+narrowToTheRight*h    -1.0f;
            float rightOuterY = y+toTheRight*h          -1.0f;
            if(noteCurrentlyPlayed){
                startX += 3.0f;
                middleX -= 2.0f;
                leftOuterY += 3.0f;
                leftInnerY += 3.0f;
                endX -= 3.0f;
                rightInnerY -= 3.0f;
                rightOuterY -= 3.0f;
            }
            p.startNewSubPath(startX, leftOuterY);
            p.lineTo(middleX, leftOuterY);
            p.lineTo(middleX, leftInnerY);
            p.lineTo(endX, leftInnerY);
            p.lineTo(endX, rightInnerY);
            p.lineTo(middleX, rightInnerY);
            p.lineTo(middleX, rightOuterY);
            p.lineTo(startX, rightOuterY);
            p.closeSubPath();
            
            if(noteCurrentlyPlayed){
                startX += 5.0f;
                middleX -= 5.0f;
                leftOuterY += 5.0f;
                leftInnerY += 5.0f;
                endX -= 5.0f;
                rightInnerY -= 5.0f;
                rightOuterY -= 5.0f;
                innerPath.startNewSubPath(startX, leftOuterY);
                innerPath.lineTo(middleX, leftOuterY);
                innerPath.lineTo(middleX, leftInnerY);
                innerPath.lineTo(endX, leftInnerY);
                innerPath.lineTo(endX, rightInnerY);
                innerPath.lineTo(middleX, rightInnerY);
                innerPath.lineTo(middleX, rightOuterY);
                innerPath.lineTo(startX, rightOuterY);
                innerPath.closeSubPath();
            }
        }
        
        
        
        
        
        g.setColour(col);
        g.fillPath(p);
        if (noteCurrentlyPlayed){
            col = ControllerSingleton::pointsColor;
            //col = (funcType != Chord::FUNC_NAN)?colourForKeyBorder:Colours::darkred;
            g.setColour(col);
            g.strokePath(p, PathStrokeType(thicknessForKeyBorder*2.0f));
            //g.fillPath(innerPath);
        }
        g.setColour(Colours::lightgrey);
        //
//        g.setColour(col);
//        g.fillRect(x,y-0.5f*h,w,h);
//        g.setColour(Colours::lightgrey);
//        g.drawRect(x,y-0.5f*h,w,h, (funcType != Chord::FUNC_NAN)?thicknessForKeyBorder*1.5f:thicknessForKeyBorder);
        
    }
    
//    g.setColour(Colours::black);
//    for (int i = lowestKeyNr; i <= highestKeyNr; i++){
//        int func = (i+9)%12;
//
//        float h = height/ControllerSingleton::nrOfVisualizedKeys*2.0f;
//        float y = ((visu_lB+visu_r - (base+(float) i / 12.0f))/visu_r*height)-0.5f*h;
//        //float y = ((visu_lB+visu_r - (base+(float) i / (float)nrVisualizedKeys))/visu_r*height)-0.5f*h;
//        String s = "none";
//        switch(func){
//            case 0:
//                s = "C";
//                break;
//            case 2:
//                s = "D";
//                break;
//            case 4:
//                s = "E";
//                break;
//            case 5:
//                s = "F";
//                break;
//            case 7:
//                s = "G";
//                break;
//            case 9:
//                s = "A";
//                break;
//            case 11:
//                s = "B";
//                break;
//        }
//        if(s != "none"){
//            g.drawText(s, 0.0f, y, width/ControllerSingleton::barsPerScreen*0.95f, h, Justification::right);
//        }
//
//    }
    visualizePitch(visu_lB, visu_r, g, height, width, height/ControllerSingleton::nrOfVisualizedKeys);
}

void ChordVisualisation::visualizePitch(float visu_lB, float visu_r, Graphics &g, float height, float width, float h){
    if(ControllerSingleton::pitch_Visualize){
        if(ControllerSingleton::pitch_visualizeGraph){
            float timeWindowInBars = ControllerSingleton::barsPerScreen*(ControllerSingleton::basicp_ScreenPortion/(1.0f - ControllerSingleton::basicp_ScreenPortion));
            
            float timeWindowInSeconds =
            timeWindowInBars*ControllerSingleton::bpb/ControllerSingleton::bpm*60.0f;
            
            float timeWindowInSamples = timeWindowInSeconds*SharedResources::samplerate;
            
            
            Path p;
            int samplePeekIntoPast = 0;
            for(int i = 0; i < SharedResources::pitchHistorySize; i++){
                std::pair<double, int> tmpDot = SharedResources::pitchHistory[(SharedResources::pitchHistoryIndex-i+SharedResources::pitchHistorySize)%SharedResources::pitchHistorySize];
                
                samplePeekIntoPast += tmpDot.second;
                
                std::cout << "samplePeekIntoPast" << (float)samplePeekIntoPast << "\n";
                
                bool isLast = false;
                
                if((float)samplePeekIntoPast > timeWindowInSamples){
                    isLast = true;
                    std::cout << "isLast!!!" << "\n";
                }
                
                float x = (1.0f-(float)samplePeekIntoPast/timeWindowInSamples)*ControllerSingleton::basicp_ScreenPortion*width;
                
                float y = ((visu_lB+visu_r)-tmpDot.first)/visu_r*height;
                
                if(i == 0){
                    p.startNewSubPath(x, y);
                }
                else{
                    p.lineTo(x, y);
                }
                
                std::cout << "x" << x << "y" << y << "\n";
                
                if(isLast)
                    break;
            }
            
            g.setColour(ControllerSingleton::pointsColor);
            g.strokePath(p, PathStrokeType (height/ControllerSingleton::nrOfVisualizedKeys/8.0f*std::sqrt((float)width/(float)height)));
//            p.applyTransform(AffineTransform().translated(0, -1.0f*height));
//            g.strokePath(p, PathStrokeType (height/ControllerSingleton::nrOfVisualizedKeys/8.0f*std::sqrt((float)width/(float)height)));
//            p.applyTransform(AffineTransform().translated(0, 2.0f*height));
//            g.strokePath(p, PathStrokeType (height/ControllerSingleton::nrOfVisualizedKeys/8.0f*std::sqrt((float)width/(float)height)));
        }
        if(ControllerSingleton::pitch_visualizeBubble){
            float timeWindowInBars = ControllerSingleton::barsPerScreen*(ControllerSingleton::basicp_ScreenPortion/(1.0f - ControllerSingleton::basicp_ScreenPortion));
            
            float timeWindowInSeconds =
            0.5f;
            
            float timeWindowInSamples = timeWindowInSeconds*SharedResources::samplerate;
            float biggestDiameter = 0.6f*h;
            float smallestDiameter = 2.0f;
            int nrOfPoints = 20;
            std::vector<std::pair<Point<float>, float>> vectorOfXYAndDiameter;
            
            int j = 0;
            for(int i = 0; i < nrOfPoints; i++){
                float respectiveSample = (float)i/(nrOfPoints+1.0f)*timeWindowInSamples;
                float y = 0.0f;
                while(true){
                    std::cout << "INDEX" << (SharedResources::pitchHistoryIndex-j+SharedResources::pitchHistorySize)%SharedResources::pitchHistorySize << "\n";
                    auto tmpDot = SharedResources::pitchHistory[(SharedResources::pitchHistoryIndex-j+SharedResources::pitchHistorySize)%SharedResources::pitchHistorySize];
                    int sampleSize = tmpDot.second;
                    if (std::abs(j*sampleSize - respectiveSample) < sampleSize/2.0f){
                        if(std::isnan(tmpDot.first) || std::isinf(tmpDot.first)){
                            std::cout<< "ISNAN";
                            break;
                            
                        }
                        std::cout << "jo" << tmpDot.first << "\n";
                        y = ((visu_lB+visu_r)-tmpDot.first)/visu_r*height;
                        if(std::isnan(y) || std::isinf(y)){
                            y = 0.0f;
                        }
                        std::cout << "y" << y << "\n" ;
                        break;
                    }
                    j++;
                }
                
                float x = width*ControllerSingleton::basicp_ScreenPortion*(1.0f-1.0f/(nrOfPoints+1)*(i)) - biggestDiameter/2.0f;
                float diameter = biggestDiameter - ((float)i/(float)nrOfPoints)*(biggestDiameter-smallestDiameter);
                vectorOfXYAndDiameter.push_back(std::pair<Point<float>, float> (Point<float>(x,y), diameter));
                
            }
            
            
            
            if(ControllerSingleton::dropShadows){
                Colour dropShadowCol = Colour::fromRGBA(0,0,0,255);
                for(auto & a : vectorOfXYAndDiameter){
                    DropShadow * bla = new DropShadow(dropShadowCol, std::max(1.0f, 0.4f*a.second), Point<int>(0,0));
                    bla -> drawForRectangle(g, *(new Rectangle<int>(a.first.getX()-0.25f*a.second, a.first.getY()-0.1f*a.second, 0.6f*a.second, 0.6f*a.second)));
                }
            }
            g.setColour(ControllerSingleton::pointsColor);
            for(auto & a : vectorOfXYAndDiameter){
                g.fillEllipse(a.first.getX()-0.5*a.second, a.first.getY()-0.5*a.second, a.second, a.second);
            }
            
            
            int samplePeekIntoPast = 0;
        }
    }
    
    


}

void ChordVisualisation::visualize(Chord c, float visu_lB, float visu_r, Graphics& g, float height, float width, float layer){
    if(isCurrentChord(c)){
        currentlyPlayingNotes = c.functionForNote;
    }
    if(isOnScreen(c)){
        
        int lowestKeyNr = (int)std::floor(fmod(visu_lB, 1.0f)*12.0f)-3; //-3 für GuideLines
        float relBase = std::round(visu_lB - (fmod(visu_lB, 1.0f)));
        int highestKeyNr = (int)std::ceil((visu_lB+visu_r-relBase)*12.0f)+3; //+3 für GuideLines

        float x = (((1.0f/ControllerSingleton::barsPerScreen*c.positionX)*(1.0f-ControllerSingleton::basicp_ScreenPortion)) + ControllerSingleton::basicp_ScreenPortion)*width;
        float h = height/ControllerSingleton::nrOfVisualizedKeys;
        float w = (1.0f/ControllerSingleton::barsPerScreen*c.lengthInBars)*(1.0f-ControllerSingleton::basicp_ScreenPortion)*width-10.0f;
//        if(layer == 1){
//            g.setColour(Colours::turquoise.interpolatedWith(Colour::fromRGBA(0,0,0,0), 0.8f));
//            g.fillRect(x,0.0f,w,height);
//        }
    
        for (int i = lowestKeyNr; i <= highestKeyNr; i++){
            float y = ((visu_lB+visu_r - (relBase+(float) i /12.0f))/visu_r*height);
            
            
            int func = (i+9+12)%12;
            Chord::FunctionType functionType = getFunctionTypeUnderVisuConstraints(c, func);
            if(functionType != Chord::FUNC_NAN){
                if(functionType == Chord::FUNC_REGULAR && ControllerSingleton::chords_visuArray[functionType]){
                    float h2 = h/3.0f;//TODO: diese Berechnung in die jeweilige Funktion geben
                    float y2 = y-h2/2.0f;
                    float h3 = h/5.0f;
                    float y3 = y-h3/2.0f;
                    if(layer == 0.0f){
                        if(ControllerSingleton::chords_Visualize)
                            visualizeNoteAsDotBackground(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x,
                                                         y3, w, h3);
                    }
                    //if(layer == 0)
                        //visualizeNoteAsDot(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x, y2, w, h2);


                }
                else{
                    float h2 = 0.7f*h;
                    if(functionType == Chord::FUNC_1){
                        h2 = 1.0f*h;
                    }
                    float y2 = y-h2/2.0f;
                    float h3 = h/5.0f;
                    float y3 = y-h3/2.0f;
                    if(layer == 0.0f){
                        if(ControllerSingleton::chords_visualizeAsDots){
                            if(ControllerSingleton::chords_Visualize)
                                visualizeNoteAsDotBackground(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x,
                                                         y3, w, h3);}
                        if(ControllerSingleton::chords_visualizeAsKeys){
                            if(ControllerSingleton::chords_Visualize)
                                visualizeNoteAsKey(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x,
                                               y2, w, h2);}
                    }
                    
                    if(layer == 0.5f){
                        
                        std::vector<std::tuple<int, int, int>> guideLines = c.getGuideLines(func);
                        Chord nextChord = c.acquireNext();
                        if(guideLines.size() > 0){
                            float w2 = (1.0f/ControllerSingleton::barsPerScreen*nextChord.lengthInBars)*width*(1.0f-ControllerSingleton::basicp_ScreenPortion)-10.0f;
                            //TODO hier haben wir ein Problem, das funktioniert nicht, wenn barsperscreen kleiner der eigentlichen Bars is...
                            bool isWrapAround = false;
                            float positionXNextChord = nextChord.positionX;
                            if (nextChord.positionX < c.positionX){
                                positionXNextChord += Chord::totalLengthOfSongInBars;
                                isWrapAround = true;
                            }
                            float x2 = (1.0f/ControllerSingleton::barsPerScreen*(positionXNextChord)*(1.0f-ControllerSingleton::basicp_ScreenPortion) + (ControllerSingleton::basicp_ScreenPortion))*width;
                            if(ControllerSingleton::chords_visualizeGuidelines){
                                for(int i = 0; i < guideLines.size(); i++){
                                    float y2_2 = y - 1.0f*std::get<1>(guideLines[i])*h;
                                    visualizeGuideLine(x, y, w, x2, y2_2, w2, h3, height, g);
//                                    if(isWrapAround){std::cout << "wraparound";}
//                                    visualizeGuideLine(x-(1.0f/ControllerSingleton::barsPerScreen*(Chord::totalLengthOfSongInBars))*(1.0f-ControllerSingleton::basicp_ScreenPortion)*width,
//                                                                                               y,
//                                                                                               w,
//                                                                                               x2-(1.0f/ControllerSingleton::barsPerScreen*(Chord::totalLengthOfSongInBars))*(1.0f-ControllerSingleton::basicp_ScreenPortion)*width,
//                                                                                               y2_2,
//                                                                                               w2,
//                                                                                               h3,
//                                                                                               height,
//                                                                                               g);
                                }
                            }
                        }
                    }
                    
                    
                    if(layer == 1.0f){
                        if(ControllerSingleton::chords_visualizeAsDots){
                            if(ControllerSingleton::chords_Visualize)
                                visualizeNoteAsDot(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x, y2, w, h2);
                            
                        }
                    }

                }
            }


        }
        if(isCurrentChord(c)){
            float chordPositionRightNow = (0-c.positionX)/c.lengthInBars;

            float timeSinceArrivalMs = 60000.0f*(chordPositionRightNow*c.lengthInBars*ControllerSingleton::bpb/ControllerSingleton::bpm);
            float mix = 0.0f;
            if(timeSinceArrivalMs < 350.0f){
                mix = 1.0f-timeSinceArrivalMs/350.0f;
            }
            mix *= 0.2f;
            g.setColour(Colours::white.interpolatedWith(Colour::fromRGBA(0.0f,0.0f,0.0f, 0.0f), 1.0f-mix));
            g.fillAll();
        }

        
    }
    
}


//==============================================================================
//private
void ChordVisualisation::visualizeNoteAsKey(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float relBase, int i, Graphics& g, float height, float width, float x, float y, float w, float h){
    

    //Dropshadow
    /*
    if(ControllerSingleton::dropShadows){
        DropShadow * bla = new DropShadow(Colour::fromRGBA(0,0,0,100), 10, Point<int>(10,10));
        bla -> drawForRectangle(g, *(new Rectangle<int>(x,y,w,h)));
    }
    */

    int isBlackKey = isBlack(func);
    Colour col;
    //get Colour
    if(isBlackKey){
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourBlackScheme.at(Chord::FUNC_REGULAR):functionTypeToColourBlackScheme.at(functionType);
    }
    else{
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourWhiteScheme.at(Chord::FUNC_REGULAR):functionTypeToColourWhiteScheme.at(functionType);
    }

    if(ControllerSingleton::chords_fadeOutHorizontal){
        g.setGradientFill(*(new ColourGradient(col, x, 0, Colour::fromRGBA(0,0,0,0), x+w, 0, false)));
    }
    else{
        g.setColour(col);
    }
    g.fillRoundedRectangle(x,y,w,h,2.0f);
    col = colourForKeyBorder;
    if(ControllerSingleton::chords_fadeOutHorizontal){
        g.setGradientFill(*(new ColourGradient(col, x, 0, Colour::fromRGBA(0,0,0,0), x+w, 0, false)));
    }
    else{
        g.setColour(col);
    }
    g.drawRoundedRectangle(x,y,w,h,2.0f, thicknessForKeyBorder);

    g.setFont(h/3.0f);
    g.setColour(Colours::black);
    if(functionType != Chord::FUNC_REGULAR)
        g.drawText(keyName_get(func, c, functionType), x ,y, w,h, Justification::centred, true);
}



void ChordVisualisation::visualizeNoteAsDot(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float relBase, int i, Graphics& g, float height, float width, float x, float y, float w, float h){
    
    

    int isBlackKey = isBlack(func);

    Colour col;
    Colour col2 = colourForKeyBorder;
    Colour col3 = Colours::black;
    Colour dropShadowCol = Colour::fromRGBA(0,0,0,255);
    //get Colour
    if(isBlackKey){
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourBlackScheme.at(Chord::FUNC_REGULAR):functionTypeToColourBlackScheme.at(functionType);
    }
    else{
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourWhiteScheme.at(Chord::FUNC_REGULAR):functionTypeToColourWhiteScheme.at(functionType);
    }
    
    if(isCurrentChord(c)){
        x = std::max(x, (ControllerSingleton::basicp_ScreenPortion * (1.0f) * width));

        float mix = 0.0f;
        float chordPositionRightNow = (0-c.positionX)/c.lengthInBars;
        if(chordPositionRightNow > 0.5f){
            mix = std::pow((chordPositionRightNow-0.5f)*2.0f, 1);
        }
        col = col.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        col2 = col2.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        col3 = col3.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        dropShadowCol = dropShadowCol.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        
    }
    
    if(ControllerSingleton::dropShadows){
        DropShadow * bla = new DropShadow(dropShadowCol, 0.3*h, Point<int>(0,0));
        bla -> drawForRectangle(g, *(new Rectangle<int>(x-0.25f*h, y+0.25f*h, 0.6f*h, 0.6f*h)));
    }
    
    g.setColour(col);
    g.fillEllipse(x-0.5*h,y,h,h);
    g.setColour(col2);
    g.drawEllipse(x-0.5*h,y,h,h,thicknessForKeyBorder);

    g.setFont(h/3.0f);
    g.setColour(col3);
    if(functionType != Chord::FUNC_REGULAR){}
        g.drawText(keyName_get(func, c, functionType), x-0.5*h ,y,h,h, Justification::centred, true);
    
    


}


void ChordVisualisation::visualizeNoteAsDotBackground(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float relBase, int i, Graphics& g, float height, float width, float x, float y, float w, float h){

    //bool isBlackKey = isBlack(func);
    
    Colour col = Colours::white.interpolatedWith(Colour::fromRGBA(0,0,0,0), isCurrentChord(c)?0.4f:0.75f);
    float x2 = std::max(x, (ControllerSingleton::basicp_ScreenPortion*(1.0f)*width));
    if(ControllerSingleton::chords_fadeOutHorizontal && isCurrentChord(c)){
        g.setGradientFill(*(new ColourGradient(col, x, 0, Colour::fromRGBA(255,255,255,40), x+w, 0, false)));
    }
    else{
        g.setColour(col);
    }
    if(x+w-x2 >= 0)
        g.fillRect(x2,y,x+w-x2,h);

}

void ChordVisualisation::visualizeGuideLine(float x, float y, float w, float x2, float y2, float w2, float hVisu, float height, Graphics& g){
    Path p;
    p.startNewSubPath(x+w*0.5f, y);
    p.lineTo(x+w*0.75f, y);
    p.cubicTo(x2+0.1f*w2, y, x+w*0.75f+(w2*(0.25f-0.1f)), y2, x2+w2*0.25f, y2);
    p.lineTo(x2+w2*0.5f, y2);
    g.setColour(Colours::yellow);
    g.strokePath(p, PathStrokeType(hVisu));
}



Chord::FunctionType ChordVisualisation::getFunctionTypeUnderVisuConstraints(Chord c, int func){

    //translate e.g. 13 to reg or av to reg or 13 to 13
    Chord::FunctionType functionType = c.functionForNote[func];
    if(functionType != Chord::FUNC_NAN){
        functionType = ControllerSingleton::chords_visuArray[functionType]?functionType:Chord::FUNC_REGULAR;
    }
    return functionType;
}

bool ChordVisualisation::isOnScreen(Chord c){//TODO Einberechnen der Buttongröße für Dotvisualisation
    if(c.positionX > ControllerSingleton::barsPerScreen)
        return false;
    if(c.positionX+c.lengthInBars+0.5f < 0.0f)
        return false;

    return true;
}

bool ChordVisualisation::isCurrentChord(Chord c){
    if(c.positionX <= 0.0f && c.positionX+c.lengthInBars >= 0)
        return true;
    return false;
}

String ChordVisualisation::keyName_get(int func, Chord c, Chord::FunctionType funcType){
    if(funcType == Chord::FUNC_1){
        return c.baseName+c.chordName;
    }
    int distFromBase = (func-c.base+12)%12;
    const int distFrombaseInNatural = keyName_DistFromBaseInNaturalNotes[distFromBase];
    std::pair<const String, const String> namePairFromAbsoluteFunc = keyName_NamePairFromAbsoluteFunc[func];
    std::map<juce_wchar, int> bla = {{'C', 0},{'D', 1},{'E', 2},{'F', 3},{'G', 4},{'A', 5},{'B', 6}};
    int indexOfBaseInNatural = bla.at(c.baseName[0]);
    juce_wchar naturalNoteName = keyName_naturalNotesFromC[(indexOfBaseInNatural+distFrombaseInNatural)%7];
    String s = namePairFromAbsoluteFunc.first.startsWithChar(naturalNoteName)?namePairFromAbsoluteFunc.first:namePairFromAbsoluteFunc.second;
    return s;
}

bool ChordVisualisation::isBlack(int func){
    if(func == 1 || func == 3 || func == 6 || func == 8 || func == 10){
        return true;
    }
    else return false;
}
