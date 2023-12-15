#include "RigidBody.h"
#include <math.h>

RigidBody::RigidBody(bool dyn, physx::PxGeometry* nGeo, physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos, Vector4 nColor, float life_time)
	: _dyn(dyn), _geo(nGeo), _gPhysics(gPhysics), _gScene(gScene), _pos(pos), _color(nColor), _life_time(life_time) {

	type = ACTIVE;

	if (_dyn) {
		// rb	
		rb = gPhysics->createRigidDynamic(physx::PxTransform({_pos.x, _pos.y, _pos.z}));
		rb->setLinearVelocity({0,5,0});
		rb->setAngularVelocity({0,0,0});
		physx::PxShape* shape_ad = CreateShape(*_geo);
		rb->attachShape(*shape_ad);
		physx::PxRigidBodyExt::updateMassAndInertia(*rb, 0.15);
		gScene->addActor(*rb);

		RenderItem* dynamic_item;
		rItem = new RenderItem(shape_ad, rb, _color);
			
	}
	else {
		// st	
		st = gPhysics->createRigidStatic(physx::PxTransform({ _pos.x, _pos.y, _pos.z }));
		physx::PxShape* shape = CreateShape(*_geo);
		st->attachShape(*shape);
		gScene->addActor(*st);

		rItem = new RenderItem(shape, st, _color);
	}
}

RigidBody::~RigidBody() {
	rItem->release();
}

