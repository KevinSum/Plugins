#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class TremoloAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener//, public Button::Listener
{
public:
    TremoloAudioProcessorEditor (TremoloAudioProcessor&);
    ~TremoloAudioProcessorEditor();

    //==============================================================================
	void timerCallback();
    void paint (Graphics&) override;
	void sliderValueChanged(Slider*);
	//void buttonClicked(Button*);
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

	// Audio Plugin Processor
    TremoloAudioProcessor& processor;

	TremoloAudioProcessor* getProcessor() const
	{
		return static_cast <TremoloAudioProcessor*> (getAudioProcessor());
	}

	// Initialize Sliders and labels
	Slider frequencySlider;
	Label frequencyLabel;
	Slider depthSlider;
	Label depthLabel;
	
	/*
	TextButton sineButton;
	TextButton triangleButton;
	TextButton squareButton;
	*/
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremoloAudioProcessorEditor)
};
