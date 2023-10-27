#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Particle* p, std::string name)
    : ParticleGenerator(name, 1) {
    _model = p;

}

GaussianParticleGenerator::~GaussianParticleGenerator() {

}

std::list<Particle*> GaussianParticleGenerator::generateParticle() {
	std::list<Particle*> nP;
	int dir = _u(_mt);

    Firework* pType = static_cast <Firework*> (_model);
    if (pType) {
        Firework* par = new Firework(_model->getColor(), Vector3(p(_mt), 0, p(_mt)),
            Vector3(dir * _model->getVelocity().x * v(_mt), a(_mt) * _model->getVelocity().y, dir * _model->getVelocity().z * v(_mt)),
            _model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), 1);
        par->setLifeTime(2);
        par->addGenerator(new GaussianParticleGenerator(par->clone(), "n"));
        nP.push_back(par);
    }
    else {
        Particle* par = new Particle(_model->getColor(), Vector3(p(_mt), 0, p(_mt)),
            Vector3(dir * _model->getVelocity().x * v(_mt), a(_mt) * _model->getVelocity().y, dir * _model->getVelocity().z * v(_mt)),
            _model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f));
        par->setLifeTime(2);
        nP.push_back(par);
    }   

	return nP;
};

