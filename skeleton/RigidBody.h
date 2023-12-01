#pragma once
#include "core.hpp"

class RigidBody
{
private:
	bool _dyn;
	physx::PxGeometry* geo;

	physx::PxRigidDynamic* rb;
	physx::PxRigidStatic* st;
public:
	RigidBody(bool dyn, physx::PxGeometry* nGeo);
};

