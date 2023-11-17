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
	Vector3 nGravity;
	Vector3 airV = Vector3(1, 0, 0);
	float nAir = 100;
	switch (currentGenerator)
	{
	timer = 0;
	Particle* p;
	Firework* fP;
	case FOUNTAIN:
		invM = 1/2.0f;
		vel = Vector3(30, 300, 30);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 0, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			Vector3(0,0,0), damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(10);
		generateSystem(p, currentGenerator, "f", 2500);
		nGravity = Vector3(0, -10, 0);
		break;
	case FOG:
		invM = 1/2.0f;
		vel = Vector3(0.1, 0.1, 0.1);
		color = Vector4(1, 1, 1, 1);
		p = new Particle(color, Vector3(0, 0, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(5);
		generateSystem(p, currentGenerator, "fg", 5000);
		nGravity = Vector3(0, -1, 0);
		break;
	case RAIN:
		invM = 1/2.0f;
		vel = Vector3(0, 0, 0);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 0, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "r", 5000);
		nGravity = Vector3(0, -5, 0);
		break;
	case FIREWORK1:
		invM = 1/2.0f;
		vel = Vector3(20, 400, 20);
		color = Vector4(1, 1, 1, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 2, invM);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 0, "f1");
		nGravity = Vector3(0, -10, 0);
		break;
	case FIREWORK2:
		invM = 1/2.0f;
		vel = Vector3(10, 400, 10);
		color = Vector4(1, 0, 0, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 1, invM);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 1, "f2");
		nGravity = Vector3(0, -10, 0);
		break;
	case FIREWORK3:
		invM = 1/2.0f;
		vel = Vector3(20, 500, 20);
		color = Vector4(1, 0, 1, 1);
		fP = new Firework(color, Vector3(0, 0, 0),
			vel, _gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 3, invM);
		_firework_pool.push_back(fP);
		fP->setLifeTime(3);
		generateFireworksSystem(fP, 2, "f3");
		nGravity = Vector3(0, -10, 0);
		break;
	}
	gr = new GravityForceGenerator(nGravity);
	_fg.push_back(gr);
	aV = new ParticleDragGenerator(nAir,0, airV);
	_fg.push_back(aV);
	wV = new WhirlwindForceGenerator(1, 0, Vector3(0,0,0), 0.5, 50);
	_fg.push_back(wV);
	eF = new ExplosionForceGenerator(50,500);
	_fg.push_back(eF);
}

Particle* ParticleSystem::newParticle() {
	return new Particle(color, Vector3(0,0,0),Vector3(0,0,0),
		_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 1/2.0f);
}

void ParticleSystem::iParticles(double t) {
	timer += t;
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if (count < (*g)->getNumParticles()) {
			std::list<Particle*> aux;
			aux = (*g)->generateParticle();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				particles.push_back(*gp);
				if(gravedad)
					_pfr.addRegistry(gr, *gp);
				if(torbellino)
					_pfr.addRegistry(wV, *gp);
				count++;
			}

		}

		for (auto shot = particles.begin(); shot != particles.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				if (timer > 3 && explosion) {
					_pfr.addRegistry(eF, *shot);
					if(timer > 4)
						timer = 0;
				}
				air(*shot);
				_pfr.updateForces(t);
				(*shot)->integrate(t);
				// Remove particle if invalid
				if ((*shot)->getPosition().p.y < 0.0f ||
					(*shot)->time >(*shot)->getLifeTime() ||
					(*shot)->getPosition().p.y > 500.0f)
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
				if (gravedad)
					_pfr.addRegistry(gr, *gp);
				if (torbellino)
					_pfr.addRegistry(wV, *gp);
				count++;
			}

		}

		for (auto shot = fireworks.begin(); shot != fireworks.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				air(*shot);
				_pfr.updateForces(t);
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

void ParticleSystem::air(Particle* p) {
	if (viento) {
		if (p->getPosition().p.x < 80 && p->getPosition().p.x > -80
			&& p->getPosition().p.z < 80 && p->getPosition().p.z > -80) {
			_pfr.addRegistry(aV, p);
		}
		else {
			_pfr.deleteParticleRegistry(p);
		}
	}	
}

