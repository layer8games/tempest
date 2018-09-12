#include <Engine/ParticleDragForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleDragForce::ParticleDragForce(void) 
{  }

ParticleDragForce::ParticleDragForce(real drag, real dragSqr) 
: 
_drag(drag), 
_dragSqr(dragSqr)
{  }

ParticleDragForce::~ParticleDragForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleDragForce::v_UpdateForce(shared_ptr<Particle> particle)
{
	KM::Vector force = particle->GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _drag * dragCoeff  + _dragSqr * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	particle->AddForce(force);
}