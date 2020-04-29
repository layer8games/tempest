#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>
#include <Engine/GravityForce.h>

namespace TempestPhysics
{
    class PhysicsFactory
    {
    public:
        TEMPEST_API ~PhysicsFactory(void);

        inline p_RigidBody2D MakeRigidBody2D(void)
        {
            return p_RigidBody2D(new RigidBody2D());
        }

        inline p_RigidBody3D MakeRigidBody3D(void)
        {
            return p_RigidBody3D(new RigidBody3D());
        }

        inline p_GravityForce MakeGravityForce(void)
        {
            return p_GravityForce(new GravityForce());
        }

        TEMPEST_API static shared_ptr<PhysicsFactory> Instance(void);

    protected:
        PhysicsFactory(void);

    private:
        static shared_ptr<PhysicsFactory> _instance;
    };//end Class
    typedef shared_ptr<PhysicsFactory> P_PhysicsFactory;
}//end Namespace
