#include <Engine/GravityForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GravityForce::GravityForce(void) 
: 
_gravityAcc(KM::Vector4(0.0f, -1.0f, 0.0f))
{  }

GravityForce::GravityForce(const KM::Vector4& gravity) 
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
void GravityForce::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
	if(!RigidBody2D->HasFiniteMass()) 
	{
		return;
	}

	RigidBody2D->AddForce(_gravityAcc * RigidBody2D->GetMass());
}

void GravityForce::v_UpdateForce(shared_ptr<RigidBody3D> body)
{
	if(body->HasFiniteMass()) 
	{
		return;
	}

	body->AddForce(_gravityAcc * body->GetMass());
}