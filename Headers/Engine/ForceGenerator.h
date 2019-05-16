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
/*!
	The ForceGenerator provides the interface for forces to be generated and then accumulated by anything that uses forces 
	for physics calculations.

	It is based on the Cyclone engine design found in "Game Physics Engine Development, second edition" by Ian Millington.
*/

	class ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*!
	No implemenation.
*/
		ForceGenerator(void);

/*!
	No implementation.
*/
		virtual ~ForceGenerator(void);


//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
/*!
	Unimplemented virtual function. Each force defines what happens during an update. This is the part that will make the 
	forces different.
	\param particle defines this as the Particle object version.
*/
		virtual void v_UpdateForce(shared_ptr<Particle> particle)=0;

/*!
	Unimplemented virtual function. Each force defines what happens during an update. This is the part that will make the 
	forces different.
	\param particle defines this as the RigidBody object version.
*/
		virtual void v_UpdateForce(shared_ptr<RigidBody> body)=0;

	private:

	};//end class
}//end namespace
