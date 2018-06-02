#include <Engine/ParticleGravityForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleGravityForce::ParticleGravityForce(void) 
: 
_gravityAcc2D(KM::Vector2(0.0f, -1.0f)),
_gravityAcc3D(KM::Vector3(0.0f, -1.0f, 0.0f))
{  }

ParticleGravityForce::ParticleGravityForce(const KM::Vector2& gravity) 
: 
_gravityAcc2D(gravity),
_gravityAcc3D(0.0f)
{  }

ParticleGravityForce::ParticleGravityForce(const KM::Vector3& gravity) 
: 
_gravityAcc2D(0.0f),
_gravityAcc3D(gravity)
{  }

ParticleGravityForce::~ParticleGravityForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleGravityForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
	if(!particle->HasFiniteMass()) return;

	particle->AddForce(_gravityAcc2D * particle->GetMass());
}

void ParticleGravityForce::v_UpdateForce(shared_ptr<Particle3D> particle)
{
	if(!particle->HasFiniteMass()) return;

	particle->AddForce(_gravityAcc3D * particle->GetMass());
}