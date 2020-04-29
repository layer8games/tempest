#include "stdafx.h"
#include <Engine/DragForce.h>

using namespace TempestPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
DragForce::DragForce(void)
:
_drag(0.0f),
_dragSqr(0.0f)
{  }

DragForce::DragForce(real drag) 
: 
_drag(drag), 
_dragSqr(_drag * _drag)
{  }

DragForce::~DragForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void DragForce::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
    TM::Vector2 force = RigidBody2D->GetVelocity();

    real dragCoeff = force.Magnitude();
    dragCoeff = _drag * dragCoeff  + _dragSqr * dragCoeff * dragCoeff;

    force.Normalize();
    force *= -dragCoeff;

    RigidBody2D->AddForce(force);
}

void DragForce::v_UpdateForce(shared_ptr<RigidBody3D> body)
{
    TM::Vector3 force = body->GetVelocity();

    real dragCoeff = force.Magnitude();
    dragCoeff = _drag * dragCoeff  + _dragSqr * dragCoeff * dragCoeff;

    force.Normalize();
    force *= -dragCoeff;

    body->AddForce(force);
}