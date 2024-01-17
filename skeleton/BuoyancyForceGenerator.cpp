#include "BuoyancyForceGenerator.h"
#include <iostream>

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float v, float d) {
	_height = h;
	_volume = v;
	_liquid_density = 1000;

	_liquid_particle = new Particle(Vector4(0, 0, 0.0, 0), Vector3(0, 35, 0), 
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85,
		Particle::ACTIVE, &physx::PxBoxGeometry(1, 1, 1), 0);
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->getPosition().p.y;
	float h0 = _liquid_particle->getPosition().p.y;

	Vector3 f(0,0,0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h0 > _height * 0.5) {
		immersed = 1;
	}
	else {
		immersed = ((h0 - h) / _height) + 0.5;
	}

	f.y = _liquid_density * _volume * immersed;
	//f.y = _liquid_density * _volume * immersed * _gravity;

	particle->addForce(f);
}

