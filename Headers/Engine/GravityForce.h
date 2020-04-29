#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{ 
    class GravityForce : public ForceGenerator
    {
    public:		
        TEMPEST_API GravityForce(void);

        TEMPEST_API GravityForce(const TM::Vector3& gravity);

        TEMPEST_API ~GravityForce(void);
		
        TEMPEST_API void v_UpdateForce(p_RigidBody2D body) final;

        TEMPEST_API void v_UpdateForce(p_RigidBody3D body) final;
		
        inline void Set(TM::Vector3& gravity)
        {
            _gravityAcc = gravity;
        }

        inline void Set(F32 xVal, F32 yVal, F32 zVal)
        {
            _gravityAcc.x = xVal;
            _gravityAcc.y = yVal;
            _gravityAcc.z = zVal;
        }

    private:
        TM::Vector3 _gravityAcc;
    };//end class
    typedef shared_ptr<GravityForce> p_GravityForce;
}//end namespace