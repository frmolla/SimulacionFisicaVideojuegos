#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <vector>
#include <list>
#include "Firework.h"
#include "Fountain.h"
#include <string>

class ParticleSystem
{
public:
	enum generatorTypes { FOUNTAIN, FOG, RAIN, FIREWORK1, FIREWORK2, FIREWORK3 };

	ParticleSystem(int currentGenerator);
	~ParticleSystem();

	void integrate(double t);
	ParticleGenerator* getParticleGenerator(const std::string& name); 
	void generateFireworksSystem(unsigned firework_type, std::string name);
	void generateSystem(Particle* p, int t, std::string name, int num = 2500);

	void setGenerator(int currentGenerator);
	Particle* newParticle();

private:
	int currentShotType;

	int dir = -1;
	int count = 0;
	int exp = 0;
	float damping;
	float invM;
	Vector4 color;
	Vector3 vel;
	Vector3 _gravity = Vector3(0, -10, 0);
	physx::PxTransform pos;

	std::list<Particle*> newE;

	std::vector<Particle*> particles;
	std::vector<Firework*> fireworks;
	std::list<ParticleGenerator*> _particle_generators;

	ParticleGenerator* _firework_generator;
	std::vector<Firework*> _firework_pool;

	void onParticleDeath(Particle* p);
	void createFireworksSystem();

};

