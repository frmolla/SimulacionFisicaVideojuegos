#include "ExplosionForceGenerator.h"
#include <iostream>
#include <cmath>

ExplosionForceGenerator::ExplosionForceGenerator(const float k, float r, Vector3 o) // añadir tE constructora
	: ForceGenerator() {
	_k = k;
	_r = r;
	ori = o;
	tE = 500;
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 v;

	if ((particle->getPosition().p - ori).magnitude() < _r) {
		v.x = (particle->getPosition().p.x - ori.x);
		v.y = (particle->getPosition().p.y - ori.y);
		v.z = (particle->getPosition().p.z - ori.z);
	}

	_t += t;

	particle->addForce((_k/_r*_r) * v * exp(-t/tE));
}

void ExplosionForceGenerator::updateForce(RigidBody* particle, double t) {
	Vector3 v;

	if ((particle->getPosition().p - ori).magnitude() < _r) {
		v.x = (particle->getPosition().p.x - ori.x);
		v.y = (particle->getPosition().p.y - ori.y);
		v.z = (particle->getPosition().p.z - ori.z);
	}

	_t += t;

	particle->getDynamicObj()->addForce((_k / _r * _r) * v * exp(-t / tE));
}



