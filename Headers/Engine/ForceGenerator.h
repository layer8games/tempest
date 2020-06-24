#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Timer.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{	
    class ForceGenerator
    {
    public:
        TEMPEST_API ForceGenerator(void);

        TEMPEST_API virtual ~ForceGenerator(void);
    
        virtual void v_UpdateForce(p_RigidBody2D body)=0;

        virtual void v_UpdateForce(p_RigidBody3D body)=0;

    };//end class
    typedef shared_ptr<ForceGenerator> p_ForceGenerator;
}//end namespace
