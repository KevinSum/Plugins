#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TremoloAudioProcessorEditor::TremoloAudioProcessorEditor (TremoloAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (285, 150);

	// Settings for labels and sliders
	frequencyLabel.setText("Frequency", dontSendNotification);
	frequencySlider.addListener(this);
	frequencySlider.setSliderStyle(Slider::Rotary);
	frequencySlider.setRange(0, 32.0, 0.01);
	frequencySlider.setValue(getProcessor()->getParameter(0)); // Set initial value, from getProcessor method in PluginProcessor.cpp
	frequencySlider.setTextValueSuffix(" Hz");
	frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
	addAndMakeVisible(&frequencySlider);
	frequencyLabel.attachToComponent(&frequencySlider, false);
	frequencyLabel.setTopLeftPosition(frequencyLabel.getX() + 17, frequencyLabel.getY()); // Shift label slightly to right

	depthLabel.setText("Depth", dontSendNotification);
	depthSlider.addListener(this);
	depthSlider.setSliderStyle(Slider::Rotary);
	depthSlider.setRange(0.0, 1.0, 0.01);
	depthSlider.setValue(getProcessor()->getParameter(1));
	depthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(&depthSlider);
	depthLabel.attachToComponent(&depthSlider, false);
	depthLabel.setTopLeftPosition(depthLabel.getX() + 27, depthLabel.getY());

	
	/*addAndMakeVisible(sineButton);
	sineButton.setButtonText("Sine");
	sineButton.setRadioGroupId(1);

	addAndMakeVisible(triangleButton);
	triangleButton.setButtonText("Triangle");
	triangleButton.setRadioGroupId(1);

	addAndMakeVisible(squareButton);
	squareButton.setButtonText("Square");
	squareButton.setRadioGroupId(1);*/
}

void TremoloAudioProcessorEditor::timerCallback()
{
	TremoloAudioProcessor* thisProcessor = getProcessor(); // set processor
}

void TremoloAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	// Change parameters in processor if slider changes
	if (slider == &frequencySlider) {
		getProcessor()->setParameterNotifyingHost(TremoloAudioProcessor::frequencyParam, (float)frequencySlider.getValue());
	}
	if (slider == &depthSlider) {
		getProcessor()->setParameterNotifyingHost(TremoloAudioProcessor::depthParam, (float)depthSlider.getValue());
	}
}

/*
void TremoloAudioProcessorEditor::buttonClicked(Button* button)
{
	
	if (button == &sineButton) {
		sineButton.setToggleState(true, sendNotification);
		getProcessor()->setParameterNotifyingHost(TremoloAudioProcessor::waveParam, 0);
	}
	if (button == &triangleButton) {
		sineButton.setToggleState(true, sendNotification);
		getProcessor()->setParameterNotifyingHost(TremoloAudioProcessor::waveParam, 1);
	}
	if (button == &squareButton) {
		sineButton.setToggleState(true, sendNotification);
		getProcessor()->setParameterNotifyingHost(TremoloAudioProcessor::waveParam, 2);
	}
}
*/

TremoloAudioProcessorEditor::~TremoloAudioProcessorEditor()
{
}

//==============================================================================
void TremoloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void TremoloAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	frequencySlider.setBounds(20, 30, 100, 100);
	depthSlider.setBounds(140, 30, 100, 100);
	/*
	sineButton.setBounds(250, 30, 60, 25);
	triangleButton.setBounds(250, 60, 60, 25);
	squareButton.setBounds(250, 90, 60, 25);
	*/
}
