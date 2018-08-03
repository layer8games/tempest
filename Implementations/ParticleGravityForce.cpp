#include <Engine/ParticleGravityForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleGravityForce::ParticleGravityForce(void) 
: 
_gravityAcc(KM::Vector(0.0f, -1.0f))
{  }

ParticleGravityForce::ParticleGravityForce(const KM::Vector& gravity) 
: 
_gravityAcc(gravity)
{  }

ParticleGravityForce::~ParticleGravityForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleGravityForce::v_UpdateForce(shared_ptr<Particle> particle)
{
	if(!particle->HasFiniteMass()) return;

	particle->AddForce(_gravityAcc * particle->GetMass());
}