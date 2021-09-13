/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestjuceAudioProcessorEditor::TestjuceAudioProcessorEditor(TestjuceAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    mLoadButton.onClick = [&]() {audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadButton);

    //AttackSlider
    mAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    mAttackSlider.setRange(0.0f, 5.0f, 0.01f);
    mAttackSlider.addListener(this);
    addAndMakeVisible(mAttackSlider);

    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack", NotificationType::dontSendNotification);
    mAttackLabel.setColour(Label::ColourIds::textColourId, Colours::green);
    mAttackLabel.setJustificationType(Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);

    //DecaySlider
    mDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    mDecaySlider.setRange(0.0f, 5.0f, 0.01f);
    mDecaySlider.addListener(this);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Decay", NotificationType::dontSendNotification);
    mDecayLabel.setColour(Label::ColourIds::textColourId, Colours::green);
    mDecayLabel.setJustificationType(Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

    //SustainSlider
    mSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    mSustainSlider.setRange(0.0f, 1.0f, 0.01f);
    mSustainSlider.addListener(this);
    addAndMakeVisible(mSustainSlider);

    mSustainLable.setFont(10.0f);
    mSustainLable.setText("Sustain", NotificationType::dontSendNotification);
    mSustainLable.setColour(Label::ColourIds::textColourId, Colours::green);
    mSustainLable.setJustificationType(Justification::centredTop);
    mSustainLable.attachToComponent(&mSustainSlider, false);

    //RealeaseSlider
    mRealeaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mRealeaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    mRealeaseSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    mRealeaseSlider.setRange(0.0f, 5.0f, 0.01f);
    mRealeaseSlider.addListener(this);
    addAndMakeVisible(mRealeaseSlider);

    mRealeaseLabel.setFont(10.0f);
    mRealeaseLabel.setText("Realease", NotificationType::dontSendNotification);
    mRealeaseLabel.setColour(Label::ColourIds::textColourId, Colours::green);
    mRealeaseLabel.setJustificationType(Justification::centredTop);
    mRealeaseLabel.attachToComponent(&mRealeaseSlider, false);


    setSize(600, 200);
}

TestjuceAudioProcessorEditor::~TestjuceAudioProcessorEditor()
{
}

//==============================================================================
void TestjuceAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(Colours::black);
    g.setColour(Colours::white);

    if (mShouldBePainting) {
        Path p;
        mAudioPoints.clear();

        auto waveform = audioProcessor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        //scale audio file to window on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio) {
            mAudioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0, getHeight() / 2);

        //scale on y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample) {
            auto point = jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, point);
        }

        g.strokePath(p, PathStrokeType(2));

        mShouldBePainting = false;
    }
    //g.setColour(Colours::white);
    //g.setFont(15.f);
    //if (audioProcessor.getNumSamplerSounds() > 0) {
    //    g.fillAll(Colours::red);
    //    g.setColour(Colours::white);
    //    g.setFont(15.f);
    //    g.drawText("Sound loaded", getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 20, Justification::centred);
    //}
    //else
    //    g.drawText("Loading a sound", getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 20, Justification::centred);

}

void TestjuceAudioProcessorEditor::resized()
{
    const auto startX = 0.3f;
    const auto startY = 0.6f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.4f;
    //mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + 2 * dialWidth, startY, dialWidth, dialHeight);
    mRealeaseSlider.setBoundsRelative(startX + 3 * dialWidth, startY, dialWidth, dialHeight);

}

bool TestjuceAudioProcessorEditor::isInterestedInFileDrag(const StringArray& files) {
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
            return true;
    }
    return false;
}
void TestjuceAudioProcessorEditor::filesDropped(const StringArray& files, int x, int y) {
    for (auto file : files) {
        if (isInterestedInFileDrag(file)) {
            mShouldBePainting = true;
            audioProcessor.loadFile(file);
        }
    }
    repaint();
}

void TestjuceAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &mAttackSlider) {
        audioProcessor.getADRS().attack = mAttackSlider.getValue();
    }
    else if (slider == &mDecaySlider) {
        audioProcessor.getADRS().decay = mDecaySlider.getValue();
    }
    else if (slider == &mSustainSlider) {
        audioProcessor.getADRS().sustain = mSustainSlider.getValue();
    }
    else if (slider == &mRealeaseSlider) {
        audioProcessor.getADRS().release = mRealeaseSlider.getValue();
    }

    audioProcessor.updateADSRValue();
}