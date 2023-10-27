#include "Firework.h"
#include "GaussianParticleGenerator.h"

Firework::Firework(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* geo, int gen) 
	: Particle(nColor, initPos, initVel, initAc, nDamping, state, geo) {
	_gen = gen;
}

Firework::~Firework() {

}

std::list<Particle*> Firework::explode() {
	std::list<Particle*> newP;

	for (int i = 0; i < _gen; i++) {

		std::list<Particle*> lGen = generator->generateParticle();

		for (auto lF = lGen.begin(); lF != lGen.end(); ++lF) {
			(*lF)->setLifeTime(1);
			static_cast <Firework*> (*lF)->addGenerator(new GaussianParticleGenerator(clone(), std::to_string(i)));
			newP.push_back(*lF);
		}

		//int invM = 1 / 2.0f;
		//Vector3 vel = Vector3(5, 30, 5);
		//float damping = 0.99f;
		//Vector4 color = Vector4(0, 0, 1, 1);
		//Firework* fP = new Firework(Vector4(0, 0, 1, 1), Vector3(this->getPosition().p.x, this->getPosition().p.y, this->getPosition().p.z),
		//	Vector3(vel.x, vel.y, vel.z),
		//	Vector3(0, -10, 0), damping, Particle::ACTIVE, &physx::PxSphereGeometry(1.5f), _gen - 1);
		//fP->setLifeTime(1);
		//newP.push_back(fP);
	}
	
	return newP;
}

void Firework::addGenerator(ParticleGenerator* p) {
	generator = p;
}

Particle* Firework::clone() const {
	return new Firework(color, Vector3(pos.p.x,pos.p.y,pos.p.z), vel, ac, damping, type, &physx::PxSphereGeometry(1.5f), _gen);
}

