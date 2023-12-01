#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGenerator : public SpringForceGenerator
{
public:
	AnchoredSpringForceGenerator(float k, float x0, Vector3 anchor_pos);
	virtual void updateForce(Particle* particle, double t);
};

