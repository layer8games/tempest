/*========================================================================
The ForceGenerator provides the interface for forces to be generated 
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
#include <Engine/Particle.h>
#include <Engine/RigidBody.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
//==========================================================================================================================
//Force Generator
//==========================================================================================================================	
	class ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ForceGenerator(void);

		virtual ~ForceGenerator(void);


//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
		virtual void v_UpdateForce(shared_ptr<Particle> particle)=0;

		virtual void v_UpdateForce(shared_ptr<RigidBody> body)=0;

	private:

	};//end class
}//end namespace
