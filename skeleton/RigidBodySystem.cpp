#include "RigidBodySystem.h"

RigidBodySystem::RigidBodySystem(physx::PxPhysics* gPhysics, physx::PxScene* gScene, int currentGenerator, int pR)
 : _gPhysics(gPhysics), _gScene(gScene) {
	_pR = pR;
	setGenerator(currentGenerator);
}

RigidBodySystem::~RigidBodySystem() {

}

void RigidBodySystem::integrate(double t) {
	// agregar y borrar rb

	timer += t;
	for (auto g = _gens.begin(); g != _gens.end(); ++g) {
		/*if (count < (*g)->getNumRB() && count >= 0) {
			std::list<RigidBody*> aux;
			aux = (*g)->generateRB();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				rigid_bodys.push_back(*gp);

				if (torbellino)
					_pfr.addRegistry(wV, *gp);
				count++;
			}

		}*/
		if (lanzado) {
			lanzar(_p, _v);
			lanzado = false;
		}

		for (auto shot = rigid_bodys.begin(); shot != rigid_bodys.end(); ++shot)
		{
			if ((*shot)->type != RigidBody::UNUSED)
			{
				if (timer > 3 && explosion) {
					_pfr.addRegistry(eF, *shot);
					if (timer > 4)
						timer = 0;
				}
				_pfr.updateForces(t);

				air(*shot);
				// Remove particle if invalid
				(*shot)->time += t;
				if ((*shot)->getPosition().p.y < -1000.0f ||
					(*shot)->time > (*shot)->getLifeTime() ||
					(*shot)->getPosition().p.y > 500.0f || colAux)
				{
					// Free the slot
					colAux = false; 
					(*shot)->type = RigidBody::UNUSED;
				}
			}
		}

		auto it = rigid_bodys.begin();
		while (it != rigid_bodys.end()) {
			if ((*it)->type == RigidBody::UNUSED) {
				RigidBody* p = *it;
				_pfr.deleteParticleRegistry(p);
				it = rigid_bodys.erase(it);
				p->getRB()->release();
				delete(p);
				count--;
			}
			else
				++it;
		}
	}
}

void RigidBodySystem::generateSystem(RigidBody* p, int t, std::string name, int num) {
	// RigidBodyGenerator
	_gens.push_back(new UniformRBGenerator(p, t, name, _gPhysics, _gScene, num));
}

void RigidBodySystem::setGenerator(int currentGenerator) {
	Vector4 color;
	Vector3 airV = Vector3(0, 0, 1000);
	float nAir = 1;
	switch (currentGenerator)
	{
		RigidBody* rb;
	case DYNAMIC:
		if (_pR == 0) {
			rb = new RigidBody(true, &physx::PxBoxGeometry(5, 5, 5),
				_gPhysics, _gScene, Vector3(0, -30, 0), Vector4(1.0f, 1.0f, 0.0f, 1.0f), 10);
			generateSystem(rb, currentGenerator, "rbD", 1);
		}
		else {
			color = Vector4(randomFloat(), randomFloat(), randomFloat(), 1);
			rb = new RigidBody(true, &physx::PxBoxGeometry(5, 5, 5),
				_gPhysics, _gScene, Vector3(0, 30, 0), color, 10);
			generateSystem(rb, currentGenerator, "rbD", 15);
		}
		break;
	case STATIC:
		color = Vector4(randomFloat(), randomFloat(), randomFloat(), 1);
		rb = new RigidBody(false, &physx::PxBoxGeometry(5,5,5),
			_gPhysics, _gScene, Vector3(0, 0, 0), color, 10);
		generateSystem(rb, currentGenerator, "rbS", 15);
		break;
	}

	aV = new ParticleDragGenerator(nAir, 0, airV);
	_fg.push_back(aV);
	wV = new WhirlwindForceGenerator(1, 0, Vector3(0, 0, 0), 0.5, 500);
	_fg.push_back(wV);
	eF = new ExplosionForceGenerator(5, 500);
	_fg.push_back(eF);
}

void RigidBodySystem::lanzar(Vector3 p, Vector3 v) {
	colAux = false;
	for (auto g = _gens.begin(); g != _gens.end(); ++g) {
		if (count < (*g)->getNumRB() && count >= 0) {
			std::list<RigidBody*> aux;
			if (_pR == 0)
				(*g)->setL(p, v);
			aux = (*g)->generateRB();
			for (auto gp = aux.begin(); gp != aux.end(); ++gp) {
				rigid_bodys.push_back(*gp);

				if (torbellino)
					_pfr.addRegistry(wV, *gp);
				count++;
			}

		}
	}
}

void RigidBodySystem::air(RigidBody* p) {
	if (viento) {
		_pfr.addRegistry(aV, p);
		/*if (p->getPosition().p.x < 80 && p->getPosition().p.x > -80
			&& p->getPosition().p.z < 80 && p->getPosition().p.z > -80) {
			_pfr.addRegistry(aV, p);
		}
		else {
			_pfr.deleteParticleForceRegistry(aV, p);
		}*/
	}
	else
		_pfr.deleteParticleForceRegistry(aV, p);
}

void RigidBodySystem::col() {
	colAux = true;
}