#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Point3.h>

namespace TM = TempestMath;

namespace TempestPhysics
{
    class AnchoredSpring : public ForceGenerator
    {
    public:		
        TEMPEST_API AnchoredSpring(void);

        TEMPEST_API AnchoredSpring(const TM::Point3& anchor, real springConstant, real restLength);

        TEMPEST_API ~AnchoredSpring(void);

        TEMPEST_API void v_UpdateForce(p_RigidBody2D body) final;

        TEMPEST_API void v_UpdateForce(p_RigidBody3D body) final;

        inline void SetAnchor(const TM::Point3& anchor)
        {
            _anchor = anchor;
        }

        inline void SetSpringConstant(real constant)
        {
            _springConstant = constant;
        }

        inline void SetRestLength(real length)
        {
            _restLength = length;
        }

    private:
        TM::Point3	_anchor;	
        real _springConstant;
        real _restLength;
    };//end AnchoredSpring
    typedef shared_ptr<AnchoredSpring> p_AnchoredSpring;
}//end Namespace