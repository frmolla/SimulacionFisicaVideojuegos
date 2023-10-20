#pragma once
#include <string>
#include <list>
#include "core.hpp"
#include "Particle.h"
#include <random>

class ParticleGenerator
{
public:
	ParticleGenerator(); // sin implementar
	~ParticleGenerator(); // sin implementar
	void setParticle(Particle* model); // sin implementar
	virtual std::list<Particle*> generateParticle() = 0;
	inline void setOrigin(const Vector3& p) { _mean_pos = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_vel = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_vel;
	}
	inline void setMeanDuration(double new_duration) {
		_model->setLifeTime(new_duration);
	}
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete _model;
		//_model = p->clone();
		if (modify_pos_vel) {
			_mean_pos = p->getPosition().p;
			_mean_vel = p->getVelocity();
		}
		_model->setPosition({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNParticles(int n_p) { _num_particles = n_p; }
	inline int getNumParticles() { return _num_particles; }
	inline std::string getName() { return _name; }
protected:
	int _num_particles = 2500;
	double _generation_probability = 1;
	Particle* _model = nullptr;
	Vector3 _mean_pos, _mean_vel;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
	std::string _name;
};

