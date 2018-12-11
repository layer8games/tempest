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
_torqueAccum(0.0f),
_inverseInertiaTensor(0.0f),
_inverseMass(1.0f),
_linearDamping(0.999f),
_isAwake(false)
{  }

RigidBody::~RigidBody(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody::Integrate(void)
{
	ClearAccumulators();
}

void RigidBody::CalculateDerivedData(void)
{
	GameObject::_AccessOrientation().Normalize();

	_inverseInertiaTensor = GameObject::GetModelMatrix() * _inverseInertiaTensor;
}
//==========================================================================================================================
//Point Forces
//==========================================================================================================================
//Given in world space coordinates
void RigidBody::AddForceAtPoint(const KM::Vector& force, const KM::Vector& point)
{
	KM::Vector pt = point; 
	pt -= GameObject::GetPosition();

	_forceAccum += force; 
	_torqueAccum += pt.CrossProduct(force);

	_isAwake = true;
}	

//Force given in world space, point given in local space
void RigidBody::AddForceAtLocalPoint(const KM::Vector& force, const KM::Vector& point)
{
	KM::Vector pt = GameObject::GetModelMatrixRot() * point;
	AddForceAtPoint(force, pt);
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