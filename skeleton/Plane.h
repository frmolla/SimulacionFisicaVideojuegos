#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Plane
{
public:

	Plane(Vector4 color, Vector3 initPos, Vector3 _tam);
	~Plane();

	physx::PxTransform getPosition();

private:
	Vector4 color;
	Vector3 tam;

	physx::PxTransform pos;
	RenderItem* renderItem;
};

