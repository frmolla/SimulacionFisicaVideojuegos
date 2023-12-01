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
#include "RubberSrpingForceGenerator.h"
#include "BuoyancyForceGenerator.h"

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

	void aumK();
	void disK();
	void aumM();
	void disM();
	void aumV();
	void disV();
	void setG();
	void setW();
	inline void setE1() { elastica1 = true; }
	inline void setE2() { elastica2 = true; }
	inline void setE3() { elastica3 = true; }
	inline void setE4() { elastica4 = true; }
	inline void setE5() { elastica5 = true; }

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

	Particle* bP = nullptr;

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
	AnchoredSpringForceGenerator* aSF;
	RubberSrpingForceGenerator* rSF;
	BuoyancyForceGenerator* bSF;

	void onParticleDeath(Particle* p);
	void createFireworksSystem();
	void iParticles(double t);
	void iFireworks(double t);
	void air(Particle* p);
	void muelles1();
	void muelles2();
	void muelles3();
	void muelles4();
	void muelles5();

	bool viento = false;
	bool explosion = false;
	bool torbellino = false;
	bool gravedad = false;
	bool elastica1 = false;
	bool elastica2 = false;
	bool elastica3 = false;
	bool elastica4 = false;
	bool elastica5 = false;
};

