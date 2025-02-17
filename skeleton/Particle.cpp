#include "Particle.h"

#include <math.h>

Particle::Particle(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* nGeo, float  nInvM) 
	: vel(initVel), ac(Vector3(0,0,0)), damping(nDamping), type(state), color(nColor), geo(nGeo), invM(nInvM) {

	pos = physx::PxTransform(initPos.x, initPos.y, initPos.z);

	renderItem = new RenderItem(CreateShape(*nGeo), &pos, color);
}

Particle::~Particle() {
	renderItem->release();
}

Particle* Particle::clone() const {
	return new Particle(color, Vector3(pos.p.x,pos.p.y,pos.p.z), vel, ac, damping, type, geo, invM);
}


void Particle::integrate(double t) {
	time += t;

	ac = force * invM;

	// Euler semi-implícito
	vel.x = (vel.x + ac.x * t) * pow(damping,t);
	vel.y = (vel.y + ac.y * t) * pow(damping,t);
	vel.z = (vel.z + ac.z * t) * pow(damping,t);

	pos.p.x += vel.x * t;
	pos.p.y += vel.y * t;
	pos.p.z += vel.z * t;

	// Euler
	/*pos.p.x += vel.x * t;
	pos.p.y += vel.y * t;
	pos.p.z += vel.z * t;

	vel.x = (vel.x + ac.x * t) * pow(damping, t);
	vel.y = (vel.y + ac.y * t) * pow(damping, t);
	vel.z = (vel.z + ac.z * t) * pow(damping, t);*/

	clearForce();
}

physx::PxTransform Particle::getPosition() {
	return pos;
}

void Particle::setPosition(Vector3 nPos) {
	pos.p.x = nPos.x;
	pos.p.y = nPos.y;
	pos.p.z = nPos.z;
}

Vector3 Particle::getVelocity() {
	return vel;
}

int Particle::getLifeTime() {
	return life_time;
}

void Particle::setLifeTime(float nLifeTime) {
	life_time = nLifeTime;
}
