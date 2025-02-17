#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "ShotManager.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "Scene.h"

#include <string>

int text = 0; // 0 - p1 / 1 - p2
int win = -1; // -1 - jugando / 0 - wp1 / 1 - wp2
std::vector<std::string> display_texts = { "PROYECTO_FINAL_GB" , "Player1:", "Player2:" };
std::string angleV = "0";
std::string velV = "0";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

ShotManager* sM0;
ShotManager* sM1;
ShotManager* sM2;

Plane* ground;
Plane* target;

ParticleSystem* pF;
ParticleSystem* pN;
ParticleSystem* pL;
ParticleSystem* f1;
ParticleSystem* f2;
ParticleSystem* f3;
ParticleSystem* m1;

Scene* s;

bool f = false;
bool fO = false;
bool r = false;
bool fw1 = false;
bool fw2 = false;
bool fw3 = false;
bool m = false;

int angleAux = 0;
int velAux = 0;

float timer = 0;
float timerAUX = 0;

void init() {
	sM0 = new ShotManager(0);
	sM1 = new ShotManager(1);
	sM2 = new ShotManager(2);
	//ground = new Plane(Vector4(0.5, 0.5, 0.5, 1), Vector3(0, 0, 0), Vector3(300, 5, 300));
	//target = new Plane(Vector4(1, 0, 0, 1), Vector3(-100, 50, -100), Vector3(5, 5, 5));
	pF = new ParticleSystem(0);
	pN = new ParticleSystem(1);
	pL = new ParticleSystem(2);
	f1 = new ParticleSystem(3);
	f2 = new ParticleSystem(4);
	f3 = new ParticleSystem(5);
	m1 = new ParticleSystem(6);

	s = new Scene(gPhysics, gScene);
}

void free() {
	delete(sM0);
	delete(sM1);
	delete(sM2);
	delete(ground);
	delete(target);
	delete(pF);
	delete(pN);
	delete(pL);
	delete(f1);
	delete(f2);
	delete(f3);
	delete(m1);
	delete(s);
}

void reset() {
	text = 0;
	win = -1;
	angleV = std::to_string(0);
	angleAux = 0;
	velV = std::to_string(0);
	velAux = 0;
}

void integrate(double t) {
	if (win != -1)
		timer += t;
	timerAUX += t;
	sM0->integrate(t);
	sM1->integrate(t);
	sM2->integrate(t);
	if (f) {
		pF->integrate(t);
	}
	if (fO) {
		pN->integrate(t);
	}
	if (r) {
		pL->integrate(t);
	}
	if (fw1) {
		f1->integrate(t);
	}
	if (fw2) {
		f2->integrate(t);
	}
	if (fw3) {
		f3->integrate(t);
	}
	if (m) {
		m1->integrate(t);
	}

	s->integrate(t);

	if (timer > 10) {
		reset();
		timer = 0;
	}

	if (timerAUX > 10 && s->getColM()) {
		timerAUX = 0;
		s->setColM(false);
	}
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	//gMaterial = gPhysics->createMaterial(1.0f, 1.0f, 1.0f);
	//gMaterial = gPhysics->createMaterial(0.0f, 0.0f, 0.0f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// My particle
	init();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	integrate(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	free();

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	s->keyPress(key);

	switch(toupper(key))
	{
	case 'R': {
		if (!s->getColM()) {
			angleAux += 5;
			angleV = std::to_string(angleAux);
		}
		break;
	}	
	case 'F': {
		if (!s->getColM()) {
			angleAux -= 5;
			angleV = std::to_string(angleAux);
		}		
		break;
	}
	case 'Y': {
		if (!s->getColM()) {
			velAux += 5;
			velV = std::to_string(velAux);
		}	
		break;
	}
	case 'H': {
		if (!s->getColM()) {
			velAux -= 5;
			velV = std::to_string(velAux);
		}	
		break;
	}
	case 'C': {
		// Confirmar
		if (!s->getColM()) {
			s->actionP(angleAux, velAux, text);
			angleAux = 0;
			velAux = 0;
			angleV = std::to_string(angleAux);
			velV = std::to_string(velAux);
			text = (text + 1) % 2;
			timerAUX = 0;
		}	
		break;
	}
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	s->collisionS(actor1, actor2, win);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 

	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}