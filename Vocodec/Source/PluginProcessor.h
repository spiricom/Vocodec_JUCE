/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class VocodecAudioProcessor  : public AudioProcessor, public MidiInputCallback, public MidiKeyboardStateListener
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
    
    int presetNumber;
    int prevPresetNumber;
	bool loading;
	float interpVal = 0;

    AudioParameterFloat* vocoder_volume;
    AudioParameterFloat* vocoder_warp;
    AudioParameterFloat* vocoder_quality;
    AudioParameterFloat* vocoder_sawToPulse;
    AudioParameterFloat* vocoder_noiseThreshol;
    AudioParameterFloat* vocoder_breath;
    AudioParameterFloat* vocoder_tilt;
    AudioParameterFloat* vocoder_pulsewidth;
    AudioParameterFloat* vocoder_pulseShape;
    AudioParameterFloat* vocoderCh_volume;
    AudioParameterFloat* vocoderCh_warp;
    AudioParameterFloat* vocoderCh_quality;
    AudioParameterFloat* vocoderCh_noiseThreshold;
    AudioParameterFloat* vocoderCh_sawToPulse;
    AudioParameterFloat* vocoderCh_pulseWidth;
    AudioParameterFloat* vocoderCh_pulseShape;
    AudioParameterFloat* vocoderCh_breath;
    AudioParameterFloat* vocoderCh_speed;
    AudioParameterFloat* vocoderCh_bandSquish;
    AudioParameterFloat* vocoderCh_bandOff;
    AudioParameterFloat* vocoderCh_tilt;
    AudioParameterFloat* vocoderCh_stereo;
    AudioParameterFloat* vocoderCh_barkPull;
    AudioParameterFloat* pitchShift_shift;
    AudioParameterFloat* pitchShift_fine;
    AudioParameterFloat* pitchShift_f_Amt;
    AudioParameterFloat* pitchShift_formant;
    AudioParameterFloat* pitchShift_range;
    AudioParameterFloat* pitchShift_offset;
    AudioParameterFloat* autotuneMono_pickiness;
    AudioParameterFloat* autotuneMono_amount;
    AudioParameterFloat* autotuneMono_speed;
    AudioParameterFloat* autotuneMono_leapallow;
    AudioParameterFloat* autotuneMono_hysteresis;
    AudioParameterFloat* autotunePoly_pickiness;
    AudioParameterFloat* samplerButtonPress_start;
    AudioParameterFloat* samplerButtonPress_length;
    AudioParameterFloat* samplerButtonPress_speed;
    AudioParameterFloat* samplerButtonPress_speedMult;
    AudioParameterFloat* samplerButtonPress_crossfade;
    AudioParameterFloat* samplerKeyboard_start;
    AudioParameterFloat* samplerKeyboard_length;
    AudioParameterFloat* samplerKeyboard_speed;
    AudioParameterFloat* samplerKeyboard_speedMult;
    AudioParameterFloat* samplerKeyboard_loopOn;
    AudioParameterFloat* samplerKeyboard_crossFade;
    AudioParameterFloat* samplerKeyboard_velo_Sens;
    AudioParameterFloat* samplerAutoGrab_threshold;
    AudioParameterFloat* samplerAutoGrab_window;
    AudioParameterFloat* samplerAutoGrab_speed;
    AudioParameterFloat* samplerAutoGrab_crossFade;
    AudioParameterFloat* samplerAutoGrab_lenRand;
    AudioParameterFloat* samplerAutoGrab_spdRand;
    AudioParameterFloat* distortion_preGain;
    AudioParameterFloat* distortion_tilt;
    AudioParameterFloat* distortion_midGain;
    AudioParameterFloat* distortion_midFreq;
    AudioParameterFloat* distortion_postGain;
    AudioParameterFloat* wavefolder_gain;
    AudioParameterFloat* wavefolder_offset1;
    AudioParameterFloat* wavefolder_offset2;
    AudioParameterFloat* wavefolder_postGain;
    AudioParameterFloat* bitCrusher_quality;
    AudioParameterFloat* bitCrusher_sampRatio;
    AudioParameterFloat* bitCrusher_rounding;
    AudioParameterFloat* bitCrusher_operation;
    AudioParameterFloat* bitCrusher_postGain;
    AudioParameterFloat* bitCrusher_preGain;
    AudioParameterFloat* delay_delayL;
    AudioParameterFloat* delay_delayR;
    AudioParameterFloat* delay_highPass;
    AudioParameterFloat* delay_lowPass;
    AudioParameterFloat* delay_feedback;
    AudioParameterFloat* delay_postGain;
    AudioParameterFloat* delay_postGain1;
    AudioParameterFloat* delay_postGain2;
    AudioParameterFloat* delay_postGain3;
    AudioParameterFloat* reverb_size;
    AudioParameterFloat* reverb_fBLowPass;
    AudioParameterFloat* reverb_inHighPass;
    AudioParameterFloat* reverb_inLowPass;
    AudioParameterFloat* reverb_fBGain;
    AudioParameterFloat* reverb2_size;
    AudioParameterFloat* reverb2_lowPass;
    AudioParameterFloat* reverb2_highPass;
    AudioParameterFloat* reverb2_peakFreq;
    AudioParameterFloat* reverb2_peakGain;
    AudioParameterFloat* livingString_freq1;
    AudioParameterFloat* livingString_detune;
    AudioParameterFloat* livingString_decay;
    AudioParameterFloat* livingString_damping;
    AudioParameterFloat* livingString_pickPos;
    AudioParameterFloat* livingString_prepPos;
    AudioParameterFloat* livingString_prepForce;
    AudioParameterFloat* livingString_letRing;
    AudioParameterFloat* livingString_freq2;
    AudioParameterFloat* livingString_freq3;
    AudioParameterFloat* livingString_freq4;
    AudioParameterFloat* livingString_freq5;
    AudioParameterFloat* livingString_freq6;
    AudioParameterFloat* livingStringSynth_pluckVol;
    AudioParameterFloat* livingStringSynth_pluckTone;
    AudioParameterFloat* livingStringSynth_decay;
    AudioParameterFloat* livingStringSynth_damping;
    AudioParameterFloat* livingStringSynth_pickPos;
    AudioParameterFloat* livingStringSynth_prepPos;
    AudioParameterFloat* livingStringSynth_prepForce;
    AudioParameterFloat* livingStringSynth_letRing;
    AudioParameterFloat* livingStringSynth_fBLevel;
    AudioParameterFloat* livingStringSynth_release;
    AudioParameterFloat* classicSynth_volume;
    AudioParameterFloat* classicSynth_lowPass;
    AudioParameterFloat* classicSynth_keyFollow;
    AudioParameterFloat* classicSynth_detune;
    AudioParameterFloat* classicSynth_filterQ;
    AudioParameterFloat* classicSynth_attack;
    AudioParameterFloat* classicSynth_decay;
    AudioParameterFloat* classicSynth_sustain;
    AudioParameterFloat* classicSynth_release;
    AudioParameterFloat* classicSynth_leak;
    AudioParameterFloat* classicSynth_fAttack;
    AudioParameterFloat* classicSynth_fDecay;
    AudioParameterFloat* classicSynth_fSustain;
    AudioParameterFloat* classicSynth_fRelease;
    AudioParameterFloat* classicSynth_fLeak;
    AudioParameterFloat* classicSynth_fAmount;
    AudioParameterFloat* classicSynth_sawPulse;
    AudioParameterFloat* rhodes_brightness;
    AudioParameterFloat* rhodes_tremDepth;
    AudioParameterFloat* rhodes_tremRate;
    AudioParameterFloat* rhodes_drive;
    AudioParameterFloat* rhodes_panSpread;
    AudioParameterFloat* rhodes_attack;
    AudioParameterFloat* rhodes_decay;
    AudioParameterFloat* rhodes_sustain;
    AudioParameterFloat* rhodes_release;
    AudioParameterFloat* rhodes_leak;
    AudioParameterFloat* rhodes_index1;
    AudioParameterFloat* rhodes_index2;
    AudioParameterFloat* rhodes_index3;
    AudioParameterFloat* rhodes_index4;
    AudioParameterFloat* rhodes_index5;
    AudioParameterFloat* rhodes_ratio1;
    AudioParameterFloat* rhodes_ratio2;
    AudioParameterFloat* rhodes_ratio3;
    AudioParameterFloat* rhodes_ratio4;
    AudioParameterFloat* rhodes_ratio5;
    AudioParameterFloat* rhodes_ratio6;
    AudioParameterFloat* rhodes_feedback;
    AudioParameterFloat* rhodes_tuneSnap;
    AudioParameterFloat* rhodes_randDecay;
    AudioParameterFloat* rhodes_randSust;
    
private:
    
	bool isAddingFromMidiInput = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocodecAudioProcessor)
};
