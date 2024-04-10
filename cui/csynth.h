#ifndef CSYNTH
#define CSYNTH

#include <vector>
#include "olcNoiseMaker.h"

struct Note
{
	int id; // position in scale
	double on;
	double off;
	bool active;
	int channel;

	Note()
	{
		id = 0;
		on = 0.0;
		off = 0.0;
		active = false;
		channel = 0;
	}
};

const enum oscillatorType {
	SINE,
	SQUARE,
	TRIANGLE,
	SAW_ANALOG,
	SAW_DIGITAL,
	WHITE_NOISE,
	PULSE,
	UNDERWATER,
	DARK_HALLWAY
};

class Oscillator {
public:
	double w(const double dHertz);
	double LFO(const double dTime, const int nLFOType, const double dLFOHertz);
	double osc(const double dTime, const double dHertz, const int nType,
		const double dLFOHertz, const double dLFOAmplitude, const int nLFOType );
};


class Envelope {
public:
	virtual double amplitude(const double dTime, const double dTimeOn, const double dTimeOff) = 0;
};

class Envelope_ADSR : public Envelope {
public:
	Envelope_ADSR();
	virtual double amplitude(const double dTime, const double dTimeOn, const double dTimeOff);
	double getAmplitude(const double dTime, const double dTimeOn, const double dTimeOff);
	double getAttackTime();
	double getDecayTime();
	double getSustainAmplitude();
	double getReleaseTime();
	double getStartAmplitude();
	void setAttackTime(double);
	void setDecayTime(double);
	void setSustainAmplitude(double);
	void setReleaseTime(double);
	void setStartAmplitude(double);
private:
	double dAttackTime;
	double dDecayTime;
	double dSustainAmplitude;
	double dReleaseTime;
	double dStartAmplitude;
};


class Instrument {
public:

	Instrument();
	double sound(const double dTime, Note n, bool& bNoteFinished);
	double scale(const int nNoteID, const int nScaleID);

	void setActive(int nOscillatorID, bool bActive);
	bool getActive(int nOscillatorID);
	void setOscillatorType(int nOscillatorID, oscillatorType nType);
	oscillatorType getOscillatorType(int nOscillatorID);
	void setTranspose(int nOscillatorID, int nTranspose);
	int getTranspose(int nOscillatorID);
	void setVolume(int nOscillatorID, double dVolume);
	double getVolume(int nOscillatorID);
	void setLFOHertz(int nOscillatorID, double dLFOHertz);
	double getLFOHertz(int nOscillatorID);
	void setLFOAmplitude(int nOscillatorID, double dLFOAmplitude);
	double getLFOAmplitude(int nOscillatorId);
	void setDetune(int nOscillatorID, double dDetune);
	double getDetune(int nOscillatorID);
	void setLFOType(int nOscillatorID, int nLFOType);
	int getLFOType(int nOscillatorID);
	void setName(string sName);
	string getName();

	Envelope_ADSR env1;
	Envelope_ADSR env2;
	Envelope_ADSR env3;

private:
	double dVolume;
	string sName;
	Oscillator osc1, osc2, osc3;
	bool vecActiveOsc[3];
	oscillatorType vecTypeOsc[3];
	double vecVolumeOsc[3];
	int vecTransposeOsc[3];
	double vecLFOHertz[3];
	double vecLFOAmplitude[3];
	double vecDetuneOsc[3];
	int vecLFOType[3];
};


#endif