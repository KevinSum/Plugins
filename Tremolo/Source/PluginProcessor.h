#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class TremoloAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TremoloAudioProcessor();
    ~TremoloAudioProcessor();

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
    bool isMidiEffect () const override;
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

	void updateAngleDelta();

	// Parameter Variables
	enum Parameters
	{
		// For changing parameters when sliders change
		frequencyParam,
		depthParam
		//waveParam
	};
	float frequency;
	float depth;
	float mod[2];
	//int wave; // 1 = Sine, 2 = Triangle, 3 = Square
private:
    //==============================================================================
	float currentSampleRate;
	float currentAngle[2], angleDelta;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremoloAudioProcessor)
};


