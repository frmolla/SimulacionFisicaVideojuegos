#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int currentShotType) {
	setGenerator(currentShotType);
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
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if (count < (*g)->getNumParticles()) {
			std::list<Particle*> aux;
			aux = (*g)->generateParticle();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				particles.push_back(*gp);
				count++;
			}
			
		}

		for (auto shot = particles.begin(); shot != particles.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				(*shot)->integrate(t);
				// Remove particle if invalid
				if ((*shot)->getPosition().p.y < 0.0f ||
					(*shot)->time >(*shot)->getLifeTime() ||
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
}

ParticleGenerator* ParticleSystem::getParticleGenerator(const std::string& name) {
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if ((*g)->getName() == name)
			return *g;
	}
	return nullptr;
}

void ParticleSystem::generateFireworksSystem(unsigned firework_type) {
	//_particle_generators.push_back(new UniformParticleGenerator());
}

void ParticleSystem::generateFountainSystem(Particle* p) {
	_particle_generators.push_back(new UniformParticleGenerator(p));
}

void ParticleSystem::setGenerator(int currentGenerator) {
	switch (currentGenerator)
	{
	case FOUNTAIN:
		invM = 1 / 2.0f;
		vel = Vector3(1, 30, 1);
		damping = 0.99f;
		color = Vector4(0, 0, 1, 1);
		Particle* p = new Particle(color, Vector3(rand() % 5, 0, rand() % 5),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		generateFountainSystem(p);
		break;
	/*case FIREWORK:
		generateFireworksSystem(0);
		break;*/
	}
}

Particle* ParticleSystem::newParticle() {
	return new Particle(color, Vector3(0,0,0),Vector3(0,0,0),
		_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
}

