#include "stdafx.h"
#include "Engine/RigidBody3D.h"
using namespace TempestPhysics;

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

void RigidBody3D::Integrate(void)
{
    if(_obj == nullptr)
    {
        TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::Integrate: object not set!");
        return;
    }

    if(_inverseMass == 0) return;

    F32 delta = TM::Timer::Instance()->DeltaTime();

    assert(delta > 0.0f);

    _obj->AddScaledPosition(_velocity, delta);    
    _obj->AddOrientation(_rotation * delta);

    TM::Vector3 resultingAcc = _acceleration;

    //Optional hard coded gravity should be added here

    resultingAcc.AddScaledVector(_forceAccum, delta);

    _velocity.AddScaledVector(resultingAcc, delta);
    _velocity *= real_pow(_linearDamping, delta);


    TM::Vector3 angularAcc = _inverseInertiaTensorInWorld * _torqueAccum;

    _rotation.AddScaledVector(angularAcc, delta);
    _rotation *= real_pow(_angularDamping, delta);


    CalculateDerivedData();
    ClearAccumulators();
}

void RigidBody3D::CalculateDerivedData(void)
{
    _obj->NormalizeOrientation();

    // TODO:: This functionality was removed from Matrix4 and needs to be re-added
    // _inverseInertiaTensorInWorld = _obj->GetModelMatrix().Transform3x3(_inverseInertiaTensor);
}

void RigidBody3D::SetActive(bool state)
{
    _active = state;
}

bool RigidBody3D::GetActive(void) const
{
    if(_obj != nullptr)
    {
        return _obj->GetActiveUpdate() && _active;
    }

    return _active;
}

const TM::Matrix4& RigidBody3D::GetInverseInertiaTensor(void) const
{
    return _inverseInertiaTensor;
}

void RigidBody3D::SetInverseInertiaTensor(const TM::Matrix4& mat)
{
    _inverseInertiaTensor.SetAsInverse(mat);
}

const TM::Vector3& RigidBody3D::GetVelocity(void) const
{
    return _velocity;
}

void RigidBody3D::SetVelocity(const TM::Vector4& vec)
{
    _velocity = vec; 
}

void RigidBody3D::SetVelocity(F32 x, F32 y, F32 z)
{
    _velocity.Set(x, y, z);
}

void RigidBody3D::AddScaledVelocity(const TM::Vector4& vec, F32 scale)
{
    _velocity.AddScaledVector(vec, scale);
}

const TM::Vector3& RigidBody3D::GetAcceleration(void) const
{
    return _acceleration;
}

void RigidBody3D::SetAcceleration(const TM::Vector4& vec)
{
    _acceleration = vec;
}

void RigidBody3D::SetAcceleration(F32 x, F32 y, F32 z)
{
    _acceleration.Set(x, y, z);
}

void RigidBody3D::AddScaledAcceleration(const TM::Vector4& vec, F32 scale)
{
    _acceleration.AddScaledVector(vec, scale);
}

const TM::Vector3& RigidBody3D::GetRotation(void) const
{
    return _rotation;
}

void RigidBody3D::SetRotation(const TM::Vector3& vec)
{
    _rotation = vec;
}

void RigidBody3D::SetRotation(F32 x, F32 y, F32 z)
{
    _rotation.Set(x, y, z);
}

void RigidBody3D::AddScaledRotation(const TM::Vector3& vec, F32 scale)
{
    _rotation.AddScaledVector(vec, scale);
}

const TM::Vector3& RigidBody3D::GetForces(void) const
{
    return _forceAccum;
}

void RigidBody3D::AddForce(const TM::Vector3& force)
{
    _forceAccum += force;
    _isAwake = true;
}

const TM::Vector3& RigidBody3D::GetTorque(void) const
{
    return _torqueAccum;
}

void RigidBody3D::AddTorque(const TM::Vector3& torque)
{
    _torqueAccum += torque;
}

void RigidBody3D::ClearAccumulators(void)
{
    _forceAccum.Reset();
    _torqueAccum.Reset();
}

void RigidBody3D::AddForceAtPoint(const TM::Vector3& force, const TM::Point3& point)
{
    if(_obj == nullptr)
    {
        TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::AddForceAtPoint: object not set!");
        return;
    }

    TM::Vector3 pt {};
    pt -= _obj->GetPosition();

    _forceAccum += force; 
    _torqueAccum += pt.CrossProduct(force);

    _isAwake = true;
}

real RigidBody3D::GetInverseMass(void) const
{
    return _inverseMass;
}

void RigidBody3D::SetInverseMass(real val)
{
    _inverseMass = val;
}

bool RigidBody3D::HasFiniteMass(void) const
{
    return _inverseMass >= 0.0f;
}

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

void RigidBody3D::SetMass(real mass)
{
    assert(mass != 0.0f);
    _inverseMass = static_cast<real>(1.0f) / mass;
}

real RigidBody3D::GetLinearDamping(void) const
{
    return _linearDamping;
}

void RigidBody3D::SetLinearDamping(real val)
{
    _linearDamping = val;
}

real RigidBody3D::GetAngularDamping(void) const
{
    return _angularDamping;
}

void RigidBody3D::SetAngularDamping(real val)
{
    _angularDamping = val;
}

bool RigidBody3D::GetIsAwake(void)
{
    return _isAwake;
}

void RigidBody3D::SetObject(TE::GameObject3D* obj)
{
    _obj = obj;
}

const TM::Point3 RigidBody3D::GetPosition(void)
{
   if(_obj != nullptr)
   {
        return _obj->GetPosition();
   }
   else
   {
       TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody3D::GetPosition Set the GameObject before calling GetPosition");
       return TM::Point3(0.0f);
   }
}

/*
    This needs: 
    1. GameObject to cache the world transform Matrix4 - should be done
    2. multiply the _invserInertiaTensorInWorld by it. 

    The book is confusing. This must be high performance, it will be called every frame.
    Add this in when actually doing something interesting with 3D rigid bodies. For now
    everything is 2D.
*/
void RigidBody3D::_TransformInertiaTensor(void)
{
    
}