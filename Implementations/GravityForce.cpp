#include <Engine/GravityForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GravityForce::GravityForce(void) 
: 
_gravityAcc(KM::Vector(0.0f, -1.0f, 0.0f))
{  }

GravityForce::GravityForce(const KM::Vector& gravity) 
: 
_gravityAcc(gravity)
{  }

GravityForce::~GravityForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void GravityForce::v_UpdateForce(shared_ptr<Particle> particle)
{
	if(!particle->HasFiniteMass()) 
	{
		return;
	}

	particle->AddForce(_gravityAcc * particle->GetMass());
}

void GravityForce::v_UpdateForce(shared_ptr<RigidBody> body)
{
	if(body->HasFiniteMass()) 
	{
		return;
	}

	body->AddForce(_gravityAcc * body->GetMass());
}