#include "WhirlwindForceGenerator.h"
#include <iostream>

WhirlwindForceGenerator::WhirlwindForceGenerator(const float k1, const float k2, Vector3 airVelocity, const float k, float r, Vector3 o) 
	: ParticleDragGenerator(k1,k2,airVelocity){
	_k = k;
	_r = r;
	ori = o;
}

void WhirlwindForceGenerator::updateForce(Particle* particle, double t) {

	if ((particle->getPosition().p - ori).magnitude() < _r) {
		_airVelocity.x = -(particle->getPosition().p.z - ori.z);
		_airVelocity.y = (80 - (particle->getPosition().p.y - ori.y));
		_airVelocity.z = ((particle->getPosition().p.x - ori.x));
	}

	ParticleDragGenerator::updateForce(particle,t);
}


