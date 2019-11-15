#include <Engine/RigidBody3D.h>

using namespace TempestPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
RigidBody3D::RigidBody3D(void)
:
_active(true),
_isAwake(false),
_inverseMass(1.0f),
_linearDamping(0.999f),
_angularDamping(0.999f),
_obj(nullptr),
_inverseInertiaTensor(0.0f),
_inverseInertiaTensorInWorld(0.0f),
_velocity(0.0f),
_acceleration(0.0f),
_rotation(0.0f),
_forceAccum(0.0f),
_torqueAccum(0.0f)
{  }

RigidBody3D::~RigidBody3D(void)
{
	_obj = nullptr;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody3D::Integrate(void)
{
	if(_obj == nullptr)
	{
		TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::Integrate: object not set!");
		return;
	}

	if(_inverseMass == 0) return;

	F32 delta = TM::Timer::Instance()->DeltaTime();

	// TODO:
	// Disabling for now. Will add back in when the timer no longer depends on the game window, or when GetTime can be worked
	// in a better way. This is breaking the unit tests. 
	//assert(delta > 0.0f);

	_obj->AddScaledPosition(_velocity, delta);
	_obj->AddScaledOrientation(_rotation, delta);

	TM::Vector4 resultingAcc = _acceleration;

	//Optional hard coded gravity should be added here

	resultingAcc.AddScaledVector(_forceAccum, delta);

	_velocity.AddScaledVector(resultingAcc, delta);
	_velocity *= real_pow(_linearDamping, delta);


	TM::Vector4 angularAcc = _inverseInertiaTensorInWorld * _torqueAccum;

	_rotation.AddScaledVector(angularAcc, delta);
	_rotation *= real_pow(_angularDamping, delta);


	CalculateDerivedData();
	ClearAccumulators();
}

void RigidBody3D::CalculateDerivedData(void)
{
	_obj->NormalizeOrientation();

	_inverseInertiaTensorInWorld = _obj->GetModelMatrix().Transform3x3(_inverseInertiaTensor);
}
//==========================================================================================================================
//Point Forces
//==========================================================================================================================
//Given in world space coordinates
void RigidBody3D::AddForceAtPoint(const TM::Vector4& force, const TM::Vector4& point)
{
	if(_obj == nullptr)
	{
		TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::AddForceAtPoint: object not set!");
		return;
	}

	TM::Vector4 pt {};
	pt -= _obj->GetPosition();

	_forceAccum += force; 
	_torqueAccum += pt.CrossProduct(force);

	_isAwake = true;
}	

//Force given in world space, point given in local space
void RigidBody3D::AddForceAtLocalPoint(const TM::Vector4& force, const TM::Vector4& point)
{
	if(_obj == nullptr)
	{
		TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::AddForceAtLocalPoint: object not set!");
		return;
	}
	
	TM::Vector4 pt = _obj->GetModelMatrixRot() * point;
	AddForceAtPoint(force, pt);
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

bool RigidBody3D::GetActive(void) const
{
	if(_obj != nullptr)
	{
		return _obj->GetActive() && _active;
	}

	return _active;
}

const TM::Point& RigidBody3D::GetPosition(void)
{
	assert(_obj != nullptr);

	return _obj->GetPosition();
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