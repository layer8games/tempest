#include <Engine/RigidBody3D.h>

using namespace KillerPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
RigidBody3D::RigidBody3D(void)
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

RigidBody3D::~RigidBody3D(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody3D::Integrate(KM::Point& pos, KM::Quaternion& orientation, const KM::Matrix4& modelMat)
{
	F32 delta = KM::Timer::Instance()->DeltaTime();

	assert(delta > 0.0f);

	pos.AddScaledVector(_velocity, delta);
	orientation.AddScaledVector(_rotation, delta);

	KM::Vector4 resultingAcc = _acceleration;

	//Optional hard coded gravity should be added here

	resultingAcc.AddScaledVector(_forceAccum, delta);

	_velocity.AddScaledVector(resultingAcc, delta);
	_velocity *= real_pow(_linearDamping, delta);


	KM::Vector4 angularAcc = _inverseInertiaTensorInWorld * _torqueAccum;

	_rotation.AddScaledVector(angularAcc, delta);
	_rotation *= real_pow(_angularDamping, delta);


	CalculateDerivedData(orientation, modelMat);
	ClearAccumulators();
}

void RigidBody3D::CalculateDerivedData(KM::Quaternion& orientation, const KM::Matrix4& modelMat)
{
	orientation.Normalize();

	_inverseInertiaTensorInWorld = modelMat.Transform3x3(_inverseInertiaTensor);
}
//==========================================================================================================================
//Point Forces
//==========================================================================================================================
//Given in world space coordinates
void RigidBody3D::AddForceAtPoint(KM::Point& pos, const KM::Vector4& force, const KM::Vector4& point)
{
	KM::Vector4 pt {};
	pt -= pos;

	_forceAccum += force; 
	_torqueAccum += pt.CrossProduct(force);

	_isAwake = true;
}	

//Force given in world space, point given in local space
void RigidBody3D::AddForceAtLocalPoint(KM::Point& pos, const KM::Vector4& force, const KM::Vector4& point, const KM::Matrix4& rotationMat)
{
	KM::Vector4 pt = rotationMat * point;
	AddForceAtPoint(pos, force, pt);
}

//==========================================================================================================================
//Mass
//==========================================================================================================================
const real RigidBody3D::GetMass(void)
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
void RigidBody3D::_TransformInertiaTensor(void)
{
	
}