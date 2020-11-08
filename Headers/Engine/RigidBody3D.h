#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/ErrorManager.h"
#include "Engine/Timer.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"
#include "Engine/Quaternion.h"
#include "Engine/Matrix4.h"
#include "Engine/GameObject3D.h"

namespace TM = TempestMath;
namespace TE = Tempest;

#include <cassert>

namespace TempestPhysics
{
    class RigidBody3D
    {
    public:
        TEMPEST_API RigidBody3D(void);

        TEMPEST_API ~RigidBody3D(void);
        
        TEMPEST_API void Integrate(void);

        TEMPEST_API void CalculateDerivedData(void);

        TEMPEST_API void SetActive(bool state);

        TEMPEST_API bool GetActive(void) const;

        TEMPEST_API const TM::Point3 GetPosition(void);

        TEMPEST_API const TM::Matrix4& GetInverseInertiaTensor(void) const;

        TEMPEST_API void SetInverseInertiaTensor(const TM::Matrix4& mat);
    
        TEMPEST_API const TM::Vector3& GetVelocity(void) const;

        TEMPEST_API void SetVelocity(const TM::Vector4& vec);

        TEMPEST_API void SetVelocity(F32 x, F32 y, F32 z);

        TEMPEST_API void AddScaledVelocity(const TM::Vector4& vec, F32 scale);

        TEMPEST_API const TM::Vector3& GetAcceleration(void) const;

        TEMPEST_API void SetAcceleration(const TM::Vector4& vec);

        TEMPEST_API void SetAcceleration(F32 x, F32 y, F32 z);

        TEMPEST_API void AddScaledAcceleration(const TM::Vector4& vec, F32 scale);

        TEMPEST_API const TM::Vector3& GetRotation(void) const;

        TEMPEST_API void SetRotation(const TM::Vector3& vec);

        TEMPEST_API void SetRotation(F32 x, F32 y, F32 z);

        TEMPEST_API void AddScaledRotation(const TM::Vector3& vec, F32 scale);

        TEMPEST_API const TM::Vector3& GetForces(void) const;

        TEMPEST_API void AddForce(const TM::Vector3& force);

        TEMPEST_API const TM::Vector3& GetTorque(void) const;

        TEMPEST_API void AddTorque(const TM::Vector3& torque);

        TEMPEST_API void ClearAccumulators(void);

        TEMPEST_API void AddForceAtPoint(const TM::Vector3& force, const TM::Point3& point);

        TEMPEST_API real GetInverseMass(void) const;

        TEMPEST_API void SetInverseMass(real val);

        TEMPEST_API bool HasFiniteMass(void) const;

        TEMPEST_API const real GetMass(void);

        TEMPEST_API void SetMass(real mass);

        TEMPEST_API real GetLinearDamping(void) const;

        TEMPEST_API void SetLinearDamping(real val);

        TEMPEST_API real GetAngularDamping(void) const;

        TEMPEST_API void SetAngularDamping(real val);

        TEMPEST_API bool GetIsAwake(void);

        TEMPEST_API void SetObject(TE::GameObject3D* obj);

    private:
        void _TransformInertiaTensor(void);

        bool _active;
        bool _isAwake;
        real _inverseMass;
        real _linearDamping;
        real _angularDamping;
        TE::GameObject3D* _obj;
        TM::Matrix4 _inverseInertiaTensor;
        TM::Matrix4 _inverseInertiaTensorInWorld;
        TM::Vector3 _velocity;
        TM::Vector3 _acceleration;
        TM::Vector3 _rotation;
        TM::Vector3 _forceAccum;
        TM::Vector3 _torqueAccum;
    };//end Class
    typedef shared_ptr<RigidBody3D> p_RigidBody3D;
}//end Namespace
