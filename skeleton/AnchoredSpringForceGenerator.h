#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGenerator : public SpringForceGenerator
{
public:
	AnchoredSpringForceGenerator(float k, float x0, Particle* p);
	virtual void updateForce(Particle* particle, double t);
};

