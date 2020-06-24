#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>

namespace TM = TempestMath;

namespace TempestPhysics
{
    class SpringForce : public ForceGenerator
    {
    public:
        TEMPEST_API SpringForce(void);

        TEMPEST_API SpringForce(shared_ptr<RigidBody2D> otherEnd, real springConstant, real restLength);

        TEMPEST_API ~SpringForce(void);

        TEMPEST_API void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D) final;
        
        void MakeBungie(bool state) 
        { 
            _isBungie = state; 
        }
        
        inline void SetOtherEnd(shared_ptr<RigidBody2D> end) 
        { 
            _otherEnd = end; 
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
        shared_ptr<RigidBody2D> _otherEnd;		
        real _springConstant;
        real _restLength;	
        bool _isBungie;		
        
    };//end SpringForce	
    typedef shared_ptr<SpringForce> p_SpringForce;
}//end Namespace