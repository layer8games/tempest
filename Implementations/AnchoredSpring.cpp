#include "stdafx.h"
#include <Engine/AnchoredSpring.h>
using namespace TempestPhysics;

AnchoredSpring::AnchoredSpring(void)
:
_anchor(0.0f),
_springConstant(1),
_restLength(1)
{  }

AnchoredSpring::AnchoredSpring(const TM::Point3& anchor, real springConstant, real restLength)
:
_anchor(anchor),
_springConstant(springConstant),
_restLength(restLength)
{  }

AnchoredSpring::~AnchoredSpring(void)
{  }

void AnchoredSpring::v_UpdateForce(p_RigidBody2D otherBody)
{
    //Calculate thevector of the spring
    TM::Vector2 force {};
    force = otherBody->GetPosition() - _anchor;
    force -= _anchor;

    //Calculate the magnitude of the force
    real magnitude = force.Magnitude();
    magnitude = (_restLength - magnitude) * _springConstant;

    //Calculate the final force and apply it
    force.Normalize();
    force *= static_cast<F32>(magnitude);
    otherBody->AddForce(force);
}

//TODO: Implement
void AnchoredSpring::v_UpdateForce(p_RigidBody3D body)
{
    TM::Vector3 force {}; 
    force = body->GetPosition();
    force -= _anchor;

    real magnitude = force.Magnitude();
    magnitude = (_restLength - magnitude) * _springConstant;

    force.Normalize();
    force *= static_cast<F32>(magnitude);
    body->AddForce(force);
}
