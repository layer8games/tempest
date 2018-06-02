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
#include <Engine/ParticleForceGenerator.h>
#include <Engine/Vector2.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class ParticleDragForce : public ParticleForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ParticleDragForce(void);

		ParticleDragForce(real k1, real k2);

		~ParticleDragForce(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================		
		void v_UpdateForce(shared_ptr<Particle2D> particle) final;

		void v_UpdateForce(shared_ptr<Particle3D> particle) final;		

	private:
		//Drag Coefficient
		real _k1;
		//Drag Coefficient Squared
		real _k2;
	};//end class
}//end namespace