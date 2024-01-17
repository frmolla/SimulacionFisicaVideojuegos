#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator();
	ParticleDragGenerator(const float k1, const float k2, Vector3 airVelocity);
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }
	inline void setVel(Vector3 v) { _airVelocity = v; }
protected:
	float _k1;
	float _k2;
	Vector3 _airVelocity = Vector3(0,0,0);
};

