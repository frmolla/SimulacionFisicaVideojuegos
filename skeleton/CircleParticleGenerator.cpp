#include "CircleParticleGenerator.h"
#include <math.h>

CircleParticleGenerator::CircleParticleGenerator(Particle* p, std::string name)
    : GaussianParticleGenerator(p, name) {
    _model = p;
}

CircleParticleGenerator::~CircleParticleGenerator() {

}

std::list<Particle*> CircleParticleGenerator::generateParticle() {
    std::list<Particle*> nP;

    Firework* pType = static_cast <Firework*> (_model);
    int p = vr(_mt);
    if (pType) {
        Vector4 c;
        if (rand() % 2 == 1)
            c = Vector4(1, 0, 0, 1);
        else 
            c = Vector4(1, 1, 1, 1);
        Firework* par = new Firework(c, Vector3(nPos.x, nPos.y, nPos.z),
            Vector3(cos(r) * 20, a(_mt), sin(r) * 20),
            _model->getAc(), _model->getDamping(), Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), gen);
        par->setLifeTime(3);
        par->addGenerator(this);
        setParticle(par, true);
        nP.push_back(par);
    }

    return nP;
};

