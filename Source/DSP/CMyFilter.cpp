#pragma once;
#include <math.h>
#include <algorithm>

#define SAMPLE_RATE 96000.0f //set maximum frequency. 96khz

// --------------------------------------------------------------------------------
// CMyFilter
// --------------------------------------------------------------------------------
class CMyFilter
{
private:
	float a0, a1, a2, b0, b1, b2;

	float out1, out2;
	float in1, in2;

	inline void LowPass(float freq, float q, float samplerate);
	inline void HighPass(float freq, float q, float samplerate);
	inline void BandPass(float freq, float bw, float samplerate);
	inline void Notch(float freq, float bw, float samplerate);
	inline void LowShelf(float freq, float q, float gain, float samplerate);
	inline void HighShelf(float freq, float q, float gain, float samplerate);
	inline void Peaking(float freq, float bw, float gain, float samplerate);
	inline void AllPass(float freq, float q, float samplerate);
    
public:
	inline CMyFilter();

	inline float Process(float in);
	inline void ClockProcess(float* inL, float* inR);
	inline void SetFilter(int mode, float freq, float bw, float samplerate, float gain = 1.0f);

	enum FilterType { LP = 0, HP, BP, N, LoSh, HiSh, Peak, AP};
};

// --------------------------------------------------------------------------------
//
// --------------------------------------------------------------------------------
CMyFilter::CMyFilter()
{
	a0 = 1.0f;
	a1 = 0.0f;
	a2 = 0.0f;
	b0 = 1.0f;
	b1 = 0.0f;
	b2 = 0.0f;

	in1 = 0.0f;
	in2 = 0.0f;

	out1 = 0.0f;
	out2 = 0.0f;
}



// --------------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------------
float CMyFilter::Process(float in)
{
	float out = b0 / a0 * in + b1 / a0 * in1 + b2 / a0 * in2
		- a1 / a0 * out1 - a2 / a0 * out2;

	in2 = in1;
	in1 = in;

	out2 = out1;
	out1 = out;

	return out;
}

void CMyFilter::ClockProcess(float* LeftSample, float* RightSample)
{
	*LeftSample = Process(*LeftSample);
	*RightSample = Process(*RightSample);
}

void CMyFilter::SetFilter(int mode, float freq, float bw, float samplerate, float gain)
{
	freq = freq / 2.0f; //ex.200kHz -> 100kHz

    switch (mode)
	{
	case 0:
		LowPass(freq, bw, samplerate);
		break;
	case 1:
		HighPass(freq, bw, samplerate);
		break;
	case 2:
		BandPass(freq, bw, samplerate);
		break;
	case 3:
		Notch(freq, bw, samplerate);
		break;
	case 4:
		LowShelf(freq, bw, gain, samplerate);
		break;
	case 5:
		HighShelf(freq, bw, gain, samplerate);
		break;
	case 6:
		Peaking(freq, bw, gain, samplerate);
		break;
	case 7:	
		AllPass(freq, bw, samplerate);
		break;
	}
}
// --------------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------------
void CMyFilter::LowPass(float freq, float q, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f - cos(omega)) / 2.0f;
	b1 = 1.0f - cos(omega);
	b2 = (1.0f - cos(omega)) / 2.0f;
}

void CMyFilter::HighPass(float freq, float q, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f + cos(omega)) / 2.0f;
	b1 = -(1.0f + cos(omega));
	b2 = (1.0f + cos(omega)) / 2.0f;
}

void CMyFilter::BandPass(float freq, float bw, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = alpha;
	b1 = 0.0f;
	b2 = -alpha;
}

void CMyFilter::Notch(float freq, float bw, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f;
}

void CMyFilter::LowShelf(float freq, float q, float gain, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	a0 = (A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega));
}

void CMyFilter::HighShelf(float freq, float q, float gain, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	a0 = (A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega));
}

void CMyFilter::Peaking(float freq, float bw, float gain, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
	float A = pow(10.0f, (gain / 40.0f));

	a0 = 1.0f + alpha / A;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha / A;
	b0 = 1.0f + alpha * A;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f - alpha * A;
}

void CMyFilter::AllPass(float freq, float q, float samplerate)
{
	float omega = 2.0f * 3.14159265f *  freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f - alpha;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f + alpha;
}