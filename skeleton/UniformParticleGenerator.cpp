#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Particle* p, int kind,std::string name, int num) : ParticleGenerator(name, num) {
	_model = p;
	_kind = kind;
}

UniformParticleGenerator::~UniformParticleGenerator() {
	
}

std::list<Particle*> UniformParticleGenerator::generateParticle() {

	std::list<Particle*> nP;

	switch (_kind)
	{
	case 0:
		nP.push_back(new Particle(_model->getColor(), Vector3(_p(_mt), 0, _p(_mt)),
			Vector3(_model->getVelocity().x * _v(_mt), _model->getVelocity().y * _k(_mt), _model->getVelocity().z * _v(_mt)),
			_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f)));
		break;
	case 1:
		nP.push_back(new Particle(_model->getColor(), Vector3(_f(_mt), _f(_mt), _f(_mt)),
			Vector3(_fv(_mt) * _model->getVelocity().x,_fv(_mt) * _model->getVelocity().y, _fv(_mt) * _model->getVelocity().z),
			Vector3(0,0,0), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.0f)));
		break;
	case 2:
		nP.push_back(new Particle(_model->getColor(), Vector3(_f(_mt), 150, _f(_mt)),
			Vector3(_model->getVelocity().x * _v(_mt), _model->getVelocity().y, _model->getVelocity().z * _v(_mt)),
			_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(0.2f)));
		break;
	}
	

	return nP;
}

