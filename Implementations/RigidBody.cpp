#include <Engine/RigidBody.h>

using namespace KillerPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
RigidBody::RigidBody(void)
:
_inverseInertiaTensor(0.0f),
_inverseInertiaTensorInWorld(0.0f),
_velocity(0.0f),
_acceleration(0.0f),
_rotation(0.0f),
_forceAccum(0.0f),
_transformMatrix(1.0f),
_inverseMass(1.0f),
_linearDamping(0.999f)
{  }

RigidBody::~RigidBody(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody::v_Update(void)
{  }

void RigidBody::CalculateDerivedData(void)
{
	GameObject::_AccessOrientation().Normalize();

	_CalculateTransformMatrix();
}

//==========================================================================================================================
//Mass
//==========================================================================================================================
const real RigidBody::GetMass(void)
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

/*
	This needs: 
	1. GameObject to cache the world transform matrix
	2. multiply the _invserInertiaTensorInWorld by it. 

	The book is confusing. This must be high performance, it will be called every frame.
*/
void RigidBody::_TransformInertiaTensor(void)
{
	
}