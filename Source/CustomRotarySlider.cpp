#include "CustomRotarySlider.h"

void CustomRotarySlider::paint(juce::Graphics& g)
{
	auto startAngleRadian = degreesToRadians(180.0f + 45.0f);
	auto endAngleRadian = degreesToRadians(180.0f - 45.0f) + MathConstants<float>::twoPi;
	auto range = getRange();
	auto sliderBounds = getSliderBounds();

	g.setColour(Colours::yellow);
	//g.drawRect(sliderBounds);

	getLookAndFeel().drawRotarySlider(
		g,
		sliderBounds.getX(),
		sliderBounds.getY(),
		sliderBounds.getWidth(),
		sliderBounds.getHeight(),
		jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0),
		startAngleRadian,
		endAngleRadian,
		*this);
}

Rectangle<int> CustomRotarySlider::getSliderBounds() const
{
	return getLocalBounds();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tooltips
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CustomRotarySlider::getTooltipString()
{
	int selectedOption = (int)getValue();
	if (getName() == "Distortion")
	{
		switch ((int)selectedOption)
		{
		case Hardclip:
			return("Distortion Type : Hardclip");
			break;
		case Softclip:
			return("Distortion Type : Softclip");
			break;
		case Root:
			return("Distortion Type : Root Extraction");
			break;
		case Atan:
			return("Distortion Type : Atan");
			break;
		case Scream:
			return("Distortion Type : Scream");
			break;
		case Bitcrush:
			return("Distortion Type : Bitcrush");
			break;
		case Sine:
			return("Distortion Type : Sine");
			break;
		case Cosine:
			return("Distortion Type : Cosine");
			break;
		}
	}
	else if (getName() == "Slope")
	{
		int slope = (selectedOption + 1) * 12;
		String str;
		str << "Slope : ";
		str << slope;
		str << " db/oct";
		return(str);
	}
	else if (getName() == "Symmetry")
	{
		auto value = round(getValue() * 100);
		String str;
		str << "Symmetry : ";
		if (value == 0)
		{
			str << "Centered";
		}
		else
		{
			str << value;
			str << "%";
		}
		return str;
	}
	else if (getName() == "Analyser Type")
	{
		AnalyserType analyserType = static_cast<AnalyserType>(selectedOption);
		String str = getAnalyserName(analyserType);
		return "Analyser Type : " + str;
	}
	else if (getName() == "Lowpass" || getName() == "Highpass" || getName() == "Peak")
	{
		String str;
		str << (round(getValue() * 100)) / 100;
		return
			(String)getName() + " : " +
			str + " " +
			(String)getTextValueSuffix();
	}
	else if (getName() == "Peak Resonance")
	{
		String str;
		str << (round(getValue() * 100)) / 100;
		return
			"Resonance : " +
			str + " " +
			(String)getTextValueSuffix();
	}
	else if (getName() == "Girth")
	{
		String str;
		str << (round(getValue() * 100));
		str << "%";
		return
			(String)getName() + " : " +
			str + " " +
			(String)getTextValueSuffix();
	}
	else
	{
		String str;
		str << (round(getValue() * 100)) / 100;
		return
			(String)getName() + " : " +
			str + "" +
			(String)getTextValueSuffix();
	}
	return "";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Analyser Name
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CustomRotarySlider::getAnalyserName(AnalyserType analyserType)
{
	switch (analyserType)
	{
	case AnalyserType::Automatic:
	{
		return "Automatic";
		break;
	}
	case AnalyserType::Options:
	{
		return "Options";
		break;
	}
	case AnalyserType::Response:
	{
		return "Filter Response";
		break;
	}
	case AnalyserType::Shapercurve:
	{
		return "Shapercurve";
		break;
	}
	case AnalyserType::Waveform:
	{
		return "Waveform";
		break;
	}
	}
	return "Unknown Analyser Type";
}