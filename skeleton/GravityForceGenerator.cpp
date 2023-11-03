#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) {
	_gravity = g;
}

void GravityForceGenerator::updateForce(Particle* particle) {
	if (fabs(particle->getInvM() < 1e-10))
		return;

	// aqui deberia ser la masa
	particle->addForce(_gravity * 1/particle->getInvM());
}
