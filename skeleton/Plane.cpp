#include "Plane.h"

Plane::Plane(Vector4 color, Vector3 initPos, Vector3 _tam) : tam(_tam) {

	pos = physx::PxTransform(initPos.x, initPos.y, initPos.z);

	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(tam)), &pos, color);
}

Plane::~Plane() {
	renderItem->release();
}

physx::PxTransform Plane::getPosition() {
	return pos;
}


