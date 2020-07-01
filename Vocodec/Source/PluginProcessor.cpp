/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "sfx.h"

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
	if (loading)
    switch (presetNumber) {
        case 1:
            vocodec::SFXVocoderFrame();
            break;
        case 2:
            vocodec::SFXVocoderChFrame();
            break;
        case 3:
            vocodec::SFXPitchShiftFrame();
            break;
        case 4:
            vocodec::SFXNeartuneFrame();
            break;
        case 5:
            vocodec::SFXAutotuneFrame();
            break;
        case 6:
            vocodec::SFXSamplerBPFrame();
            break;
        case 7:
            vocodec::SFXSamplerKFrame();
            break;
        case 8:
            vocodec::SFXSamplerAutoFrame();
            break;
        case 9:
            vocodec::SFXDistortionFrame();
            break;
        case 10:
            vocodec::SFXWaveFolderFrame();
            break;
        case 11:
            vocodec::SFXBitcrusherFrame();
            break;
        case 12:
            vocodec::SFXDelayFrame();
            break;
        case 13:
            vocodec::SFXReverbFrame();
            break;
        case 14:
            vocodec::SFXReverb2Frame();
            break;
        case 15:
            vocodec::SFXLivingStringFrame();
            break;
        case 16:
            vocodec::SFXLivingStringSynthFrame();
            break;
        case 17:
            vocodec::SFXClassicSynthFrame();
            break;
        case 18:
            vocodec::SFXRhodesFrame();
            break;
        default:
            break;
    }


	int time;
	MidiMessage m;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
		// kludgy, but just trying to see if this works...
		handleIncomingMidiMessage(nullptr, m);
	}
    
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
   
    
for (int i = 0; i < buffer.getNumSamples(); i++){
    
    float audio [2];
    audio[0] = leftChannel[i];
    audio[1] = rightChannel[i];
	if (loading)
    switch (presetNumber) {
        case 1:
            vocodec::SFXVocoderTick(audio);
            break;
        case 2:
            vocodec::SFXVocoderChTick(audio);
            break;
        case 3:
            vocodec::SFXPitchShiftTick(audio);
            break;
        case 4:
            vocodec::SFXNeartuneTick(audio);
            break;
        case 5:
            vocodec::SFXAutotuneTick(audio);
            break;
        case 6:
            vocodec::SFXSamplerBPTick(audio);
            break;
        case 7:
            vocodec::SFXSamplerKTick(audio);
            break;
        case 8:
            vocodec::SFXSamplerAutoTick(audio);
            break;
        case 9:
            vocodec::SFXDistortionTick(audio);
            break;
        case 10:
            vocodec::SFXWaveFolderTick(audio);
            break;
        case 11:
            vocodec::SFXBitcrusherTick(audio);
            break;
        case 12:
            vocodec::SFXDelayTick(audio);
            break;
        case 13:
            vocodec::SFXReverbTick(audio);
            break;
        case 14:
            vocodec::SFXReverb2Tick(audio);
            break;
        case 15:
            vocodec::SFXLivingStringTick(audio);
            break;
        case 16:
            vocodec::SFXLivingStringSynthTick(audio);
            break;
        case 17:
            vocodec::SFXClassicSynthTick(audio);
            break;
        case 18:
            vocodec::SFXRhodesTick(audio);
            break;
        default:
            break;
    }
    
 
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

void VocodecAudioProcessor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
	if (message.isNoteOn()) {
		vocodec::noteOn(message.getNoteNumber(), message.getVelocity());
	}
	else {
		vocodec::noteOff(message.getNoteNumber(), message.getVelocity());
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