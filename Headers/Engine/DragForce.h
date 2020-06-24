#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector2.h>
#include <Engine/Vector4.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{
    class DragForce : public ForceGenerator
    {
    public:
        TEMPEST_API DragForce(void);

        TEMPEST_API DragForce(real drag);

        TEMPEST_API ~DragForce(void);
        
        TEMPEST_API void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D) final;

        TEMPEST_API void v_UpdateForce(shared_ptr<RigidBody3D> body) final;

        inline void SetDrag(real d)
        {
            _drag = d;
            _dragSqr = _drag * _drag;
        }

        inline real GetDrag(void)
        {
            return _drag;
        }

    private:
        real _drag;		
        real _dragSqr;	
    };//end class
    typedef shared_ptr<DragForce> p_DragForce;
}//end namespace