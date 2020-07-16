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
    xml->removeAllAttributes();
    switch (presetNumber) {
        case 1:
            xml->setAttribute("Volume", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Warp", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Quality", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("SawToPulse", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("NoiseThreshold", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("Breath", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("PulseWidth", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("PulseShape", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 2:
            xml->setAttribute("Volume", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Warp", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Quality", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("NoiseThreshold", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("SawToPulse", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("PulseWidth", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("PulseShape", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("Breath", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("BandSquish", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            xml->setAttribute("BandOff", vocodec::presetKnobValues[vocodec::currentPreset][10]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[vocodec::currentPreset][11]);
            xml->setAttribute("Stereo", vocodec::presetKnobValues[vocodec::currentPreset][12]);
            xml->setAttribute("BarkPull", vocodec::presetKnobValues[vocodec::currentPreset][13]);
            break;
        case 3:
            xml->setAttribute("Shift", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Fine", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("F AMT", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Formant", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("Range", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("Offset", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 4:
            xml->setAttribute("Pickiness", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Amount", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Leapallow", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("Hysteresis", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 5:
            xml->setAttribute("Pickiness", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 6:
            xml->setAttribute("Start", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Length", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("SpeedMult", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 7:
            xml->setAttribute("Start", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Length", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("SpeedMult", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("LoopOn", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("Velo Sens", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 8:
            xml->setAttribute("Threshold", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Window", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("LenRand", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("SpdRand", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 9:
            xml->setAttribute("PreGain", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("MidGain", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("MidFreq", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 10:
            xml->setAttribute("Gain", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Offset1", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Offset2", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 11:
            xml->setAttribute("Quality", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("SampRatio", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Rounding", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Operation", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("preGain", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 12:
            xml->setAttribute("DelayL", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("DelayR", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("HighPass", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("Feedback", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 13:
            xml->setAttribute("Size", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("FBLowPass", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("InHighPass", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("InLowPass", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("FBGain", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 14:
            xml->setAttribute("Size", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("HighPass", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("PeakFreq", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PeakGain", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            break;
        case 15:
            xml->setAttribute("Freq1", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("Detune", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Damping", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PickPos", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("PrepPos", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("PrepForce", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("LetRing", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            xml->setAttribute("Freq2", vocodec::presetKnobValues[vocodec::currentPreset][10]);
            xml->setAttribute("Freq3", vocodec::presetKnobValues[vocodec::currentPreset][11]);
            xml->setAttribute("Freq4", vocodec::presetKnobValues[vocodec::currentPreset][12]);
            xml->setAttribute("Freq5", vocodec::presetKnobValues[vocodec::currentPreset][13]);
            xml->setAttribute("Freq6", vocodec::presetKnobValues[vocodec::currentPreset][14]);
            break;
        case 16:
            xml->setAttribute("PluckVol", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("PluckTone", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Damping", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PickPos", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("PrepPos", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("PrepForce", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("LetRing", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("FBLevel", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("Release", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            break;
        case 17:
            xml->setAttribute("Volume", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("KeyFollow", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Detune", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("FilterQ", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("Attack", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("Sustain", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("Release", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("Leak", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            xml->setAttribute("FAttack", vocodec::presetKnobValues[vocodec::currentPreset][10]);
            xml->setAttribute("FDecay", vocodec::presetKnobValues[vocodec::currentPreset][11]);
            xml->setAttribute("FSustain", vocodec::presetKnobValues[vocodec::currentPreset][12]);
            xml->setAttribute("FRelease", vocodec::presetKnobValues[vocodec::currentPreset][13]);
            xml->setAttribute("FLeak", vocodec::presetKnobValues[vocodec::currentPreset][14]);
            xml->setAttribute("FAmount", vocodec::presetKnobValues[vocodec::currentPreset][15]);
            xml->setAttribute("Saw/Pulse", vocodec::presetKnobValues[vocodec::currentPreset][16]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][17]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][18]);
            xml->setAttribute("", vocodec::presetKnobValues[vocodec::currentPreset][19]);
            break;
        case 18:
            xml->setAttribute("Brightness", vocodec::presetKnobValues[vocodec::currentPreset][0]);
            xml->setAttribute("TremDepth", vocodec::presetKnobValues[vocodec::currentPreset][1]);
            xml->setAttribute("TremRate", vocodec::presetKnobValues[vocodec::currentPreset][2]);
            xml->setAttribute("Drive", vocodec::presetKnobValues[vocodec::currentPreset][3]);
            xml->setAttribute("PanSpread", vocodec::presetKnobValues[vocodec::currentPreset][4]);
            xml->setAttribute("Attack", vocodec::presetKnobValues[vocodec::currentPreset][5]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[vocodec::currentPreset][6]);
            xml->setAttribute("Sustain", vocodec::presetKnobValues[vocodec::currentPreset][7]);
            xml->setAttribute("Release", vocodec::presetKnobValues[vocodec::currentPreset][8]);
            xml->setAttribute("Leak", vocodec::presetKnobValues[vocodec::currentPreset][9]);
            xml->setAttribute("Index1", vocodec::presetKnobValues[vocodec::currentPreset][10]);
            xml->setAttribute("Index2", vocodec::presetKnobValues[vocodec::currentPreset][11]);
            xml->setAttribute("Index3", vocodec::presetKnobValues[vocodec::currentPreset][12]);
            xml->setAttribute("Index4", vocodec::presetKnobValues[vocodec::currentPreset][13]);
            xml->setAttribute("Index5", vocodec::presetKnobValues[vocodec::currentPreset][14]);
            xml->setAttribute("Ratio1", vocodec::presetKnobValues[vocodec::currentPreset][15]);
            xml->setAttribute("Ratio2", vocodec::presetKnobValues[vocodec::currentPreset][16]);
            xml->setAttribute("Ratio3", vocodec::presetKnobValues[vocodec::currentPreset][17]);
            xml->setAttribute("Ratio4", vocodec::presetKnobValues[vocodec::currentPreset][18]);
            xml->setAttribute("Ratio5", vocodec::presetKnobValues[vocodec::currentPreset][19]);
            xml->setAttribute("Ratio6", vocodec::presetKnobValues[vocodec::currentPreset][20]);
            xml->setAttribute("Feedback", vocodec::presetKnobValues[vocodec::currentPreset][21]);
            xml->setAttribute("TuneSnap", vocodec::presetKnobValues[vocodec::currentPreset][22]);
            xml->setAttribute("RandDecay", vocodec::presetKnobValues[vocodec::currentPreset][23]);
            xml->setAttribute("RandSust", vocodec::presetKnobValues[vocodec::currentPreset][24]);
            break;
        default:
            break;
    }
    
    xml->setAttribute("DryWet", interpVal);
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
        switch (presetNumber) {
               case 1:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Warp");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("SawToPulse");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("NoiseThreshold");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("Breath");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("PulseWidth");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("PulseShape");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 2:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Warp");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("NoiseThreshold");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("SawToPulse");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("PulseWidth");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("PulseShape");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("Breath");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("BandSquish");
                   vocodec::presetKnobValues[vocodec::currentPreset][10] = xml->getDoubleAttribute("BandOff");
                   vocodec::presetKnobValues[vocodec::currentPreset][11] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[vocodec::currentPreset][12] = xml->getDoubleAttribute("Stereo");
                   vocodec::presetKnobValues[vocodec::currentPreset][13] = xml->getDoubleAttribute("BarkPull");
                   break;
               case 3:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Shift");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Fine");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("F AMT");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Formant");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("Range");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("Offset");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 4:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Pickiness");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Amount");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Leapallow");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("Hysteresis");
                   break;
               case 5:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Pickiness");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("");
                   break;
               case 6:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Start");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Length");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("SpeedMult");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("CrossFade");
                   break;
               case 7:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Start");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Length");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("SpeedMult");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("LoopOn");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("CrossFade");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("Velo Sens");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 8:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Threshold");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Window");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("CrossFade");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("LenRand");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("SpdRand");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 9:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("PreGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("MidGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("MidFreq");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PostGain");
                   break;
               case 10:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Gain");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Offset1");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Offset2");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("");
                   break;
               case 11:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("SampRatio");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Rounding");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Operation");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("preGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 12:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("DelayL");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("DelayR");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("HighPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("Feedback");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   break;
               case 13:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Size");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("FBLowPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("InHighPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("InLowPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("FBGain");
                   break;
               case 14:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Size");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("HighPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("PeakFreq");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PeakGain");
                   break;
               case 15:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Freq1");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("Detune");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Damping");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PickPos");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("PrepPos");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("PrepForce");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("LetRing");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][10] = xml->getDoubleAttribute("Freq2");
                   vocodec::presetKnobValues[vocodec::currentPreset][11] = xml->getDoubleAttribute("Freq3");
                   vocodec::presetKnobValues[vocodec::currentPreset][12] = xml->getDoubleAttribute("Freq4");
                   vocodec::presetKnobValues[vocodec::currentPreset][13] = xml->getDoubleAttribute("Freq5");
                   vocodec::presetKnobValues[vocodec::currentPreset][14] = xml->getDoubleAttribute("Freq6");
                   break;
               case 16:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("PluckVol");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("PluckTone");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Damping");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PickPos");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("PrepPos");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("PrepForce");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("LetRing");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("FBLevel");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("Release");
                   break;
               case 17:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("KeyFollow");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Detune");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("FilterQ");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("Attack");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("Sustain");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("Release");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("Leak");
                   vocodec::presetKnobValues[vocodec::currentPreset][10] = xml->getDoubleAttribute("FAttack");
                   vocodec::presetKnobValues[vocodec::currentPreset][11] = xml->getDoubleAttribute("FDecay");
                   vocodec::presetKnobValues[vocodec::currentPreset][12] = xml->getDoubleAttribute("FSustain");
                   vocodec::presetKnobValues[vocodec::currentPreset][13] = xml->getDoubleAttribute("FRelease");
                   vocodec::presetKnobValues[vocodec::currentPreset][14] = xml->getDoubleAttribute("FLeak");
                   vocodec::presetKnobValues[vocodec::currentPreset][15] = xml->getDoubleAttribute("FAmount");
                   vocodec::presetKnobValues[vocodec::currentPreset][16] = xml->getDoubleAttribute("Saw/Pulse");
                   vocodec::presetKnobValues[vocodec::currentPreset][17] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][18] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[vocodec::currentPreset][19] = xml->getDoubleAttribute("");
                   break;
               case 18:
                   vocodec::presetKnobValues[vocodec::currentPreset][0] = xml->getDoubleAttribute("Brightness");
                   vocodec::presetKnobValues[vocodec::currentPreset][1] = xml->getDoubleAttribute("TremDepth");
                   vocodec::presetKnobValues[vocodec::currentPreset][2] = xml->getDoubleAttribute("TremRate");
                   vocodec::presetKnobValues[vocodec::currentPreset][3] = xml->getDoubleAttribute("Drive");
                   vocodec::presetKnobValues[vocodec::currentPreset][4] = xml->getDoubleAttribute("PanSpread");
                   vocodec::presetKnobValues[vocodec::currentPreset][5] = xml->getDoubleAttribute("Attack");
                   vocodec::presetKnobValues[vocodec::currentPreset][6] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[vocodec::currentPreset][7] = xml->getDoubleAttribute("Sustain");
                   vocodec::presetKnobValues[vocodec::currentPreset][8] = xml->getDoubleAttribute("Release");
                   vocodec::presetKnobValues[vocodec::currentPreset][9] = xml->getDoubleAttribute("Leak");
                   vocodec::presetKnobValues[vocodec::currentPreset][10] = xml->getDoubleAttribute("Index1");
                   vocodec::presetKnobValues[vocodec::currentPreset][11] = xml->getDoubleAttribute("Index2");
                   vocodec::presetKnobValues[vocodec::currentPreset][12] = xml->getDoubleAttribute("Index3");
                   vocodec::presetKnobValues[vocodec::currentPreset][13] = xml->getDoubleAttribute("Index4");
                   vocodec::presetKnobValues[vocodec::currentPreset][14] = xml->getDoubleAttribute("Index5");
                   vocodec::presetKnobValues[vocodec::currentPreset][15] = xml->getDoubleAttribute("Ratio1");
                   vocodec::presetKnobValues[vocodec::currentPreset][16] = xml->getDoubleAttribute("Ratio2");
                   vocodec::presetKnobValues[vocodec::currentPreset][17] = xml->getDoubleAttribute("Ratio3");
                   vocodec::presetKnobValues[vocodec::currentPreset][18] = xml->getDoubleAttribute("Ratio4");
                   vocodec::presetKnobValues[vocodec::currentPreset][19] = xml->getDoubleAttribute("Ratio5");
                   vocodec::presetKnobValues[vocodec::currentPreset][20] = xml->getDoubleAttribute("Ratio6");
                   vocodec::presetKnobValues[vocodec::currentPreset][21] = xml->getDoubleAttribute("Feedback");
                   vocodec::presetKnobValues[vocodec::currentPreset][22] = xml->getDoubleAttribute("TuneSnap");
                   vocodec::presetKnobValues[vocodec::currentPreset][23] = xml->getDoubleAttribute("RandDecay");
                   vocodec::presetKnobValues[vocodec::currentPreset][24] = xml->getDoubleAttribute("RandSust");
                   break;
               default:
                   break;
           }
     
        interpVal = xml->getDoubleAttribute("DryWet");
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

