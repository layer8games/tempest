#include "stdafx.h"
#include <Engine/SpringForce.h>
using namespace TempestPhysics;

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


void SpringForce::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
    TM::Vector2 force {};
    force = RigidBody2D->GetPosition();
    force -= _otherEnd->GetPosition();

    real magnitude = force.Magnitude();

    if(_isBungie && magnitude <= _restLength) 
    {
        return;
    }

    magnitude = real_abs(magnitude - _restLength) * _springConstant;

    force.Normalize();
    force *= static_cast<F32>(-magnitude);

    RigidBody2D->AddForce(force);
}
