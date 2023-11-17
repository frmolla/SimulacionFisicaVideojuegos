#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	enum shotStates { UNUSED, ACTIVE };

	Particle(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* nGeo, float nInvM);
	~Particle();

	Particle* clone() const;

	int type;

	float time = 0;

	void integrate(double t);
	physx::PxTransform getPosition();
	void setPosition(Vector3 nPos);
	Vector3 getVelocity();

	int getLifeTime();
	void setLifeTime(float nLifeTime);

	inline Vector4 getColor() { return color; }
	inline Vector3 getAc() { return ac; }
	inline float getDamping() { return damping; }
	inline float getInvM() { return invM; }

	Vector3 force = Vector3(0,0,0);
	inline void addForce(Vector3 f) { force += f; }
	inline void clearForce() { force *= 0.0; }

protected:
	Vector4 color;

	float life_time;
	Vector3 vel;
	Vector3 ac;
	float damping;
	float invM;
	physx::PxTransform pos; 
	physx::PxGeometry* geo;
	RenderItem* renderItem;
};

