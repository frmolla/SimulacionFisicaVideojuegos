#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) {

}

void GravityForceGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvM() < 1e-10))
		return;

	// aqui deberia ser la masa
	particle->addForce(_gravity * 1/particle->getInvM());
}
