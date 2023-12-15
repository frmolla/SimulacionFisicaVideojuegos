#include "Scene.h"

Scene::Scene(physx::PxPhysics* gPhysics, physx::PxScene* gScene)
	: _gPhysics(gPhysics), _gScene(gScene) {

	ground = new RigidBody(false, &physx::PxBoxGeometry(150,20,150), _gPhysics, _gScene, Vector3(0,10,0), Vector4(0.7,0.7,0.7,1), -1);
	//ob = new RigidBody(true, &physx::PxBoxGeometry(5,5,5), _gPhysics, _gScene, Vector3(0,50,0), Vector4(0.8, 0.8, 0.8, 1), -1);

	rbD = new RigidBodySystem(_gPhysics, _gScene, 0);
}

Scene::~Scene() {
	
}

void Scene::integrate(double t) {
	rbD->integrate(t);
}

void Scene::keyPress(unsigned char key) {
	switch (toupper(key))
	{
	case 'A': {
		//rbS;
		break;
	}
	case 'S': {
		//rbD;
		break;
	}
	default:
		break;
	}
}
