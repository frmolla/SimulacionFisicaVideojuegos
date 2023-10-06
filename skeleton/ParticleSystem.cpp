#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int currentShotType) {
	setParticle(currentShotType);
}

ParticleSystem::~ParticleSystem() {
	auto it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->type == Particle::UNUSED) {
			Particle* p = *it;
			it = particles.erase(it);
			delete(p);
		}
		else
			++it;
	}
}

void ParticleSystem::integrate(double t) {
	if(count < MAX_P){
		newParticle();
		count++;
	}

	for (auto shot = particles.begin(); shot != particles.end(); ++shot)
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
	auto it = particles.begin();
	while (it != particles.end()) {
		if ((*it)->type == Particle::UNUSED) {
			Particle* p = *it;
			it = particles.erase(it);
			delete(p);
			count--;
		}
		else
			++it;
	}
}

void ParticleSystem::setParticle(int currentShotType) {
	switch (currentShotType)
	{
	case FOUNTAIN:
		invM = 1 / 2.0f;
		vel = Vector3(1, 30, 1);
		ac = Vector3(0.0, -5.0f, 00.0);
		damping = 0.99f;
		color = Vector4(0, 0, 1, 1);
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
		color = Vector4(1, 0, 0, 1);
		break;
	}
}

void ParticleSystem::newParticle() {
	dir = (dir != 1) ? 1 : -1;
	particles.push_back(new Particle(color, Vector3(rand() % 5, 0, rand() % 5),
		Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
		ac, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f)));
}

