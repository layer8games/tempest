#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point3.h>
#include <Engine/Quaternion.h>
#include <Engine/Matrix4.h>
#include <Engine/GameObject3D.h>

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

        inline void SetActive(bool state)
        {
            _active = state;
        }

        TEMPEST_API bool GetActive(void) const;

        const TM::Point3 GetPosition(void);

        inline const TM::Matrix4& GetInverseInertiaTensor(void) const
        {
            return _inverseInertiaTensor;
        }

        void SetInverseInertiaTensor(const TM::Matrix4& mat)
        {
            _inverseInertiaTensor.SetAsInverse(mat);
        }
    
        inline const TM::Vector3& GetVelocity(void) const
        {
            return _velocity;
        }

        inline void SetVelocity(const TM::Vector4& vec)
        {
            _velocity = vec; 
        }

        inline void SetVelocity(F32 x, F32 y, F32 z)
        {
            _velocity.x = x;
            _velocity.y = y;
            _velocity.z = z;
        }

        inline void AddScaledVelocity(const TM::Vector4& vec, F32 scale)
        {
            _velocity.AddScaledVector(vec, scale);
        }

        inline const TM::Vector3& GetAcceleration(void) const
        {
            return _acceleration;
        }

        inline void SetAcceleration(const TM::Vector4& vec)
        {
            _acceleration = vec;
        }

        inline void SetAcceleration(F32 x, F32 y, F32 z)
        {
            _acceleration.x = x; 
            _acceleration.y = y;
            _acceleration.z = z;
        }

        inline void AddScaledAcceleration(const TM::Vector4& vec, F32 scale)
        {
            _acceleration.AddScaledVector(vec, scale);
        }

        inline const TM::Vector3& GetRotation(void) const
        {
            return _rotation;
        }

        inline void SetRotation(const TM::Vector3& vec)
        {
            _rotation = vec;
        }

        inline void SetRotation(F32 x, F32 y, F32 z)
        {
            _rotation.x = x; 
            _rotation.y = y;
            _rotation.z = z;
        }

        inline void AddScaledRotation(const TM::Vector3& vec, F32 scale)
        {
            _rotation.AddScaledVector(vec, scale);
        }

        inline const TM::Vector3& GetForces(void) const
        {
            return _forceAccum;
        }

        inline void AddForce(const TM::Vector3& force)
        {
            _forceAccum += force;
            _isAwake = true;
        }

        inline const TM::Vector3& GetTorque(void) const
        {
            return _torqueAccum;
        }

        inline void AddTorque(const TM::Vector3& torque)
        {
            _torqueAccum += torque;
        }

        inline void ClearAccumulators(void)
        {
            _forceAccum.Reset();
            _torqueAccum.Reset();
        }

        TEMPEST_API void AddForceAtPoint(const TM::Vector3& force, const TM::Point3& point);

        TEMPEST_API void AddForceAtLocalPoint(const TM::Vector3& force, const TM::Point3& point);

        inline real GetInverseMass(void) const
        {
            return _inverseMass;
        }

        inline void SetInverseMass(real val)
        {
            _inverseMass = val;
        }

        inline bool HasFiniteMass(void) const
        {
            return _inverseMass >= 0.0f;
        }

        TEMPEST_API const real GetMass(void);

        inline void SetMass(real mass)
        {
            assert(mass != 0.0f);
            _inverseMass = static_cast<real>(1.0f) / mass;
        }

        inline real GetLinearDamping(void) const
        {
            return _linearDamping;
        }

        inline void SetLinearDamping(real val)
        {
            _linearDamping = val;
        }

        inline real GetAngularDamping(void) const
        {
            return _angularDamping;
        }

        inline void SetAngularDamping(real val)
        {
            _angularDamping = val;
        }

        inline bool GetIsAwake(void)
        {
            return _isAwake;
        }

        inline void SetObject(TE::GameObject3D* obj)
        {
            _obj = obj;
        }

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
