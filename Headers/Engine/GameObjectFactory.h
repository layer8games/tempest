#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Glyph.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace TP = TempestPhysics;

namespace Tempest
{
    class GameObjectFactory
    {
    public:
        TEMPEST_API ~GameObjectFactory(void);

        inline p_Glyph MakeGlyph(void)
        {
            return make_shared<Glyph>();
        }

        inline TP::p_RigidBody2D MakeRigidBody2D(void)
        {
            return TP::p_RigidBody2D(new TP::RigidBody2D());
        }

        inline TP::p_RigidBody3D MakeRigidBody3D(void)
        {
            return TP::p_RigidBody3D(new TP::RigidBody3D());
        }

        TEMPEST_API static shared_ptr<GameObjectFactory> Instance(void);

    protected:
        GameObjectFactory(void);

    private:
        static shared_ptr<GameObjectFactory> _instance;
        
    };//end Class

    typedef shared_ptr<GameObjectFactory> P_GameObjectFactory;
}//end Namespace
