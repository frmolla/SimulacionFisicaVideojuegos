#pragma once

#include "Particle.h"
#include <vector>

class ShotManager
{

const int LIFE_TIME = 10;

public:
	enum shotTypes { PISTOL, ARTILLERY, FIREBALL };

	ShotManager(int currentShotType);
	~ShotManager();

	void integrate(double t);

	void setShot(int currentShotType);

	void shot();

private:
	int currentShotType;

	Vector4 color;
	Vector3 vel;
	Vector3 ac;
	float damping;
	float invM;
	physx::PxTransform pos;

	std::vector<Particle*> projectiles;
};

