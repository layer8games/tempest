/*========================================================================
Particle Drag for 2D Particles. 

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
	class Particle2DDragForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2DDragForce(void);

		Particle2DDragForce(real k1, real k2);

		~Particle2DDragForce(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================		
		void v_UpdateForce(shared_ptr<Particle2D> particle) final;

	private:
		//Drag Coefficient
		real _k1;
		//Drag Coefficient Squared
		real _k2;
	};//end class
}//end namespace