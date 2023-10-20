#include "Particle.h"

#include <math.h>

Particle::Particle(Vector4 nColor, Vector3 initPos, Vector3 initVel, Vector3 initAc, float nDamping, int state, physx::PxGeometry* geo) 
	: vel(initVel), ac(initAc), damping(nDamping), type(state), color(nColor) {

	pos = physx::PxTransform(initPos.x, initPos.y, initPos.z);

	renderItem = new RenderItem(CreateShape(*geo), &pos, color);
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	time += t;

	vel.x = (vel.x + ac.x * t) * pow(damping,t);
	vel.y = (vel.y + ac.y * t) * pow(damping,t);
	vel.z = (vel.z + ac.z * t) * pow(damping,t);

	pos.p.x += vel.x * t;
	pos.p.y += vel.y * t;
	pos.p.z += vel.z * t;
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

void Particle::setLifeTime(int nLifeTime) {
	life_time = nLifeTime;
}
