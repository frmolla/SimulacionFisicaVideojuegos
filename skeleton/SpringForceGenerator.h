#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
protected:
	float _k;
	float _x0;
	Particle* other;
public:
	SpringForceGenerator(float k, float x0, Particle* p);
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) { _k = k; }
	inline float getK() { return _k; }
	virtual ~SpringForceGenerator() {}
};

