/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "DSP/CMyFilter.cpp"

//==============================================================================
/**
*/
class PizzaKnobFilterPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PizzaKnobFilterPluginAudioProcessor();
    ~PizzaKnobFilterPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
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

    //==============================================================================
	enum Parameters { MasterBypass = 0, Mode, Freq, Q, Volume, totalNumParam };
	bool NeedsUIUpdate() { return UIUpdateFlag; };
	void RequestUIUpdate() { UIUpdateFlag = true; };
	void ClearUIUpdateFlag() { UIUpdateFlag = false; };

	int getNumParameters() override;
	float getParameter(int index) override;
	void setParameter(int index, float newValue) override;
	const String getParameterName(int index) override;
	const String getParameterText(int index) override;
	
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PizzaKnobFilterPluginAudioProcessor)
    
    //==============================================================================
	float UserParams[totalNumParam];
	bool UIUpdateFlag;
	
	//Processor
	CMyFilter MultiFilter;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
