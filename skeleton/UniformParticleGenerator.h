#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
private:
	Vector3 _vel_width, _pos_width;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
	std::uniform_real_distribution<double> _v{ 0,2 };
	std::uniform_real_distribution<double> _p{ 0,5 };
public:
	UniformParticleGenerator(Particle* p);
	~UniformParticleGenerator();
	virtual std::list<Particle*> generateParticle();
};

