#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Plane
{
public:

	Plane(Vector4 color, Vector3 initPos);
	~Plane();

	physx::PxTransform getPosition();

private:
	Vector4 color;

	physx::PxTransform pos;
	RenderItem* renderItem;
};

