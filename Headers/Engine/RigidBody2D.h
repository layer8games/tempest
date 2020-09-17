#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/ErrorManager.h"
#include "Engine/Timer.h"
#include "Engine/Vector2.h"
#include "Engine/GameObject2D.h"
#include "Engine/SteeringOutput2D.h"

#include <cassert>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{
    class RigidBody2D
    {
    public:
        TEMPEST_API RigidBody2D(void);

        TEMPEST_API RigidBody2D(const RigidBody2D* RigidBody2D);

        TEMPEST_API RigidBody2D(const RigidBody2D& RigidBody2D);

        TEMPEST_API virtual ~RigidBody2D(void);

        TEMPEST_API void Integrate(void);

        void UpdateVelocityAndAcceleration(const TE::SteeringOutput2D steering);

        TEMPEST_API void ClearAccumulator(void);

        inline void SetRotation(real euler)
        {
            _rotation = euler;
        }

        inline real GetRotation(void) const
        {
            return _rotation;
        }

        inline void SetActive(bool state)
        {
            _active = state;
        }

        TEMPEST_API bool GetActive(void) const;

        inline void SetObject(TE::GameObject2D* obj)
        {
            _obj = obj;
        }

        inline TE::GameObject2D* GetGameObject(void) const
        {
            return _obj;
        }

        const TM::Point2 GetPosition(void) const;

        inline const TM::Vector2& GetVelocity(void) const
        {
            return _velocity;
        }

        inline void SetVelocity(const TM::Vector2& vel)
        {
            _velocity = vel;
        }

        inline void SetVelocity(F32 x, F32 y)
        {
            _velocity.x = x;
            _velocity.y = y;
        }

        inline const TM::Vector2& GetAcceleration(void) const
        {
            return _acceleration;
        }

        inline void SetAcceleration(const TM::Vector2& acc)
        {
            _acceleration = acc;
        }

        inline void SetAcceleration(F32 x, F32 y)
        {
            _acceleration.x = x;
            _acceleration.y = y;
        }

        inline const TM::Vector2& GetForces(void) const
        {
            return _forceAccum;
        }

        TEMPEST_API void AddForce(const TM::Vector2& force);

        TEMPEST_API void AddForceAtPoint(const TM::Vector2& force, const TM::Point2 point);

        inline const TM::Vector2& GetGravityForce(void) const
        {
            return _gravityForce;
        }

        inline void SetGravityForce(const TM::Vector2& grav)
        {
            _gravityForce = grav;
        }

        inline const real GetInverseMass(void) const
        {
            return _inverseMass;
        }

        inline void SetInverseMass(real inverseMass)
        {
            _inverseMass = inverseMass;
        }

        inline bool HasFiniteMass(void)
        {
            return _inverseMass >= 0.0f;
        }

        TEMPEST_API const real GetMass(void);

        inline void SetMass(real mass)
        {
            assert(mass != 0.0f);
            _inverseMass = static_cast<real>(1.0f) / mass;
        }

        TEMPEST_API void SetMomentOfInertia(real inertia);

        TEMPEST_API real GetMomentOfInertia(void) const;

        inline const real GetLinearDamping(void) const
        {
            return _linearDamping;
        }

        inline void SetLinearDamping(real damp)
        {
            _linearDamping = damp;
        }

        TEMPEST_API void SetAngularDamping(real angularDamping);

        TEMPEST_API real GetAngularDamping(void) const;

    private:
        bool _active;
        real _inverseMass;
        real _inverseMomentOfInertia;
        real _linearDamping;
        real _angularDamping;
        real _rotation;
        real _torqueAccum;
        TE::GameObject2D* _obj;
        TM::Vector2 _velocity;
        TM::Vector2 _acceleration;
        TM::Vector2 _forceAccum;
        TM::Vector2 _gravityForce;

    };// end class
    typedef shared_ptr<RigidBody2D> p_RigidBody2D;
}// end namespace