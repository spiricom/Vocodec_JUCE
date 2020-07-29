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
    addParameter(vocoder_volume = new juce::AudioParameterFloat("vocoder_volume", "vocoder_volume", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_warp = new juce::AudioParameterFloat("vocoder_warp", "vocoder_warp", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_quality = new juce::AudioParameterFloat("vocoder_quality", "vocoder_quality", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_sawToPulse = new juce::AudioParameterFloat("vocoder_sawToPulse", "vocoder_sawToPulse", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_noiseThreshold = new juce::AudioParameterFloat("vocoder_noiseThreshold", "vocoder_noiseThreshold", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_breath = new juce::AudioParameterFloat("vocoder_breath", "vocoder_breath", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_tilt = new juce::AudioParameterFloat("vocoder_tilt", "vocoder_tilt", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_pulsewidth = new juce::AudioParameterFloat("vocoder_pulsewidth", "vocoder_pulsewidth", 0.0f, 1.0f, 0.5f));
    addParameter(vocoder_pulseShape = new juce::AudioParameterFloat("vocoder_pulseShape", "vocoder_pulseShape", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_volume = new juce::AudioParameterFloat("vocoderCh_volume", "vocoderCh_volume", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_warp = new juce::AudioParameterFloat("vocoderCh_warp", "vocoderCh_warp", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_quality = new juce::AudioParameterFloat("vocoderCh_quality", "vocoderCh_quality", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_bandWidth = new juce::AudioParameterFloat("vocoderCh_bandWidth", "vocoderCh_bandWidth", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_noiseThreshold = new juce::AudioParameterFloat("vocoderCh_noiseThreshold", "vocoderCh_noiseThreshold", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_sawToPulse = new juce::AudioParameterFloat("vocoderCh_sawToPulse", "vocoderCh_sawToPulse", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_pulseWidth = new juce::AudioParameterFloat("vocoderCh_pulseWidth", "vocoderCh_pulseWidth", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_pulseShape = new juce::AudioParameterFloat("vocoderCh_pulseShape", "vocoderCh_pulseShape", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_breath = new juce::AudioParameterFloat("vocoderCh_breath", "vocoderCh_breath", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_speed = new juce::AudioParameterFloat("vocoderCh_speed", "vocoderCh_speed", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_bandSquish = new juce::AudioParameterFloat("vocoderCh_bandSquish", "vocoderCh_bandSquish", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_bandOff = new juce::AudioParameterFloat("vocoderCh_bandOff", "vocoderCh_bandOff", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_tilt = new juce::AudioParameterFloat("vocoderCh_tilt", "vocoderCh_tilt", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_stereo = new juce::AudioParameterFloat("vocoderCh_stereo", "vocoderCh_stereo", 0.0f, 1.0f, 0.5f));
    addParameter(vocoderCh_barkPull = new juce::AudioParameterFloat("vocoderCh_barkPull", "vocoderCh_barkPull", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_shift = new juce::AudioParameterFloat("pitchShift_shift", "pitchShift_shift", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_fine = new juce::AudioParameterFloat("pitchShift_fine", "pitchShift_fine", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_f_Amt = new juce::AudioParameterFloat("pitchShift_f_Amt", "pitchShift_f_Amt", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_formant = new juce::AudioParameterFloat("pitchShift_formant", "pitchShift_formant", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_range = new juce::AudioParameterFloat("pitchShift_range", "pitchShift_range", 0.0f, 1.0f, 0.5f));
    addParameter(pitchShift_offset = new juce::AudioParameterFloat("pitchShift_offset", "pitchShift_offset", 0.0f, 1.0f, 0.5f));
    addParameter(autotuneMono_pickiness = new juce::AudioParameterFloat("autotuneMono_pickiness", "autotuneMono_pickiness", 0.0f, 1.0f, 0.5f));
    addParameter(autotuneMono_amount = new juce::AudioParameterFloat("autotuneMono_amount", "autotuneMono_amount", 0.0f, 1.0f, 0.5f));
    addParameter(autotuneMono_speed = new juce::AudioParameterFloat("autotuneMono_speed", "autotuneMono_speed", 0.0f, 1.0f, 0.5f));
    addParameter(autotuneMono_leapallow = new juce::AudioParameterFloat("autotuneMono_leapallow", "autotuneMono_leapallow", 0.0f, 1.0f, 0.5f));
    addParameter(autotuneMono_hysteresis = new juce::AudioParameterFloat("autotuneMono_hysteresis", "autotuneMono_hysteresis", 0.0f, 1.0f, 0.5f));
    addParameter(autotunePoly_pickiness = new juce::AudioParameterFloat("autotunePoly_pickiness", "autotunePoly_pickiness", 0.0f, 1.0f, 0.5f));
    addParameter(samplerButtonPress_start = new juce::AudioParameterFloat("samplerButtonPress_start", "samplerButtonPress_start", 0.0f, 1.0f, 0.5f));
    addParameter(samplerButtonPress_length = new juce::AudioParameterFloat("samplerButtonPress_length", "samplerButtonPress_length", 0.0f, 1.0f, 0.5f));
    addParameter(samplerButtonPress_speed = new juce::AudioParameterFloat("samplerButtonPress_speed", "samplerButtonPress_speed", 0.0f, 1.0f, 0.5f));
    addParameter(samplerButtonPress_speedMult = new juce::AudioParameterFloat("samplerButtonPress_speedMult", "samplerButtonPress_speedMult", 0.0f, 1.0f, 0.5f));
    addParameter(samplerButtonPress_crossfade = new juce::AudioParameterFloat("samplerButtonPress_crossfade", "samplerButtonPress_crossfade", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_start = new juce::AudioParameterFloat("samplerKeyboard_start", "samplerKeyboard_start", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_length = new juce::AudioParameterFloat("samplerKeyboard_length", "samplerKeyboard_length", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_speed = new juce::AudioParameterFloat("samplerKeyboard_speed", "samplerKeyboard_speed", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_speedMult = new juce::AudioParameterFloat("samplerKeyboard_speedMult", "samplerKeyboard_speedMult", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_loopOn = new juce::AudioParameterFloat("samplerKeyboard_loopOn", "samplerKeyboard_loopOn", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_crossFade = new juce::AudioParameterFloat("samplerKeyboard_crossFade", "samplerKeyboard_crossFade", 0.0f, 1.0f, 0.5f));
    addParameter(samplerKeyboard_velo_Sens = new juce::AudioParameterFloat("samplerKeyboard_velo_Sens", "samplerKeyboard_velo_Sens", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_threshold = new juce::AudioParameterFloat("samplerAutoGrab_threshold", "samplerAutoGrab_threshold", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_window = new juce::AudioParameterFloat("samplerAutoGrab_window", "samplerAutoGrab_window", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_speed = new juce::AudioParameterFloat("samplerAutoGrab_speed", "samplerAutoGrab_speed", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_crossFade = new juce::AudioParameterFloat("samplerAutoGrab_crossFade", "samplerAutoGrab_crossFade", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_lenRand = new juce::AudioParameterFloat("samplerAutoGrab_lenRand", "samplerAutoGrab_lenRand", 0.0f, 1.0f, 0.5f));
    addParameter(samplerAutoGrab_spdRand = new juce::AudioParameterFloat("samplerAutoGrab_spdRand", "samplerAutoGrab_spdRand", 0.0f, 1.0f, 0.5f));
    addParameter(distortion_preGain = new juce::AudioParameterFloat("distortion_preGain", "distortion_preGain", 0.0f, 1.0f, 0.5f));
    addParameter(distortion_tilt = new juce::AudioParameterFloat("distortion_tilt", "distortion_tilt", 0.0f, 1.0f, 0.5f));
    addParameter(distortion_midGain = new juce::AudioParameterFloat("distortion_midGain", "distortion_midGain", 0.0f, 1.0f, 0.5f));
    addParameter(distortion_midFreq = new juce::AudioParameterFloat("distortion_midFreq", "distortion_midFreq", 0.0f, 1.0f, 0.5f));
    addParameter(distortion_postGain = new juce::AudioParameterFloat("distortion_postGain", "distortion_postGain", 0.0f, 1.0f, 0.5f));
    addParameter(wavefolder_gain = new juce::AudioParameterFloat("wavefolder_gain", "wavefolder_gain", 0.0f, 1.0f, 0.5f));
    addParameter(wavefolder_offset1 = new juce::AudioParameterFloat("wavefolder_offset1", "wavefolder_offset1", 0.0f, 1.0f, 0.5f));
    addParameter(wavefolder_offset2 = new juce::AudioParameterFloat("wavefolder_offset2", "wavefolder_offset2", 0.0f, 1.0f, 0.5f));
    addParameter(wavefolder_postGain = new juce::AudioParameterFloat("wavefolder_postGain", "wavefolder_postGain", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_quality = new juce::AudioParameterFloat("bitCrusher_quality", "bitCrusher_quality", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_sampRatio = new juce::AudioParameterFloat("bitCrusher_sampRatio", "bitCrusher_sampRatio", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_rounding = new juce::AudioParameterFloat("bitCrusher_rounding", "bitCrusher_rounding", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_operation = new juce::AudioParameterFloat("bitCrusher_operation", "bitCrusher_operation", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_postGain = new juce::AudioParameterFloat("bitCrusher_postGain", "bitCrusher_postGain", 0.0f, 1.0f, 0.5f));
    addParameter(bitCrusher_preGain = new juce::AudioParameterFloat("bitCrusher_preGain", "bitCrusher_preGain", 0.0f, 1.0f, 0.5f));
    addParameter(delay_delayL = new juce::AudioParameterFloat("delay_delayL", "delay_delayL", 0.0f, 1.0f, 0.5f));
    addParameter(delay_delayR = new juce::AudioParameterFloat("delay_delayR", "delay_delayR", 0.0f, 1.0f, 0.5f));
    addParameter(delay_highPass = new juce::AudioParameterFloat("delay_highPass", "delay_highPass", 0.0f, 1.0f, 0.5f));
    addParameter(delay_lowPass = new juce::AudioParameterFloat("delay_lowPass", "delay_lowPass", 0.0f, 1.0f, 0.5f));
    addParameter(delay_feedback = new juce::AudioParameterFloat("delay_feedback", "delay_feedback", 0.0f, 1.0f, 0.5f));
    addParameter(delay_postGain = new juce::AudioParameterFloat("delay_postGain", "delay_postGain", 0.0f, 1.0f, 0.5f));
    addParameter(delay_postGain1 = new juce::AudioParameterFloat("delay_postGain1", "delay_postGain1", 0.0f, 1.0f, 0.5f));
    addParameter(delay_postGain2 = new juce::AudioParameterFloat("delay_postGain2", "delay_postGain2", 0.0f, 1.0f, 0.5f));
    addParameter(delay_postGain3 = new juce::AudioParameterFloat("delay_postGain3", "delay_postGain3", 0.0f, 1.0f, 0.5f));
    addParameter(reverb_size = new juce::AudioParameterFloat("reverb_size", "reverb_size", 0.0f, 1.0f, 0.5f));
    addParameter(reverb_fBLowPass = new juce::AudioParameterFloat("reverb_fBLowPass", "reverb_fBLowPass", 0.0f, 1.0f, 0.5f));
    addParameter(reverb_inHighPass = new juce::AudioParameterFloat("reverb_inHighPass", "reverb_inHighPass", 0.0f, 1.0f, 0.5f));
    addParameter(reverb_inLowPass = new juce::AudioParameterFloat("reverb_inLowPass", "reverb_inLowPass", 0.0f, 1.0f, 0.5f));
    addParameter(reverb_fBGain = new juce::AudioParameterFloat("reverb_fBGain", "reverb_fBGain", 0.0f, 1.0f, 0.5f));
    addParameter(reverb2_size = new juce::AudioParameterFloat("reverb2_size", "reverb2_size", 0.0f, 1.0f, 0.5f));
    addParameter(reverb2_lowPass = new juce::AudioParameterFloat("reverb2_lowPass", "reverb2_lowPass", 0.0f, 1.0f, 0.5f));
    addParameter(reverb2_highPass = new juce::AudioParameterFloat("reverb2_highPass", "reverb2_highPass", 0.0f, 1.0f, 0.5f));
    addParameter(reverb2_peakFreq = new juce::AudioParameterFloat("reverb2_peakFreq", "reverb2_peakFreq", 0.0f, 1.0f, 0.5f));
    addParameter(reverb2_peakGain = new juce::AudioParameterFloat("reverb2_peakGain", "reverb2_peakGain", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq1 = new juce::AudioParameterFloat("livingString_freq1", "livingString_freq1", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_detune = new juce::AudioParameterFloat("livingString_detune", "livingString_detune", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_decay = new juce::AudioParameterFloat("livingString_decay", "livingString_decay", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_damping = new juce::AudioParameterFloat("livingString_damping", "livingString_damping", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_pickPos = new juce::AudioParameterFloat("livingString_pickPos", "livingString_pickPos", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_prepPos = new juce::AudioParameterFloat("livingString_prepPos", "livingString_prepPos", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_prepForce = new juce::AudioParameterFloat("livingString_prepForce", "livingString_prepForce", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_letRing = new juce::AudioParameterFloat("livingString_letRing", "livingString_letRing", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq2 = new juce::AudioParameterFloat("livingString_freq2", "livingString_freq2", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq3 = new juce::AudioParameterFloat("livingString_freq3", "livingString_freq3", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq4 = new juce::AudioParameterFloat("livingString_freq4", "livingString_freq4", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq5 = new juce::AudioParameterFloat("livingString_freq5", "livingString_freq5", 0.0f, 1.0f, 0.5f));
    addParameter(livingString_freq6 = new juce::AudioParameterFloat("livingString_freq6", "livingString_freq6", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_pluckVol = new juce::AudioParameterFloat("livingStringSynth_pluckVol", "livingStringSynth_pluckVol", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_pluckTone = new juce::AudioParameterFloat("livingStringSynth_pluckTone", "livingStringSynth_pluckTone", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_decay = new juce::AudioParameterFloat("livingStringSynth_decay", "livingStringSynth_decay", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_damping = new juce::AudioParameterFloat("livingStringSynth_damping", "livingStringSynth_damping", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_pickPos = new juce::AudioParameterFloat("livingStringSynth_pickPos", "livingStringSynth_pickPos", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_prepPos = new juce::AudioParameterFloat("livingStringSynth_prepPos", "livingStringSynth_prepPos", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_prepForce = new juce::AudioParameterFloat("livingStringSynth_prepForce", "livingStringSynth_prepForce", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_letRing = new juce::AudioParameterFloat("livingStringSynth_letRing", "livingStringSynth_letRing", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_fBLevel = new juce::AudioParameterFloat("livingStringSynth_fBLevel", "livingStringSynth_fBLevel", 0.0f, 1.0f, 0.5f));
    addParameter(livingStringSynth_release = new juce::AudioParameterFloat("livingStringSynth_release", "livingStringSynth_release", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_volume = new juce::AudioParameterFloat("classicSynth_volume", "classicSynth_volume", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_lowPass = new juce::AudioParameterFloat("classicSynth_lowPass", "classicSynth_lowPass", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_keyFollow = new juce::AudioParameterFloat("classicSynth_keyFollow", "classicSynth_keyFollow", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_detune = new juce::AudioParameterFloat("classicSynth_detune", "classicSynth_detune", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_filterQ = new juce::AudioParameterFloat("classicSynth_filterQ", "classicSynth_filterQ", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_attack = new juce::AudioParameterFloat("classicSynth_attack", "classicSynth_attack", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_decay = new juce::AudioParameterFloat("classicSynth_decay", "classicSynth_decay", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_sustain = new juce::AudioParameterFloat("classicSynth_sustain", "classicSynth_sustain", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_release = new juce::AudioParameterFloat("classicSynth_release", "classicSynth_release", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_leak = new juce::AudioParameterFloat("classicSynth_leak", "classicSynth_leak", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fAttack = new juce::AudioParameterFloat("classicSynth_fAttack", "classicSynth_fAttack", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fDecay = new juce::AudioParameterFloat("classicSynth_fDecay", "classicSynth_fDecay", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fSustain = new juce::AudioParameterFloat("classicSynth_fSustain", "classicSynth_fSustain", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fRelease = new juce::AudioParameterFloat("classicSynth_fRelease", "classicSynth_fRelease", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fLeak = new juce::AudioParameterFloat("classicSynth_fLeak", "classicSynth_fLeak", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_fAmount = new juce::AudioParameterFloat("classicSynth_fAmount", "classicSynth_fAmount", 0.0f, 1.0f, 0.5f));
    addParameter(classicSynth_sawPulse = new juce::AudioParameterFloat("classicSynth_sawPulse", "classicSynth_sawPulse", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_brightness = new juce::AudioParameterFloat("rhodes_brightness", "rhodes_brightness", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_tremDepth = new juce::AudioParameterFloat("rhodes_tremDepth", "rhodes_tremDepth", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_tremRate = new juce::AudioParameterFloat("rhodes_tremRate", "rhodes_tremRate", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_drive = new juce::AudioParameterFloat("rhodes_drive", "rhodes_drive", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_panSpread = new juce::AudioParameterFloat("rhodes_panSpread", "rhodes_panSpread", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_attack = new juce::AudioParameterFloat("rhodes_attack", "rhodes_attack", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_decay = new juce::AudioParameterFloat("rhodes_decay", "rhodes_decay", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_sustain = new juce::AudioParameterFloat("rhodes_sustain", "rhodes_sustain", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_release = new juce::AudioParameterFloat("rhodes_release", "rhodes_release", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_leak = new juce::AudioParameterFloat("rhodes_leak", "rhodes_leak", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_index1 = new juce::AudioParameterFloat("rhodes_index1", "rhodes_index1", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_index2 = new juce::AudioParameterFloat("rhodes_index2", "rhodes_index2", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_index3 = new juce::AudioParameterFloat("rhodes_index3", "rhodes_index3", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_index4 = new juce::AudioParameterFloat("rhodes_index4", "rhodes_index4", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_index5 = new juce::AudioParameterFloat("rhodes_index5", "rhodes_index5", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio1 = new juce::AudioParameterFloat("rhodes_ratio1", "rhodes_ratio1", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio2 = new juce::AudioParameterFloat("rhodes_ratio2", "rhodes_ratio2", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio3 = new juce::AudioParameterFloat("rhodes_ratio3", "rhodes_ratio3", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio4 = new juce::AudioParameterFloat("rhodes_ratio4", "rhodes_ratio4", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio5 = new juce::AudioParameterFloat("rhodes_ratio5", "rhodes_ratio5", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_ratio6 = new juce::AudioParameterFloat("rhodes_ratio6", "rhodes_ratio6", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_feedback = new juce::AudioParameterFloat("rhodes_feedback", "rhodes_feedback", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_tuneSnap = new juce::AudioParameterFloat("rhodes_tuneSnap", "rhodes_tuneSnap", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_randDecay = new juce::AudioParameterFloat("rhodes_randDecay", "rhodes_randDecay", 0.0f, 1.0f, 0.5f));
    addParameter(rhodes_randSust = new juce::AudioParameterFloat("rhodes_randSust", "rhodes_randSust", 0.0f, 1.0f, 0.5f));
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
    
    vocodec::presetKnobValues[0][0] = vocoder_volume->get();
    vocodec::presetKnobValues[0][1] = vocoder_warp->get();
    vocodec::presetKnobValues[0][2] = vocoder_quality->get();
    vocodec::presetKnobValues[0][3] = vocoder_sawToPulse->get();
    vocodec::presetKnobValues[0][4] = vocoder_noiseThreshold->get();
    vocodec::presetKnobValues[0][5] = vocoder_breath->get();
    vocodec::presetKnobValues[0][6] = vocoder_tilt->get();
    vocodec::presetKnobValues[0][7] = vocoder_pulsewidth->get();
    vocodec::presetKnobValues[0][8] = vocoder_pulseShape->get();

    vocodec::presetKnobValues[1][0] = vocoderCh_volume->get();
    vocodec::presetKnobValues[1][1] = vocoderCh_warp->get();
    vocodec::presetKnobValues[1][2] = vocoderCh_quality->get();
    vocodec::presetKnobValues[1][3] = vocoderCh_bandWidth->get();
    vocodec::presetKnobValues[1][4] = vocoderCh_noiseThreshold->get();
    vocodec::presetKnobValues[1][5] = vocoderCh_sawToPulse->get();
    vocodec::presetKnobValues[1][6] = vocoderCh_pulseWidth->get();
    vocodec::presetKnobValues[1][7] = vocoderCh_pulseShape->get();
    vocodec::presetKnobValues[1][8] = vocoderCh_breath->get();
    vocodec::presetKnobValues[1][9] = vocoderCh_speed->get();
    vocodec::presetKnobValues[1][10] = vocoderCh_bandSquish->get();
    vocodec::presetKnobValues[1][11] = vocoderCh_bandOff->get();
    vocodec::presetKnobValues[1][12] = vocoderCh_tilt->get();
    vocodec::presetKnobValues[1][13] = vocoderCh_stereo->get();
    vocodec::presetKnobValues[1][14] = vocoderCh_barkPull->get();

    vocodec::presetKnobValues[2][0] = pitchShift_shift->get();
    vocodec::presetKnobValues[2][1] = pitchShift_fine->get();
    vocodec::presetKnobValues[2][2] = pitchShift_f_Amt->get();
    vocodec::presetKnobValues[2][3] = pitchShift_formant->get();
    vocodec::presetKnobValues[2][4] = pitchShift_range->get();
    vocodec::presetKnobValues[2][5] = pitchShift_offset->get();

    vocodec::presetKnobValues[3][0] = autotuneMono_pickiness->get();
    vocodec::presetKnobValues[3][1] = autotuneMono_amount->get();
    vocodec::presetKnobValues[3][2] = autotuneMono_speed->get();
    vocodec::presetKnobValues[3][3] = autotuneMono_leapallow->get();
    vocodec::presetKnobValues[3][4] = autotuneMono_hysteresis->get();

    vocodec::presetKnobValues[4][0] = autotunePoly_pickiness->get();

    vocodec::presetKnobValues[5][0] = samplerButtonPress_start->get();
    vocodec::presetKnobValues[5][1] = samplerButtonPress_length->get();
    vocodec::presetKnobValues[5][2] = samplerButtonPress_speed->get();
    vocodec::presetKnobValues[5][3] = samplerButtonPress_speedMult->get();
    vocodec::presetKnobValues[5][4] = samplerButtonPress_crossfade->get();

    vocodec::presetKnobValues[6][0] = samplerKeyboard_start->get();
    vocodec::presetKnobValues[6][1] = samplerKeyboard_length->get();
    vocodec::presetKnobValues[6][2] = samplerKeyboard_speed->get();
    vocodec::presetKnobValues[6][3] = samplerKeyboard_speedMult->get();
    vocodec::presetKnobValues[6][4] = samplerKeyboard_loopOn->get();
    vocodec::presetKnobValues[6][5] = samplerKeyboard_crossFade->get();
    vocodec::presetKnobValues[6][6] = samplerKeyboard_velo_Sens->get();

    vocodec::presetKnobValues[7][0] = samplerAutoGrab_threshold->get();
    vocodec::presetKnobValues[7][1] = samplerAutoGrab_window->get();
    vocodec::presetKnobValues[7][2] = samplerAutoGrab_speed->get();
    vocodec::presetKnobValues[7][3] = samplerAutoGrab_crossFade->get();
    vocodec::presetKnobValues[7][5] = samplerAutoGrab_lenRand->get();
    vocodec::presetKnobValues[7][6] = samplerAutoGrab_spdRand->get();

    vocodec::presetKnobValues[8][0] = distortion_preGain->get();
    vocodec::presetKnobValues[8][1] = distortion_tilt->get();
    vocodec::presetKnobValues[8][2] = distortion_midGain->get();
    vocodec::presetKnobValues[8][3] = distortion_midFreq->get();
    vocodec::presetKnobValues[8][4] = distortion_postGain->get();

    vocodec::presetKnobValues[9][0] = wavefolder_gain->get();
    vocodec::presetKnobValues[9][1] = wavefolder_offset1->get();
    vocodec::presetKnobValues[9][2] = wavefolder_offset2->get();
    vocodec::presetKnobValues[9][3] = wavefolder_postGain->get();

    vocodec::presetKnobValues[10][0] = bitCrusher_quality->get();
    vocodec::presetKnobValues[10][1] = bitCrusher_sampRatio->get();
    vocodec::presetKnobValues[10][2] = bitCrusher_rounding->get();
    vocodec::presetKnobValues[10][3] = bitCrusher_operation->get();
    vocodec::presetKnobValues[10][4] = bitCrusher_postGain->get();
    vocodec::presetKnobValues[10][5] = bitCrusher_preGain->get();

    vocodec::presetKnobValues[11][0] = delay_delayL->get();
    vocodec::presetKnobValues[11][1] = delay_delayR->get();
    vocodec::presetKnobValues[11][2] = delay_highPass->get();
    vocodec::presetKnobValues[11][3] = delay_lowPass->get();
    vocodec::presetKnobValues[11][4] = delay_feedback->get();
    vocodec::presetKnobValues[11][5] = delay_postGain->get();
    vocodec::presetKnobValues[11][6] = delay_postGain1->get();
    vocodec::presetKnobValues[11][7] = delay_postGain2->get();
    vocodec::presetKnobValues[11][8] = delay_postGain3->get();

    vocodec::presetKnobValues[12][0] = reverb_size->get();
    vocodec::presetKnobValues[12][1] = reverb_fBLowPass->get();
    vocodec::presetKnobValues[12][2] = reverb_inHighPass->get();
    vocodec::presetKnobValues[12][3] = reverb_inLowPass->get();
    vocodec::presetKnobValues[12][4] = reverb_fBGain->get();

    vocodec::presetKnobValues[13][0] = reverb2_size->get();
    vocodec::presetKnobValues[13][1] = reverb2_lowPass->get();
    vocodec::presetKnobValues[13][2] = reverb2_highPass->get();
    vocodec::presetKnobValues[13][3] = reverb2_peakFreq->get();
    vocodec::presetKnobValues[13][4] = reverb2_peakGain->get();

    vocodec::presetKnobValues[14][0] = livingString_freq1->get();
    vocodec::presetKnobValues[14][1] = livingString_detune->get();
    vocodec::presetKnobValues[14][2] = livingString_decay->get();
    vocodec::presetKnobValues[14][3] = livingString_damping->get();
    vocodec::presetKnobValues[14][4] = livingString_pickPos->get();
    vocodec::presetKnobValues[14][5] = livingString_prepPos->get();
    vocodec::presetKnobValues[14][6] = livingString_prepForce->get();
    vocodec::presetKnobValues[14][7] = livingString_letRing->get();
    vocodec::presetKnobValues[14][10] = livingString_freq2->get();
    vocodec::presetKnobValues[14][11] = livingString_freq3->get();
    vocodec::presetKnobValues[14][12] = livingString_freq4->get();
    vocodec::presetKnobValues[14][13] = livingString_freq5->get();
    vocodec::presetKnobValues[14][14] = livingString_freq6->get();

    vocodec::presetKnobValues[15][0] = livingStringSynth_pluckVol->get();
    vocodec::presetKnobValues[15][1] = livingStringSynth_pluckTone->get();
    vocodec::presetKnobValues[15][2] = livingStringSynth_decay->get();
    vocodec::presetKnobValues[15][3] = livingStringSynth_damping->get();
    vocodec::presetKnobValues[15][4] = livingStringSynth_pickPos->get();
    vocodec::presetKnobValues[15][5] = livingStringSynth_prepPos->get();
    vocodec::presetKnobValues[15][6] = livingStringSynth_prepForce->get();
    vocodec::presetKnobValues[15][7] = livingStringSynth_letRing->get();
    vocodec::presetKnobValues[15][8] = livingStringSynth_fBLevel->get();
    vocodec::presetKnobValues[15][9] = livingStringSynth_release->get();

    vocodec::presetKnobValues[16][0] = classicSynth_volume->get();
    vocodec::presetKnobValues[16][1] = classicSynth_lowPass->get();
    vocodec::presetKnobValues[16][2] = classicSynth_keyFollow->get();
    vocodec::presetKnobValues[16][3] = classicSynth_detune->get();
    vocodec::presetKnobValues[16][4] = classicSynth_filterQ->get();
    vocodec::presetKnobValues[16][5] = classicSynth_attack->get();
    vocodec::presetKnobValues[16][6] = classicSynth_decay->get();
    vocodec::presetKnobValues[16][7] = classicSynth_sustain->get();
    vocodec::presetKnobValues[16][8] = classicSynth_release->get();
    vocodec::presetKnobValues[16][9] = classicSynth_leak->get();
    vocodec::presetKnobValues[16][10] = classicSynth_fAttack->get();
    vocodec::presetKnobValues[16][11] = classicSynth_fDecay->get();
    vocodec::presetKnobValues[16][12] = classicSynth_fSustain->get();
    vocodec::presetKnobValues[16][13] = classicSynth_fRelease->get();
    vocodec::presetKnobValues[16][14] = classicSynth_fLeak->get();
    vocodec::presetKnobValues[16][15] = classicSynth_fAmount->get();
    vocodec::presetKnobValues[16][16] = classicSynth_sawPulse->get();

    vocodec::presetKnobValues[17][0] = rhodes_brightness->get();
    vocodec::presetKnobValues[17][1] = rhodes_tremDepth->get();
    vocodec::presetKnobValues[17][2] = rhodes_tremRate->get();
    vocodec::presetKnobValues[17][3] = rhodes_drive->get();
    vocodec::presetKnobValues[17][4] = rhodes_panSpread->get();
    vocodec::presetKnobValues[17][5] = rhodes_attack->get();
    vocodec::presetKnobValues[17][6] = rhodes_decay->get();
    vocodec::presetKnobValues[17][7] = rhodes_sustain->get();
    vocodec::presetKnobValues[17][8] = rhodes_release->get();
    vocodec::presetKnobValues[17][9] = rhodes_leak->get();
    vocodec::presetKnobValues[17][10] = rhodes_index1->get();
    vocodec::presetKnobValues[17][11] = rhodes_index2->get();
    vocodec::presetKnobValues[17][12] = rhodes_index3->get();
    vocodec::presetKnobValues[17][13] = rhodes_index4->get();
    vocodec::presetKnobValues[17][14] = rhodes_index5->get();
    vocodec::presetKnobValues[17][15] = rhodes_ratio1->get();
    vocodec::presetKnobValues[17][16] = rhodes_ratio2->get();
    vocodec::presetKnobValues[17][17] = rhodes_ratio3->get();
    vocodec::presetKnobValues[17][18] = rhodes_ratio4->get();
    vocodec::presetKnobValues[17][19] = rhodes_ratio5->get();
    vocodec::presetKnobValues[17][20] = rhodes_ratio6->get();
    vocodec::presetKnobValues[17][21] = rhodes_feedback->get();
    vocodec::presetKnobValues[17][22] = rhodes_tuneSnap->get();
    vocodec::presetKnobValues[17][23] = rhodes_randDecay->get();
    vocodec::presetKnobValues[17][24] = rhodes_randSust->get();
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
    //xml->removeAllAttributes();
    switch (presetNumber) {
        case 1:
            *vocoder_volume = vocodec::presetKnobValues[presetNumber - 1][0];
            juce::MemoryOutputStream(destData, true).writeFloat(*vocoder_volume);
            xml->setAttribute("Warp", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Quality", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("SawToPulse", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("NoiseThreshold", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("Breath", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("PulseWidth", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("PulseShape", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 2:
            xml->setAttribute("Volume", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Warp", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Quality", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("NoiseThreshold", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("SawToPulse", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("PulseWidth", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("PulseShape", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("Breath", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("BandSquish", vocodec::presetKnobValues[presetNumber - 1][9]);
            xml->setAttribute("BandOff", vocodec::presetKnobValues[presetNumber - 1][10]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[presetNumber - 1][11]);
            xml->setAttribute("Stereo", vocodec::presetKnobValues[presetNumber - 1][12]);
            xml->setAttribute("BarkPull", vocodec::presetKnobValues[presetNumber - 1][13]);
            break;
        case 3:
            xml->setAttribute("Shift", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Fine", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("F AMT", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Formant", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("Range", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("Offset", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 4:
            xml->setAttribute("Pickiness", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Amount", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Leapallow", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("Hysteresis", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 5:
            xml->setAttribute("Pickiness", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 6:
            xml->setAttribute("Start", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Length", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("SpeedMult", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 7:
            xml->setAttribute("Start", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Length", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("SpeedMult", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("LoopOn", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("Velo Sens", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 8:
            xml->setAttribute("Threshold", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Window", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Speed", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("CrossFade", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("LenRand", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("SpdRand", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 9:
            xml->setAttribute("PreGain", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Tilt", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("MidGain", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("MidFreq", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 10:
            xml->setAttribute("Gain", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Offset1", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Offset2", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 11:
            xml->setAttribute("Quality", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("SampRatio", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Rounding", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Operation", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("preGain", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 12:
            xml->setAttribute("DelayL", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("DelayR", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("HighPass", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("Feedback", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("PostGain", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 13:
            xml->setAttribute("Size", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("FBLowPass", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("InHighPass", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("InLowPass", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("FBGain", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 14:
            xml->setAttribute("Size", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("HighPass", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("PeakFreq", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PeakGain", vocodec::presetKnobValues[presetNumber - 1][4]);
            break;
        case 15:
            xml->setAttribute("Freq1", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("Detune", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Damping", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PickPos", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("PrepPos", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("PrepForce", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("LetRing", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][9]);
            xml->setAttribute("Freq2", vocodec::presetKnobValues[presetNumber - 1][10]);
            xml->setAttribute("Freq3", vocodec::presetKnobValues[presetNumber - 1][11]);
            xml->setAttribute("Freq4", vocodec::presetKnobValues[presetNumber - 1][12]);
            xml->setAttribute("Freq5", vocodec::presetKnobValues[presetNumber - 1][13]);
            xml->setAttribute("Freq6", vocodec::presetKnobValues[presetNumber - 1][14]);
            break;
        case 16:
            xml->setAttribute("PluckVol", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("PluckTone", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Damping", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PickPos", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("PrepPos", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("PrepForce", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("LetRing", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("FBLevel", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("Release", vocodec::presetKnobValues[presetNumber - 1][9]);
            break;
        case 17:
            xml->setAttribute("Volume", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("LowPass", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("KeyFollow", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Detune", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("FilterQ", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("Attack", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("Sustain", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("Release", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("Leak", vocodec::presetKnobValues[presetNumber - 1][9]);
            xml->setAttribute("FAttack", vocodec::presetKnobValues[presetNumber - 1][10]);
            xml->setAttribute("FDecay", vocodec::presetKnobValues[presetNumber - 1][11]);
            xml->setAttribute("FSustain", vocodec::presetKnobValues[presetNumber - 1][12]);
            xml->setAttribute("FRelease", vocodec::presetKnobValues[presetNumber - 1][13]);
            xml->setAttribute("FLeak", vocodec::presetKnobValues[presetNumber - 1][14]);
            xml->setAttribute("FAmount", vocodec::presetKnobValues[presetNumber - 1][15]);
            xml->setAttribute("Saw/Pulse", vocodec::presetKnobValues[presetNumber - 1][16]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][17]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][18]);
            xml->setAttribute("", vocodec::presetKnobValues[presetNumber - 1][19]);
            break;
        case 18:
            xml->setAttribute("Brightness", vocodec::presetKnobValues[presetNumber - 1][0]);
            xml->setAttribute("TremDepth", vocodec::presetKnobValues[presetNumber - 1][1]);
            xml->setAttribute("TremRate", vocodec::presetKnobValues[presetNumber - 1][2]);
            xml->setAttribute("Drive", vocodec::presetKnobValues[presetNumber - 1][3]);
            xml->setAttribute("PanSpread", vocodec::presetKnobValues[presetNumber - 1][4]);
            xml->setAttribute("Attack", vocodec::presetKnobValues[presetNumber - 1][5]);
            xml->setAttribute("Decay", vocodec::presetKnobValues[presetNumber - 1][6]);
            xml->setAttribute("Sustain", vocodec::presetKnobValues[presetNumber - 1][7]);
            xml->setAttribute("Release", vocodec::presetKnobValues[presetNumber - 1][8]);
            xml->setAttribute("Leak", vocodec::presetKnobValues[presetNumber - 1][9]);
            xml->setAttribute("Index1", vocodec::presetKnobValues[presetNumber - 1][10]);
            xml->setAttribute("Index2", vocodec::presetKnobValues[presetNumber - 1][11]);
            xml->setAttribute("Index3", vocodec::presetKnobValues[presetNumber - 1][12]);
            xml->setAttribute("Index4", vocodec::presetKnobValues[presetNumber - 1][13]);
            xml->setAttribute("Index5", vocodec::presetKnobValues[presetNumber - 1][14]);
            xml->setAttribute("Ratio1", vocodec::presetKnobValues[presetNumber - 1][15]);
            xml->setAttribute("Ratio2", vocodec::presetKnobValues[presetNumber - 1][16]);
            xml->setAttribute("Ratio3", vocodec::presetKnobValues[presetNumber - 1][17]);
            xml->setAttribute("Ratio4", vocodec::presetKnobValues[presetNumber - 1][18]);
            xml->setAttribute("Ratio5", vocodec::presetKnobValues[presetNumber - 1][19]);
            xml->setAttribute("Ratio6", vocodec::presetKnobValues[presetNumber - 1][20]);
            xml->setAttribute("Feedback", vocodec::presetKnobValues[presetNumber - 1][21]);
            xml->setAttribute("TuneSnap", vocodec::presetKnobValues[presetNumber - 1][22]);
            xml->setAttribute("RandDecay", vocodec::presetKnobValues[presetNumber - 1][23]);
            xml->setAttribute("RandSust", vocodec::presetKnobValues[presetNumber - 1][24]);
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
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Warp");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("SawToPulse");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("NoiseThreshold");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("Breath");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("PulseWidth");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("PulseShape");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 2:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Warp");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("NoiseThreshold");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("SawToPulse");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("PulseWidth");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("PulseShape");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("Breath");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("BandSquish");
                   vocodec::presetKnobValues[presetNumber - 1][10] = xml->getDoubleAttribute("BandOff");
                   vocodec::presetKnobValues[presetNumber - 1][11] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[presetNumber - 1][12] = xml->getDoubleAttribute("Stereo");
                   vocodec::presetKnobValues[presetNumber - 1][13] = xml->getDoubleAttribute("BarkPull");
                   break;
               case 3:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Shift");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Fine");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("F AMT");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Formant");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("Range");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("Offset");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 4:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Pickiness");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Amount");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Leapallow");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("Hysteresis");
                   break;
               case 5:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Pickiness");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("");
                   break;
               case 6:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Start");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Length");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("SpeedMult");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("CrossFade");
                   break;
               case 7:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Start");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Length");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("SpeedMult");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("LoopOn");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("CrossFade");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("Velo Sens");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 8:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Threshold");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Window");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Speed");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("CrossFade");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("LenRand");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("SpdRand");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 9:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("PreGain");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Tilt");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("MidGain");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("MidFreq");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PostGain");
                   break;
               case 10:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Gain");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Offset1");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Offset2");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("");
                   break;
               case 11:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Quality");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("SampRatio");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Rounding");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Operation");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("preGain");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 12:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("DelayL");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("DelayR");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("HighPass");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("Feedback");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("PostGain");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   break;
               case 13:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Size");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("FBLowPass");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("InHighPass");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("InLowPass");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("FBGain");
                   break;
               case 14:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Size");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("HighPass");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("PeakFreq");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PeakGain");
                   break;
               case 15:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Freq1");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("Detune");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Damping");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PickPos");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("PrepPos");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("PrepForce");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("LetRing");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][10] = xml->getDoubleAttribute("Freq2");
                   vocodec::presetKnobValues[presetNumber - 1][11] = xml->getDoubleAttribute("Freq3");
                   vocodec::presetKnobValues[presetNumber - 1][12] = xml->getDoubleAttribute("Freq4");
                   vocodec::presetKnobValues[presetNumber - 1][13] = xml->getDoubleAttribute("Freq5");
                   vocodec::presetKnobValues[presetNumber - 1][14] = xml->getDoubleAttribute("Freq6");
                   break;
               case 16:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("PluckVol");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("PluckTone");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Damping");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PickPos");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("PrepPos");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("PrepForce");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("LetRing");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("FBLevel");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("Release");
                   break;
               case 17:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Volume");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("LowPass");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("KeyFollow");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Detune");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("FilterQ");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("Attack");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("Sustain");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("Release");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("Leak");
                   vocodec::presetKnobValues[presetNumber - 1][10] = xml->getDoubleAttribute("FAttack");
                   vocodec::presetKnobValues[presetNumber - 1][11] = xml->getDoubleAttribute("FDecay");
                   vocodec::presetKnobValues[presetNumber - 1][12] = xml->getDoubleAttribute("FSustain");
                   vocodec::presetKnobValues[presetNumber - 1][13] = xml->getDoubleAttribute("FRelease");
                   vocodec::presetKnobValues[presetNumber - 1][14] = xml->getDoubleAttribute("FLeak");
                   vocodec::presetKnobValues[presetNumber - 1][15] = xml->getDoubleAttribute("FAmount");
                   vocodec::presetKnobValues[presetNumber - 1][16] = xml->getDoubleAttribute("Saw/Pulse");
                   vocodec::presetKnobValues[presetNumber - 1][17] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][18] = xml->getDoubleAttribute("");
                   vocodec::presetKnobValues[presetNumber - 1][19] = xml->getDoubleAttribute("");
                   break;
               case 18:
                   vocodec::presetKnobValues[presetNumber - 1][0] = xml->getDoubleAttribute("Brightness");
                   vocodec::presetKnobValues[presetNumber - 1][1] = xml->getDoubleAttribute("TremDepth");
                   vocodec::presetKnobValues[presetNumber - 1][2] = xml->getDoubleAttribute("TremRate");
                   vocodec::presetKnobValues[presetNumber - 1][3] = xml->getDoubleAttribute("Drive");
                   vocodec::presetKnobValues[presetNumber - 1][4] = xml->getDoubleAttribute("PanSpread");
                   vocodec::presetKnobValues[presetNumber - 1][5] = xml->getDoubleAttribute("Attack");
                   vocodec::presetKnobValues[presetNumber - 1][6] = xml->getDoubleAttribute("Decay");
                   vocodec::presetKnobValues[presetNumber - 1][7] = xml->getDoubleAttribute("Sustain");
                   vocodec::presetKnobValues[presetNumber - 1][8] = xml->getDoubleAttribute("Release");
                   vocodec::presetKnobValues[presetNumber - 1][9] = xml->getDoubleAttribute("Leak");
                   vocodec::presetKnobValues[presetNumber - 1][10] = xml->getDoubleAttribute("Index1");
                   vocodec::presetKnobValues[presetNumber - 1][11] = xml->getDoubleAttribute("Index2");
                   vocodec::presetKnobValues[presetNumber - 1][12] = xml->getDoubleAttribute("Index3");
                   vocodec::presetKnobValues[presetNumber - 1][13] = xml->getDoubleAttribute("Index4");
                   vocodec::presetKnobValues[presetNumber - 1][14] = xml->getDoubleAttribute("Index5");
                   vocodec::presetKnobValues[presetNumber - 1][15] = xml->getDoubleAttribute("Ratio1");
                   vocodec::presetKnobValues[presetNumber - 1][16] = xml->getDoubleAttribute("Ratio2");
                   vocodec::presetKnobValues[presetNumber - 1][17] = xml->getDoubleAttribute("Ratio3");
                   vocodec::presetKnobValues[presetNumber - 1][18] = xml->getDoubleAttribute("Ratio4");
                   vocodec::presetKnobValues[presetNumber - 1][19] = xml->getDoubleAttribute("Ratio5");
                   vocodec::presetKnobValues[presetNumber - 1][20] = xml->getDoubleAttribute("Ratio6");
                   vocodec::presetKnobValues[presetNumber - 1][21] = xml->getDoubleAttribute("Feedback");
                   vocodec::presetKnobValues[presetNumber - 1][22] = xml->getDoubleAttribute("TuneSnap");
                   vocodec::presetKnobValues[presetNumber - 1][23] = xml->getDoubleAttribute("RandDecay");
                   vocodec::presetKnobValues[presetNumber - 1][24] = xml->getDoubleAttribute("RandSust");
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

