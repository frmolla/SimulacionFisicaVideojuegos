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

std::string display_text = "SIM_FIS";


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

bool f = false;
bool fO = false;
bool r = false;
bool fw1 = false;
bool fw2 = false;
bool fw3 = false;
bool m = false;

void init() {
	sM0 = new ShotManager(0);
	sM1 = new ShotManager(1);
	sM2 = new ShotManager(2);
	ground = new Plane(Vector4(0.5, 0.5, 0.5, 1), Vector3(0, 0, 0), Vector3(300, 5, 300));
	target = new Plane(Vector4(1, 0, 0, 1), Vector3(-100, 50, -100), Vector3(5, 5, 5));
	pF = new ParticleSystem(0);
	pN = new ParticleSystem(1);
	pL = new ParticleSystem(2);
	f1 = new ParticleSystem(3);
	f2 = new ParticleSystem(4);
	f3 = new ParticleSystem(5);
	m1 = new ParticleSystem(6);
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
}

void integrate(double t) {
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

	switch(toupper(key))
	{
	case '1': {
		sM0->shot();
		break;
	}
	case '2': {
		sM1->shot();
		break;
	}
	case '3': {
		sM2->shot(); 
		break;
	}
	case 'Z': {
		f = !f;
		break;
	}
	case 'X': {
		fO = !fO;
		break;
	}
	case 'C': {
		r = !r;
		break;
	}
	case 'V': {
		fw1 = !fw1;
		break;
	}
	case 'B': {
		fw2 = !fw2;
		break;
	}
	case 'N': {
		fw3 = !fw3;
		break;
	}
	case 'M': {
		m = !m;
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