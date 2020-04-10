#pragma once

//=====Engine Includes=====
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
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
        TEMPEST_API RigidBody3D(void);

        TEMPEST_API ~RigidBody3D(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
        TEMPEST_API void Integrate(void);

        TEMPEST_API void CalculateDerivedData(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== Active =====
        inline void SetActive(bool state)
        {
            _active = state;
        }

        TEMPEST_API bool GetActive(void) const;

//===== Object Position =====
        const TM::Point3 GetPosition(void);

//===== Inertia Tensor =====
        inline const TM::Matrix4& GetInverseInertiaTensor(void) const
        {
            return _inverseInertiaTensor;
        }

        void SetInverseInertiaTensor(const TM::Matrix4& mat)
        {
            _inverseInertiaTensor.SetAsInverse(mat);
        }

//===== Velocity =====		
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

//===== Acceleration =====
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

//===== Rotation =====
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

//===== Forces =====
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

        //Given in world space coordinates
        TEMPEST_API void AddForceAtPoint(const TM::Vector3& force, const TM::Point3& point);

        //Force given in world space, point given in local space
        TEMPEST_API void AddForceAtLocalPoint(const TM::Vector3& force, const TM::Point3& point);

//===== Mass =====
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

//===== Linear Damping =====
        inline real GetLinearDamping(void) const
        {
            return _linearDamping;
        }

        inline void SetLinearDamping(real val)
        {
            _linearDamping = val;
        }

//===== Angular Damping =====
        inline real GetAngularDamping(void) const
        {
            return _angularDamping;
        }

        inline void SetAngularDamping(real val)
        {
            _angularDamping = val;
        }

//===== Awake =====
        inline bool GetIsAwake(void)
        {
            return _isAwake;
        }

//===== GameObject =====
        inline void SetObject(TE::GameObject3D* obj)
        {
            _obj = obj;
        }

    private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================


        void _TransformInertiaTensor(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        bool 		        _active;
        bool 	            _isAwake;
        real 	            _inverseMass;
        real 	            _linearDamping;
        real 	            _angularDamping;
        TE::GameObject3D*   _obj;
        TM::Matrix4         _inverseInertiaTensor;
        TM::Matrix4         _inverseInertiaTensorInWorld;
        TM::Vector3         _velocity;
        TM::Vector3         _acceleration;
        TM::Vector3         _rotation;
        TM::Vector3         _forceAccum;
        TM::Vector3         _torqueAccum;
            

    };//end Class
    typedef shared_ptr<RigidBody3D> p_RigidBody3D;
}//end Namespace
