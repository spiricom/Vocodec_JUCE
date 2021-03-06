/*
  ==============================================================================

    UIConstants.h
    Created: 20 Aug 2020 11:05:42am
    Author:  Matthew Wang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define MIN_METER_VOL -80.0f
#define INV_MIN_METER_VOL -0.0125f

const Colour darkergrey { 0xff333333 };

const std::vector<Colour> cLightColours = {
    Colours::limegreen,
    Colours::red,
    Colours::limegreen,
    Colours::gold,
    Colours::limegreen,
    Colours::limegreen,
    Colours::red,
    Colours::gold,
    Colours::red,
    Colours::gold,
    Colours::red,
    Colours::gold,
    Colours::red,
    Colours::gold,
    Colours::red
};

const std::initializer_list<const char*> cPluginParamPrefixes = {
    "vocoder",
    "vocoderCh",
    "pitchShift",
    "autotuneMono",
    "autotunePoly",
    "samplerButtonPress",
    "samplerKeyboard",
    "samplerAutoGrab",
    "distortion",
    "wavefolder",
    "bitCrusher",
    "delay",
    "reverb",
    "reverb2",
    "livingString",
    "livingStringSynth",
    "classicSynth",
    "rhodes",
    "wavetableSynth"
};

const std::initializer_list<const char*> cPluginParamNames = {
    "vocoder_volume",
    "vocoder_warp",
    "vocoder_quality",
    "vocoder_sawToPulse",
    "vocoder_noiseThreshold",
    "vocoder_breath",
    "vocoder_tilt",
    "vocoder_pulsewidth",
    "vocoder_pulseShape",
    "vocoderCh_volume",
    "vocoderCh_warp",
    "vocoderCh_quality",
    "vocoderCh_bandWidth",
    "vocoderCh_noiseThreshold",
    "vocoderCh_sawToPulse",
    "vocoderCh_pulseWidth",
    "vocoderCh_pulseShape",
    "vocoderCh_breath",
    "vocoderCh_speed",
    "vocoderCh_bandSquish",
    "vocoderCh_bandOff",
    "vocoderCh_tilt",
    "vocoderCh_stereo",
    "vocoderCh_barkPull",
    "pitchShift_shift",
    "pitchShift_fine",
    "pitchShift_f_Amt",
    "pitchShift_formant",
    "pitchShift_range",
    "pitchShift_offset",
    "autotuneMono_pickiness",
    "autotuneMono_amount",
    "autotuneMono_speed",
    "autotuneMono_leapallow",
    "autotuneMono_hysteresis",
    "autotunePoly_pickiness",
    "samplerButtonPress_start",
    "samplerButtonPress_length",
    "samplerButtonPress_speed",
    "samplerButtonPress_speedMult",
    "samplerButtonPress_crossfade",
    "samplerKeyboard_start",
    "samplerKeyboard_length",
    "samplerKeyboard_speed",
    "samplerKeyboard_speedMult",
    "samplerKeyboard_loopOn",
    "samplerKeyboard_crossFade",
    "samplerKeyboard_velo_Sens",
    "samplerAutoGrab_threshold",
    "samplerAutoGrab_window",
    "samplerAutoGrab_speed",
    "samplerAutoGrab_crossFade",
    "samplerAutoGrab_lenRand",
    "samplerAutoGrab_spdRand",
    "distortion_preGain",
    "distortion_tilt",
    "distortion_midGain",
    "distortion_midFreq",
    "distortion_postGain",
    "wavefolder_gain",
    "wavefolder_offset1",
    "wavefolder_offset2",
    "wavefolder_postGain",
    "bitCrusher_quality",
    "bitCrusher_sampRatio",
    "bitCrusher_rounding",
    "bitCrusher_operation",
    "bitCrusher_postGain",
    "bitCrusher_preGain",
    "delay_delayL",
    "delay_delayR",
    "delay_highPass",
    "delay_lowPass",
    "delay_feedback",
    "delay_postGain",
    "delay_postGain1",
    "delay_postGain2",
    "delay_postGain3",
    "reverb_size",
    "reverb_fBLowPass",
    "reverb_inHighPass",
    "reverb_inLowPass",
    "reverb_fBGain",
    "reverb2_size",
    "reverb2_lowPass",
    "reverb2_highPass",
    "reverb2_peakFreq",
    "reverb2_peakGain",
    "livingString_freq1",
    "livingString_detune",
    "livingString_decay",
    "livingString_damping",
    "livingString_pickPos",
    "livingString_prepPos",
    "livingString_prepForce",
    "livingString_letRing",
    "livingString_freq2",
    "livingString_freq3",
    "livingString_freq4",
    "livingString_freq5",
    "livingString_freq6",
    "livingStringSynth_pluckVol",
    "livingStringSynth_pluckTone",
    "livingStringSynth_decay",
    "livingStringSynth_damping",
    "livingStringSynth_pickPos",
    "livingStringSynth_prepPos",
    "livingStringSynth_prepForce",
    "livingStringSynth_letRing",
    "livingStringSynth_fBLevel",
    "livingStringSynth_release",
    "classicSynth_volume",
    "classicSynth_lowPass",
    "classicSynth_keyFollow",
    "classicSynth_detune",
    "classicSynth_filterQ",
    "classicSynth_attack",
    "classicSynth_decay",
    "classicSynth_sustain",
    "classicSynth_release",
    "classicSynth_leak",
    "classicSynth_fAttack",
    "classicSynth_fDecay",
    "classicSynth_fSustain",
    "classicSynth_fRelease",
    "classicSynth_fLeak",
    "classicSynth_fAmount",
    "classicSynth_sawPulse",
    "rhodes_brightness",
    "rhodes_tremDepth",
    "rhodes_tremRate",
    "rhodes_drive",
    "rhodes_panSpread",
    "rhodes_attack",
    "rhodes_decay",
    "rhodes_sustain",
    "rhodes_release",
    "rhodes_leak",
    "rhodes_index1",
    "rhodes_index2",
    "rhodes_index3",
    "rhodes_index4",
    "rhodes_index5",
    "rhodes_ratio1",
    "rhodes_ratio2",
    "rhodes_ratio3",
    "rhodes_ratio4",
    "rhodes_ratio5",
    "rhodes_ratio6",
    "rhodes_feedback",
    "rhodes_tuneSnap",
    "rhodes_randDecay",
    "rhodes_randSust",
    "wavetableSynth_index",
    "wavetableSynth_phase1",
    "wavetableSynth_phase2",
    "wavetableSynth_phase3",
    "wavetableSynth_phase4",
    "wavetableSynth_gain1",
    "wavetableSynth_gain2",
    "wavetableSynth_gain3",
    "wavetableSynth_gain4"
};

const std::initializer_list<const char*> cChoiceParamNames = {
    "vocoder_numVoices",
    "vocoder_internalExternal",
    "vocoder_freeze",
    
    "vocoderCh_numVoices",
    "vocoderCh_internalExternal",
    "vocoderCh_freeze",
    
//    "pitchShift_"/
    
    "autotuneMono_useChromatic",
    "autotuneMono_lock",
    
//    "autotunePoly_",

    "samplerButtonPress_playMode",
    "samplerButtonPress_paused",
    
    "samplerKeyboard_controlAllKeys",
    
    "samplerAutoGrab_playMode",
    "samplerAutoGrab_triggerChannel",
    "samplerAutoGrab_quantizeRate",
    
    "distortion_mode",
    
    "waveFolder_mode",
    
    "bitCrusher_stereo",
    
    "delay_shaper",
    "delay_uncapFeedback",
    "delay_freeze",
    
    "reverb_uncapFeedback",
    "reverb_freeze",
    
    "reverb2_freeze",
    
    "livingString_ignoreFreqKnobs",
    "livingString_independentStrings",
    "livingString_feedback",
    
    "livingStringSynth_numVoices",
    "livingStringSynth_audioIn",
    "livingStringSynth_feedback",
    
    "classicSynth_numVoices",
    
    "rhodes_numVoices",
    "rhodes_sound",
    "rhodes_tremoloStereo",
    
    "wavetableSynth_numVoices",
};
