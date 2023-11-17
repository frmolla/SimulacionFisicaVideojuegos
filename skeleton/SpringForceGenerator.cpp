#include "SpringForceGenerator.h"
#include <iostream>

SpringForceGenerator::SpringForceGenerator(float k, float x0, Particle* p) {
	_k = k;
	_x0 = x0;
	other = p;
}

void SpringForceGenerator::updateForce(Particle* particle, double t) {
	// Check that the partivle has Finite Mass
	if (fabs(particle->getInvM() < 1e-10))
		return;

	Vector3 force = -_k * (other->getPosition().p - particle->getPosition().p);
	particle->addForce(force);
}

