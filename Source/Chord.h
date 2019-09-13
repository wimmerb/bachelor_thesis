/*
  ==============================================================================

    Chord.h
    Created: 14 Jun 2019 3:27:20pm
    Author:  expert239

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <optional>
#include <list>

class Chord
{
public:

    //==========================================================================
    Chord(String scale, String chordType, String base, float lengthInBars);
    ~Chord();
    //==========================================================================
    void updatePosition(float samplePositionOfSong);
    enum FunctionType {
        FUNC_1,
        FUNC_3,
        FUNC_5,
        FUNC_7,
        FUNC_9,
        FUNC_11,
        FUNC_13,
        FUNC_REGULAR,
        FUNC_AVOID,
        FUNC_NAN
    };
    
    
    FunctionType * functionForNote = new FunctionType [12];
    float lengthInBars;
    float positionX;
    
    String toString();
    static void initFromChordVector(std::vector<Chord> * cv);

    String baseName;
    String chordName;
    String scaleName;
    int base;
    
    Chord acquireNext();
    
    int Id;
    static int IdCount;
    
    static float totalLengthOfSongInBars;
    
    std::vector<std::tuple<int, int, int>> guideLines;
    std::vector<std::tuple<int, int, int>> getGuideLines(int func);
    //==========================================================================
    
private:
    
    //==========================================================================
    const std::map<const String, const std::vector<FunctionType>> scaleNameToFunctions =
            {
                    {"Major",
                    {FUNC_1, FUNC_NAN, FUNC_9, FUNC_NAN, FUNC_3, FUNC_11, FUNC_NAN, FUNC_5, FUNC_NAN, FUNC_13, FUNC_NAN, FUNC_7}},
                    {"Lydian",
                    {FUNC_1, FUNC_NAN, FUNC_9, FUNC_NAN, FUNC_3, FUNC_NAN, FUNC_11, FUNC_5, FUNC_NAN, FUNC_13, FUNC_NAN, FUNC_7}},
                    {"Mixolydian",
                     {FUNC_1, FUNC_NAN, FUNC_9, FUNC_NAN, FUNC_3, FUNC_11, FUNC_NAN, FUNC_5, FUNC_NAN, FUNC_13, FUNC_7, FUNC_NAN}},
                     {"HM5",
                     {FUNC_1, FUNC_9, FUNC_NAN, FUNC_NAN, FUNC_3, FUNC_11, FUNC_NAN, FUNC_5, FUNC_13, FUNC_NAN, FUNC_7, FUNC_NAN}},
                    {"Altered",
                     {FUNC_1, FUNC_9, FUNC_NAN, FUNC_9, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_13, FUNC_NAN, FUNC_7, FUNC_NAN}},
                    {"Minor",
                     {FUNC_1, FUNC_NAN, FUNC_9, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_5, FUNC_13, FUNC_NAN, FUNC_7, FUNC_NAN}},
                    {"Phrygian",
                    {FUNC_1, FUNC_9, FUNC_NAN, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_5, FUNC_13, FUNC_NAN, FUNC_7, FUNC_NAN}},
                    {"Dorian",
                     {FUNC_1, FUNC_NAN, FUNC_9, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_5, FUNC_NAN, FUNC_13, FUNC_7, FUNC_NAN}},
                    {"Harmonic",
                     {FUNC_1, FUNC_NAN, FUNC_9, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_5, FUNC_13, FUNC_NAN, FUNC_NAN, FUNC_7}},
                    {"Melodic",
                     {FUNC_1, FUNC_NAN, FUNC_9, FUNC_3, FUNC_NAN, FUNC_11, FUNC_NAN, FUNC_5, FUNC_NAN, FUNC_13, FUNC_NAN, FUNC_7}},
            };

    const std::map<const String, const int> baseToInt =
            {
                    {"C", 0},{"C#", 1},{"Db", 1},{"D", 2},{"D#", 3},{"Eb", 3},{"E", 4},{"F", 5},
                    {"F#", 6},{"Gb", 6},{"G", 7},{"G#", 8},{"Ab", 8},{"A", 9},{"A#", 10},{"Bb", 10},
                    {"B", 11},
            };

            
    void initFunctionForNote(String scaleName, String chordName);
    
    void initGuidelines();

    
    static std::vector<Chord> * chordVector;
    
    float beginsAtSampleCount = 0.0f;
    float endsAtSampleCount = 0.0f;

    //==========================================================================
    
};
