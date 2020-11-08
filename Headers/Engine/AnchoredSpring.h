#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/ForceGenerator.h"
#include "Engine/Vector3.h"

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

        TEMPEST_API void SetAnchor(const TM::Point3& anchor);

        TEMPEST_API void SetSpringConstant(real constant);

        TEMPEST_API void SetRestLength(real length);

    private:
        TM::Point3 _anchor;
        real _springConstant;
        real _restLength;
    };//end AnchoredSpring
    typedef shared_ptr<AnchoredSpring> p_AnchoredSpring;
}//end Namespace