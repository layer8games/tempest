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
_torqueAccum(0.0f),
_inverseMass(1.0f),
_linearDamping(0.999f),
_angularDamping(0.999f),
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
	F32 delta = KM::Timer::Instance()->DeltaTime();

	assert(delta > 0.0f);

	GameObject::_AccessPosition().AddScaledVector(_velocity, delta);
	GameObject::_AccessOrientation().AddScaledVector(_rotation, delta);

	KM::Vector4 resultingAcc = _acceleration;

	//Optional hard coded gravity should be added here

	resultingAcc.AddScaledVector4(_forceAccum, delta);

	_velocity.AddScaledVector4(resultingAcc, delta);
	_velocity *= real_pow(_linearDamping, delta);


	KM::Vector4 angularAcc = _inverseInertiaTensorInWorld * _torqueAccum;

	_rotation.AddScaledVector4(angularAcc, delta);
	_rotation *= real_pow(_angularDamping, delta);


	CalculateDerivedData();
	ClearAccumulators();
}

void RigidBody::CalculateDerivedData(void)
{
	GameObject::_AccessOrientation().Normalize();

	_inverseInertiaTensorInWorld = GameObject::GetModelMatrix().Transform3x3(_inverseInertiaTensor);
}
//==========================================================================================================================
//Point Forces
//==========================================================================================================================
//Given in world space coordinates
void RigidBody::AddForceAtPoint(const KM::Vector4& force, const KM::Vector4& point)
{
	KM::Vector4 pt = point; 
	pt -= GameObject::GetPosition();

	_forceAccum += force; 
	_torqueAccum += pt.CrossProduct(force);

	_isAwake = true;
}	

//Force given in world space, point given in local space
void RigidBody::AddForceAtLocalPoint(const KM::Vector4& force, const KM::Vector4& point)
{
	KM::Vector4 pt = GameObject::GetModelMatrixRot() * point;
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

/*
	This needs: 
	1. GameObject to cache the world transform Matrix4
	2. multiply the _invserInertiaTensorInWorld by it. 

	The book is confusing. This must be high performance, it will be called every frame.
*/
void RigidBody::_TransformInertiaTensor(void)
{
	
}