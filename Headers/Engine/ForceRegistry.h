#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>

namespace TM = TempestMath;
namespace TE = Tempest;

//=====STL includes=====
#include <vector>

namespace TempestPhysics
{ 
    class ForceRegistry
    {
    public:		 
        TEMPEST_API ForceRegistry(void);

        TEMPEST_API ~ForceRegistry(void);
	
        TEMPEST_API void Add(p_RigidBody2D RigidBody2D, p_ForceGenerator forceGen);

        TEMPEST_API void Add(p_RigidBody3D body, p_ForceGenerator forceGen);

        TEMPEST_API void Remove(p_RigidBody2D RigidBody2D, p_ForceGenerator forceGen);
 
        TEMPEST_API void Remove(p_RigidBody3D body, p_ForceGenerator forceGen);

        TEMPEST_API void Clear(void);

        TEMPEST_API void UpdateForces(void);
        
    private:	
        struct _RigidBody2DForceRegistration
        {
            p_RigidBody2D rigidBody;
            p_ForceGenerator forceGen;			
 
            bool operator ==(_RigidBody2DForceRegistration p)
            {
                if(p.rigidBody == rigidBody && p.forceGen == forceGen)
                    return true;
                else
                    return false;
            }			
        };//end struct

        struct _RigidBody3DRegistration
        {
            p_RigidBody3D body;	
            p_ForceGenerator forceGen;

            bool operator ==(_RigidBody3DRegistration b)
            {
                if(b.body == body && b.forceGen == forceGen)
                    return true;
                else
                    return false;
            }
        };
 
        typedef std::vector<_RigidBody2DForceRegistration> RigidBody2DRegistry;

        typedef std::vector<_RigidBody3DRegistration> RigidBody3DRegistry;
        
        RigidBody2DRegistry _body2DRegistrations;
        RigidBody3DRegistry _body3DRegistrations;	

    };//end class
    typedef shared_ptr<ForceRegistry> p_ForceRegistry;
}//end namespacef