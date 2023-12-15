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
	switch (_kind)
	{
	case 0:
		p = new RigidBody(true, &physx::PxBoxGeometry(2 + (rand() % 2), 2 + (rand() % 2), 2 + (rand() % 2)),
			_gPhysics, _gScene, Vector3(40 * _v(_mt), _r(_mt), 40 * _v(_mt)), _model->getColor(), _model->getLifeTime());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	case 1:
		p = new RigidBody(false, &physx::PxBoxGeometry(5, 5, 5), _gPhysics, _gScene, Vector3(_f(_mt), 150, _f(_mt)), _model->getColor(), _model->getLifeTime());
		p->setLifeTime(_model->getLifeTime());
		nP.push_back(p);
		break;
	}

	return nP;
}

