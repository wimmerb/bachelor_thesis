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
#include "ControllerSingleton.h"

//==============================================================================
class AnalyserComponent   : public AudioAppComponent,
                            private AsyncUpdater
{
public:
    AnalyserComponent() : pitchMPM(fftSize),    audioSetupComp (deviceManager,
                                                                                 0,     // minimum input channels
                                                                                 256,   // maximum input channels
                                                                                 0,     // minimum output channels
                                                                                 256,   // maximum output channels
                                                                                 false, // ability to select midi inputs
                                                                                 false, // ability to select midi output device
                                                                                 false, // treat channels as stereo pairs
                                                                                 false) // hide advanced options
    {
        //setOpaque (true);
        setVisible(false);
        setAudioChannels (2, 2);  // we want to also control output

        setSize (700, 500);
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"Samplerate:\t";
        std::cout<<deviceManager.getCurrentAudioDevice()->getCurrentSampleRate();
        std::cout<<"\n¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        std::cout<<"¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢\n";
        SharedResources::samplerate = deviceManager.getCurrentAudioDevice()->getCurrentSampleRate();
        samplerateComp = deviceManager.getCurrentAudioDevice()->getCurrentSampleRate()/44100;

        SharedResources::pitchHistorySize = fftSize;
        
        //handleInputs
        dywapitch_inittracking(tracker);
        
        shutdownAudio();
        //handleOutputs
        formatManager.registerBasicFormats();
        std::unique_ptr<AudioFormatReader> reader;
        if(ControllerSingleton::songAudioFileName.isEmpty()){
            
            std::cout << "empty";
            std::unique_ptr<MemoryInputStream> memoryInput( new MemoryInputStream (BinaryData::SONGS_1625_wav, BinaryData::SONGS_1625_wavSize, false));
            formatManager.createReaderFor(memoryInput.release());
            reader.reset(formatManager.createReaderFor (memoryInput.release()));
            
        }
        else{
            String s = "";
            s.append(ControllerSingleton::songAudioFileName, 200);
            s.append("_wav", 10);
            int size;
            std::unique_ptr<MemoryInputStream> memoryInput( new MemoryInputStream (BinaryData::getNamedResource(s.getCharPointer(), size), (size_t) size, false));
            reader.reset(formatManager.createReaderFor (memoryInput.release()));
            
        }
        //std::unique_ptr<AudioFormatReader> reader (formatManager.createReaderFor (x));
        
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
            //setAudioChannels (0, (int) reader->numChannels);                                // [7]
            SharedResources::sampleCountOfSong = fileToPlay.getNumSamples();
        }
        
        std::unique_ptr<MemoryInputStream> memoryInput( new MemoryInputStream (BinaryData::AUDIO_Stick_Count_wav, (size_t) BinaryData::AUDIO_Stick_Count_wavSize, false));
        std::unique_ptr<AudioFormatReader> counterReader(formatManager.createReaderFor (memoryInput.release()));
        int lenghtInSamplesForCountIn = std::round((float)ControllerSingleton::bpb/(float)ControllerSingleton::bpm*60.0f*(float)SharedResources::samplerate);
        if (counterReader.get() != nullptr)
        {
            counterFileToPlay.setSize((int) counterReader->numChannels, lenghtInSamplesForCountIn);
            counterFileToPlay.clear();
            int stepSize = std::round(lenghtInSamplesForCountIn/ControllerSingleton::bpb);
            for(int i = 0; i < ControllerSingleton::bpb; i++){
                counterReader->read(&counterFileToPlay, i*stepSize, std::min(stepSize, (int)counterReader->lengthInSamples), 0, true, true);
            }
            setAudioChannels (2, (int) counterReader->numChannels);
            counterFilePositionToPlay = 0;
            SharedResources::countIn = true;
        }
        //isActivated = true;
        
        
        
        //MPM
        pitchMPM.setSampleRate (SharedResources::samplerate);
        //pitchMPM.setBufferSize (fftSize);
    }

    ~AnalyserComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int, double) override {}
    void releaseResources() override          {}
    
    void receiveControls (const String & s){
        if(s == "Play"){
            isPlaying = true;
        }
        if(s == "Pause"){
            isPlaying = false;
        }
        if(s == "Stop"){
            handleStop();
        }
    }
    
    void handleStop(){
        receiveControls ("Pause");
        wantToStop = true;
    }
    
    void reset(){
        SharedResources::countIn = true;
        freshStart = true;
        counterFilePositionToPlay = 0;
        positionToPlay = 0;
        
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        //std::cout << bufferToFill.numSamples << "\n"; -> 512 Samples am Mac
        //Audio-Video Sync
        SharedResources::samplesPositionOfSong = positionToPlay+bufferToFill.numSamples;
//
        //HandleInput
        {
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
        }

//        if(!isActivated)
//            return;
        //HandleOutput
        {
        auto numInputChannels = fileToPlay.getNumChannels();
        auto numOutputChannels = bufferToFill.buffer->getNumChannels();

        auto outputSamplesRemaining = bufferToFill.numSamples;
        auto outputSamplesOffset = bufferToFill.startSample;
        
        double fadeVolumeOld = fadeVolume;
        
        bool playBackPlaying = true;
            
        if(!isPlaying && fadeVolume == 0.0){
            if(wantToStop){
                reset();
                wantToStop = false;
            }
            playBackPlaying = false;
        }
        
        
        if ((!isPlaying && fadeVolume == 1.0) || (isPlaying && fadeVolume == 0.0)){
            fadeVolume = 1.0 - fadeVolume;
            if(isPlaying && freshStart){
                fadeVolumeOld = 1.0;
                freshStart = false;
            }
        }
        
        while (outputSamplesRemaining > 0)
        {
            
            auto bufferSamplesRemaining = fileToPlay.getNumSamples() - positionToPlay;
            if(SharedResources::countIn){
                bufferSamplesRemaining = counterFileToPlay.getNumSamples() - counterFilePositionToPlay;
            }
            auto samplesThisTime = jmin (outputSamplesRemaining, bufferSamplesRemaining);
            
            //zeromem (SynthBuffer, sizeof (SynthBuffer));
            double quantizedPitch = std::floor((double)SharedResources::synthPitch) + std::round(std::fmod((double)SharedResources::synthPitch, 1.0)*12.0)/12.0;
            double pitchInHz = 110.0 * std::pow(2.0, quantizedPitch);
            double AngularDistance = 2.0*MathConstants<double>::pi*pitchInHz/(double)SharedResources::samplerate;
            for(int i = 0; i < samplesThisTime; i++){
                SynthPosition += AngularDistance;
                //SynthPosition = std::fmod(SynthPosition, 2.0*pi);
                if(SharedResources::synthIsPlaying){
                    SynthVolume = std::min(1.0, SynthVolume+0.1);
                }
                else{
                    SynthVolume = std::max(0.0, SynthVolume-0.1);
                }
                SynthBuffer[i] = (float)std::sin(SynthPosition)*SynthVolume;
            }
            
            if(playBackPlaying){
                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                    if(SharedResources::countIn){
                        bufferToFill.buffer->copyFrom (channel,
                                                       outputSamplesOffset,
                                                       counterFileToPlay,
                                                       channel % numInputChannels,
                                                       counterFilePositionToPlay,
                                                       samplesThisTime);
                        bufferToFill.buffer->applyGainRamp(channel, outputSamplesOffset, samplesThisTime, fadeVolumeOld, fadeVolume);
                        bufferToFill.buffer->addFrom(channel,
                                                     outputSamplesOffset,
                                                     SynthBuffer,
                                                     samplesThisTime, 0.15f
                                                     );
                    }
                    else{
                        bufferToFill.buffer->copyFrom (channel,
                                                       outputSamplesOffset,
                                                       fileToPlay,
                                                       channel % numInputChannels,
                                                       positionToPlay,
                                                       samplesThisTime);
                        bufferToFill.buffer->applyGainRamp(channel, outputSamplesOffset, samplesThisTime, fadeVolumeOld, fadeVolume);
                        bufferToFill.buffer->addFrom(channel,
                                                     outputSamplesOffset,
                                                     SynthBuffer,
                                                     samplesThisTime, 0.3f
                                                     );
                    }
                    bufferToFill.buffer->applyGain(channel, outputSamplesOffset, samplesThisTime, 0.5f);
                }

                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                if(SharedResources::countIn){
                    counterFilePositionToPlay += samplesThisTime;
                    positionToPlay = 0-counterFileToPlay.getNumSamples()+counterFilePositionToPlay+SharedResources::sampleCountOfSong;
                    if (counterFilePositionToPlay == counterFileToPlay.getNumSamples()){
                        counterFilePositionToPlay = 0;
                        positionToPlay = 0;
                        SharedResources::countIn = false;
                    }
                }
                else{
                    positionToPlay += samplesThisTime;
                    if (positionToPlay == fileToPlay.getNumSamples())
                        positionToPlay = 0;
                }
            }
            else{
                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                        bufferToFill.buffer->addFrom(channel,
                                                     outputSamplesOffset,
                                                     SynthBuffer,
                                                     samplesThisTime, 0.3f
                                                     );
                    bufferToFill.buffer->applyGain(channel, outputSamplesOffset, samplesThisTime, 0.5f);
                }
                
                
                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
            }

            
            
            
        }
        //If some other command needs to be placed here: watch out for the return if not isPlaying
        }
        
        
    }


    void handleAsyncUpdate() override
    {
        
        if (nextFFTBlockReady)
        {
            


            //OriginalPitchtrack
            
            double rms = 0.0;
//            rms = 1.0;
            for(int i = 0; i < fftSize; i++){
                rms += ptData[i] * ptData[i];
            }
            rms = std::sqrt(rms/fftSize);
            
            std::cout << rms << "RMS \n";
            
            //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "§§§§§§§§§§§RMS§§§§§§§§§\n");

            //rms = rms/(double)fftSize;
            
            //__android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%lf", rms);
            
            
                double x = 1.0;
                if(SharedResources::synthIsPlaying){
                    x = 110.0 * std::pow(2.0, SharedResources::synthPitch);
                    if (x > 0.0)
                        SharedResources::trackedPitch = log2(x/55.0/2.0);
                }
                else if(rms > 0.001 && (ControllerSingleton::pitchTrack_useMPM||ControllerSingleton::pitchTrack_useDywa)){
                    if(ControllerSingleton::pitchTrack_useMPM)
                        x = (double)pitchMPM.getPitch(fftData);
                    else if(ControllerSingleton::pitchTrack_useDywa)
                        x = samplerateComp*dywapitch_computepitch(tracker, ptData, 0, fftSize);
                    if (x > 0.0)
                        SharedResources::trackedPitch = log2(x/55.0/2.0);


                }
            
            std::cout << SharedResources::trackedPitch << "X\n";
            std::cout << SharedResources::synthPitch << "Synth\n";
            
            
            //tested if seen by others -> CHECK
//            SharedResources::trackedPitch = 2.0+0.15*std::sin(positionToPlay*0.0001);
//            if(std::abs(SharedResources::trackedPitch) > 1000.0f){
//                std::cout<< "GAVEHIMNAN";
//            }
            SharedResources::pitchHistory[SharedResources::pitchHistoryIndex = (SharedResources::pitchHistoryIndex+1)%SharedResources::pitchHistorySize]
            = std::pair<double, int>(SharedResources::trackedPitch, fftSize);

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
                //pitchMPM.getPitch(fftData);
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

    //SineWaveSynthesis
    float SynthBuffer [2048];
    double SynthPosition = 0.0;
    double SynthVolume = 0.0;
    
    //volumeFade
    double fadeVolume = 0.0;
    bool freshStart = true;
    bool isPlaying = false;
    bool wantToStop = false;
    //stub
    int i = 0;

    //MPM
    adamski::PitchMPM pitchMPM;
    
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
    AudioSampleBuffer counterFileToPlay;
    int counterFilePositionToPlay;
    
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
