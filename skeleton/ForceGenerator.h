#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() {};
	virtual ~ForceGenerator() {}

	virtual void updateForce(Particle* particle, double t) = 0;
	std::string _name;
	double _t = 0.0; 
	double _duration = -1e10;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; 
	}
};

