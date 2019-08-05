/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             SpectrumAnalyserTutorial
 version:          2.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Displays an FFT spectrum analyser.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_dsp, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2017, linux_make

 type:             Component
 mainClass:        AnalyserComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once
#include "dywapitchtrack.h"
#include <time.h>
#include <iostream>
#include <unistd.h>
#include "SharedResources.h"

//==============================================================================
class AnalyserComponent   : public AudioAppComponent,
                            private AsyncUpdater
{
public:
    AnalyserComponent()
        :                                                         audioSetupComp (deviceManager,
                                                                                 0,     // minimum input channels
                                                                                 256,   // maximum input channels
                                                                                 0,     // minimum output channels
                                                                                 256,   // maximum output channels
                                                                                 false, // ability to select midi inputs
                                                                                 false, // ability to select midi output device
                                                                                 false, // treat channels as stereo pairs
                                                                                 false) // hide advanced options
    {
        setOpaque (true);
        setAudioChannels (2, 2);  // we want to also control output

        setSize (700, 500);
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"Samplerate:\t";
        std::cout<<deviceManager.getCurrentAudioDevice()->getCurrentSampleRate();
        std::cout<<"\n¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        samplerateComp = deviceManager.getCurrentAudioDevice()->getCurrentSampleRate()/44100;

        //handleInputs
        dywapitch_inittracking(tracker);
        
        shutdownAudio();
        //handleOutputs
        formatManager.registerBasicFormats();
        
        File x ("/Users/expert239/Desktop/BA_hacky_1625.wav");
        std::unique_ptr<AudioFormatReader> reader (formatManager.createReaderFor (x));
        
        if (reader.get() != nullptr)
        {
            fileToPlay.setSize ((int) reader->numChannels, (int) reader->lengthInSamples);  // [4]
            reader->read (&fileToPlay,                                                      // [5]
                          0,                                                                //  [5.1]
                          (int) reader->lengthInSamples,                                    //  [5.2]
                          0,                                                                //  [5.3]
                          true,                                                             //  [5.4]
                          true);                                                            //  [5.5]
            positionToPlay = 0;                                                                   // [6]
            setAudioChannels (0, (int) reader->numChannels);                                // [7]
            SharedResources::sampleCountOfSong = fileToPlay.getNumSamples();
        }
        //isActivated = true;
        
    }

    ~AnalyserComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int, double) override {}
    void releaseResources() override          {}

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        //Audio-Video Sync
        SharedResources::samplesPositionOfSong = positionToPlay+bufferToFill.numSamples;
//
        //HandleInput
        if (bufferToFill.buffer->getNumChannels() > 0)
        {
            auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
            for (auto i = 0; i < bufferToFill.numSamples; ++i)
                pushNextSampleIntoFifo (channelData[i]);


            auto activeOutputChannels = deviceManager.getCurrentAudioDevice()->getActiveOutputChannels();
            auto maxOutputChannels = activeOutputChannels.getHighestBit()+1;
            for (auto channel = 0; channel < maxOutputChannels; ++channel){
                //auto* outBuffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
                bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
                /*
                auto* inBuffer = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);
                for(auto sample = 0; sample < bufferToFill.numSamples; ++sample){
                    auto level = 0.0f;
                    outBuffer[sample] =  inBuffer[sample] * level;
                }
                 */

            }

        }
        //setExitTime();
        //displayTiming();

