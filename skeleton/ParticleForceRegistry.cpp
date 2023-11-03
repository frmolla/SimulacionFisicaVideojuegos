#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = FaP.begin(); it != FaP.end(); ++it) {
		for (auto it2 = FaP[it->first].begin(); it2 != FaP[it->first].end(); ++it2) {
			it->first->updateForce((*it2));
		}
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	FaP[fg].insert(p);
	PaF[p].insert(fg);
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	for (auto it = FaP.begin(); it != FaP.end(); ++it) {
		if (FaP[it->first].find(p) != FaP[it->first].end()) {
			FaP[it->first].erase(p);
			PaF[p].erase(it->first);
		}
	}
}

void ParticleForceRegistry::deleteForceRegistry() {

}
