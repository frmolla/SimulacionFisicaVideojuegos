#pragma once
#include "core.hpp"
#include "RigidBody.h"
#include "RigidBodySystem.h"

class Scene
{
public:
	Scene(physx::PxPhysics* gPhysics, physx::PxScene* gScene);
	~Scene();
	void init();
	void integrate(double t);
	void keyPress(unsigned char key);
private:
	physx::PxPhysics* _gPhysics;
	physx::PxScene* _gScene;

	RigidBodySystem* rbS;
	RigidBodySystem* rbD;

	RigidBody* ground;
	RigidBody* ob;
};

