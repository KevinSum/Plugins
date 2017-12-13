#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class DelayAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
										
{
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor();

    //==============================================================================
	void timerCallback();
	void sliderValueChanged (Slider*);
    void paint (Graphics&) override;
    void resized() override;

private:
    // Initialize processor, sliders and labels
    DelayAudioProcessor& processor;

	Slider delayTimeSlider;
	Label delayTimeLabel;

	Slider feedbackSlider;
	Label feedbackLabel;

	Slider dryMixSlider;
	Label dryMixLabel;

	Slider wetMixSlider;
	Label wetMixLabel;

	DelayAudioProcessor* getProcessor() const
	{
		return static_cast <DelayAudioProcessor*> (getAudioProcessor());
	}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};
