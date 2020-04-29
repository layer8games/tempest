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
    class EngineFactory
    {
    public:
        TEMPEST_API ~EngineFactory(void);

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

        TEMPEST_API static shared_ptr<EngineFactory> Instance(void);

    protected:
        EngineFactory(void);

    private:
        static shared_ptr<EngineFactory> _instance;
        
    };//end Class

    typedef shared_ptr<EngineFactory> P_EngineFactory;
}//end Namespace
