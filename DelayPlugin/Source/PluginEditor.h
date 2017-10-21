#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class DelayPluginAudioProcessorEditor  : public AudioProcessorEditor,
									   	 public Slider::Listener
										
{
public:
    DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor&);
    ~DelayPluginAudioProcessorEditor();

    //==============================================================================
	void timerCallback();
	void sliderValueChanged (Slider*);
    void paint (Graphics&) override;
    void resized() override;

private:
    // Initialize processor, sliders and labels
    DelayPluginAudioProcessor& processor;

	Slider delayTimeSlider;
	Label delayTimeLabel;

	Slider feedbackSlider;
	Label feedbackLabel;

	Slider dryMixSlider;
	Label dryMixLabel;

	Slider wetMixSlider;
	Label wetMixLabel;

	DelayPluginAudioProcessor* getProcessor() const
	{
		return static_cast <DelayPluginAudioProcessor*> (getAudioProcessor());
	}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPluginAudioProcessorEditor)
};
