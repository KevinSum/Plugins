#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (500, 150);

	// Settings for labels and sliders
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::green);

	delayTimeLabel.setText("Delay", dontSendNotification);
	delayTimeSlider.addListener(this);
	delayTimeSlider.setSliderStyle(Slider::Rotary);
	delayTimeSlider.setRange(0.01, 2.0, 0.01);
	delayTimeSlider.setValue(getProcessor()->getParameter(0)); // Set initial value, from getProcessor method in PluginProcessor.cpp
	delayTimeSlider.setTextValueSuffix(" s");
	delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	addAndMakeVisible(&delayTimeSlider);
	delayTimeLabel.attachToComponent(&delayTimeSlider, false);
	delayTimeLabel.setTopLeftPosition(delayTimeLabel.getX() + 27, delayTimeLabel.getY()); // Shift label slightly to right

	feedbackLabel.setText("Feedback", dontSendNotification);
	feedbackSlider.addListener(this);
	feedbackSlider.setSliderStyle(Slider::Rotary);
	feedbackSlider.setRange(0.0, 1.0, 0.01);
	feedbackSlider.setValue(getProcessor()->getParameter(1));
	feedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(&feedbackSlider);
	feedbackLabel.attachToComponent(&feedbackSlider, false);
	feedbackLabel.setTopLeftPosition(feedbackLabel.getX() + 16, feedbackLabel.getY());

	dryMixLabel.setText("Dry Mix", dontSendNotification);
	dryMixSlider.addListener(this);
	dryMixSlider.setSliderStyle(Slider::Rotary);
	dryMixSlider.setRange(0.0, 1.0, 0.01);
	dryMixSlider.setValue(getProcessor()->getParameter(2));
	dryMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(&dryMixSlider);
	dryMixLabel.attachToComponent(&dryMixSlider, false);
	dryMixLabel.setTopLeftPosition(dryMixLabel.getX() + 21, dryMixLabel.getY());

	wetMixLabel.setText("Wet Mix", dontSendNotification);
	wetMixSlider.addListener(this);
	wetMixSlider.setSliderStyle(Slider::Rotary); 
	wetMixSlider.setRange(0.0, 1.0, 0.01);
	wetMixSlider.setValue(getProcessor()->getParameter(3));
	wetMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(&wetMixSlider);
	wetMixLabel.attachToComponent(&wetMixSlider, false);
	wetMixLabel.setTopLeftPosition(wetMixLabel.getX() + 21, wetMixLabel.getY());
}

void DelayAudioProcessorEditor::timerCallback()
{
	DelayAudioProcessor* thisProcessor = getProcessor(); // set processor
}

void DelayAudioProcessorEditor::sliderValueChanged(Slider* slider) 
{
	// change parameters in processor if slider changes
	if (slider == &delayTimeSlider) {
		getProcessor()->setParameterNotifyingHost(DelayAudioProcessor::delayTimeParam, (float)delayTimeSlider.getValue());
	}
	if (slider == &feedbackSlider) {
		getProcessor()->setParameterNotifyingHost(DelayAudioProcessor::feedbackParam, (float)feedbackSlider.getValue());
	}
	if (slider == &dryMixSlider) {
		getProcessor()->setParameterNotifyingHost(DelayAudioProcessor::dryMixParam, (float)dryMixSlider.getValue());
	}
	if (slider == &wetMixSlider) {
		getProcessor()->setParameterNotifyingHost(DelayAudioProcessor::wetMixParam, (float)wetMixSlider.getValue());
	}
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
}

//==============================================================================
void DelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DelayAudioProcessorEditor::resized()
{
    // Position of components
	delayTimeSlider.setBounds(20, 30, 100, 100);
	feedbackSlider.setBounds(140, 30, 100, 100);
	dryMixSlider.setBounds(260, 30, 100, 100);
	wetMixSlider.setBounds(380, 30, 100, 100);
}
