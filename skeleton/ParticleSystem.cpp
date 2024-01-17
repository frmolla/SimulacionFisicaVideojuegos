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
	Vector3 airV = Vector3(0, 0, 1);
	float nAir = 10;
	switch (currentGenerator)
	{
	timer = 0;
	Particle* p;
	Firework* fP;
	case FOUNTAIN:
		invM = 1/2.0f;
		vel = Vector3(25, 475, 25);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 0, -150),
			Vector3(vel.x, vel.y, vel.z),
			Vector3(0,0,0), damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(10);
		generateSystem(p, currentGenerator, "f", 2500);
		nGravity = Vector3(0, -10, 0);
		gravedad = true;
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
		//nGravity = Vector3(0, -1, 0);
		nGravity = Vector3(0, -0.00000001, 0);
		break;
	case RAIN:
		invM = 1/2.0f;
		vel = Vector3(0, 0, 0);
		color = Vector4(0.3f, 0.78f, 0.92f, 1);
		p = new Particle(color, Vector3(0, 0, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(3);
		generateSystem(p, currentGenerator, "r", 5000);
		nGravity = Vector3(0, -5, 0);
		gravedad = true;
		break;
	case FIREWORK1:
		invM = 1/2.0f;
		vel = Vector3(20, 1, 20);
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
	case MUELLE1:
		invM = 1 / 2.0f;
		vel = Vector3(30, 300, 30);
		color = Vector4(0, 0, 1, 1);
		p = new Particle(color, Vector3(0, 0, 0),
			Vector3(dir * vel.x * (rand() % 2), vel.y, dir * vel.z * (rand() % 2)),
			Vector3(0, 0, 0), damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), invM);
		p->setLifeTime(60);
		generateSystem(p, currentGenerator, "f", 0);
		nGravity = Vector3(0, -10, 0);
		break;
	}
	gr = new GravityForceGenerator(nGravity);
	_fg.push_back(gr);
	aV = new ParticleDragGenerator(nAir,0, airV);
	_fg.push_back(aV);
	wV = new WhirlwindForceGenerator(1, 0, Vector3(0,0,0), 0.5, 500);
	_fg.push_back(wV);
	eF = new ExplosionForceGenerator(5,500);
	_fg.push_back(eF);
}

Particle* ParticleSystem::newParticle() {
	return new Particle(color, Vector3(0,0,0),Vector3(0,0,0),
		_gravity, damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 1/2.0f);
}

