#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int currentShotType) {
	/*int N = 5;
	for (int i = 0; i < N; i++) {
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		damping = 0.99f;
		color = Vector4(0, 0, 1, 1);
		Firework* fP = new Firework(color, Vector3(rand() % 5, 0, rand() % 5),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), N - i);	
		_firework_pool.push_back(fP);
		fP->setLifeTime(1);
		fP->addGenerator(new GaussianParticleGenerator(_firework_pool[i]->clone(), std::to_string(i)));
	}*/

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

					//Firework* pType = static_cast <Firework*> (*shot);
					//if (pType) {
					//	if (static_cast<Firework*> (*shot)) {
					//		newE = static_cast <Firework*> (*shot)->explode();
					//	}
					//}
				}
			}
		}

		/*for (auto lF = newE.begin(); lF != newE.end(); ++lF) {
			particles.push_back(*lF);
			count++;
		}

		newE.clear();*/

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

void ParticleSystem::generateFireworksSystem(unsigned firework_type, std::string name) {
	
	_firework_generator = new GaussianParticleGenerator(_firework_pool[firework_type]->clone(), name);

	_particle_generators.push_back(_firework_generator);
}

void ParticleSystem::generateSystem(Particle* p, int t, std::string name, int num) {
	_particle_generators.push_back(new UniformParticleGenerator(p, t, name, num));
}

void ParticleSystem::setGenerator(int currentGenerator) {
	damping = 0.99f;
	switch (currentGenerator)
	{
	Particle* p;
	case FOUNTAIN:
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(rand() % 5, 0, rand() % 5),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "f");
		break;
	case FOG:
		invM = 1 / 2.0f;
		vel = Vector3(1, 1, 1);
		color = Vector4(1, 1, 1, 1);
		p = new Particle(color, Vector3(rand() % 5, 0, rand() % 5),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "fg", 5000);
		break;
	case RAIN:
		invM = 1 / 2.0f;
		vel = Vector3(1, 0, 1);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(rand() % 5, 0, rand() % 5),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "r");
		break;
	case FIREWORK1:
		generateFireworksSystem(0, "f1");
		break;
	case FIREWORK2:
		generateFireworksSystem(1, "f2");
		break;
	case FIREWORK3:
		generateFireworksSystem(2, "f3");
		break;
	}
}

Particle* ParticleSystem::newParticle() {
	return new Particle(color, Vector3(0,0,0),Vector3(0,0,0),
		_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
}

