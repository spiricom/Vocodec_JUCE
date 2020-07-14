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
    presetNumber = 0;
    prevPresetNumber = 0;
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
    if (presetNumber == 0)
    {
        presetNumber = 1;
        loading = true;
    }
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
    {
        for (int i = 0; i < vocodec::ButtonNil; ++i)
            for (int j = 0; j < vocodec::ActionNil; ++j)
            {
                vocodec::buttonActionsSFX[i][j] = false;
                vocodec::buttonActionsUI[i][j] = false;
            }
        
        switch (prevPresetNumber) {
            case 1:
                vocodec::SFXVocoderFree();
                break;
            case 2:
                vocodec::SFXVocoderChFree();
                break;
            case 3:
                vocodec::SFXPitchShiftFree();
                break;
            case 4:
                vocodec::SFXNeartuneFree();
                break;
            case 5:
                vocodec::SFXAutotuneFree();
                break;
            case 6:
                vocodec::SFXSamplerBPFree();
                break;
            case 7:
                vocodec::SFXSamplerKFree();
                break;
            case 8:
                vocodec::SFXSamplerAutoFree();
                break;
            case 9:
                vocodec::SFXDistortionFree();
                break;
            case 10:
                vocodec::SFXWaveFolderFree();
                break;
            case 11:
                vocodec::SFXBitcrusherFree();
                break;
            case 12:
                vocodec::SFXDelayFree();
                break;
            case 13:
                vocodec::SFXReverbFree();
                break;
            case 14:
                vocodec::SFXReverb2Free();
                break;
            case 15:
                vocodec::SFXLivingStringFree();
                break;
            case 16:
                vocodec::SFXLivingStringSynthFree();
                break;
            case 17:
                vocodec::SFXClassicSynthFree();
                break;
            case 18:
                vocodec::SFXRhodesFree();
                break;
            default:
                break;
        }
        
        switch (presetNumber) {
            case 1:
                vocodec::SFXVocoderAlloc();
                break;
            case 2:
                vocodec::SFXVocoderChAlloc();
                break;
            case 3:
                vocodec::SFXPitchShiftAlloc();
                break;
            case 4:
                vocodec::SFXNeartuneAlloc();
                break;
            case 5:
                vocodec::SFXAutotuneAlloc();
                break;
            case 6:
                vocodec::SFXSamplerBPAlloc();
                break;
            case 7:
                vocodec::SFXSamplerKAlloc();
                break;
            case 8:
                vocodec::SFXSamplerAutoAlloc();
                break;
            case 9:
                vocodec::SFXDistortionAlloc();
                break;
            case 10:
                vocodec::SFXWaveFolderAlloc();
                break;
            case 11:
                vocodec::SFXBitcrusherAlloc();
                break;
            case 12:
                vocodec::SFXDelayAlloc();
                break;
            case 13:
                vocodec::SFXReverbAlloc();
                break;
            case 14:
                vocodec::SFXReverb2Alloc();
                break;
            case 15:
                vocodec::SFXLivingStringAlloc();
                break;
            case 16:
                vocodec::SFXLivingStringSynthAlloc();
                break;
            case 17:
                vocodec::SFXClassicSynthAlloc();
                break;
            case 18:
                vocodec::SFXRhodesAlloc();
                break;
            default:
                break;
        }
        loading = false;
    }
    
    if (!loading)
    {
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
    }
    
    
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
        
        float audio [2];
        audio[0] = leftChannel[i];
        audio[1] = rightChannel[i];
        if (!loading)
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
        
		audio[0] = LEAF_interpolation_linear(leftChannel[i], audio[0], interpVal);
        buffer.setSample(0, i, audio[0]);
        if(buffer.getNumChannels() > 1){
			audio[1] = LEAF_interpolation_linear(rightChannel[i], audio[1], interpVal);
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
    std::unique_ptr<XmlElement> xml(new XmlElement("Vocodec"));
    
    xml->setAttribute("Knob1", vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 0)]);
    xml->setAttribute("Knob2", vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 1)]);
    xml->setAttribute("Knob3", vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 2)]);
    xml->setAttribute("Knob4", vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 3)]);
    xml->setAttribute("Knob5", vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 4)]);
    //missig dryWet knob
    xml->setAttribute("ButtonEdit", vocodec::buttonActionsSFX[0][vocodec::ActionPress]);
    xml->setAttribute("ButtonLeft", vocodec::buttonActionsSFX[1][vocodec::ActionPress]);
    xml->setAttribute("ButtonRight", vocodec::buttonActionsSFX[2][vocodec::ActionPress]);
    xml->setAttribute("ButtonDown", vocodec::buttonActionsSFX[3][vocodec::ActionPress]);
    xml->setAttribute("ButtonUp", vocodec::buttonActionsSFX[4][vocodec::ActionPress]);
    xml->setAttribute("ButtonA", vocodec::buttonActionsSFX[5][vocodec::ActionPress]);
    xml->setAttribute("ButtonB", vocodec::buttonActionsSFX[6][vocodec::ActionPress]);
    xml->setAttribute("ButtonC", vocodec::buttonActionsSFX[7][vocodec::ActionPress]);
    xml->setAttribute("ButtonD", vocodec::buttonActionsSFX[8][vocodec::ActionPress]);
    xml->setAttribute("ButtonE", vocodec::buttonActionsSFX[9][vocodec::ActionPress]);
    
    copyXmlToBinary(*xml, destData);
}

void VocodecAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    
    if(xml.get() != nullptr && xml->hasTagName("Vocodec"))
    {
        vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 0)] = xml->getDoubleAttribute("Knob1");
        vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 1)] = xml->getDoubleAttribute("Knob2");
        vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 2)] = xml->getDoubleAttribute("Knob3");
        vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 3)] = xml->getDoubleAttribute("Knob4");
        vocodec::presetKnobValues[vocodec::currentPreset][(vocodec::knobPage * 5 + 4)] = xml->getDoubleAttribute("Knob5");
        //missing dryWet knob
        
        vocodec::buttonActionsSFX[0][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonEdit");
        vocodec::buttonActionsSFX[1][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonLeft");
        vocodec::buttonActionsSFX[2][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonRight");
        vocodec::buttonActionsSFX[3][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonDown");
        vocodec::buttonActionsSFX[4][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonUp");
        vocodec::buttonActionsSFX[5][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonA");
        vocodec::buttonActionsSFX[6][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonB");
        vocodec::buttonActionsSFX[7][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonC");
        vocodec::buttonActionsSFX[8][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonD");
        vocodec::buttonActionsSFX[9][vocodec::ActionPress] = xml->getDoubleAttribute("ButtonE");
        
    }
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

