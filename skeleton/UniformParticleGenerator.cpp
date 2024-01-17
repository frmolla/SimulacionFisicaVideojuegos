#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Particle* p, int kind,std::string name, int num) : ParticleGenerator(name, num) {
	_model = p;
	_kind = kind;
}

UniformParticleGenerator::~UniformParticleGenerator() {
	
}

std::list<Particle*> UniformParticleGenerator::generateParticle() {

	std::list<Particle*> nP;
	Particle* p;
	switch (_kind)
	{
	case 0:
		p = new Particle(_model->getColor(), Vector3(_model->getPosition().p.x + _p(_mt), 20, _model->getPosition().p.z + _p(_mt)),
			Vector3(_model->getVelocity().x * _v(_mt), _model->getVelocity().y * _k(_mt), _model->getVelocity().z * _v(_mt)),
			_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), _model->getInvM());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	case 1:
		p = new Particle(_model->getColor(), Vector3(_f(_mt), _f(_mt), _f(_mt)),
			Vector3(_fv(_mt) * _model->getVelocity().x, _fv(_mt) * _model->getVelocity().y, _fv(_mt) * _model->getVelocity().z),
			Vector3(0, 0, 0), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.0f), _model->getInvM());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	case 2:
		p = new Particle(_model->getColor(), Vector3(_f(_mt), 250, _f(_mt)),
			Vector3(_model->getVelocity().x * _v(_mt), _model->getVelocity().y, _model->getVelocity().z * _v(_mt)),
			_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(0.2f), _model->getInvM());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	case 6:
		p = new Particle(_model->getColor(), Vector3(0, 50, _v(_mt) * 10),
			Vector3(0, 0, 0),
			_model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(5.0f), _model->getInvM());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	}
	
	return nP;
}

