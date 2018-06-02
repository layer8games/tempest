/*========================================================================
The ParticleForceGenerator provides the interface for forces to be generated 
and then accumulated by anything that uses forces for physics calculations.

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>
#include <Engine/Particle2D.h>
#include <Engine/Particle3D.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
//==========================================================================================================================
//Force Generator
//==========================================================================================================================	
	class ParticleForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ParticleForceGenerator(void);

		virtual ~ParticleForceGenerator(void);


//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
		virtual void v_UpdateForce(shared_ptr<Particle2D> particle)=0;

		virtual void v_UpdateForce(shared_ptr<Particle3D> particle)=0;
	private:

	};//end class
}//end namespace
