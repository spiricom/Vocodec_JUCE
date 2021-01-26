/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UIConstants.h"
#include "sfx.h"

//==============================================================================
/**
*/

class VocodecAudioProcessor : public AudioProcessor,
                              public MidiInputCallback,
                              public MidiKeyboardStateListener,
                              public HighResolutionTimer
{
public:
    //==============================================================================
    VocodecAudioProcessor();
    ~VocodecAudioProcessor();
	//==============================================================================
	MidiKeyboardState keyboardState;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

	void setMidiInput();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void hiResTimerCallback() override;
    
    void updateChoiceParams();
    void updateChoiceValues();
    void updateAllValues();
    
    StringArray pluginParamPrefixes;
    StringArray pluginParamNames;
    StringArray choiceParamNames;

    AudioParameterFloat* inputGain;
    AudioParameterFloat* dryWetMix;
    HashMap<int, AudioParameterFloat*> pluginParams;
    HashMap<String, AudioParameterChoice*> choiceParams;
    
    float audioInput[2], audioOutput[2];
    
    tEnvelopeFollower inputFollower[2], outputFollower[2];
    
    vocodec::Vocodec vcd;
    
    float editorScale = 1.0f;
    
private:
    
    char small_memory[SMALL_MEM_SIZE];
    char medium_memory[MED_MEM_SIZE];
    char large_memory[LARGE_MEM_SIZE];
    
    uint16_t ADC_values[NUM_ADC_CHANNELS];
    
	bool isAddingFromMidiInput = false;
    
    int processingInactiveCount;
    int processingInactiveThreshold;
    bool processingFalseBlock = false;
    bool processingBlock = false;
    
    static void loadWav(vocodec::Vocodec* vcd) { vcd->attemptFileLoad = 1; }
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessor)
};
