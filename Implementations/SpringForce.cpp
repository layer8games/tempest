#include <Engine/SpringForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//SpringForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
SpringForce::SpringForce(void) 
:
_otherEnd(),
_springConstant(1),
_restLength(1),
_isBungie(false)
{  }

SpringForce::SpringForce(shared_ptr<Particle> otherEnd, real springConstatant, real restLength)
:
_otherEnd(otherEnd),
_springConstant(springConstatant),
_restLength(restLength),
_isBungie(false)
{  }

SpringForce::~SpringForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void SpringForce::v_UpdateForce(shared_ptr<Particle> particle)
{
//=====Calculate Vector4 of the spring=====
	KM::Vector4 force {};
	force = particle->GetPosition();
	force -= _otherEnd->GetPosition();

//=====Calculate magnitude of force=====
	real magnitude = force.Magnitude();

	//=====Bungie Checke=====
	if(_isBungie && magnitude <= _restLength) 
	{
		return;
	}

	magnitude = real_abs(magnitude - _restLength) * _springConstant;

//=====Calculate final force=====
	force.Normalize();
	force *= static_cast<F32>(-magnitude);

	particle->AddForce(force);
}

//TODO: Implement
void SpringForce::v_UpdateForce(shared_ptr<RigidBody> body)
{
	KM::Vector4 force {};
	force = body->GetPosition();
	force -= _otherEnd->GetPosition();

	real magnitude = force.Magnitude();

	if(_isBungie && magnitude <= _restLength)
	{
		return;
	}

	magnitude = real_abs(magnitude - _restLength) * _springConstant;

	force.Normalize();
	force *= static_cast<F32>(-magnitude);

	body->AddForce(force);
}