//        if(!isActivated)
//            return;
        //HandleOutput

        auto numInputChannels = fileToPlay.getNumChannels();
        auto numOutputChannels = bufferToFill.buffer->getNumChannels();

        auto outputSamplesRemaining = bufferToFill.numSamples;                                  // [8]
        auto outputSamplesOffset = bufferToFill.startSample;                                    // [9]

        while (outputSamplesRemaining > 0)
        {
            auto bufferSamplesRemaining = fileToPlay.getNumSamples() - positionToPlay;                // [10]
            auto samplesThisTime = jmin (outputSamplesRemaining, bufferSamplesRemaining);       // [11]

            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                bufferToFill.buffer->copyFrom (channel,                                         // [12]
                                               outputSamplesOffset,                             //  [12.1]
                                               fileToPlay,                                      //  [12.2]
                                               channel % numInputChannels,                      //  [12.3]
                                               positionToPlay,                                  //  [12.4]
                                               samplesThisTime);                                //  [12.5]
            }

            outputSamplesRemaining -= samplesThisTime;                                          // [13]
            outputSamplesOffset += samplesThisTime;                                             // [14]
            positionToPlay += samplesThisTime;                                                        // [15]

            if (positionToPlay == fileToPlay.getNumSamples())
                positionToPlay = 0;                                                                   // [16]
            
            
        }
        
        
        
        
    }


    void handleAsyncUpdate() override
    {
        
        if (nextFFTBlockReady)
        {
            


            //OriginalPitchtrack
            
            double rms = 0.0;
            for(int i = 0; i < fftSize; i++){
                rms += std::abs(ptData[i]);
            }
            //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§RMS§§§§§§§§§\n");

            rms = rms/(double)fftSize;
            //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%lf", rms);
            if(rms>0.004){
                double x = samplerateComp*dywapitch_computepitch(tracker, ptData, 0, fftSize);
                if (x > 0.0){
                    SharedResources::trackedPitch = log2(x/55.0);
                }
            }
            
            //tested if seen by others -> CHECK
            //SharedResources::trackedPitch = 1.0+0.15*std::sin(positionToPlay*0.0006);
            if( (static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/100.0)))>95.0    )
                SharedResources::trackedPitch = 1.0 + 0.4*(((static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/2.0))))-1.0f);
            
            SharedResources::trackedPitch = SharedResources::trackedPitch+0.002*std::sin(positionToPlay*0.0007);
            SharedResources::pitchHistory[SharedResources::pitchHistoryIndex = (SharedResources::pitchHistoryIndex+1)%SharedResources::pitchHistorySize]
            = std::pair<double, int>(SharedResources::trackedPitch, positionToPlay);

            nextFFTBlockReady = false;

            setExitTime();
            //displayTiming();
        }
    }

    void pushNextSampleIntoFifo (float sample) noexcept
    {
        // if the fifo contains enough data, set a flag to say
        // that the next frame should now be rendered..
        if (fifoIndex == fftSize)
        {
            if (! nextFFTBlockReady)
            {


                zeromem (fftData, sizeof (fftData));
                memcpy (fftData, fifo, sizeof (fifo));

                zeromem (ptData, sizeof(ptData));


                for (int i = 0; i < fftSize; i++){
                    ptData[i] = (double) fftData[i];
                }








                nextFFTBlockReady = true;

                //triggerAsyncUpdate ();
                handleAsyncUpdate();


            }

            setEnterTime();
            fifoIndex = 0;
        }

        fifo[fifoIndex++] = sample;
    }

    enum
    {
        fftOrder  = 10,
        fftSize   = 1 << fftOrder,
    };

    

private:

    //stub
    int i = 0;

    //analyserAttributes
    float fifo [fftSize];
    float fftData [fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;

    //tracker
    double ptData [fftSize];
    dywapitchtracker * tracker = new dywapitchtracker;
    double * tracked;



    //Deviceselector
    AudioDeviceSelectorComponent audioSetupComp;
    double samplerateComp = 0.0;
    
    
    //OutputHandling
    AudioFormatManager formatManager;
    AudioSampleBuffer fileToPlay;
    int positionToPlay;
    
    //activation
//    bool isActivated = false;


    //systimes
    double a = 0.0;
    double b = 0.0;


    void displayTiming(){
        //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§§§§§§displaytimingAnalyser§§§§§§§§§§§§§§\n");
        //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%lf", b-a);
        //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§\n");
    }

    void setEnterTime(){
        a = now_ms();
    }

    void setExitTime(){
        b = now_ms();
    }

    static double now_ms(void) {

        struct timespec res;
        clock_gettime(CLOCK_REALTIME, &res);
        return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};
