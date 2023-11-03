#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int currentShotType) {
	setGenerator(currentShotType);
	_fg.push_back(new GravityForceGenerator(Vector3(0,-10,0)));
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
	
	_pfr.updateForces(t);
		
	iParticles(t);

	iFireworks(t);

}

ParticleGenerator* ParticleSystem::getParticleGenerator(const std::string& name) {
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if ((*g)->getName() == name)
			return *g;
	}
	return nullptr;
}

void ParticleSystem::generateFireworksSystem(Firework* f, unsigned firework_type, std::string name) {
	
	if (firework_type == 0) {
		auto normal = new GaussianParticleGenerator(f->clone(), name);
		normal->newGen(3);
		normal->setTGen(3);
		_firework_generator = normal;
	}
	else if (firework_type == 1) {
		auto normal = new CircleParticleGenerator(f->clone(), name);
		normal->newGen(2);
		normal->setTGen(2);
		_firework_generator = normal;
	}
	if (firework_type == 2) {
		auto normal = new CircleParticleGenerator(f->clone(), name);
		normal->newGen(3);
		normal->setTGen(3);
		_firework_generator = normal;
	}
	
	_fireworks_generators.push_back(_firework_generator);
}

void ParticleSystem::generateSystem(Particle* p, int t, std::string name, int num) {
	_particle_generators.push_back(new UniformParticleGenerator(p, t, name, num));
}

void ParticleSystem::setGenerator(int currentGenerator) {
	damping = 0.99f;
	switch (currentGenerator)
	{
	Particle* p;
	Firework* fP;
	case FOUNTAIN:
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 10, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			Vector3(0,0,0), damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "f");
		break;
	case FOG:
		invM = 1 / 2.0f;
		vel = Vector3(1, 1, 1);
		color = Vector4(1, 1, 1, 1);
		p = new Particle(color, Vector3(0, 10, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "fg", 5000);
		break;
	case RAIN:
		invM = 1 / 2.0f;
		vel = Vector3(1, 0, 1);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 10, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "r");
		break;
	case FIREWORK1:
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		color = Vector4(1, 1, 1, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 2);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 0, "f1");
		break;
	case FIREWORK2:
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		color = Vector4(1, 0, 0, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 1);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 1, "f2");
		break;
	case FIREWORK3:
		invM = 1 / 2.0f;
		vel = Vector3(5, 30, 5);
		color = Vector4(1, 0, 1, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 3);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 2, "f3");
		break;
	}
}

Particle* ParticleSystem::newParticle() {
	return new Particle(color, Vector3(0,0,0),Vector3(0,0,0),
		_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
}

void ParticleSystem::iParticles(double t) {
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if (count < (*g)->getNumParticles()) {
			std::list<Particle*> aux;
			aux = (*g)->generateParticle();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				particles.push_back(*gp);
				_pfr.addRegistry(*_fg.begin(), *gp);
				count++;
			}

		}

		for (auto shot = particles.begin(); shot != particles.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				_pfr.updateForces(t);
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

void ParticleSystem::iFireworks(double t) {
	for (auto g = _fireworks_generators.begin(); g != _fireworks_generators.end(); ++g) {
		if (count < (*g)->getNumParticles()) {
			std::list<Particle*> aux;
			auto normal = static_cast<GaussianParticleGenerator*> (*g);
			normal->newGen(normal->getTGen());
			normal->newPos(0,0,0);
			aux = (*g)->generateParticle();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				fireworks.push_back(*gp);
				count++;
			}

		}

		for (auto shot = fireworks.begin(); shot != fireworks.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				(*shot)->integrate(t);
				// Remove particle if invalid
				if ((*shot)->getPosition().p.y < 0.0f ||
					(*shot)->time >(*shot)->getLifeTime())
				{
					// Free the slot
					(*shot)->type = Particle::UNUSED;
					newE.push_back(static_cast <Firework*> (*shot)->explode());
					
				}
			}
		}

		for (auto lF = newE.begin(); lF != newE.end(); ++lF) {
			for (auto it2 = (*lF).begin(); it2 != (*lF).end(); ++it2) {
				fireworks.push_back(*it2);
				count++;
			}	
		}

		newE.clear();

		auto it = fireworks.begin();
		while (it != fireworks.end()) {
			if ((*it)->type == Particle::UNUSED) {
				Particle* p = *it;
				it = fireworks.erase(it);
				delete(p);
				count--;
			}
			else
				++it;
		}
	}
}
