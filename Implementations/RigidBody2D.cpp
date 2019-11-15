#include <Engine/RigidBody2D.h>
#include <iostream>

using namespace TempestPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
RigidBody2D::RigidBody2D(void)
:
_active(true),
_inverseMass(1.0f),
_damping(0.999f),
_obj(nullptr),
_velocity(0.0f),
_acceleration(0.0f),
_forceAccum(0.0f),
_gravityForce(0.0f)
{
	_velocity.Make2D();
	_acceleration.Make2D();
	_forceAccum.Make2D();
	_gravityForce.Make2D();
}

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
{
	_obj = nullptr;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody2D::Integrate(void)
{
	//if(_obj.expired())
	if(_obj == nullptr)
	{
		TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody2D::Integrate: object not set!");
		return;
	}

	if(_inverseMass == 0) return;

	F32 delta = TM::Timer::Instance()->DeltaTime();

	// TODO:
	// Disabling for now. Will add back in when the timer no longer depends on the game window, or when GetTime can be worked
	// in a better way. This is breaking the unit tests. 
	//assert(delta > 0.0f);

	//auto object = _obj.lock();
	//object->AddScaledPosition(_velocity, delta);
	_obj->AddScaledPosition(_velocity, delta);

	TM::Vector4 resultingAcc = _acceleration;
	
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

void RigidBody2D::AddForce(const TM::Vector4 force)
{
	_forceAccum += force;
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
bool RigidBody2D::GetActive(void) const
{
	//if(!_obj.expired())
	if(_obj != nullptr)
	{
		//auto object = _obj.lock();
		//return object->GetActive() && _active;
		return _obj->GetActive() && _active;
	}

	return _active;
}

const TM::Point& RigidBody2D::GetPosition(void) const
{
	//assert(!_obj.expired());
	assert(_obj != nullptr);

	//auto object = _obj.lock();

	//return object->GetPosition();

	return _obj->GetPosition();
}

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