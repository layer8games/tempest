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
#include <Engine/Vector.h>

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

		ParticleDragForce(real drag, real dragSqr);

		~ParticleDragForce(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================		
		void v_UpdateForce(shared_ptr<Particle> particle) final;	

	private:
		//Drag Coefficient
		real _drag;
		//Drag Coefficient Squared
		real _dragSqr;
	};//end class
}//end namespace