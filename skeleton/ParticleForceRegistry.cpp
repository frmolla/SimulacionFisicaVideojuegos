#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = begin(); it != end(); ++it) {
		it->first->updateForce(it->second);
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {

}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {

}

void ParticleForceRegistry::deleteForceRegistry() {

}
