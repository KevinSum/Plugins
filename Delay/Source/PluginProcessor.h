#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class DelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DelayAudioProcessor();
    ~DelayAudioProcessor();

    //==============================================================================
	float getParameter(int index) override;
	void setParameter(int index, float newValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
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

	// Parameter Variables
	enum Parameters
	{
		// For changing parameters when sliders change
		delayTimeParam,
		feedbackParam,
		dryMixParam,
		wetMixParam
	};

	float delayTime;
	float feedback;
	float dryMix;
	float wetMix;


private:
    //==============================================================================
	//Parameter Variables

	AudioSampleBuffer delayBuffer;
	int delayBufferSize;
	int delayBufferWritePointer; 
	int delayBufferReadPointer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
};
