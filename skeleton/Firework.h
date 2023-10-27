#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"

class Firework : public Particle
{
public:
	Firework(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* geo, int gen);
	~Firework();
	std::list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	Particle* clone() const;
protected:
	unsigned _type;
	std::list<std::shared_ptr<ParticleGenerator> > _gens;
private:
	int _gen;
	int cir = 36;
	Particle* pModel;
	ParticleGenerator* generator;
};

