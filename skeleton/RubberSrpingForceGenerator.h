#pragma once
#include "SpringForceGenerator.h"

class RubberSrpingForceGenerator : public SpringForceGenerator
{
private:
	float _dis;
public:
	RubberSrpingForceGenerator(float k, float x0, Particle* p, float dis);
	virtual void updateForce(Particle* particle, double t);
};





