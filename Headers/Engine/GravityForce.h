/*========================================================================
A Particle force for 2D particles which simulates Gravity. In this case, 
down is going to be -y. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



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
	class GravityForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		GravityForce(void);

		GravityForce(const KM::Vector& gravity);

		~GravityForce(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_UpdateForce(shared_ptr<Particle> particle) final;

		void v_UpdateForce(shared_ptr<RigidBody> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		inline void SetGravityAcceleration(KM::Vector& gravity)
		{
			_gravityAcc = gravity;
		}

	private:
		KM::Vector _gravityAcc;
	};//end class
}//end namespace