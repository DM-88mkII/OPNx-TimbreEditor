#pragma once
// By Martin Finke
// https://www.martin-finke.de/articles/audio-plugins-013-filter/



class Filter {
public:
	enum FilterMode {
		FILTER_MODE_NONE,//add
		FILTER_MODE_LOWPASS,// = 0,
		FILTER_MODE_HIGHPASS,
		FILTER_MODE_BANDPASS,
		kNumFilterModes
	};
	Filter() :
	cutoff(0.99),
	resonance(0.0),
	mode(FILTER_MODE_NONE),
	buf0(0.0),
	buf1(0.0),
	buf2(0.0),
	buf3(0.0),
	lastIn{0},
	lastOut{0},
	cutoffMod(0.0)
	{
		calculateFeedbackAmount();
	};
	double process(double inputValue);
	inline void setCutoff(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
	inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
	inline void setFilterMode(FilterMode newMode) { mode = newMode; }
	inline void setCutoffMod(double newCutoffMod) {
		cutoffMod = newCutoffMod;
		calculateFeedbackAmount();
	}
	inline void calculateFeedbackAmount() {
		feedbackAmount = resonance + resonance / (1.0 - getCalculatedCutoff());
	}
	inline double getCalculatedCutoff() const {
		return fmax(fmin(cutoff + cutoffMod, 0.99), 0.01);
	};
	inline void setDCCut(bool newDCCut) { DCCut = newDCCut; }
	inline void setDCCutRate(double newDCCutRate) { DCCutRate = newDCCutRate; }
private:
	double cutoff;
	double resonance;
	FilterMode mode;
	double feedbackAmount;
	double buf0;
	double buf1;
	double buf2;
	double buf3;
	double lastIn;
	double lastOut;
	double cutoffMod;
	bool DCCut;
	double DCCutRate;
};
