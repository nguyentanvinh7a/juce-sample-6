/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TestjuceAudioProcessorEditor : public juce::AudioProcessorEditor,
    public FileDragAndDropTarget,
    public Slider::Listener
{
public:
    TestjuceAudioProcessorEditor(TestjuceAudioProcessor&);
    ~TestjuceAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::TextButton mLoadButton{ "Load" };
    std::vector<float> mAudioPoints;
    bool mShouldBePainting = false;

    Slider mAttackSlider, mDecaySlider, mSustainSlider, mRealeaseSlider;
    Label mAttackLabel, mDecayLabel, mSustainLable, mRealeaseLabel;

    TestjuceAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestjuceAudioProcessorEditor)
};