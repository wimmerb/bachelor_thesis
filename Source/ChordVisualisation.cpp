/*
  ==============================================================================

    ChordVisualisation.cpp
    Created: 23 Jun 2019 4:06:57pm
    Author:  expert239

  ==============================================================================
*/

#include "ChordVisualisation.h"
#include "ControllerSingleton.h"

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
        bla -> drawForRectangle(g, *(new Rectangle<int>(width/ControllerSingleton::barsPerScreen, 0, 1, height)));
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

        Colour col = isBlackKey?Colour::fromRGBA(0,0,0,120):Colour::fromRGBA(255,255,255,120);

        

        w = 1.0f/ControllerSingleton::barsPerScreen*width;
        h = height/ControllerSingleton::nrOfVisualizedKeys;
        x = 0.0f;
        y = ((visu_lB+visu_r - (relBase+(float) i /12.0f))/visu_r*height);
        

        col = isBlackKey?Colour::fromRGBA(0,0,0,100):Colour::fromRGBA(255,255,255,100);
        
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

        Path p;
        if(isBlackKey){
            p.startNewSubPath(x+0.4f*w, y-0.45f*h);
            p.lineTo(x+w, y-0.45f*h);
            p.lineTo(x+w, y+0.45f*h);
            p.lineTo(x+0.4f*w, y+0.45f*h);
        }
        else{
            float toTheLeft = 0.5f;
            float toTheRight = 0.5f;
            float narrowToTheRight = 0.55f;
            float narrowToTheLeft = 0.55f;
            //Left is up, right is down
            if(!(func == 0 || func == 4 || func == 5 || func == 11)){
                toTheLeft = 1.0f;
                toTheRight = 1.0f;
            }
            if(func == 4 || func == 11){
                toTheRight = 1.0f;
                narrowToTheLeft = 0.5f;
            }
            if(func == 0 || func == 5){
                toTheLeft = 1.0f;
                narrowToTheRight = 0.5f;
            }
            float startX = x                            +1.0f;
            float middleX = x+0.4f*w                    -1.0f;
            float endX = x+w                            -1.0f;
            float leftOuterY = y-toTheLeft*h            +1.0f;
            float leftInnerY = y-narrowToTheLeft*h      +1.0f;
            float rightInnerY = y+narrowToTheRight*h    -1.0f;
            float rightOuterY = y+toTheRight*h          -1.0f;
            p.startNewSubPath(startX, leftOuterY);
            p.lineTo(middleX, leftOuterY);
            p.lineTo(middleX, leftInnerY);
            p.lineTo(endX, leftInnerY);
            p.lineTo(endX, rightInnerY);
            p.lineTo(middleX, rightInnerY);
            p.lineTo(middleX, rightOuterY);
            p.lineTo(startX, rightOuterY);
        }
        p.closeSubPath();
        g.setColour(col);
        g.fillPath(p);
        g.setColour(Colours::lightgrey);
        //g.strokePath(p, PathStrokeType((funcType != Chord::FUNC_NAN)?thicknessForKeyBorder*1.5f:thicknessForKeyBorder));
//        g.setColour(col);
//        g.fillRect(x,y-0.5f*h,w,h);
//        g.setColour(Colours::lightgrey);
//        g.drawRect(x,y-0.5f*h,w,h, (funcType != Chord::FUNC_NAN)?thicknessForKeyBorder*1.5f:thicknessForKeyBorder);
    }
}

