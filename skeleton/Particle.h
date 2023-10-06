#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	enum shotStates { UNUSED, ACTIVE };

	Particle(Vector4 color, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* geo);
	~Particle();

	int type;

	float time = 0;

	void integrate(double t);
	physx::PxTransform getPosition();

private:
	Vector4 color;

	Vector3 vel;
	Vector3 ac;
	float damping;
	float invM;
	physx::PxTransform pos; 
	RenderItem* renderItem;
};

