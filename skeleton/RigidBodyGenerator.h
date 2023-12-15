#pragma once
#include <string>
#include <list>
#include "core.hpp"
#include "RigidBody.h"
#include <random>
#include <string>

class RigidBodyGenerator
{
public:
	RigidBodyGenerator(std::string name, int numP); 
	~RigidBodyGenerator(); 
	void setRB(RigidBody* model); 
	virtual std::list<RigidBody*> generateRB() = 0;
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
	inline void setRB(RigidBody* p, bool modify_pos_vel = true) {
		delete _model;
		_model = p->clone();
		if (modify_pos_vel) {
			_mean_pos = p->getPosition().p;
			_mean_vel = p->getVelocity();
		}
		_model->setPosition({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNRB(int n_p) { _num_RB = n_p; }
	inline int getNumRB() { return _num_RB; }
	inline std::string getName() { return _name; }
protected:
	int _num_RB = 1;
	double _generation_probability = 1;
	RigidBody* _model = nullptr;
	Vector3 _mean_pos, _mean_vel;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
	std::string _name;
};

