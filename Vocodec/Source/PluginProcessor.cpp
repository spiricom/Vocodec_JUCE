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
pluginParamPrefixes(cPluginParamPrefixes),
pluginParamNames(cPluginParamNames),
choiceParamNames(cChoiceParamNames)
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
                         
    choiceParams.set("vocoder_numVoices",
                     new AudioParameterChoice("vocoder_numVoices", "vocoder_numVoices",
                                              StringArray("Poly", "Mono"), 0));
    choiceParams.set("vocoder_internalExternal",
                     new AudioParameterChoice("vocoder_internalExternal", "vocoder_internalExternal",
                                              StringArray("Internal", "External"), 0));
    choiceParams.set("vocoder_freeze",
                     new AudioParameterChoice("vocoder_freeze", "vocoder_freeze",
                                              StringArray("Normal", "Frozen"), 0));
    
    choiceParams.set("vocoderCh_numVoices",
                     new AudioParameterChoice("vocoderCh_numVoices", "vocoderCh_numVoices",
                                              StringArray("Poly", "Mono"), 0));
    choiceParams.set("vocoderCh_internalExternal",
                     new AudioParameterChoice("vocoderCh_internalExternal", "vocoderCh_internalExternal",
                                              StringArray("Internal", "External"), 0));
    choiceParams.set("vocoderCh_freeze",
                     new AudioParameterChoice("vocoderCh_freeze", "vocoderCh_freeze",
                                              StringArray("Normal", "Frozen"), 0));
    
    //    "pitchShift_"/
    
    choiceParams.set("autotuneMono_useChromatic",
                     new AudioParameterChoice("autotuneMono_useChromatic", "autotuneMono_useChromatic",
                                              StringArray("Off", "On"), 0));
    choiceParams.set("autotuneMono_lock",
                     new AudioParameterChoice("autotuneMono_lock", "autotuneMono_lock",
                                              StringArray("Unlocked", "Locked"), 0));
    
    //    "autotunePoly_",
    
    choiceParams.set("samplerButtonPress_playMode",
                     new AudioParameterChoice("samplerButtonPress_playMode", "samplerButtonPress_playMode",
                                              StringArray("Loop", "Back'n'Forth"), 0));
    choiceParams.set("samplerButtonPress_paused",
                     new AudioParameterChoice("samplerButtonPress_paused",
                                              "samplerButtonPress_paused",
                                              StringArray("Playing", "Paused"), 0));
    
    choiceParams.set("samplerKeyboard_controlAllKeys",
                     new AudioParameterChoice("samplerKeyboard_controlAllKeys",
                                              "samplerKeyboard_controlAllKeys",
                                              StringArray("Single Key", "All Keys"), 0));
    
    choiceParams.set("samplerAutoGrab_playMode",
                     new AudioParameterChoice("samplerAutoGrab_playMode", "samplerAutoGrab_playMode",
                                              StringArray("Loop", "Back'n'Forth"), 0));
    choiceParams.set("samplerAutoGrab_triggerChannel",
                     new AudioParameterChoice("samplerAutoGrab_triggerChannel", "samplerAutoGrab_triggerChannel",
                                              StringArray("1", "2"), 0));
    choiceParams.set("samplerAutoGrab_quantizeRate",
                     new AudioParameterChoice("samplerAutoGrab_quantizeRate", "samplerAutoGrab_quantizeRate",
                                              StringArray("Continuous", "Quantized"), 0));
    
    choiceParams.set("distortion_mode",
                     new AudioParameterChoice("distortion_mode", "distortion_mode",
                                              StringArray("Shaper", "TanH"), 0));
    
    choiceParams.set("waveFolder_mode",
                     new AudioParameterChoice("waveFolder_mode", "waveFolder_mode",
                                              StringArray("Series", "Oversampled"), 0));
    
    choiceParams.set("bitCrusher_stereo",
                     new AudioParameterChoice("bitCrusher_stereo", "bitCrusher_stereo",
                                              StringArray("Mono", "Stereo"), 0));
    
    choiceParams.set("delay_shaper",
                     new AudioParameterChoice("delay_shaper", "delay_shaper",
                                              StringArray("Off", "On"), 0));
    choiceParams.set("delay_uncapFeedback",
                     new AudioParameterChoice("delay_uncapFeedback", "delay_uncapFeedback",
                                              StringArray("Capped", "Uncapped"), 0));
    choiceParams.set("delay_freeze",
                     new AudioParameterChoice("delay_freeze", "delay_freeze",
                                              StringArray("Normal", "Frozen"), 0));
    
    choiceParams.set("reverb_uncapFeedback",
                     new AudioParameterChoice("reverb_uncapFeedback", "reverb_uncapFeedback",
                                              StringArray("Capped", "Uncapped"), 0));
    choiceParams.set("reverb_freeze",
                     new AudioParameterChoice("reverb_freeze", "reverb_freeze",
                                              StringArray("Normal", "Frozen"), 0));
    
    choiceParams.set("reverb2_freeze",
                     new AudioParameterChoice("reverb2_freeze", "reverb2_freeze",
                                              StringArray("Normal", "Frozen"), 0));
    
    choiceParams.set("livingString_ignoreFreqKnobs",
                     new AudioParameterChoice("livingString_ignoreFreqKnobs", "livingString_ignoreFreqKnobs",
                                              StringArray("Use Knobs", "Use MIDI"), 0));
    choiceParams.set("livingString_independentStrings",
                     new AudioParameterChoice("livingString_independentStrings",
                                              "livingString_independentStrings",
                                              StringArray("Proportional", "Independent"), 0));
    choiceParams.set("livingString_feedback",
                     new AudioParameterChoice("livingString_feedback", "livingString_feedback",
                                              StringArray("Off", "On"), 0));
    
    choiceParams.set("livingStringSynth_numVoices",
                     new AudioParameterChoice("livingStringSynth_numVoices", "livingStringSynth_numVoices",
                                              StringArray("Poly", "Mono"), 0));
    choiceParams.set("livingStringSynth_audioIn",
                     new AudioParameterChoice("livingStringSynth_audioIn", "livingStringSynth_audioIn",
                                              StringArray("Off", "On"), 0));
    choiceParams.set("livingStringSynth_feedback",
                     new AudioParameterChoice("livingStringSynth_feedback", "livingStringSynth_feedback",
                                              StringArray("Off", "On"), 0));
    
    choiceParams.set("classicSynth_numVoices",
                     new AudioParameterChoice("classicSynth_numVoices", "classicSynth_numVoices",
                                              StringArray("Poly", "Mono"), 0));
    
    choiceParams.set("rhodes_numVoices",
                     new AudioParameterChoice("rhodes_numVoices", "rhodes_numVoices",
                                              StringArray("Poly", "Mono"), 0));
    choiceParams.set("rhodes_sound",
                     new AudioParameterChoice("rhodes_sound", "rhodes_sound",
                                              StringArray(String(vcd.soundNames[0]),
                                                          String(vcd.soundNames[1]),
                                                          String(vcd.soundNames[2]),
                                                          String(vcd.soundNames[3]),
                                                          String(vcd.soundNames[4])), 0));
    choiceParams.set("rhodes_tremoloStereo",
                     new AudioParameterChoice("rhodes_tremoloStereo", "rhodes_tremoloStereo",
                                              StringArray("Off", "On"), 0));
    
    for (auto paramName : choiceParamNames)
        addParameter(choiceParams[paramName]);
}

