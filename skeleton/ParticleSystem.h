#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "CircleParticleGenerator.h"
#include <vector>
#include <list>
#include "Firework.h"
#include "Fountain.h"
#include <string>
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"

class ParticleSystem
{
public:
	enum generatorTypes { FOUNTAIN, FOG, RAIN, FIREWORK1, FIREWORK2, FIREWORK3, MUELLE1 };

	ParticleSystem(int currentGenerator);
	~ParticleSystem();

	void integrate(double t);
	ParticleGenerator* getParticleGenerator(const std::string& name); 
	void generateFireworksSystem(Firework* p, unsigned firework_type, std::string name);
	void generateSystem(Particle* p, int t, std::string name, int num = 1);

	void setGenerator(int currentGenerator);
	Particle* newParticle();

private:
	int currentShotType;

	float timer = 0;

	int typeF = 0;
	int dir = -1;
	int count = 0;
	int exp = 0;
	float damping;
	float invM;
	Vector4 color;
	Vector3 vel;
	Vector3 _gravity = Vector3(0, -10, 0);
	physx::PxTransform pos;

	std::list<std::list<Particle*>> newE;

	std::vector<Particle*> particles;
	std::vector<Particle*> fireworks;
	std::list<ParticleGenerator*> _particle_generators;

	std::list<ParticleGenerator*> _fireworks_generators;
	ParticleGenerator* _firework_generator;
	std::vector<Firework*> _firework_pool;

	std::list<ForceGenerator*> _fg;
	ParticleForceRegistry _pfr;

	GravityForceGenerator* gr;
	ParticleDragGenerator* aV;
	WhirlwindForceGenerator* wV;
	ExplosionForceGenerator* eF;
	SpringForceGenerator* sF;

	void onParticleDeath(Particle* p);
	void createFireworksSystem();
	void iParticles(double t);
	void iFireworks(double t);
	void air(Particle* p);
	void muelles1();

	bool viento = false;
	bool explosion = false;
	bool torbellino = false;
	bool gravedad = false;
	bool elastica1 = true;
};

