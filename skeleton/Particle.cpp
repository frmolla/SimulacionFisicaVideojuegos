#include "Particle.h"

Particle::Particle(Vector3 nPos, Vector3 nVel) {

	pos = physx::PxTransform(nPos.x, nPos.y, nPos.z);
	vel = nVel;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pos, Vector4(1, 0, 0, 1));
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	pos.p.x += vel.x;
	pos.p.y += vel.y;
	pos.p.z += vel.z;
}
