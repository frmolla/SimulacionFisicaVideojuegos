#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator
{
private:
	float _k;
	float _r;
	Vector3 ori;
	float _t = 0;
	float tE;
public:
	ExplosionForceGenerator();
	ExplosionForceGenerator(const float k, float r, Vector3 o = Vector3(0, 0, 0));
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* particle, double t);
};

