#include "Plane.h"

Plane::Plane(Vector4 color, Vector3 initPos) {

	pos = physx::PxTransform(initPos.x, initPos.y, initPos.z);

	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(300,5,300)), &pos, color);
}

Plane::~Plane() {
	renderItem->release();
}

physx::PxTransform Plane::getPosition() {
	return pos;
}


