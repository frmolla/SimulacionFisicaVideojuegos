#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double duration) {
	for (auto it = FaP.begin(); it != FaP.end(); ++it) {
		for (auto it2 = FaP[it->first].begin(); it2 != FaP[it->first].end(); ++it2) {
			it->first->updateForce((*it2), duration);
		}
	}

	for (auto it = FaRB.begin(); it != FaRB.end(); ++it) {
		for (auto it2 = FaRB[it->first].begin(); it2 != FaRB[it->first].end(); ++it2) {
			it->first->updateForce((*it2), duration);
		}
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p) {
	FaP[fg].insert(p);
	PaF[p].insert(fg);
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, RigidBody* p) {
	FaRB[fg].insert(p);
	RBaF[p].insert(fg);
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	for (auto it = FaP.begin(); it != FaP.end(); ++it) {
		if (FaP[it->first].find(p) != FaP[it->first].end()) {
			FaP[it->first].erase(p);
			PaF[p].erase(it->first);
		}
	}
}

void ParticleForceRegistry::deleteParticleRegistry(RigidBody* p) {
	for (auto it = FaP.begin(); it != FaP.end(); ++it) {
		if (FaRB[it->first].find(p) != FaRB[it->first].end()) {
			FaRB[it->first].erase(p);
			RBaF[p].erase(it->first);
		}
	}
}

void ParticleForceRegistry::deleteParticleForceRegistry(ForceGenerator* fg, Particle* p) {
	if (FaP[fg].find(p) != FaP[fg].end()) {
		FaP[fg].erase(p);
		PaF[p].erase(fg);
	}
}

void ParticleForceRegistry::deleteParticleForceRegistry(ForceGenerator* fg, RigidBody* p) {
	if (FaRB[fg].find(p) != FaRB[fg].end()) {
		FaRB[fg].erase(p);
		RBaF[p].erase(fg);
	}
}

void ParticleForceRegistry::deleteForceRegistry(ForceGenerator* fg) {

}
