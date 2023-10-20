#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Particle* p) : ParticleGenerator() {
	_model = p;
}

UniformParticleGenerator::~UniformParticleGenerator() {
	delete _model;
}

std::list<Particle*> UniformParticleGenerator::generateParticle() {
	std::list<Particle*> nP;
	int dir = _u(_mt);

	nP.push_back(new Particle(_model->getColor(), Vector3(_p(_mt), 0, _p(_mt)),
		Vector3(dir * _model->getVelocity().x * _v(_mt), _model->getVelocity().y, dir * _model->getVelocity().z * _v(_mt)),
		_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f)));

	return nP;
}

