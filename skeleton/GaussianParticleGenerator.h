#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"

class GaussianParticleGenerator : public ParticleGenerator
{
private:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
	std::normal_distribution<double> p{0,2};
	std::normal_distribution<double> v{1,0.25};
	std::normal_distribution<double> a{1,0.15};
public:
	GaussianParticleGenerator(Particle* p, std::string name);
	~GaussianParticleGenerator();
	virtual std::list<Particle*> generateParticle();
};

