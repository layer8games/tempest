#include <Engine/RigidBody2D.h>
#include <iostream>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
RigidBody2D::RigidBody2D(void)
:
_velocity(0.0f),
_acceleration(0.0f),
_forceAccum(0.0f),
_gravityForce(0.0f),
_inverseMass(1.0f),
_damping(0.999f)
{  }

RigidBody2D::RigidBody2D(const RigidBody2D* RigidBody2D)
:
_velocity(RigidBody2D->GetVelocity()),
_acceleration(RigidBody2D->GetAcceleration()),
_forceAccum(RigidBody2D->GetForces()),
_gravityForce(RigidBody2D->GetGravityForce()),
_inverseMass(RigidBody2D->GetInverseMass()),
_damping(RigidBody2D->GetDamping())
{  }

RigidBody2D::RigidBody2D(const RigidBody2D& RigidBody2D)
:
_velocity(RigidBody2D.GetVelocity()),
_acceleration(RigidBody2D.GetAcceleration()),
_forceAccum(RigidBody2D.GetForces()),
_gravityForce(RigidBody2D.GetGravityForce()),
_inverseMass(RigidBody2D.GetInverseMass()),
_damping(RigidBody2D.GetDamping())
{  }

RigidBody2D::~RigidBody2D(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody2D::Integrate(KM::Point& pos)
{
	if(_inverseMass == 0) return;

	F32 delta = KM::Timer::Instance()->DeltaTime();

	assert(delta > 0.0f);

	pos.AddScaledVector(_velocity, delta);

	KM::Vector4 resultingAcc = _acceleration;
	
	resultingAcc += _gravityForce;

	resultingAcc.AddScaledVector(_forceAccum, delta);

	_velocity.AddScaledVector(resultingAcc, delta);

	_velocity *= real_pow(_damping, delta);

	ClearAccumulator();
}

void RigidBody2D::ClearAccumulator(void)
{
	_forceAccum.Reset();
}

void RigidBody2D::AddForce(const KM::Vector4 force)
{
	_forceAccum += force;
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
const real RigidBody2D::GetMass(void)
{
	if(_inverseMass == 0.0f)
	{
		return REAL_MAX;
	}
	else
	{
		return static_cast<real>(1.0f) / _inverseMass;
	}
}