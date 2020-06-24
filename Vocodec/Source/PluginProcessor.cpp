/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
                       )
#endif
{
    
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
   
    
    LEAF_init(sampleRate, samplesPerBlock, vocodec::medium_memory, 519000, []() {return (float)rand() / RAND_MAX; });
    tMempool_init(&vocodec::smallPool, vocodec::small_memory, 80328);
    tMempool_init(&vocodec::largePool, vocodec::large_memory, 33554432);
    vocodec::initGlobalSFXObjects();
    vocodec::SFXVocoderAlloc();
    
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
    vocodec::SFXVocoderFrame();
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
       float* leftChannel = buffer.getWritePointer(0);
       float* rightChannel;
    
    if (buffer.getNumChannels()== 1){
  
        rightChannel = buffer.getWritePointer(0);
    }else{
        rightChannel = buffer.getWritePointer(1);
    }
    
    int time;
        MidiMessage m;
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if(m.isNoteOn()){
                    vocodec::noteOn(m.getNoteNumber(), m.getVelocity());
            }
            
            if(m.isNoteOff()){
                vocodec::noteOff(m.getNoteNumber(), m.getVelocity());
            }
            
        }
    
for (int i = 0; i < buffer.getNumSamples(); i++){
    
    float audio [2];
    audio[0] = leftChannel[i];
    audio[1] = rightChannel[i];
    vocodec::SFXVocoderTick(audio);
    buffer.setSample(0, i, audio[0]);
    if(buffer.getNumChannels() > 1){
       buffer.setSample(1, i, audio[1]);
    }
 }

    
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VocodecAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocodecAudioProcessor();
}