void ParticleSystem::iParticles(double t) {
	timer += t;
	for (auto g = _particle_generators.begin(); g != _particle_generators.end(); ++g) {
		if (count < (*g)->getNumParticles() && count >= 0) {
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

		if (elastica1) {
			muelles1();
			elastica1 = false;
		}

		if (elastica2) {
			muelles2();
			elastica2 = false;
		}

		if (elastica3) {
			muelles3();
			elastica3 = false;
		}

		if (elastica4) {
			muelles4();
			elastica4 = false;
		}

		if (elastica5) {
			muelles5();
			elastica5 = false;
			elastica5aux = true;
		}

		for (auto shot = particles.begin(); shot != particles.end(); ++shot)
		{
			if ((*shot)->type != Particle::UNUSED)
			{
				if(gravedad)
					_pfr.addRegistry(gr, *shot);
				else
					_pfr.deleteParticleForceRegistry(gr, *shot);

				if (timer > 3 && explosion) {
					_pfr.addRegistry(eF, *shot);
					if(timer > 4)
						timer = 0;
				}
				air(*shot);
				_pfr.updateForces(t);
				(*shot)->integrate(t);
				// Remove particle if invalid
				if ((*shot)->getPosition().p.y < -1000.0f ||
					(*shot)->time > (*shot)->getLifeTime() ||
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
				_pfr.deleteParticleRegistry(p);
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
			if (fin) {
				std::list<Particle*> aux;
				auto normal = static_cast<GaussianParticleGenerator*> (*g);
				normal->newGen(normal->getTGen());
				if (fin)
					normal->newPos(posVictoria.x, posVictoria.y, posVictoria.z);
				else
					normal->newPos(0, 0, 0);
				aux = (*g)->generateParticle();
				for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
					fireworks.push_back(*gp);
					if (gravedad)
						_pfr.addRegistry(gr, *gp);
					if (torbellino)
						_pfr.addRegistry(wV, *gp);
					count++;
				}
				fin = false;
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
		if (elastica5aux) {
			if (p->getPosition().p.x < 80 && p->getPosition().p.x > -80
				&& p->getPosition().p.z < 80 && p->getPosition().p.z > -80) {
				_pfr.addRegistry(aV, p);
			}
			else {
				_pfr.deleteParticleForceRegistry(aV, p);
			}
		}
		else {
			_pfr.addRegistry(aV, p);
		}		
	}	
	else 
		_pfr.deleteParticleForceRegistry(aV, p);
}

void ParticleSystem::muelles1() {

	// Muelle fijo
	Particle* p3 = new Particle(Vector4(1, 1, 1, 1), Vector3(0, 130, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p3->setLifeTime(60);
	particles.push_back(p3);

	aSF = new AnchoredSpringForceGenerator(5, 10, Vector3(0, 150, 0));
	_pfr.addRegistry(aSF, p3);
	_fg.push_back(aSF);

}

void ParticleSystem::muelles2() {

	// Muelle no fijo
	Particle* p1 = new Particle(Vector4(1,1,1,1), Vector3(-10,10,0),
		Vector3(0,0,0), Vector3(0,0,0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1/2.0f);
	p1->setLifeTime(60);
	particles.push_back(p1);

	Particle* p2 = new Particle(Vector4(1,1,1,1), Vector3(20,10,0),
		Vector3(0,0,0), Vector3(0,0,0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p2->setLifeTime(60);
	particles.push_back(p2);

	sF = new SpringForceGenerator(1, 20, p2);
	_pfr.addRegistry(sF, p1);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(1, 20, p1);
	_pfr.addRegistry(sF, p2);
	_fg.push_back(sF); 

}

void ParticleSystem::muelles3() {

	// Goma elástica
	Particle* p1 = new Particle(Vector4(1, 1, 1, 1), Vector3(30, 50, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p1->setLifeTime(60);
	particles.push_back(p1);

	Particle* p2 = new Particle(Vector4(1, 1, 1, 1), Vector3(0, 50, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p2->setLifeTime(60);
	particles.push_back(p2);

	rSF = new RubberSrpingForceGenerator(0.1, 20, p2, 20);
	_pfr.addRegistry(rSF, p1);
	_fg.push_back(rSF);

	rSF = new RubberSrpingForceGenerator(0.1, 20, p1, 20);
	_pfr.addRegistry(rSF, p2);
	_fg.push_back(rSF);

	// Goma elástica extremo fijo
	/*Particle* p1 = new Particle(Vector4(1, 1, 1, 1), Vector3(30, 50, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxBoxGeometry(5, 5, 5), 0);
	p1->setLifeTime(60);
	particles.push_back(p1);

	Particle* p2 = new Particle(Vector4(1, 1, 1, 1), Vector3(0, 50, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p2->setLifeTime(60);
	particles.push_back(p2);

	rSF = new RubberSrpingForceGenerator(0.1, 20, p2, 20);
	_pfr.addRegistry(rSF, p1);
	_fg.push_back(rSF);

	rSF = new RubberSrpingForceGenerator(0.1, 20, p1, 20);
	_pfr.addRegistry(rSF, p2);
	_fg.push_back(rSF);*/

}

void ParticleSystem::muelles4() {

	int k = 2;
	int x0 = 15;

	// Muelle no fijo
	Particle* p1 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 100, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p1->setLifeTime(60);
	particles.push_back(p1);

	Particle* p2 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 90, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p2->setLifeTime(60);
	particles.push_back(p2);

	Particle* p3 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 80, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p3->setLifeTime(60);
	particles.push_back(p3);

	Particle* p4 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 70, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p4->setLifeTime(60);
	particles.push_back(p4);

	Particle* p5 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 60, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p5->setLifeTime(60);
	particles.push_back(p5);

	Particle* p6 = new Particle(Vector4(1, 1, 1, 1), Vector3(20, 50, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), 1 / 2.0f);
	p6->setLifeTime(60);
	particles.push_back(p6);

	sF = new SpringForceGenerator(k, x0, p2);
	_pfr.addRegistry(sF, p1);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p1);
	_pfr.addRegistry(sF, p2);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p3);
	_pfr.addRegistry(sF, p2);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p2);
	_pfr.addRegistry(sF, p3);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p4);
	_pfr.addRegistry(sF, p3);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p3);
	_pfr.addRegistry(sF, p4);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p5);
	_pfr.addRegistry(sF, p4);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p4);
	_pfr.addRegistry(sF, p5);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p6);
	_pfr.addRegistry(sF, p5);
	_fg.push_back(sF);

	sF = new SpringForceGenerator(k, x0, p5);
	_pfr.addRegistry(sF, p6);
	_fg.push_back(sF);
}

void ParticleSystem::muelles5() {

	float m = 20.0f;
	float h = 5;
	float v = h*h*h/1000;
	float d = m / v;

	// Flotación
	bP = new Particle(Vector4(0.5f, 0.08f, 0.08f, 1.0f), Vector3(-125, 30, 75),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxBoxGeometry(h, h, h), 1 / m);
	bP->setLifeTime(60);
	particles.push_back(bP);

	bSF = new BuoyancyForceGenerator(h, v, d);
	_pfr.addRegistry(bSF, bP);
	_fg.push_back(rSF);

	bP = new Particle(Vector4(0.5f, 0.08f, 0.08f, 1.0f), Vector3(125, 30, 75),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxBoxGeometry(h, h, h), 1 / m);
	bP->setLifeTime(60);
	particles.push_back(bP);

	bSF = new BuoyancyForceGenerator(h, v, d);
	_pfr.addRegistry(bSF, bP);
	_fg.push_back(rSF);
}


void ParticleSystem::aumK() {
	aSF->setK(aSF->getK() + 0.1);
	std::cout << aSF->getK() << std::endl;
}

void ParticleSystem::disK() {
	aSF->setK(aSF->getK() - 0.1);
	std::cout << aSF->getK() << std::endl;
}

void ParticleSystem::setG() {
	gravedad = !gravedad;
}

void ParticleSystem::setW() {
	viento = !viento;
	std::cout << viento << std::endl;
	
}

void ParticleSystem::setWF(int fuerzaV) {
	viento = true;
	aV->setVel(Vector3(fuerzaV,0,0));
}

void ParticleSystem::aumM() {
	bP->setInvM(bP->getInvM() + 0.01);
	std::cout << bP->getInvM() << std::endl;
}

void ParticleSystem::disM() {
	bP->setInvM(bP->getInvM() - 0.01);
	std::cout << bP->getInvM() << std::endl;
}

void ParticleSystem::aumV() {
	bSF->setV(bSF->getV() + 0.1);
	std::cout << bSF->getV() << std::endl;
}

void ParticleSystem::disV() {
	bSF->setV(bSF->getV() - 0.1);
	std::cout << bSF->getV() << std::endl;
}


