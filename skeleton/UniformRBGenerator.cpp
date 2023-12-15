#include "UniformRBGenerator.h"

UniformRBGenerator::UniformRBGenerator(RigidBody* p, int kind, std::string name, physx::PxPhysics* gPhysics, physx::PxScene* gScene, int num)
	: RigidBodyGenerator(name, num), _gPhysics(gPhysics), _gScene(gScene) {
	_model = p;
	_kind = kind;
}

UniformRBGenerator::~UniformRBGenerator() {

}

std::list<RigidBody*> UniformRBGenerator::generateRB() {
	std::list<RigidBody*> nP;
	RigidBody* p;
	physx::PxBoxGeometry* g;
	float mI = _m(_mt);
	switch (_kind)
	{
	case 0:
		//g = new physx::PxBoxGeometry(2 + (rand() % 2), 2 + (rand() % 2), 2 + (rand() % 2));
		g = new physx::PxBoxGeometry(3, 3, 3);
		p = new RigidBody(true, g, _gPhysics, _gScene,Vector3(40 * _v(_mt), _r(_mt), 40 * _v(_mt)),
			_model->getColor(), _model->getLifeTime(), mI);
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	case 1:
		//g = new physx::PxBoxGeometry(2 + (rand() % 2), 2 + (rand() % 2), 2 + (rand() % 2));
		g = new physx::PxBoxGeometry(3, 3, 3);
		p = new RigidBody(false, g, _gPhysics, _gScene, Vector3(40 * _v(_mt), _r(_mt), 40 * _v(_mt)),
			_model->getColor(), _model->getLifeTime());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	}

	return nP;
}

