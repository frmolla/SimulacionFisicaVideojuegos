#include "Scene.h"
#include <iostream>

Scene::Scene(physx::PxPhysics* gPhysics, physx::PxScene* gScene)
	: _gPhysics(gPhysics), _gScene(gScene) {

	srand(time(NULL));

	initScene();

	rbD = new RigidBodySystem(_gPhysics, _gScene, 0, 0);
	rbD->setWind(Vector3(viento, 0, 0));
}

Scene::~Scene() {
	
}

void Scene::integrate(double t) {
	colS = rbD->getCol();
	rbD->integrate(t);
	pF->integrate(t);
	m1->integrate(t);
	if (clima == 0)
		pN->integrate(t);
	else
		pL->integrate(t);

	if (win == 0) { // wp1
		f1->integrate(t);
		if (!end) {
			f1->setPV(posP1);
			end = true;
		}
	}
	else if (win == 1) { // wp2
		f1->integrate(t);
		if (!end) {
			f1->setPV(posP2);
			end = true;
		}	
	}
}

void Scene::keyPress(unsigned char key) {
	switch (toupper(key))
	{
	case 'A': {

		break;
	}
	case 'S': {

		break;
	}
	default:
		break;
	}
}

void Scene::actionP(int angle, int vel, int turno) {
	colM = true;
	_angle = angle; // cuidado rad
	_vel = vel;
	_turno = turno;

	Vector3 pos;
	int vx, vy;
	if (_turno == 0) {
		pos = Vector3(posP1.x, posP1.y + 50, posP1.z); // 0 - posP1
		vx = vel * cos(angle * 3.14 / 180);
		vy = vel * sin(angle * 3.14 / 180);
	}
	else {
		pos = Vector3(posP2.x, posP2.y + 50, posP2.z);  // 1 - posP2
		vx = -vel * cos(-angle * 3.14 / 180);
		vy = -vel * sin(-angle * 3.14 / 180);
	}
	
	rbD->setLanzamiento(pos, Vector3(vx, vy, 0));
}

void Scene::collisionS(physx::PxActor* actor1, physx::PxActor* actor2, int & v) {
	if (actor1 == player1->getST()) {
		// win player2
		v = 1;
	}
	else if (actor2 == player1->getST()) {
		// win player2
		v = 1;
	}
	else if (actor1 == player2->getST()) {
		// win player 1
		v = 0;
	}
	else if (actor2 == player2->getST()) {
		// win player 1
		v = 0;
	}
	if (actor1->getName() == "plat" || actor2->getName() == "plat") {
		rbD->col();
		colM = false;
	}
}

void Scene::initScene() {

	initSystems();

	ground = new RigidBody(false, &physx::PxBoxGeometry(200, 20, 200), _gPhysics, _gScene, Vector3(0, 10, 0), Vector4(0.64f, 0.64f, 0.65f, 1.0f), -1);
	sun = new RigidBody(false, &physx::PxSphereGeometry(50), _gPhysics, _gScene, Vector3(0, 500, 0), Vector4(1.0f, 1.0f, 0.0f, 1.0f), -1);
	//ob = new RigidBody(true, &physx::PxBoxGeometry(5,5,5), _gPhysics, _gScene, Vector3(0,50,0), Vector4(0.8, 0.8, 0.8, 1), -1);

	plat1 = new RigidBody(false, &physx::PxBoxGeometry(20, 40, 20), _gPhysics, _gScene, Vector3(-100, 20, 0), Vector4(0.37f, 0.63f, 0.64f, 1.0f), -1);
	player1 = new RigidBody(false, &physx::PxBoxGeometry(10, 10, 10), _gPhysics, _gScene, posP1, Vector4(0.86f, 0.66f, 0.36f, 1.0f), -1);
	player1->getST()->setName("p1");

	plat2 = new RigidBody(false, &physx::PxBoxGeometry(20, 40, 20), _gPhysics, _gScene, Vector3(100, 20, 0), Vector4(0.37f, 0.63f, 0.64f, 1.0f), -1);
	player2 = new RigidBody(false, &physx::PxBoxGeometry(10, 10, 10), _gPhysics, _gScene, posP2, Vector4(0.86f, 0.66f, 0.36f, 1.0f), -1);
	player2->getST()->setName("p2");

	for (int i = 1; i < 9; i++) {
		int h;
		if (i == 1 || i == 8) {
			h = 50;
		}
		else {
			int s = rand() % 2;
			if (s == 0)
				h = 40 + (rand() % 5) * 10;
			else
				h = 60 - (rand() % 5) * 10;
		}
		RigidBody* k = new RigidBody(false, &physx::PxBoxGeometry(10, h, 20), _gPhysics, _gScene, Vector3(90 - 20 * i, 20, 0), colores[i % 3], -1);
	}

	for (int i = 1; i < 25; i++) {
		int h;
		if (i == 1 || i == 8) {
			h = 100;
		}
		else {
			int s = rand() % 2;
			if (s == 0)
				h = 100 + (rand() % 5) * 10;
			else
				h = 100 - (rand() % 5) * 10;
		}
		RigidBody* k = new RigidBody(false, &physx::PxBoxGeometry(10, h, 20), _gPhysics, _gScene, Vector3(250 - 20 * i, 20, -200), colores[i % 3], -1);
		k = new RigidBody(false, &physx::PxBoxGeometry(10, h, 20), _gPhysics, _gScene, Vector3(-200, 20, 250 - 40 * i), colores[i % 3], -1);
		k = new RigidBody(false, &physx::PxBoxGeometry(10, h, 20), _gPhysics, _gScene, Vector3(200, 20, 250 - 40 * i), colores[i % 3], -1);
	}
}

void Scene::initSystems() {
	pF = new ParticleSystem(0);
	pN = new ParticleSystem(1);
	pL = new ParticleSystem(2);
	m1 = new ParticleSystem(6);
	f1 = new ParticleSystem(4);

	m1->setE5();
	m1->setG();
	m1->setE1();

	clima = (rand() % 2);
	viento = (rand() % 2);
	if (viento == 0)
		viento = (rand() % 2) + 1 * 20;
	else
		viento = (rand() % 2) + 1 * -20;

	pF->setWF(viento/20);
	pN->setWF(viento/20);
	pL->setWF(viento/20);
	m1->setWF(viento);
}
