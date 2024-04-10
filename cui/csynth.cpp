#include "csynth.h"

using namespace std;

double Oscillator::w(const double dHertz)
{
	return dHertz * 2.0 * PI;
}

double Oscillator::LFO(const double dTime, const int nLFOType = SINE, const double dLFOHertz = 0.0) {
	switch (nLFOType) {
	case SINE: default:
		return sin(w(dLFOHertz) * dTime);
	case SAW_DIGITAL:
		return atan(tan(w(dLFOHertz) * dTime)) * (2.0 / PI);
	}
}

double Oscillator::osc(const double dTime, const double dHertz, const int nType = SINE,
	const double dLFOHertz = 0.0, const double dLFOAmplitude = 0.0, const int nLFOType = SINE)
{

	double dFreq = w(dHertz) * dTime + dLFOAmplitude * dHertz * LFO(dTime, nLFOType, dLFOHertz);
	//y = sin(note + LFO)

	switch (nType)
	{
	case SINE:
		return sin(dFreq);

	case SQUARE:
		return sin(dFreq) > 0 ? 1.0 : -1.0;

	case TRIANGLE:
		return asin(sin(dFreq)) * (2.0 / PI);

	case SAW_ANALOG:
	{
		double dOutput = 0.0;
		for (double n = 1.0; n < 100.0; n++) {
			dOutput += (sin(n * dFreq)) / n;
		}
		return dOutput * (2.0 / PI);
	}

	case SAW_DIGITAL:
		return atan(tan(dFreq)) * (2.0 / PI);

	case WHITE_NOISE:
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;

	case PULSE:
	{
		double dOutput = 0.0;
		double cOutput = PI / 2.0;
		for (double n = 1.0; n < 100.0; n++) {
			dOutput += (sin(n * dFreq)) / n;
			cOutput += (sin(n * dFreq)) / n;
		}
		return dOutput - cOutput * (2.0 / PI);
	}

	case UNDERWATER:
	{
		double dOutput = 0.0;
		for (double n = 1.0; n < 100.0; n++) {
			dOutput += sin(cos(n) * dFreq) / n;
		}
		return dOutput * (2.0 / PI); 
	}

	case DARK_HALLWAY:
	{
		double dOutput = 0.0;
		for (double n = 1.0; n < 100.0; n++) {
			dOutput += sin(tan(n) * dFreq) / n;
		}
		return dOutput * (2.0 / PI);
	}

	default:
		return 0.0;
	}
}

Envelope_ADSR::Envelope_ADSR()
{
	dAttackTime = 0.1;
	dDecayTime = 0.1;
	dSustainAmplitude = 1.0;
	dReleaseTime = 0.2;
	dStartAmplitude = 1.0;
}

double Envelope_ADSR::amplitude(const double dTime, const double dTimeOn, const double dTimeOff)
{
	double dAmplitude = 0.0;
	double dReleaseAmplitude = 0.0;

	if (dTimeOn > dTimeOff) // Note is on
	{
		double dLifeTime = dTime - dTimeOn;

		if (dLifeTime <= dAttackTime)
			dAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;

		if (dLifeTime > dAttackTime && dLifeTime <= (dAttackTime + dDecayTime))
			dAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;

		if (dLifeTime > (dAttackTime + dDecayTime))
			dAmplitude = dSustainAmplitude;
	}
	else // Note is off
	{
		double dLifeTime = dTimeOff - dTimeOn;

		if (dLifeTime <= dAttackTime)
			dReleaseAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;

		if (dLifeTime > dAttackTime && dLifeTime <= (dAttackTime + dDecayTime))
			dReleaseAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;

		if (dLifeTime > (dAttackTime + dDecayTime))
			dReleaseAmplitude = dSustainAmplitude;

		dAmplitude = ((dTime - dTimeOff) / dReleaseTime) * (0.0 - dReleaseAmplitude) + dReleaseAmplitude;
	}

	if (dAmplitude <= 0.000)
		dAmplitude = 0.0;

	return dAmplitude;
}

double Envelope_ADSR::getAmplitude(const double dTime, const double dTimeOn, const double dTimeOff)
{
	return amplitude(dTime, dTimeOn, dTimeOff);
}

double Envelope_ADSR::getAttackTime() { return dAttackTime; }
double Envelope_ADSR::getDecayTime() { return dDecayTime; }
double Envelope_ADSR::getSustainAmplitude() { return dSustainAmplitude; }
double Envelope_ADSR::getReleaseTime() { return dReleaseTime; }
double Envelope_ADSR::getStartAmplitude() { return dStartAmplitude; }
void Envelope_ADSR::setAttackTime(double d) { dAttackTime = d; };
void Envelope_ADSR::setDecayTime(double d) { dDecayTime = d; };
void Envelope_ADSR::setSustainAmplitude(double d) { dSustainAmplitude = d; };
void Envelope_ADSR::setReleaseTime(double d) { dReleaseTime = d; };
void Envelope_ADSR::setStartAmplitude(double d) { dStartAmplitude = d; };