VocodecAudioProcessor::~VocodecAudioProcessor()
{
    stopTimer();
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
    processingInactiveThreshold = 10 * (samplesPerBlock / sampleRate) * 1000;
    
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
        vocodec::OLED_writePreset(&vcd);
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
    
    if (processingFalseBlock) return;
    processingBlock = true;
    
    updateAllValues();
    
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
    
    vocodec::buttonCheck(&vcd);
    vocodec::adcCheck(&vcd);
    
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
    
    updateChoiceParams();
    
    vocodec::OLED_process(&vcd);
    processingBlock = false;
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
    std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("Vocodec"));
    xml->setAttribute("preset", vcd.currentPreset);
    xml->setAttribute(dryWetMix->getName(50), *dryWetMix);
    for (auto param : pluginParams)
        xml->setAttribute(param->getName(50).removeCharacters(StringRef(" /<>")), *param);
    for (auto param : choiceParams)
        xml->setAttribute(param->getName(50).removeCharacters(StringRef(" /<>")), param->getIndex());
    copyXmlToBinary(*xml, destData);
}

void VocodecAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        vcd.currentPreset = (vocodec::VocodecPresetType) xmlState->getIntAttribute("preset", 0);
        vcd.loadingPreset = 1;

        String name = dryWetMix->getName(50);
        dryWetMix->setValueNotifyingHost((float)xmlState->getDoubleAttribute(name, 1.0f));

        for (int p = 0; p < int(vocodec::PresetNil); ++p)
        {
            for (int v = 0; v < vcd.numPages[p] * KNOB_PAGE_SIZE; ++v)
            {
                int paramId = (p * NUM_PRESET_KNOB_VALUES) + v;
                if (pluginParams.contains(paramId))
                {
                    name = pluginParams[paramId]->getName(50);
                    name = name.removeCharacters(StringRef(" /<>"));
                    pluginParams[paramId]->setValueNotifyingHost((float)xmlState->getDoubleAttribute(name, vcd.defaultPresetKnobValues[p][v]));
                }
            }
        }
        
        for (auto param : choiceParams)
        {
            name = param->getName(50);
            name = name.removeCharacters(StringRef(" /<>"));
            *param = xmlState->getIntAttribute(name, 0);
        }
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
    if (processingBlock) return;
    if (processingInactiveCount > processingInactiveThreshold)
    {
        processingFalseBlock = true;
        
        updateAllValues();
        
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
        
        vocodec::buttonCheck(&vcd);
        vocodec::adcCheck(&vcd);
        vcd.frameFunctions[currentPreset](&vcd);
        float audio[2] = { 0.0f, 0.0f };
        vcd.tickFunctions[currentPreset](&vcd, audio);
        
        updateChoiceParams();
        
        vocodec::OLED_process(&vcd);
    }
    else processingInactiveCount++;
    processingFalseBlock = false;
}

