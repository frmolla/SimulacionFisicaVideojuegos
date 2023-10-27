#pragma once
#include "GaussianParticleGenerator.h"

class CircleParticleGenerator : public GaussianParticleGenerator
{
public:
	CircleParticleGenerator(Particle* p, std::string name);
	~CircleParticleGenerator();
	virtual std::list<Particle*> generateParticle();
};

