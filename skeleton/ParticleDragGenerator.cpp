#include "ParticleDragGenerator.h"
#include <iostream>

ParticleDragGenerator::ParticleDragGenerator() {

}

ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2, Vector3 airVelocity) {
	_k1 = k1;
	_k2 = k2;
	_airVelocity = airVelocity;
}

void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	// Check that the partivle has Finite Mass
	if (fabs(particle->getInvM() < 1e-10))
		return;

	// Compute the drag force
	Vector3 v = particle->getVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = (_airVelocity-v) * drag_coef;
	dragF = _k1 * (_airVelocity - v);
	// Apply the drag force
	//std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << "\n";
	particle->addForce(dragF);
}

void ParticleDragGenerator::updateForce(RigidBody* particle, double t) {
	// Compute the drag force
	Vector3 v = particle->getVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = (_airVelocity - v) * drag_coef;
	dragF = _k1 * (_airVelocity - v);
	// Apply the drag force
	//std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << "\n";
	particle->getDynamicObj()->addForce(dragF);
}

