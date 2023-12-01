#include "RigidBody.h"

RigidBody::RigidBody(bool dyn, physx::PxGeometry* nGeo) : _dyn(dyn){
	if (_dyn) {
		// rb
		/*
		rb = gPhysics->createRigisDynamic(PxTransfrom({-70,200,-27}));
		rb->setLinearVelocity({0,5,0});
		rb->setAngularVelocity({0,0,0});
		PxShape* shape_ad = CreateShape(geo);
		rb->attachShape(*shape_ad);
		PxRigidBodyExt::updateMassAndInertia(*rb, 0.15);
		gScene->addActor(*rb);

		RenderItem* dynamic_item;
		dynamic_item = new RenderItem(shape_ad, rb, { 0.8, 0.8, 0.8, 1 });
		*/	
	}
	else {
		// st
		/*
		st = gPhysics->createRigidStatic(PxTransform({0,0,0}));
		PxShape* shape = CreateShape(geo);
		st->attachShape(*shape);
		gScene->addActor(*st);

		RenderItem* item;
		item = new RenderItem(shape, st, { 0.8, 0.8, 0.8, 1 });
		*/
	}
}
