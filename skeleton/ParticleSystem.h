#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include <vector>
#include <list>
#include "Firework.h"
#include "Fountain.h"

class ParticleSystem
{
public:
	enum generatorTypes { FOUNTAIN, FIREWORK };

	ParticleSystem(int currentGenerator);
	~ParticleSystem();

	void integrate(double t);
	ParticleGenerator* getParticleGenerator(const std::string& name); // por implementar
	void generateFireworksSystem(unsigned firework_type); // por implementar
	void generateFountainSystem(Particle* p); // por implementar

	void setGenerator(int currentGenerator);
	Particle* newParticle();

private:
	int currentShotType;

	int dir = -1;
	int count = 0;
	float damping;
	float invM;
	Vector4 color;
	Vector3 vel;
	Vector3 _gravity = Vector3(0, -10, 0);
	physx::PxTransform pos;

	std::vector<Particle*> particles;
	std::list<ParticleGenerator*> _particle_generators; // sin usar

	ParticleGenerator* _firework_generator;
	std::vector<Firework*> _firework_pool;

	void onParticleDeath(Particle* p);
	void createFireworksSystem();

};

