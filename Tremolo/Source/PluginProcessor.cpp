/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TremoloAudioProcessor::TremoloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	frequency = 10;
	currentAngle[0] = 0.0;
	currentAngle[1] = 0.0;
	depth = 0.6;
}

TremoloAudioProcessor::~TremoloAudioProcessor()
{
}

//==============================================================================
const String TremoloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TremoloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TremoloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TremoloAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TremoloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TremoloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TremoloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TremoloAudioProcessor::setCurrentProgram (int index)
{
}

const String TremoloAudioProcessor::getProgramName (int index)
{
    return {};
}

void TremoloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

float TremoloAudioProcessor::getParameter(int index)
{
	// Get parameters values - For changing slider to initial values at start
	switch (index) {
	case frequencyParam:
		return frequency;
		break;
	case depthParam:
		return depth;
		break;
	}
}

void TremoloAudioProcessor::setParameter(int index, float newValue)
{
	// Set parameter values - For when sliders are moved
	switch (index) {
	case frequencyParam:
		frequency = newValue;
		updateAngleDelta();
		break;
	case depthParam:
		depth = newValue;
		break;
	}
}

//==============================================================================
void TremoloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	currentSampleRate = sampleRate;
	updateAngleDelta();
}

void TremoloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TremoloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TremoloAudioProcessor::updateAngleDelta()
{
	// Get the angle interval for the sine wave
	const double intervalsPerCycle = frequency / currentSampleRate; 
	angleDelta = intervalsPerCycle * double_Pi;
}

void TremoloAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
		
		for (int i = 0; i < numSamples; ++i)
		{
			// Calculate modulation
			mod[channel] = 1 + depth * sin(currentAngle[channel]);
			currentAngle[channel] += angleDelta;  // Increment for next sample
			  
			channelData[i] *= mod[channel]; // Sample * Modulation

			// Wrap angle 
			currentAngle[channel] = std::fmod(currentAngle[channel] + angleDelta, double_Pi * 2.0);
		}
    } 
}

//==============================================================================
bool TremoloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TremoloAudioProcessor::createEditor()
{
    return new TremoloAudioProcessorEditor (*this);
}

//==============================================================================
void TremoloAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// Create XML
	XmlElement xml("TremoloSettings");

	//Add attributes
	xml.setAttribute("frequency", (float)frequency);
	xml.setAttribute("depth", (float)depth);

	// Store paramaters
	for (auto* param : getParameters())
		if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
			xml.setAttribute(p->paramID, p->getValue());

	//Store as binary and return
	copyXmlToBinary(xml, destData);

}

void TremoloAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// Retrieve XLM from binary 
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	// Retrieve settings
	if (xmlState != nullptr)
		if (xmlState->hasTagName("TremoloSettings"))
		{
			frequency = xmlState->getDoubleAttribute("frequency", 1.0);
			depth = xmlState->getDoubleAttribute("depth", 1.0);

			// Reload our parameters
			for (auto* param : getParameters())
				if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
					p->setValue((float)xmlState->getDoubleAttribute(p->paramID, p->getValue()));
		}

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TremoloAudioProcessor();
}
