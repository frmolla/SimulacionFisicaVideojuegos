#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"

class Firework : public Particle
{
public:
	std::list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	virtual Particle* clone() const;
protected:
	unsigned _type;
	std::list<std::shared_ptr<ParticleGenerator> > _gens;
};

