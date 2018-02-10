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
#include <Engine/Particle2DForceGenerator.h>
#include <Engine/Vector2.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class Particle2DGravityForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Particle2DGravityForce(void);

		Particle2DGravityForce(const KM::Vector2& gravity);

		~Particle2DGravityForce(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_UpdateForce(Particle2D& particle);

	private:
		KM::Vector2 _gravityAcc;
	};//end class
}//end namespace