void VocodecAudioProcessor::updateChoiceParams()
{
    *choiceParams["vocoder_numVoices"] = vcd.vocoderParams.numVoices > 1 ? 0 : 1;
    *choiceParams["vocoder_internalExternal"] = vcd.vocoderParams.internalExternal;
    *choiceParams["vocoder_freeze"] = vcd.vocoderParams.freeze;
    
    *choiceParams["vocoderCh_numVoices"] = vcd.vocoderChParams.numVoices > 1 ? 0 : 1;
    *choiceParams["vocoderCh_internalExternal"] = vcd.vocoderChParams.internalExternal;
    *choiceParams["vocoderCh_freeze"] = vcd.vocoderChParams.freeze;

    //    "pitchShift_"/

    *choiceParams["autotuneMono_useChromatic"] = vcd.neartuneParams.useChromatic;
    *choiceParams["autotuneMono_lock"] = vcd.neartuneParams.lock;

    //    "autotunePoly_",

    *choiceParams["samplerButtonPress_playMode"] = (vcd.samplerBPParams.playMode == PlayLoop) ? 0 : 1;
    *choiceParams["samplerButtonPress_paused"] = vcd.samplerBPParams.paused;

    *choiceParams["samplerKeyboard_controlAllKeys"] = vcd.samplerKParams.controlAllKeys;

    *choiceParams["samplerAutoGrab_playMode"] = (vcd.samplerAutoParams.playMode == PlayLoop) ? 0 : 1;
    *choiceParams["samplerAutoGrab_triggerChannel"] = vcd.samplerAutoParams.triggerChannel;
    *choiceParams["samplerAutoGrab_quantizeRate"] = vcd.samplerAutoParams.quantizeRate;

    *choiceParams["distortion_mode"] = vcd.distortionParams.mode;

    *choiceParams["waveFolder_mode"] = vcd.waveFolderParams.mode;

    *choiceParams["bitCrusher_stereo"] = vcd.bitcrusherParams.stereo;

    *choiceParams["delay_shaper"] = vcd.delayParams.shaper;
    *choiceParams["delay_uncapFeedback"] = vcd.delayParams.uncapFeedback;
    *choiceParams["delay_freeze"] = vcd.delayParams.freeze;

    *choiceParams["reverb_uncapFeedback"] = vcd.reverbParams.uncapFeedback;
    *choiceParams["reverb_freeze"] = vcd.reverbParams.freeze;

    *choiceParams["reverb2_freeze"] = vcd.reverb2Params.freeze;

    *choiceParams["livingString_ignoreFreqKnobs"] = vcd.livingStringParams.ignoreFreqKnobs;
    *choiceParams["livingString_independentStrings"] = vcd.livingStringParams.independentStrings;
    *choiceParams["livingString_feedback"] = vcd.livingStringParams.feedback;

    *choiceParams["livingStringSynth_numVoices"] = vcd.livingStringSynthParams.numVoices > 1 ? 0 : 1;
    *choiceParams["livingStringSynth_audioIn"] = vcd.livingStringSynthParams.audioIn;
    *choiceParams["livingString_feedback"] = vcd.livingStringSynthParams.feedback;

    *choiceParams["classicSynth_numVoices"] = vcd.classicSynthParams.numVoices > 1 ? 0 : 1;

    *choiceParams["rhodes_numVoices"] = vcd.rhodesParams.numVoices > 1 ? 0 : 1;
    *choiceParams["rhodes_sound"] = vcd.rhodesParams.sound;
    *choiceParams["rhodes_tremoloStereo"] = vcd.rhodesParams.tremoloStereo;
}