void ChordVisualisation::visualize(Chord c, float visu_lB, float visu_r, Graphics& g, float height, float width, int layer){
    if(isCurrentChord(c)){
        currentlyPlayingNotes = c.functionForNote;
    }
    if(isOnScreen(c)){
        
        int lowestKeyNr = (int)std::floor(fmod(visu_lB, 1.0f)*12.0f);
        float relBase = std::round(visu_lB - (fmod(visu_lB, 1.0f)));
        int highestKeyNr = (int)std::ceil((visu_lB+visu_r-relBase)*12.0f);

        float x = (1.0f/ControllerSingleton::barsPerScreen*(1.0f+c.positionX))*width;
        float h = height/ControllerSingleton::nrOfVisualizedKeys;
        float w = (1.0f/ControllerSingleton::barsPerScreen*c.lengthInBars)*width-10.0f;
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
                    if(layer == 1){
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
                    //if(layer == 1){
                    //    visualizeNoteAsKey(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x, y2, w, h2);
                    //}
                    if(layer == 1){
                        if(ControllerSingleton::chords_visualizeAsDots)
                            visualizeNoteAsDotBackground(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x,
                                                         y3, w, h3);
                        if(ControllerSingleton::chords_visualizeAsKeys)
                            visualizeNoteAsKey(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x,
                                               y2, w, h2);
                        
                        std::vector<std::tuple<int, int, int>> guideLines = c.getGuideLines(func);
                        Chord nextChord = c.acquireNext();
                        if(guideLines.size() > 0){
                            float w2 = (1.0f/ControllerSingleton::barsPerScreen*nextChord.lengthInBars)*width-10.0f;
                            //TODO hier haben wir ein Problem, das funktioniert nicht, wenn barsperscreen kleiner der eigentlichen Bars is...
                            bool isWrapAround = false;
                            float positionXNextChord = nextChord.positionX;
                            if (nextChord.positionX < c.positionX){
                                positionXNextChord += Chord::totalLengthOfSongInBars;
                                isWrapAround = true;
                            }
                            float x2 = (1.0f/ControllerSingleton::barsPerScreen*(1.0f+positionXNextChord))*width;
                            if(ControllerSingleton::chords_visualizeGuidelines){
                                for(int i = 0; i < guideLines.size(); i++){
                                    float y2_2 = y - 1.0f*std::get<1>(guideLines[i])*h;
                                    visualizeGuideLine(x, y, w, x2, y2_2, w2, h3, height, g);
                                    if(isWrapAround)
                                        visualizeGuideLine(x-(1.0f/ControllerSingleton::barsPerScreen*(Chord::totalLengthOfSongInBars))*width,
                                                           y,
                                                           w,
                                                           x2-(1.0f/ControllerSingleton::barsPerScreen*(Chord::totalLengthOfSongInBars))*width,
                                                           y2_2,
                                                           w2,
                                                           h3,
                                                           height,
                                                           g);
                                }
                            }
                        }
                    }
                    
                    
                    
                    
                    if(layer == 0){
                        if(ControllerSingleton::chords_visualizeAsDots)
                            visualizeNoteAsDot(c, functionType, func, visu_lB, visu_r, relBase, i , g, height, width, x, y2, w, h2);
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
    //get Colour
    if(isBlackKey){
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourBlackScheme.at(Chord::FUNC_REGULAR):functionTypeToColourBlackScheme.at(functionType);
    }
    else{
        col = !(ControllerSingleton::chords_visualizeWithColours)?functionTypeToColourWhiteScheme.at(Chord::FUNC_REGULAR):functionTypeToColourWhiteScheme.at(functionType);
    }
    
    if(isCurrentChord(c)){
        x = std::max(x, (1.0f / ControllerSingleton::barsPerScreen * (1.0f) * width));

        float mix = 0.0f;
        float chordPositionRightNow = (0-c.positionX)/c.lengthInBars;
        if(chordPositionRightNow > 0.5f){
            mix = std::pow((chordPositionRightNow-0.5f)*2.0f, 1);
        }
        col = col.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        col2 = col2.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
        col3 = col3.interpolatedWith(Colour::fromRGBA(0,0,0,0), mix);
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
    float x2 = std::max(x, (1.0f/ControllerSingleton::barsPerScreen*(1.0f)*width));
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

bool ChordVisualisation::isOnScreen(Chord c){
    if(c.positionX > ControllerSingleton::barsPerScreen - 1)
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
