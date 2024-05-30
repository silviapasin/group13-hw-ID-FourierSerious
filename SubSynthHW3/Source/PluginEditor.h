/*
  ==============================================================================

    PluginEditor.h
    Base class for the component that acts as the GUI for the AudioProcessor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"


class SubSynthAudioProcessorEditor  :   public juce::AudioProcessorEditor,
                                        private juce::OSCReceiver,
                                        private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    SubSynthAudioProcessorEditor (SubSynthAudioProcessor&);
    ~SubSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //reference to the AudioProcessor
    SubSynthAudioProcessor& audioProcessor;
    OscComponent osc; //oscillator component of the GUI
    AdsrComponent adsr; //amplitude envelope component of the GUI
    FilterComponent filter; //filter component of the GUI
    AdsrComponent filterAdsr; //filter envelope component of the GUI
    
    juce::OSCSender sender;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubSynthAudioProcessorEditor)
    
    void oscMessageReceived (const juce::OSCMessage& message) override;
    
    void showConnectionErrorMessage (const juce::String& messageText);
};
