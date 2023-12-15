#pragma once
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "ForceGenerator.h"


class ParticleForceRegistry
{
private:
	std::unordered_map<ForceGenerator*, std::unordered_set<Particle*>> FaP; // fuerza a partícula
	std::unordered_map<ForceGenerator*, std::unordered_set<RigidBody*>> FaRB; // fuerza a rb
	std::unordered_map<Particle*, std::unordered_set<ForceGenerator*>> PaF;	// partícula a fuerza
	std::unordered_map<RigidBody*, std::unordered_set<ForceGenerator*>> RBaF;	// rb a fuerza
public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fg, Particle* p);
	void addRegistry(ForceGenerator* fg, RigidBody* p);

	void deleteParticleRegistry(Particle* p);
	void deleteParticleRegistry(RigidBody* p);

	void deleteParticleForceRegistry(ForceGenerator* fg, Particle* p);
	void deleteParticleForceRegistry(ForceGenerator* fg, RigidBody* p);

	void deleteForceRegistry(ForceGenerator* fg);
};

