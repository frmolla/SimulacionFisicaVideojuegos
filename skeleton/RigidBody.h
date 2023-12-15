#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class RigidBody
{
public:
	enum states { UNUSED, ACTIVE };

	RigidBody(bool dyn, physx::PxGeometry* nGeo, physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos, Vector4 nColor, float life_time, float mI = 0.15f);
	~RigidBody();

	int type;
	float time = 0;

	float _mI;

	inline physx::PxTransform getPosition() { return (_dyn) ? rb->getGlobalPose() : st->getGlobalPose(); }

	inline void setPosition(Vector3 nPos) {
		_pos.x = nPos.x;
		_pos.y = nPos.y;
		_pos.z = nPos.z;
	}

	inline Vector3 getVelocity() {
		return (_dyn) ? rb->getLinearVelocity() : Vector3(0,0,0);
	}

	inline physx::PxRigidDynamic* getDynamicObj() {
		return rb;
	}

	inline int getLifeTime() {
		return _life_time;
	}

	inline void setLifeTime(float nLifeTime) {
		_life_time = nLifeTime;
	}

	inline Vector4 getColor() { return _color; }

	inline physx::PxGeometry* getGeo() { return _geo; }

	inline RigidBody* clone() const {
		return new RigidBody(_dyn, _geo, _gPhysics, _gScene, _pos, _color, _life_time);
	}

private:
	bool _dyn;
	physx::PxGeometry* _geo;
	physx::PxPhysics* _gPhysics;
	physx::PxScene* _gScene;

	physx::PxRigidDynamic* rb;
	physx::PxRigidStatic* st;

	Vector3 _pos;
	Vector4 _color;

	float _life_time;
	RenderItem* rItem;
};

