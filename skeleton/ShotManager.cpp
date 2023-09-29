#include "ShotManager.h"

ShotManager::ShotManager(int currentShotType) {
	setShot(currentShotType);
}

ShotManager::~ShotManager() {
	// destruir elementos vector
}

void ShotManager::integrate(double t) {
	for (auto shot = projectiles.begin(); shot != projectiles.end(); ++shot)
	{
		if ((*shot)->type != Particle::UNUSED)
		{
			(*shot)->integrate(t);
			// Remove particle if invalid
			if ((*shot)->getPosition().p.y < 0.0f ||
				(*shot)->time > LIFE_TIME ||
				(*shot)->getPosition().p.z > 200.0f)
			{
				// Free the slot
				(*shot)->type = Particle::UNUSED;
			}
		}
	}
}

void ShotManager::setShot(int currentShotType) {
	switch (currentShotType)
	{
	case PISTOL:
		invM = 1 / 2.0f;
		vel = Vector3(0, 35, 0);
		ac = Vector3(0.0, -1.0f, 00.0);
		damping = 0.99f;
		color = Vector4(0, 1, 0, 1);
		break;
	case ARTILLERY:
		invM = 1 / 200.0f;
		vel = Vector3(0, 30, 40);
		ac = Vector3(0.0, -20.0f, 00.0);
		damping = 0.99f;
		color = Vector4(0, 0, 1, 1);
		break;
	case FIREBALL:
		invM = 1 / 1.0f;
		vel = Vector3(0, 0, 10);
		ac = Vector3(0.0, -0.6f, 00.0);
		damping = 0.9f;
		color = Vector4(1,0,0,1);
		break;
	}
}

void ShotManager::shot() {
	projectiles.push_back(new Particle(color, Vector3(0,0,0), vel, ac, damping, Particle::ACTIVE));
}
