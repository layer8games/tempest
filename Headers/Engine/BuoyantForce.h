#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>

namespace TM = TempestMath;

namespace TempestPhysics
{
    class BuoyantForce : public ForceGenerator
    {
    public:
        TEMPEST_API BuoyantForce(void);

        TEMPEST_API BuoyantForce::BuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity=1000.0f);

        TEMPEST_API ~BuoyantForce(void);

        TEMPEST_API void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D);

        TEMPEST_API void v_UpdateForce(shared_ptr<RigidBody3D> body) final;

        inline void SetMaxDepth(real depth) 
        { 
            _maxDepth = depth; 
        }

        inline void SetObjectVolume(real volume) 
        { 
            _objectVolume = volume; 
        }

        inline void SetLiquidHeight(real hieght) 
        { 
            _liquidHeight = hieght; 
        }

        inline void SetLiquidDensity(real density) 
        { 
            _liquidDensity = density; 
        }
    
    private:
        real _maxDepth;		
        real _objectVolume;	
        real _liquidHeight;	
        real _liquidDensity;
    };//end BuoyantForce
    typedef shared_ptr<BuoyantForce> p_BuoyantForce;
}//end Namespace