/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GainAudioProcessorEditor::GainAudioProcessorEditor (GainAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (120, 270);

	// Settings for labels and sliders
	gainLabel.setText("Gain", dontSendNotification);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::red);
	gainSlider.addListener(this);
	gainSlider.setRange(-20, 20, 0.1);
	gainSlider.setValue(getProcessor()->getParameter(0)); // Set initial value, from getProcessor method in PluginProcessor.cpp
	gainSlider.setTextValueSuffix(" dB");
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	addAndMakeVisible(&gainSlider);
	gainLabel.attachToComponent(&gainSlider, false);
	gainLabel.setTopLeftPosition(gainLabel.getX() + 12, gainLabel.getY()); // Shift label slightly to right
}

void GainAudioProcessorEditor::timerCallback()
{
	GainAudioProcessor* thisProcessor = getProcessor(); // set processor
}

void GainAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	// Change parameters in processor if slider changes
	if (slider == &gainSlider) {
		getProcessor()->setParameterNotifyingHost(GainAudioProcessor::gainParam, (float)gainSlider.getValue());
	}
}

GainAudioProcessorEditor::~GainAudioProcessorEditor()
{
}

//==============================================================================
void GainAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void GainAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	gainSlider.setBounds(30, 40, 60, 200);
}
