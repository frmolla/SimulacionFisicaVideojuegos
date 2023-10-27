#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
	int gen;
	int tGen;
	int r = 0;
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
	std::normal_distribution<double> p{0,2};
	std::normal_distribution<double> v{1,0.25};
	std::normal_distribution<double> a{70,15};
	std::normal_distribution<double> vr{0,15};
	Vector3 nPos = Vector3(0,0,0);
public:
	GaussianParticleGenerator(Particle* p, std::string name);
	~GaussianParticleGenerator();
	virtual std::list<Particle*> generateParticle();
	void newPos(int nX, int nY, int nZ);
	void newGen(int nG);
	void newR(int nR);
	void setTGen(int nTGen);
	int getTGen();
};

