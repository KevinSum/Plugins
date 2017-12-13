#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class PingPongDelayAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener

{
public:
	PingPongDelayAudioProcessorEditor(PingPongDelayAudioProcessor&);
	~PingPongDelayAudioProcessorEditor();

	//==============================================================================
	void timerCallback();
	void sliderValueChanged(Slider*);
	void paint(Graphics&) override;
	void resized() override;

private:
	// Initialize processor, sliders and labels
	PingPongDelayAudioProcessor& processor;

	Slider delayTimeSlider;
	Label delayTimeLabel;

	Slider feedbackSlider;
	Label feedbackLabel;

	Slider dryMixSlider;
	Label dryMixLabel;

	Slider wetMixSlider;
	Label wetMixLabel;

	PingPongDelayAudioProcessor* getProcessor() const
	{
		return static_cast <PingPongDelayAudioProcessor*> (getAudioProcessor());
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PingPongDelayAudioProcessorEditor)
};
