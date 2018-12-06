#include <Engine/RigidBody.h>

using namespace KillerPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
RigidBody::RigidBody(void)
:
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