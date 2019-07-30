/*
  ==============================================================================

    ChordVisualisation.h
    Created: 23 Jun 2019 4:06:57pm
    Author:  expert239

  ==============================================================================
*/

#pragma once
#include "Chord.h"


class ChordVisualisation
{
public:

    //==========================================================================
    ChordVisualisation();
    ~ChordVisualisation();
    //==========================================================================
    void visualizeBackgroundPiano(float visu_lB, float visu_r, Graphics& g, float height, float width);
    void visualizeBasicPiano(float visu_lB, float visu_r, Graphics& g, float height, float width);
    void visualize(Chord c, float visu_lB, float visu_r, Graphics& g, float height, float width, int layer);
    bool isCurrentChord(Chord c);
    //==========================================================================
    
private:

    //==========================================================================
    void visualizeNoteAsKey(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float base, int i, Graphics& g, float height, float width, float x, float y, float w, float h);
    void visualizeNoteAsDot(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float base, int i, Graphics& g, float height, float width, float x, float y, float w, float h);
    void visualizeNoteAsDotBackground(Chord c, Chord::FunctionType functionType, int func, float visu_lB, float visu_r, float relBase, int i, Graphics& g, float height, float width, float x, float y, float w, float h);
    Chord::FunctionType getFunctionTypeUnderVisuConstraints(Chord c, int func);
    bool isOnScreen(Chord c);

    bool isBlack(int func);
    Chord::FunctionType * currentlyPlayingNotes = new Chord::FunctionType[12]{Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN,
                                                                              Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN,
                                                                              Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN, Chord::FUNC_NAN};


    //KeyNameModule //TODO Tripel machen?
    const std::pair<const String, const String> keyName_NamePairFromAbsoluteFunc [12] = {{"C","C"},
                                                                     {"C#","Db"},
                                                                     {"D","D"},
                                                                     {"D#","Eb"},
                                                                     {"E","E"},
                                                                     {"F","F"},
                                                                     {"F#","Gb"},
                                                                     {"G","G"},
                                                                     {"G#","Ab"},
                                                                     {"A","A"},
                                                                     {"A#","Bb"},
                                                                     {"B","Cb"}
                                                                     };
    const int keyName_DistFromBaseInNaturalNotes [12] = {0,1,1,2,2,3,4,4,5,5,6,6};
    const juce_wchar keyName_naturalNotesFromC [7] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
    String keyName_get(int func, Chord c, Chord::FunctionType funcType);


    //LookControl
    const Colour colourForKeyBorder = Colours::grey;
    const float thicknessForKeyBorder = 1.5f;

    enum ColourType {
        COL_BLACK,
        COL_WHITE,
        COL_BLUE,
        COL_YELLOW,
        COL_RED
    };

    const std::map<ColourType, Colour> colourTypeToColour {
            {COL_BLACK, Colours::black},
            {COL_WHITE, Colours::white},
            {COL_BLUE, Colours::blue},
            {COL_YELLOW, Colours::yellow},
            {COL_RED, Colours::red}
    };

    const std::map<Chord::FunctionType, Colour> functionTypeToColourBlackScheme = {
            {Chord::FUNC_1,        Colours::cyan},
            {Chord::FUNC_3,        Colours::lightgrey},
            {Chord::FUNC_5,        Colours::lightgrey},
            {Chord::FUNC_7,        Colours::lightgrey},
            {Chord::FUNC_9,        Colours::black},
            {Chord::FUNC_11,       Colours::black},
            {Chord::FUNC_13,       Colours::black},
            {Chord::FUNC_REGULAR,  Colours::lightgrey},
            {Chord::FUNC_AVOID,    Colours::black},
            {Chord::FUNC_NAN,      Colour::fromRGBA(0,0,0,60)},
    };

    const std::map<Chord::FunctionType, Colour> functionTypeToColourWhiteScheme = {
            {Chord::FUNC_1,        Colours::cyan},
            {Chord::FUNC_3,        Colours::lightgrey},
            {Chord::FUNC_5,        Colours::lightgrey},
            {Chord::FUNC_7,        Colours::lightgrey},
            {Chord::FUNC_9,        Colours::white},
            {Chord::FUNC_11,       Colours::white},
            {Chord::FUNC_13,       Colours::white},
            {Chord::FUNC_REGULAR,  Colours::lightgrey},
            {Chord::FUNC_AVOID,    Colours::white},
            {Chord::FUNC_NAN,      Colour::fromRGBA(255,255,255,150)},
    };
    /*
    const std::map<Chord::FunctionType, Colour> functionTypeToColourBlackScheme = {
        {Chord::FUNC_1,        Colours::black.interpolatedWith(Colours::blue, 0.75f)},
        {Chord::FUNC_3,        Colours::yellow.interpolatedWith(Colours::black, 0.5f)},
        {Chord::FUNC_5,        Colours::black},
        {Chord::FUNC_7,        Colours::yellow.interpolatedWith(Colours::black, 0.5f)},
        {Chord::FUNC_9,        Colours::black},
        {Chord::FUNC_11,       Colours::black},
        {Chord::FUNC_13,       Colours::black},
        {Chord::FUNC_REGULAR,  Colours::black},
        {Chord::FUNC_AVOID,    Colours::black},
        {Chord::FUNC_NAN,      Colour::fromRGBA(0,0,0,60)},
    };
    
    const std::map<Chord::FunctionType, Colour> functionTypeToColourWhiteScheme = {
        {Chord::FUNC_1,        Colours::white.interpolatedWith(Colours::blue, 0.75f)},
        {Chord::FUNC_3,        Colours::yellow.interpolatedWith(Colours::white, 0.5f)},
        {Chord::FUNC_5,        Colours::white},
        {Chord::FUNC_7,        Colours::yellow.interpolatedWith(Colours::white, 0.5f)},
        {Chord::FUNC_9,        Colours::white},
        {Chord::FUNC_11,       Colours::white},
        {Chord::FUNC_13,       Colours::white},
        {Chord::FUNC_REGULAR,  Colours::white},
        {Chord::FUNC_AVOID,    Colours::white},
        {Chord::FUNC_NAN,      Colour::fromRGBA(255,255,255,150)},
    };*/
    //==========================================================================
    
};