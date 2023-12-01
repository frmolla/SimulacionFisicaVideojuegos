#include "AnchoredSpringForceGenerator.h"
#include <iostream>

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float k, float x0, Vector3 anchor_pos)
	: SpringForceGenerator(k,x0,nullptr) { 
	other = new Particle(Vector4(1, 1, 1, 1), anchor_pos, 
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.85, 
		Particle::ACTIVE, &physx::PxBoxGeometry(5, 5, 5), 0);
}

void AnchoredSpringForceGenerator::updateForce(Particle* particle, double t) {
	SpringForceGenerator::updateForce(particle, t);
}

