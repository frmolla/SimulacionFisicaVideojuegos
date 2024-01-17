#pragma once
#include "core.hpp"
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "UniformRBGenerator.h"
#include "ParticleDragGenerator.h"
#include "ParticleForceRegistry.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ForceGenerator.h"
#include <list>

class RigidBodySystem
{
public:
	enum generatorTypes { DYNAMIC, STATIC };

	RigidBodySystem(physx::PxPhysics* gPhysics, physx::PxScene* gScene, int currentGenerator, int pR);
	~RigidBodySystem();

	void integrate(double t);

	void generateSystem(RigidBody* p, int t, std::string name, int num = 1);
	void setGenerator(int currentGenerator);

	void lanzar(Vector3 p, Vector3 v);

	inline void setWind(Vector3 v) { aV->setVel(v); }
	inline void setLanzamiento(Vector3 p, Vector3 v) { lanzado = true; _p = p, _v = v; }

	void col();
	inline bool getCol() { return colAux; }
private:
	physx::PxPhysics* _gPhysics;
	physx::PxScene* _gScene;

	int count = 0;
	float timer = 0;

	int _pR;

	std::vector<RigidBody*> rigid_bodys;

	std::list<RigidBodyGenerator*> _gens;
	std::list<ForceGenerator*> _fg;	
	ParticleForceRegistry _pfr;

	ParticleDragGenerator* aV;
	WhirlwindForceGenerator* wV;
	ExplosionForceGenerator* eF;

	inline float randomFloat()
	{
		return (float)(rand()) / (float)(rand());
	}

	void air(RigidBody* p);

	bool viento = true;
	bool torbellino = false;
	bool explosion = false;

	bool lanzado = false;

	bool colAux = false;

	Vector3 _p, _v;
};

