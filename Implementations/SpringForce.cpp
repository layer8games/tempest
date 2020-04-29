#include "stdafx.h"
#include <Engine/SpringForce.h>

using namespace TempestPhysics;

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

SpringForce::SpringForce(shared_ptr<RigidBody2D> otherEnd, real springConstatant, real restLength)
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
void SpringForce::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
//=====Calculate Vector4 of the spring=====
    TM::Vector2 force {};
    force = RigidBody2D->GetPosition();
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

    RigidBody2D->AddForce(force);
}
