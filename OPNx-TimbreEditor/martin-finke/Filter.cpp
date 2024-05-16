



#include "pch.h"
#include "Filter.h"



// By Paul Kellett
// http://www.musicdsp.org/showone.php?id=29

double Filter::process(double inputValue) {
	double in = inputValue;
	if (mode != FILTER_MODE_NONE)
	{
		double calculatedCutoff = getCalculatedCutoff();
		buf0 += calculatedCutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
		buf1 += calculatedCutoff * (buf0 - buf1);
		buf2 += calculatedCutoff * (buf1 - buf2);
		buf3 += calculatedCutoff * (buf2 - buf3);
		switch (mode) {
		case FILTER_MODE_LOWPASS:
			in = buf3;
			break;
		case FILTER_MODE_HIGHPASS:
			in = inputValue - buf3;
			break;
		case FILTER_MODE_BANDPASS:
			in = buf0 - buf3;
			break;
		}
	}
	
	//DC Cut
	if (DCCut){
		double out = in - lastIn + DCCutRate * lastOut;
		lastIn = in;
		lastOut = out;
		return out;
	} else {
		lastIn = in;
		lastOut = in;
		return in;
	}
}
