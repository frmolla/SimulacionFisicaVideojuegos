#pragma once
#include <string>
#include <list>
#include "core.hpp"
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(); // sin implementar
	~ParticleGenerator(); // sin implementar
	void setParticle(Particle* model); // sin implementar
	virtual std::list<Particle*> generateParticle() = 0;
private:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* _model;
};

