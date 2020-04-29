#include "stdafx.h"
#include <Engine/GravityForce.h>
using namespace TempestPhysics;

GravityForce::GravityForce(void) 
: 
_gravityAcc(0.0f, -1.0f, 0.0f)
{  }

GravityForce::GravityForce(const TM::Vector3& gravity) 
: 
_gravityAcc(gravity)
{  }

GravityForce::~GravityForce(void) 
{  }

void GravityForce::v_UpdateForce(p_RigidBody2D body)
{
    if(!body->HasFiniteMass()) 
    {
        return;
    }

    real mass = body->GetMass();
    
    body->AddForce(TM::Vector2(_gravityAcc * mass));
}

void GravityForce::v_UpdateForce(p_RigidBody3D body)
{
    if(!body->HasFiniteMass()) 
    {
        return;
    }

    body->AddForce(_gravityAcc * body->GetMass());
}