void VocodecAudioProcessor::updateChoiceValues()
{
    vcd.vocoderParams.numVoices = choiceParams["vocoder_numVoices"]->getIndex() > 0 ? 1 : NUM_VOC_VOICES;
    vcd.vocoderParams.internalExternal = choiceParams["vocoder_internalExternal"]->getIndex();
    vcd.vocoderParams.freeze = choiceParams["vocoder_freeze"]->getIndex();
    
    vcd.vocoderChParams.numVoices = choiceParams["vocoderCh_numVoices"]->getIndex() > 0 ? 1 : NUM_VOC_VOICES;
    vcd.vocoderChParams.internalExternal = choiceParams["vocoderCh_internalExternal"]->getIndex();
    vcd.vocoderChParams.freeze = choiceParams["vocoderCh_freeze"]->getIndex();
    
    //    "pitchShift_"/
    
    vcd.neartuneParams.useChromatic = choiceParams["autotuneMono_useChromatic"]->getIndex();
    vcd.neartuneParams.lock = choiceParams["autotuneMono_lock"]->getIndex();
    
    //    "autotunePoly_",
    
    vcd.samplerBPParams.playMode = choiceParams["samplerButtonPress_playMode"]->getIndex() > 0 ? PlayBackAndForth : PlayLoop;
    vcd.samplerBPParams.paused = choiceParams["samplerButtonPress_paused"]->getIndex();
    
    vcd.samplerKParams.controlAllKeys = choiceParams["samplerKeyboard_controlAllKeys"]->getIndex();
    
    vcd.samplerAutoParams.playMode = choiceParams["samplerAutoGrab_playMode"]->getIndex() > 0 ? PlayBackAndForth : PlayLoop;
    vcd.samplerAutoParams.triggerChannel = choiceParams["samplerAutoGrab_triggerChannel"]->getIndex();
    vcd.samplerAutoParams.quantizeRate = choiceParams["samplerAutoGrab_quantizeRate"]->getIndex();
    
    vcd.distortionParams.mode = choiceParams["distortion_mode"]->getIndex();
    
    vcd.waveFolderParams.mode = choiceParams["waveFolder_mode"]->getIndex();
    
    vcd.bitcrusherParams.stereo = choiceParams["bitCrusher_stereo"]->getIndex();
    
    vcd.delayParams.shaper = choiceParams["delay_shaper"]->getIndex();
    vcd.delayParams.uncapFeedback = choiceParams["delay_uncapFeedback"]->getIndex();
    vcd.delayParams.freeze = choiceParams["delay_freeze"]->getIndex();
    
    vcd.reverbParams.uncapFeedback = choiceParams["reverb_uncapFeedback"]->getIndex();
    vcd.reverbParams.freeze = choiceParams["reverb_freeze"]->getIndex();
    
    vcd.reverb2Params.freeze = choiceParams["reverb2_freeze"]->getIndex();
    
    vcd.livingStringParams.ignoreFreqKnobs = choiceParams["livingString_ignoreFreqKnobs"]->getIndex();
    vcd.livingStringParams.independentStrings = choiceParams["livingString_independentStrings"]->getIndex();
    vcd.livingStringParams.feedback = choiceParams["livingString_feedback"]->getIndex();
    
    vcd.livingStringSynthParams.numVoices = choiceParams["livingStringSynth_numVoices"]->getIndex() > 0 ? 1 : NUM_STRINGS;
    vcd.livingStringSynthParams.audioIn = choiceParams["livingStringSynth_audioIn"]->getIndex();
    vcd.livingStringSynthParams.feedback = choiceParams["livingString_feedback"]->getIndex();
    
    vcd.classicSynthParams.numVoices = choiceParams["classicSynth_numVoices"]->getIndex() > 0 ? 1 : NUM_VOC_VOICES;
    
    vcd.rhodesParams.numVoices = choiceParams["rhodes_numVoices"]->getIndex() > 0 ? 1 : NUM_VOC_VOICES;
    vcd.rhodesParams.sound = choiceParams["rhodes_sound"]->getIndex();
    vcd.rhodesParams.tremoloStereo = choiceParams["rhodes_tremoloStereo"]->getIndex();
}

void VocodecAudioProcessor::updateAllValues()
{
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
    updateChoiceValues();
}