double Instrument::scale(const int nNoteID, const int nScaleID = 0)
{
	switch (nScaleID)
	{
	case 0: default:
		return 32 * pow(1.0594630943592952645618252949463, nNoteID); //twelfth root two
	}
}

Instrument::Instrument() {
	env1.setAttackTime(0.05);
	env1.setDecayTime(1.0);
	env1.setSustainAmplitude(0.95);
	env1.setReleaseTime(0.1);

	env2.setAttackTime(0.05);
	env2.setDecayTime(1.0);
	env2.setSustainAmplitude(0.95);
	env2.setReleaseTime(0.1);

	env3.setAttackTime(0.05);
	env3.setDecayTime(1.0);
	env3.setSustainAmplitude(0.95);
	env3.setReleaseTime(0.1);

	dVolume = 1.0;
	for (int n : vecVolumeOsc) { n = 1.00; }
	for (bool b : vecActiveOsc) { b = true; }
	for (oscillatorType t : vecTypeOsc) { t = SINE; }
	for (int n : vecTransposeOsc) { n = 0; }
	for (double d : vecLFOHertz) { d = 0.0; }
	for (double d : vecLFOAmplitude) { d = 0.0; }
	for (double d : vecDetuneOsc) { d = 0.0; }
	for (int n : vecLFOType) { n = 0; }
}

double Instrument::sound(const double dTime, Note n, bool& bNoteFinished) {
	double dAmplitude1 = env1.getAmplitude(dTime, n.on, n.off);
	double dAmplitude2 = env2.getAmplitude(dTime, n.on, n.off);
	double dAmplitude3 = env3.getAmplitude(dTime, n.on, n.off);

	if (dAmplitude1 <= 0.0) bNoteFinished = true;

	double dSound =
		+ dAmplitude1 * vecActiveOsc[0] * vecVolumeOsc[0] * osc1.osc(n.on - dTime, scale(n.id + vecDetuneOsc[0] + vecTransposeOsc[0]), vecTypeOsc[0], vecLFOHertz[0], vecLFOAmplitude[0], vecLFOType[0])
		+ dAmplitude2 * vecActiveOsc[1] * vecVolumeOsc[1] * osc2.osc(n.on - dTime, scale(n.id + vecDetuneOsc[1] + vecTransposeOsc[1]), vecTypeOsc[1], vecLFOHertz[1], vecLFOAmplitude[1], vecLFOType[1])
		+ dAmplitude3 * vecActiveOsc[2] * vecVolumeOsc[2] * osc3.osc(n.on - dTime, scale(n.id + vecDetuneOsc[2] + vecTransposeOsc[2]), vecTypeOsc[2], vecLFOHertz[2], vecLFOAmplitude[2], vecLFOType[2]);

	return dSound * dVolume;
}

void Instrument::setActive(int nOscillatorID, bool bActive) {
	vecActiveOsc[nOscillatorID] = bActive;
}
bool Instrument::getActive(int nOscillatorID) { return vecActiveOsc[nOscillatorID]; }

void Instrument::setOscillatorType(int nOscillatorID, oscillatorType nType) {
	vecTypeOsc[nOscillatorID] = nType;
}
oscillatorType Instrument::getOscillatorType(int nOscillatorID) { return vecTypeOsc[nOscillatorID]; }

void Instrument::setTranspose(int nOscillatorID, int nTranspose) {
	vecTransposeOsc[nOscillatorID] = nTranspose;
}
int Instrument::getTranspose(int nOscillatorID) { return vecTransposeOsc[nOscillatorID]; }

void Instrument::setName(string sName) { this->sName = sName; }
string Instrument::getName() { return sName; }

void Instrument::setVolume(int nOscillatorID, double dVolume) {
	vecVolumeOsc[nOscillatorID] = dVolume;
}
double Instrument::getVolume(int nOscillatorID) { return vecVolumeOsc[nOscillatorID]; }

void Instrument::setLFOHertz(int nOscillatorID, double dLFOHertz) {
	vecLFOHertz[nOscillatorID] = dLFOHertz;
}
double Instrument::getLFOHertz(int nOscillatorID) { return vecLFOHertz[nOscillatorID]; }

void Instrument::setLFOAmplitude(int nOscillatorID, double dLFOAmplitude) {
	vecLFOAmplitude[nOscillatorID] = dLFOAmplitude;
}

double Instrument::getLFOAmplitude(int nOscillatorID) { return vecLFOAmplitude[nOscillatorID]; }

void Instrument::setDetune(int nOscillatorID, double dDetune) {
	vecDetuneOsc[nOscillatorID] = dDetune;
}

double Instrument::getDetune(int nOscillatorID) { return vecDetuneOsc[nOscillatorID]; }

void Instrument::setLFOType(int nOscillatorID, int nLFOType) {
	vecLFOType[nOscillatorID] = nLFOType;
}

int Instrument::getLFOType(int nOscillatorID) { return vecLFOType[nOscillatorID]; }
