#include <Engine/Particle2DGravityForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle2DGravityForce::Particle2DGravityForce(void) 
: 
_gravityAcc(KM::Vector2(0.0f, -1.0f))
{  }

Particle2DGravityForce::Particle2DGravityForce(const KM::Vector2& gravity) 
: 
_gravityAcc(gravity) 
{  }

Particle2DGravityForce::~Particle2DGravityForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Particle2DGravityForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
	if(!particle->HasFiniteMass()) return;

	particle->AddForce(_gravityAcc * particle->GetMass());
}