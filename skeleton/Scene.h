#pragma once
#include "core.hpp"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "ParticleSystem.h"

class Scene
{
public:
	Scene(physx::PxPhysics* gPhysics, physx::PxScene* gScene);
	~Scene();
	void init();
	void integrate(double t);
	void keyPress(unsigned char key);

	void actionP(int angle, int vel, int turno);
	void collisionS(physx::PxActor* actor1, physx::PxActor* actor2, int & v);

	inline bool getColM() { return colM; }
	inline void setColM(bool M) { colM = M; }
private:

	physx::PxPhysics* _gPhysics;
	physx::PxScene* _gScene;

	RigidBodySystem* rbS;
	RigidBodySystem* rbD;

	RigidBody* ground;
	RigidBody* sun;
	RigidBody* ob;

	RigidBody* plat1;
	RigidBody* plat2;

	RigidBody* player1;
	RigidBody* player2;

	ParticleSystem* pF;
	ParticleSystem* pN;
	ParticleSystem* pL;
	ParticleSystem* m1;
	ParticleSystem* f1;

	int clima = 0;
	int viento = 0;

	Vector3 posP1 = Vector3(-100, 70, 0);
	Vector3 posP2 = Vector3(100, 70, 0);

	Vector4 colores[3] = {Vector4(0.64f,0.64f,0.65f,1.0f), Vector4(0.37f, 0.63f, 0.64f, 1.0f), Vector4(0.5f, 0.08f, 0.08f, 1.0f) };

	void initScene();
	void initSystems();

	int _angle = 0;
	int _vel = 0;
	int _turno = 0; // 0 - p1 / 1 - p2

	bool end = false;

	bool colS = false;
	bool colM = false;
};

