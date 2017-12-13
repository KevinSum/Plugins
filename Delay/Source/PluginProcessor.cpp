#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayAudioProcessor::DelayAudioProcessor()
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
	// Initial Values
	delayTime = 1.0;
	dryMix = 1.0;
	wetMix = 0.5;
	feedback = 0.5;

	delayBufferSize = 1;
	delayBufferWritePointer = 0;
	delayBufferReadPointer = 0;
}

DelayAudioProcessor::~DelayAudioProcessor()
{
}

//==============================================================================
const String DelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double DelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayAudioProcessor::setCurrentProgram (int index)
{
}

const String DelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

float DelayAudioProcessor::getParameter(int index)
{
	// Get parameters values - For changing slider to initial values at start
	switch (index) {
		case delayTimeParam:
			return delayTime;
			break;
		case feedbackParam:
			return feedback;
			break;
		case dryMixParam:
			return dryMix;
			break;
		case wetMixParam:
			return wetMix;
			break;
	}
}


void DelayAudioProcessor::setParameter(int index, float newValue) 
{
	// Set parameter values - For when sliders are moved
	switch (index) {
		case delayTimeParam:
			delayTime = newValue;
			break;
		case feedbackParam:
			feedback = newValue;
			break;
		case dryMixParam:
			dryMix = newValue;
			break;
		case wetMixParam:
			wetMix = newValue;
			break;
	}
}

//==============================================================================
void DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	delayBufferSize = (int) 2.0 * sampleRate; // Max delay of 2 seconds

	delayBuffer.setSize(2, delayBufferSize);
	delayBuffer.clear();
	
	// Calculating Delay Buffer Pointer differences
	delayBufferReadPointer = (delayBufferWritePointer - delayTime * getSampleRate());
	while (delayBufferReadPointer < 0)
	{
		delayBufferReadPointer += delayBufferSize;
	}
	
}

void DelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numberOfSamples = buffer.getNumSamples();

	int dpr, dpw;

    // In case we have more outputs than inputs, this code clears any output        
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing..
    for (int channel = 0; channel < totalNumOutputChannels ; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
		float* delayData = delayBuffer.getWritePointer(channel);

		// Temp variables to use in processing loop
		dpr = delayBufferReadPointer;
		dpw = delayBufferWritePointer;
		
		// Calculating Delay Buffer Pointer differences
		delayBufferReadPointer = (delayBufferWritePointer - delayTime * getSampleRate());
		while (delayBufferReadPointer < 0)
		{
			delayBufferReadPointer += delayBufferSize;
		}


        // ..do something to the data... 
		for (int i = 0; i < numberOfSamples; ++i) {
				
			const float in = channelData[i];
			float out = 0.0;

			// Write into delay buffer
			delayData[dpw] = in + delayData[dpr] * feedback;

			// Calculate output
			out = in * dryMix + delayData[dpr] * wetMix;

			// Set output
			channelData[i] = out;
			
			// Loop delay buffer
			if (++dpr >= delayBufferSize)
				dpr -= delayBufferSize;
			if (++dpw >= delayBufferSize)
				dpw -= delayBufferSize;
		}
    }
	delayBufferReadPointer = dpr;
	delayBufferWritePointer = dpw;
}

//==============================================================================
bool DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayAudioProcessor::createEditor()
{
    return new DelayAudioProcessorEditor (*this);
}

//==============================================================================
void DelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	// Create XML
	XmlElement xml("DelaySettings");

	//Add attributes
	xml.setAttribute("delayTime", (float)delayTime);
	xml.setAttribute("feedback", (float)feedback);
	xml.setAttribute("dryMix", (float)dryMix);
	xml.setAttribute("wetMix", (float)wetMix);

	// Store paramaters
	for (auto* param : getParameters())
		if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
			xml.setAttribute(p->paramID, p->getValue());

	//Store as binary and return
	copyXmlToBinary(xml, destData);

}

void DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// Retrieve XLM from binary 
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	// Retrieve settings
	if (xmlState != nullptr)
		if (xmlState->hasTagName("DelaySettings"))
		{
			delayTime = xmlState->getDoubleAttribute("delayTime", 1.0);
			feedback = xmlState->getDoubleAttribute("feedback", 1.0);
			dryMix = xmlState->getDoubleAttribute("dryMix", 1.0);
			wetMix = xmlState->getDoubleAttribute("wetMix", 1.0);

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
    return new DelayAudioProcessor();
}
