#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) {
	_gravity = g;
}

void GravityForceGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvM() < 1e-10))
		return;

	// aqui deberia ser la masa
	float masa = 1 / particle->getInvM();
	particle->addForce(_gravity * masa);
}
