#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
private:
	int _kind;
	Vector3 _vel_width, _pos_width;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _v{ -1,1 };
	std::uniform_real_distribution<double> _k{ 0.95,1.05 };
	std::uniform_real_distribution<double> _p{ 0,5 };
	std::uniform_real_distribution<double> _f{ -100,100 };
	std::uniform_real_distribution<double> _fv{ -10,10 };
public:
	UniformParticleGenerator(Particle* p, int kind ,std::string name, int num = 1);
	~UniformParticleGenerator();
	virtual std::list<Particle*> generateParticle();
};

