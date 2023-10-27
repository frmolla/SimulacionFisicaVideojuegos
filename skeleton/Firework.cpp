#include "Firework.h"
#include "GaussianParticleGenerator.h"

Firework::Firework(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* geo, int gen) 
	: Particle(nColor, initPos, initVel, initAc, nDamping, state, geo) {
	_gen = gen;
}

Firework::~Firework() {
	renderItem->release();
}

std::list<Particle*> Firework::explode() {
	std::list<Particle*> newP;

	GaussianParticleGenerator* gpg = static_cast <GaussianParticleGenerator*> (generator);
	gpg->newGen(_gen - 1);
	if (_gen > 0) {
		for (int i = 0; i < 10; i++) {
	
			gpg->newPos(pos.p.x, pos.p.y, pos.p.z);
			gpg->newR(cir * i);
			std::list<Particle*> lGen = generator->generateParticle();

			for (auto lF = lGen.begin(); lF != lGen.end(); ++lF) {
				(*lF)->setLifeTime(3);

				newP.push_back(*lF);
			}
		}
	}
	
	return newP;
}

void Firework::addGenerator(ParticleGenerator* p) {
	generator = p;
}

Particle* Firework::clone() const {
	return new Firework(color, Vector3(pos.p.x,pos.p.y,pos.p.z), vel, ac, damping, type, &physx::PxSphereGeometry(1.5f), _gen);
}

