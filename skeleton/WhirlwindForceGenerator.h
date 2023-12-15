#pragma once
#include "ParticleDragGenerator.h"

class WhirlwindForceGenerator : public ParticleDragGenerator
{
private:
	float _k;
	float _r;
	Vector3 ori;
public:
	WhirlwindForceGenerator();
	WhirlwindForceGenerator(const float k1, const float k2, Vector3 airVelocity, const float k, float r, Vector3 o = Vector3(0, 0, 0));
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* particle, double t);
};

