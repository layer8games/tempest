/*========================================================================




This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
/*! 
	A physics ForceGenerator for Particle and RigidBody objects which simulates Gravity. By default this is set to -y.

	It is based on the Cyclone engine design found in "Game Physics Engine Development, second edition" by Ian Millington. 
*/
	class GravityForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*! 
	Sets default acceleration to 0, -1, 0. 
*/
		GravityForce(void);

/*! 
	Sets acceleration to KillerMath::Vector sent in.
	\param gravity will be the value set for the acceleration. 
*/
		GravityForce(const KM::Vector& gravity);

/*! 
	No implemenation. 
*/
		~GravityForce(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
/*! 
	If particle does not have infinite mass, the acceleration is added using KillerPhysics::Particle::AddForce.
	\param particle is the pointer to the object that will have the acceleration added to it.  
*/
		void v_UpdateForce(shared_ptr<Particle> particle) final;

/*! 
	If particle does not have infinite mass, the acceleration is added using KillerPhysics::RigidBody::AddForce.
	\param body is the pointer to the object that will have the acceleration added to it.  
*/
		void v_UpdateForce(shared_ptr<RigidBody> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
/*! 
	Changes the acceleration the force will cause on an object.
	\param gravity is the new acceleration. 
*/
		inline void SetGravityAcceleration(KM::Vector& gravity)
		{
			_gravityAcc = gravity;
		}

	private:
		KM::Vector _gravityAcc;		///< The acceleration saved for this force.
	};//end class
}//end namespace