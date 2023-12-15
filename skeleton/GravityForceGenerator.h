#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g);

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(RigidBody* particle, double t) {}

	inline void setGravity(Vector3 g) { _gravity = g; }
	inline Vector3 getGravity() { return _gravity; }
protected:
	Vector3 _gravity;
};

