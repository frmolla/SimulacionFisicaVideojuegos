#pragma once
#include "ForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float v, float d);

	virtual void updateForce(Particle* particle, double t);

	virtual ~BuoyancyForceGenerator() {};

	inline void setV(float nVolume) { _volume = nVolume; }
	inline float getV() { return _volume; }

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};