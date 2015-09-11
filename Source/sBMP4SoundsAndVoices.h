/*
==============================================================================
sBMP4: kilker subtractive synth!

Copyright (C) 2014  BMP4

Developer: Vincent Berthiaume

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
==============================================================================
*/

#ifndef sBMP4_Sounds_h
#define sBMP4_Sounds_h

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
//Synth sounds

class SineWaveSound : public SynthesiserSound
{
public:
	SineWaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override  { return true; }
	bool appliesToChannel(int /*midiChannel*/) override  { return true; }
};

class SquareWaveSound : public SynthesiserSound
{
public:
	SquareWaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override  { return true; }
	bool appliesToChannel(int /*midiChannel*/) override  { return true; }
};

class TriangleWaveSound : public SynthesiserSound
{
public:
	TriangleWaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override  { return true; }
	bool appliesToChannel(int /*midiChannel*/) override  { return true; }
};

class SawtoothWaveSound : public SynthesiserSound
{
public:
	SawtoothWaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override  { return true; }
	bool appliesToChannel(int /*midiChannel*/) override  { return true; }
};


class Bmp4SynthVoice : public SynthesiserVoice
{
public:
	Bmp4SynthVoice();

	// this is where we determine which unique sound this voice can play
	bool canPlaySound(SynthesiserSound* sound) = 0;

	virtual float getSample(double dTail) = 0;

	void renderNextBlock(AudioSampleBuffer& p_oOutputBuffer, int p_iStartSample, int p_iTotalSamples) override;

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;

	void stopNote(float /*velocity*/, bool allowTailOff) override;

	void pitchWheelMoved(int /*newValue*/) override {
		// can't be bothered implementing this for the demo!
	}

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override {
		// not interested in controllers in this case.
	}

protected:
	double m_dCurrentAngle, m_dOmega, m_dLevel, m_dTailOff;
	SynthesiserSound* m_oCurrentSynthSound;
};

class SineWaveVoice : public Bmp4SynthVoice{
public:
    SineWaveVoice();
protected:
	virtual bool canPlaySound(SynthesiserSound* sound) override;
	virtual float getSample(double dTail) override;
    int m_iK;
};

class SquareWaveVoice : public Bmp4SynthVoice{
public:
	SquareWaveVoice();
protected:
	bool canPlaySound(SynthesiserSound* sound) override;

	virtual float getSample(double dTail);

	int m_iK;
};

class TriangleWaveVoice : public SquareWaveVoice
{
	virtual bool canPlaySound(SynthesiserSound* sound) override;

	virtual float getSample(double dTail);

};

class SawtoothWaveVoice : public SquareWaveVoice
{
	virtual bool canPlaySound(SynthesiserSound* sound) override;

	virtual float getSample(double dTail);
};

#endif //sBMP4_Sounds_h