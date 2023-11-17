#include "WhirlwindForceGenerator.h"
#include <iostream>

WhirlwindForceGenerator::WhirlwindForceGenerator(const float k1, const float k2, Vector3 airVelocity, const float k, float r, Vector3 o) 
	: ForceGenerator() {
	_k = k;
	_r = r;
	ori = o;
}

void WhirlwindForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 v;

	v.x = -(particle->getPosition().p.z - ori.z);
	v.y = (50 - (particle->getPosition().p.y - ori.y));
	v.z = ((particle->getPosition().p.x - ori.x));

	particle->addForce(_k*v);
}


