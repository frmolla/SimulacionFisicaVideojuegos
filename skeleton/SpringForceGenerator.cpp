#include "SpringForceGenerator.h"
#include <iostream>

SpringForceGenerator::SpringForceGenerator(float k, float x0, Particle* p) {
	_k = k;
	_x0 = x0;
	other = p;
}

void SpringForceGenerator::updateForce(Particle* particle, double t) {

	Vector3 relative_pos_vector = other->getPosition().p - particle->getPosition().p;
	Vector3 force;
	
	const float lenght = relative_pos_vector.normalize();
	const float delta_x = lenght - _x0;

	force = relative_pos_vector * delta_x * _k;

	particle->addForce(force);
}

