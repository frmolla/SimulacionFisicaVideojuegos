#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Particle* p, std::string name)
    : ParticleGenerator(name, 1) {
    _model = p;
}

GaussianParticleGenerator::~GaussianParticleGenerator() {

}

std::list<Particle*> GaussianParticleGenerator::generateParticle() {
	std::list<Particle*> nP;

    Firework* pType = static_cast <Firework*> (_model);
    if (pType) {
        Firework* par = new Firework(Vector4(_u(_mt), _u(_mt), 0, 1), Vector3(nPos.x, nPos.y, nPos.z),
            Vector3(vr(_mt), a(_mt), vr(_mt)),
            _model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), gen);
        par->setLifeTime(3);
        par->addGenerator(this);
        setParticle(par, true);
        nP.push_back(par);
    }


	return nP;
};

void GaussianParticleGenerator::newPos(int nX, int nY, int nZ) {
    nPos.x = nX;
    nPos.y = nY;
    nPos.z = nZ;
}

void GaussianParticleGenerator::newGen(int nG) {
    gen = nG;
}

void GaussianParticleGenerator::newR(int nR) {
    r = nR;
}

void GaussianParticleGenerator::setTGen(int nTGen) {
    tGen = nTGen;
}

int GaussianParticleGenerator::getTGen() {
    return tGen;
}


