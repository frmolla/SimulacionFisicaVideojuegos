#pragma once
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "ForceGenerator.h"


class ParticleForceRegistry
{
private:
	std::unordered_map<ForceGenerator*, std::unordered_set<Particle*>> FaP; // fuerza a part�cula
	std::unordered_map<Particle*, std::unordered_set<ForceGenerator*>> PaF;	// part�cula a fuerza
public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fg, Particle* p);

	void deleteParticleRegistry(Particle* p);

	void deleteForceRegistry(ForceGenerator* fg);
};

