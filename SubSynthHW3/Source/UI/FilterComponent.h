/*
  ==============================================================================

    FilterComponent.h
    Class that handles the GUI component of the filter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class FilterComponent  :    public juce::Component
                            //private juce::OSCReceiver,
                            //private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterCutoffId, juce::String filterRedId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setFilterTypeSelValue(int itemID);
    void setCutoffFreqValue(float freq);

private:
    
    //slider for the cutoff frequency and the resonance
    juce::Slider filterCutoffSlider;
    juce::Slider filterResSlider;
    //object used to select the type of filter
    juce::ComboBox filterTypeSel { "Filter Type"};
    
    //attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResAttachment;

    //labels
    juce::Label filterSelectorLabel{ "Filter Type", "Filter Type" };
    juce::Label filterCutoffLabel{ "Filter Cutoff Freq", "Filter Cutoff Freq" };
    juce::Label filterResLabel{ "Filter Res", "Filter Res" };

    void setLinearSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
    
    //void oscMessageReceived (const juce::OSCMessage& message) override;
    
    //void showConnectionErrorMessage (const juce::String& messageText);
};
