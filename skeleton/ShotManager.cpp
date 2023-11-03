#include "ShotManager.h"

ShotManager::ShotManager(int currentShotType) {
	setShot(currentShotType);
}

ShotManager::~ShotManager() {
	auto it = projectiles.begin();
	while (it != projectiles.end()) {
		Particle* p = *it;
		it = projectiles.erase(it);
		delete(p);
	}
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
				(*shot)->getPosition().p.y > 200.0f)
			{
				// Free the slot
				(*shot)->type = Particle::UNUSED;
			}
		}
	}
	auto it = projectiles.begin();
	while (it != projectiles.end()) {
		if ((*it)->type == Particle::UNUSED) {
			Particle* p = *it;
			it = projectiles.erase(it);
			delete(p);
			count--;
		}
		else 
			++it;
	}
}

void ShotManager::setShot(int currentShotType) {
	switch (currentShotType)
	{
	case PISTOL:
		invM = 1 / 2.0f;
		vel = Vector3(95, 0 ,95);
		ac = Vector3(0.0, -1.0f, 00.0);
		damping = 0.99f;
		color = Vector4(0, 1, 0, 1);
		break;
	case ARTILLERY:
		invM = 1 / 200.0f;
		vel = Vector3(50, 0, 50);
		ac = Vector3(0.0, -10.0f, 00.0);
		damping = 0.99f;
		color = Vector4(0, 0, 1, 1);
		break;
	case FIREBALL:
		invM = 1 / 1.0f;
		vel = Vector3(100, 0, 100);
		ac = Vector3(0.0, -0.6f, 00.0);
		damping = 0.9f;
		color = Vector4(1,0,0,1);
		break;
	}
}

void ShotManager::shot() {
	if (count < MAX_P) {
		projectiles.push_back(new Particle(color, GetCamera()->getTransform().p,
			Vector3(vel.x * GetCamera()->getDir().x, vel.y * GetCamera()->getDir().y, vel.z * GetCamera()->getDir().z),
			ac, damping, Particle::ACTIVE, &physx::PxSphereGeometry(3), invM));
		count++;
	}
}
