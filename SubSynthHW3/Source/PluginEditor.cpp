/*
  ==============================================================================

    PluginEditor.cpp

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SubSynthAudioProcessorEditor::SubSynthAudioProcessorEditor (SubSynthAudioProcessor& p)
    : AudioProcessorEditor (&p),
    //initialization of the data members of the Editor 
    audioProcessor (p), 
    osc (audioProcessor.apvts, "OSCWAVETYPE"),
    adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"), 
    filter (audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRES"),
    filterAdsr ("Filter Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
{
    setSize (670, 600);
    
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::rebeccapurple);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::lightgrey);
    addAndMakeVisible(osc);
    getLookAndFeel().setColour(juce::Slider::backgroundColourId, juce::Colours::rebeccapurple);
    addAndMakeVisible(osc);
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::mediumpurple);
    addAndMakeVisible(osc);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colours::rebeccapurple);
    
    //show the components
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(filter);
    
    //wave viewer
    audioProcessor.waveViewer.setColours(juce::Colour(0xff121719), juce::Colours::rebeccapurple);
    addAndMakeVisible(audioProcessor.waveViewer);
    
    
    if (! connect (7563))
        showConnectionErrorMessage ("Error in PluginEditor: could not connect to UDP port 7563.");
    
    addListener (this, "/joystick/x");
    addListener (this, "/joystick/y");
    addListener(this, "/button");
}

SubSynthAudioProcessorEditor::~SubSynthAudioProcessorEditor()
{
}

//==============================================================================
void SubSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SubSynthAudioProcessorEditor::resized()
{
    const auto padX = 5;
    const auto padY = 30;
    const auto block_height = 180;
    const auto block_width = 250;

    osc.setBounds(padX, padY, block_width, block_height);
 
    adsr.setBounds(osc.getRight() , padY , getRight() - osc.getRight() - padX, block_height);

    filter.setBounds(padX, block_height + 2 * padY - 20, block_width, block_height);
  
    filterAdsr.setBounds(filter.getRight(), block_height + 2 * padY - 20, getRight() - filter.getRight() - padX, block_height);
    
    audioProcessor.waveViewer.setBounds(3* padX, 2 * block_height + 3 * padY - 20, getLocalBounds().getRight() - 6 * padX, block_height);
}

void SubSynthAudioProcessorEditor::oscMessageReceived (const juce::OSCMessage& message)
{
    if (message.size() == 1)
    {
        if (message[0].isFloat32())
        {
            if (message.getAddressPattern() == "/joystick/x")
            {
                filter.setCutoffFreqValue(juce::jlimit (0.0f, 0.835f, message[0].getFloat32()));
                
                if (! sender.send ("/joystick/x", juce::jlimit (0.0f, 0.835f, message[0].getFloat32()))) {
                    //showConnectionErrorMessage ("Error: could not send OSC message.");
                }
                if (! sender.connect ("127.0.0.1", 8674))
                    showConnectionErrorMessage ("Error: could not connect to UDP port 8674.");
                
            } else if (message.getAddressPattern() == "/joystick/y") {
                
                float value = juce::jlimit (0.0f, 1.0f, message[0].getFloat32());
                int itemID;
                
                if (value < 0.3f)
                    itemID = 1;
                else if (value < 0.6f)
                    itemID = 2;
                else
                    itemID = 3;
                
                filter.setFilterTypeSelValue(itemID);
                
                if (! sender.send ("/joystick/y", juce::jlimit (0.0f, 1.0f, message[0].getFloat32()))) {
                    //showConnectionErrorMessage ("Error: could not send OSC message.");
                }
                if (! sender.connect ("127.0.0.1", 8674))
                    showConnectionErrorMessage ("Error: could not connect to UDP port 8674.");
            }
        } else if (message[0].isInt32() && message.getAddressPattern() == "/button") {
            
            if (message[0].getInt32() == 0 && osc.state == true)
                osc.state = false;
                
            else if (message[0].getInt32() == 1 && osc.state == false)
            {
                int itemID = osc.getOscWaveSelectorValue() % 5 + 1;
                osc.setOscWaveSelectorValue(itemID);
                osc.state = true;
                
                if (! sender.send ("/wave", itemID - 1)) {
                    //showConnectionErrorMessage ("Error: could not send OSC message.");
                }
                if (! sender.connect ("127.0.0.1", 8674))
                    showConnectionErrorMessage ("Error: could not connect to UDP port 8674.");
            }
        }
    }
}

void SubSynthAudioProcessorEditor::showConnectionErrorMessage (const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                            "Connection error",
                                            messageText,
                                            "OK");
}

