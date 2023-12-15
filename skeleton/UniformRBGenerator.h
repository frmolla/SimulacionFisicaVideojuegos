#pragma once
#include "RigidBodyGenerator.h"

class UniformRBGenerator : public RigidBodyGenerator
{
private:
	int _kind;
	Vector3 _vel_width, _pos_width;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _v{ -1,1 };
	std::uniform_real_distribution<double> _r{ 60,100 };
	std::uniform_real_distribution<double> _m{ 0,1 };

	physx::PxPhysics* _gPhysics;
	physx::PxScene* _gScene;
public:
	UniformRBGenerator(RigidBody* p, int kind, std::string name, physx::PxPhysics* gPhysics, physx::PxScene* gScene, int num = 1);
	~UniformRBGenerator();
	virtual std::list<RigidBody*> generateRB();
};

