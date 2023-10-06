#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"
#include <vector>
#include <list>

class ParticleSystem
{
	const int LIFE_TIME = 10;
	const int MAX_P = 2500;

public:
	enum shotTypes { FOUNTAIN, ARTILLERY, FIREBALL };

	ParticleSystem(int currentShotType);
	~ParticleSystem();

	void integrate(double t);
	ParticleGenerator* getParticleGenerator(std::string name); // por implementar
	void generateFireworksSystem(); // por implementar

	void setParticle(int currentShotType);
	void newParticle();

private:
	std::vector<Particle*> particles;
	std::list<ParticleGenerator*> _particle_generators; // sin usar

	int currentShotType;

	int dir = -1;
	int count = 0;
	float damping;
	float invM;
	Vector4 color;
	Vector3 vel;
	Vector3 ac;
	physx::PxTransform pos;
};

