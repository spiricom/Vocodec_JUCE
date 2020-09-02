/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "oled.h"
#include "ui.h"

//==============================================================================
VocodecAudioProcessor::VocodecAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),
#endif
pluginParamPrefixes(StringArray(cPluginParamPrefixes)),
pluginParamNames(StringArray(cPluginParamNames))
{
    SFX_init(&vcd, &ADC_values);
    vcd.currentPreset = vocodec::PresetNil;
    vcd.previousPreset = vocodec::PresetNil;
    vcd.loadingPreset = 1;
    
    I2C_HandleTypeDef* dummyArg = nullptr;
    vocodec::OLED_init(&vcd, dummyArg);
    
    dryWetMix = new AudioParameterFloat("dryWetMix", "dryWetMix",
                                        0.0f, 1.0f, 1.0f);
    addParameter(dryWetMix);
    for (int p = 0; p < int(vocodec::PresetNil); ++p)
    {
        for (int v = 0; v < vcd.numPages[p] * KNOB_PAGE_SIZE; ++v)
        {
            String name = String(vcd.knobParamNames[p][v]);
            if (!name.isEmpty())
            {
                int paramId = (p * NUM_PRESET_KNOB_VALUES) + v;
                String fullName = pluginParamPrefixes[p] + "_" + name;
                
                AudioParameterFloat* param = new AudioParameterFloat(fullName, fullName, 0.0f, 1.0f,
                                                                     vcd.defaultPresetKnobValues[p][v]);
                pluginParams.set(paramId, param);
                addParameter(param);
            }
        }
    }
}

VocodecAudioProcessor::~VocodecAudioProcessor()
{
}

//==============================================================================
const String VocodecAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VocodecAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool VocodecAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool VocodecAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double VocodecAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VocodecAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int VocodecAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VocodecAudioProcessor::setCurrentProgram (int index)
{
}

const String VocodecAudioProcessor::getProgramName (int index)
{
    return {};
}

void VocodecAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VocodecAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    processingInactiveCount = 0;
    processingInactiveThreshold = 4 * (samplesPerBlock / sampleRate) * 1000;
    
    LEAF_init(&vcd.leaf, sampleRate, samplesPerBlock, small_memory, SMALL_MEM_SIZE,
              []() {return (float)rand() / RAND_MAX; });
    tMempool_init(&vcd.mediumPool, medium_memory, MED_MEM_SIZE, &vcd.leaf);
    tMempool_init(&vcd.largePool, large_memory, LARGE_MEM_SIZE, &vcd.leaf);
    
    tEnvelopeFollower_init(&inputFollower[0], 0.0001f, 0.9995f, &vcd.leaf);
    tEnvelopeFollower_init(&inputFollower[1], 0.0001f, 0.9995f, &vcd.leaf);
    tEnvelopeFollower_init(&outputFollower[0], 0.0001f, 0.9995f, &vcd.leaf);
    tEnvelopeFollower_init(&outputFollower[1], 0.0001f, 0.9995f, &vcd.leaf);
    
    //ramps to smooth the knobs
    for (int i = 0; i < 6; i++)
    {
        tExpSmooth_init(&vcd.adc[i], 0.0f, 0.2f, &vcd.leaf);
    }
    
    vocodec::initGlobalSFXObjects(&vcd);

    // Everything in here should only happen on the first prepareToPlay.
    // Make sure not to set presetNumber to 0 except in the constructor.
    if (vcd.currentPreset == vocodec::PresetNil)
    {
        vcd.currentPreset = vocodec::Vocoder;
    }
    vcd.previousPreset = vocodec::PresetNil;
    vcd.loadingPreset = 1;
    
    startTimer(2);
}

void VocodecAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VocodecAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void VocodecAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    processingInactiveCount = 0;
    vocodec::VocodecPresetType currentPreset = vcd.currentPreset;
    
    if (vcd.loadingPreset) return;
    vcd.frameFunctions[currentPreset](&vcd);
    
    MidiMessage m;
    for (MidiMessageMetadata metadata : midiMessages) {
        m = metadata.getMessage();
        handleIncomingMidiMessage(nullptr, m);
    }
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel;
    
    if (buffer.getNumChannels()== 1)
    {
        rightChannel = buffer.getWritePointer(0);
    }
    else
    {
        rightChannel = buffer.getWritePointer(1);
    }
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        audioInput[0] = tEnvelopeFollower_tick(&inputFollower[0], leftChannel[i]);
        audioInput[1] = tEnvelopeFollower_tick(&inputFollower[1], rightChannel[i]);
        
        float audio [2];
        audio[0] = leftChannel[i];
        audio[1] = rightChannel[i];
        
        if (vcd.loadingPreset) return;
        vcd.tickFunctions[currentPreset](&vcd, audio);
        
        float mix = dryWetMix->get();
        audio[0] = LEAF_interpolation_linear(leftChannel[i], audio[0], mix);
        
        buffer.setSample(0, i, audio[0]);
        
        if(buffer.getNumChannels() > 1)
        {
			audio[1] = LEAF_interpolation_linear(rightChannel[i], audio[1], mix);
            buffer.setSample(1, i, audio[1]);
        }
        
        audioOutput[0] = tEnvelopeFollower_tick(&outputFollower[0], audio[0]);
        audioOutput[1] = tEnvelopeFollower_tick(&outputFollower[1], audio[1]);
    }
    
    vocodec::OLED_process(&vcd);
}

//==============================================================================
bool VocodecAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VocodecAudioProcessor::createEditor()
{
    return new VocodecAudioProcessorEditor (*this);
}

//==============================================================================
void VocodecAudioProcessor::getStateInformation (MemoryBlock& destData)
{

}

void VocodecAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocodecAudioProcessor();
}

void VocodecAudioProcessor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
    const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
    if (message.isNoteOn()) {
        vocodec::noteOn(&vcd, message.getNoteNumber(), message.getVelocity());
    }
    else {
        vocodec::noteOff(&vcd, message.getNoteNumber(), message.getVelocity());
    }
    keyboardState.processNextMidiEvent(message);
}
void VocodecAudioProcessor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isAddingFromMidiInput)
    {
        auto m = MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity);
        m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
    }
}
void VocodecAudioProcessor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isAddingFromMidiInput)
    {
        auto m = MidiMessage::noteOff(midiChannel, midiNoteNumber);
        m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
    }
}

void VocodecAudioProcessor::hiResTimerCallback()
{
    vocodec::buttonCheck(&vcd);
    vocodec::adcCheck(&vcd);
    
    vocodec::VocodecPresetType currentPreset = vcd.currentPreset;
    
    if (vcd.loadingPreset)
    {
        for (int i = 0; i < vocodec::ButtonNil; ++i)
        {
            for (int j = 0; j < vocodec::ActionNil; ++j)
            {
                vcd.buttonActionsSFX[i][j] = 0;
                vcd.buttonActionsUI[i][j] = 0;
            }
        }
        
        if (vcd.previousPreset != vocodec::PresetNil)
            vcd.freeFunctions[vcd.previousPreset](&vcd);
        
        if (currentPreset != vocodec::PresetNil)
            vcd.allocFunctions[currentPreset](&vcd);
        
        vcd.previousPreset = currentPreset;
        vcd.loadingPreset = 0;
    }
    
    for (int p = 0; p < int(vocodec::PresetNil); ++p)
    {
        for (int v = 0; v < vcd.numPages[p] * KNOB_PAGE_SIZE; ++v)
        {
            String name = String(vcd.knobParamNames[p][v]);
            if (!name.isEmpty())
            {
                int paramId = (p * NUM_PRESET_KNOB_VALUES) + v;
                vcd.presetKnobValues[p][v] = pluginParams[paramId]->get();
            }
        }
    }
    
    if (processingInactiveCount > processingInactiveThreshold)
    {
        vcd.frameFunctions[currentPreset](&vcd);
        float audio[2] = { 0.0f, 0.0f };
        vcd.tickFunctions[currentPreset](&vcd, audio);
        vocodec::OLED_process(&vcd);
    }
    else processingInactiveCount++;
}
