#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{ 
///	A physics ForceGenerator for RigidBody2D and RigidBody3D objects which simulates Gravity. By default this is set to -y.
///	It is based on the Cyclone engine design found in "Game Physics Engine Development, second edition" by Ian Millington. 
    class GravityForce : public ForceGenerator
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
///	Sets default acceleration to 0, -1, 0. 
        TEMPEST_API GravityForce(void);

///	Sets acceleration to KillerMath::Vector4 sent in.
///	\param gravity will be the value set for the acceleration. 
        TEMPEST_API GravityForce(const TM::Vector3& gravity);

///	No implemenation. 
        TEMPEST_API ~GravityForce(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
///	If body does not have infinite mass, the acceleration is added using KillerPhysics::RigidBody2D::AddForce.
///	\param body is the pointer to the object that will have the acceleration added to it.  
        TEMPEST_API void v_UpdateForce(p_RigidBody2D body) final;

///	If body does not have infinite mass, the acceleration is added using KillerPhysics::RigidBody3D::AddForce.
///	\param body is the pointer to the object that will have the acceleration added to it.  
        TEMPEST_API void v_UpdateForce(p_RigidBody3D body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
///	Changes the acceleration the force will cause on an object.
///	\param gravity is the new acceleration. 
        inline void Set(TM::Vector3& gravity)
        {
            _gravityAcc = gravity;
        }

///	Changes the acceleration the force will cause on an object.
///	\param xVal is the new acceration along the x axis;
///	\param yVal is the new acceration along the y axis;
///	\param zVal is the new acceration along the z axis; 
        inline void Set(F32 xVal, F32 yVal, F32 zVal)
        {
            _gravityAcc.x = xVal;
            _gravityAcc.y = yVal;
            _gravityAcc.z = zVal;
        }

    private:
        TM::Vector3 _gravityAcc;		///< The acceleration saved for this force.
    };//end class
    typedef shared_ptr<GravityForce> p_GravityForce;
}//end namespace