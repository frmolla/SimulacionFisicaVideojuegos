#include "RubberSrpingForceGenerator.h"
#include <iostream>

RubberSrpingForceGenerator::RubberSrpingForceGenerator(float k, float x0, Particle* p, float dis)
	: SpringForceGenerator(k, x0, p) {
	other = p;
	_dis = dis;
}

void RubberSrpingForceGenerator::updateForce(Particle* particle, double t) {
	if (abs((particle->getPosition().p - other->getPosition().p).magnitude()) > _dis) {
		//std::cout << abs((particle->getPosition().p - other->getPosition().p).magnitude()) << std::endl;
		SpringForceGenerator::updateForce(particle, t);
	}

	/*Vector3 f = particle->getPosition().p;
	f -= other->getPosition().p;

	float lenght = f.normalize();
	lenght -= _x0;

	if (lenght <= 0.0f)
		return;

	f *= -(lenght*_k);
	particle->addForce(f);*/
}

