/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_8972AC7388081E28__
#define __JUCE_HEADER_8972AC7388081E28__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomGUI/FilmstripSlider.h"
#include "CustomGUI/FilmstripToggleButton.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PizzaKnobFilterPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                                   private Timer,
                                                   public SliderListener,
                                                   public ButtonListener,
                                                   public ComboBoxListener
{
public:
    //==============================================================================
    PizzaKnobFilterPluginAudioProcessorEditor (PizzaKnobFilterPluginAudioProcessor& p);
    ~PizzaKnobFilterPluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
	PizzaKnobFilterPluginAudioProcessor* getProcessor() const
     { return static_cast <PizzaKnobFilterPluginAudioProcessor*>(getAudioProcessor()); }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* bg_png;
    static const int bg_pngSize;
    static const char* mark_png;
    static const int mark_pngSize;
    static const char* credit_png;
    static const int credit_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Image image_knob;
	Image image_toggle;
    PizzaKnobFilterPluginAudioProcessor& processor;
	float UserParamRanges[PizzaKnobFilterPluginAudioProcessor::Parameters::totalNumParam];
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<FilmstripSlider> Freq;
    ScopedPointer<FilmstripSlider> Q;
    ScopedPointer<FilmstripToggleButton> Toggle;
    ScopedPointer<ComboBox> ModeSelector;
    ScopedPointer<ImageButton> imageButton2;
    ScopedPointer<HyperlinkButton> hyperlinkButton;
    ScopedPointer<HyperlinkButton> hyperlinkButton2;
    ScopedPointer<ImageButton> imageButton;
    Image cachedImage_bg_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PizzaKnobFilterPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8972AC7388081E28__
