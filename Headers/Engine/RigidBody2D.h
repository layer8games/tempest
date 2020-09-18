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

        TEMPEST_API void UpdateVelocityAndAcceleration(const TE::SteeringOutput2D steering);

        TEMPEST_API void ClearAccumulator(void);

        TEMPEST_API void SetRotation(real euler);

        TEMPEST_API real GetRotation(void) const;

        TEMPEST_API void SetActive(bool state);

        TEMPEST_API bool GetActive(void) const;

        TEMPEST_API void SetObject(TE::GameObject2D* obj);

        TEMPEST_API TE::GameObject2D* GetGameObject(void) const;

        TEMPEST_API const TM::Point2 GetPosition(void) const;

        TEMPEST_API const TM::Vector2& GetVelocity(void) const;

        TEMPEST_API void SetVelocity(const TM::Vector2& vel);

        TEMPEST_API void SetVelocity(F32 x, F32 y);

        TEMPEST_API const TM::Vector2& GetAcceleration(void) const;

        TEMPEST_API void SetAcceleration(const TM::Vector2& acc);

        TEMPEST_API void SetAcceleration(F32 x, F32 y);

        TEMPEST_API const TM::Vector2& GetForces(void) const;

        TEMPEST_API void AddForce(const TM::Vector2& force);

        TEMPEST_API void AddForceAtPoint(const TM::Vector2& force, const TM::Point2 point);

        TEMPEST_API const TM::Vector2& GetGravityForce(void) const;

        TEMPEST_API void SetGravityForce(const TM::Vector2& grav);

        TEMPEST_API const real GetInverseMass(void) const;

        TEMPEST_API void SetInverseMass(real inverseMass);

        TEMPEST_API bool HasFiniteMass(void);

        TEMPEST_API const real GetMass(void);

        TEMPEST_API void SetMass(real mass);

        TEMPEST_API void SetMomentOfInertia(real inertia);

        TEMPEST_API real GetMomentOfInertia(void) const;

        TEMPEST_API const real GetLinearDamping(void) const;

        TEMPEST_API void SetLinearDamping(real damp);

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