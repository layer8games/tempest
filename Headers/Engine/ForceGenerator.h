#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

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
	\param RigidBody2D defines this as the RigidBody2D object version.
*/
		virtual void v_UpdateForce(p_RigidBody2D body)=0;

/*!
	Unimplemented virtual function. Each force defines what happens during an update. This is the part that will make the 
	forces different.
	\param RigidBody2D defines this as the RigidBody3D object version.
*/
		virtual void v_UpdateForce(p_RigidBody3D body)=0;

	private:

	};//end class

	typedef shared_ptr<ForceGenerator> p_ForceGenerator;
}//end namespace
