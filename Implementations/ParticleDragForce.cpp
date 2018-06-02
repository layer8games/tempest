#include <Engine/ParticleDragForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleDragForce::ParticleDragForce(void) 
{  }

ParticleDragForce::ParticleDragForce(real k1, real k2) 
: 
_k1(k1), 
_k2(k2)
{  }

ParticleDragForce::~ParticleDragForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleDragForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
	KM::Vector2 force = particle->GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _k1 * dragCoeff  + _k2 * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	particle->AddForce(force);
}

void ParticleDragForce::v_UpdateForce(shared_ptr<Particle3D> particle)
{
	KM::Vector3 force = particle->GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _k1 * dragCoeff  + _k2 * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	particle->AddForce(force);
}