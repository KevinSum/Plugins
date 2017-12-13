/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class GainAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    GainAudioProcessorEditor (GainAudioProcessor&);
    ~GainAudioProcessorEditor();

    //==============================================================================
	void timerCallback();
	void sliderValueChanged(Slider* slider);
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainAudioProcessor& processor;

	// Get processor
	GainAudioProcessor* getProcessor() const
	{
		return static_cast <GainAudioProcessor*> (getAudioProcessor());
	}

	// Initialize slider and label
	Slider gainSlider;
	Label gainLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAudioProcessorEditor)
};
