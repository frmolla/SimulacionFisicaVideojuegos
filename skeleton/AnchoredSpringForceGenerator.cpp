#include "AnchoredSpringForceGenerator.h"
#include <iostream>

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float k, float x0, Particle* p) 
	: SpringForceGenerator(k,x0,p) { }

void AnchoredSpringForceGenerator::updateForce(Particle* particle, double t) {
	// Check that the partivle has Finite Mass
	if (fabs(particle->getInvM() < 1e-10))
		return;

	Vector3 force = -_k * (other->getPosition().p - particle->getPosition().p);
	particle->addForce(force);
}

