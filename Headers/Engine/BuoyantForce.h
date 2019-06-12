#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
/*!
	A spring-like force that creates a bobbing effect, like the one experienced by a boat on water.

	It uses Hooks law to generate the amount of force based on the distance 	that the spring is extended. 

	The base equation is:

	f = -k * delta * l

	Where delta is the distance that the spring has been moved and k is what is	known as the "spring constant", a value that 
	represents the "stiffness" of the spring. For our terms, the equation will look like this:

	f = -k(l - l^0)

	Where l is the location of the end of the spring, and l^0 is the reseting position of the spring.

	Since this is a Vector4 force, the Vector4 version of the law looks like this:

	f = -l(|d| - l^0)^d

	Where |d| is the magnitude or length of d, which is distance away from l^0 our spring now is, and ^d is a unit Vector4 version 
	of d. Also:

	d = xA - xB

	Where xA is the position of the spring attached to our object, and xB is the end of the spring. 

	Usage:

	The force generator cannot be re-used. For each unique spring-like force we need to have its own Spring like force. Each 
	spring-like force is created with a pointer to the object at the other end of the spring, the length of the spring, and the 
	spring constant. This then must be registered with a ForceRegistry*.

	Using depth, volume, height and desity of hypothetical liquid, it will generate a force to push an object up.
*/
	class BuoyantForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*!
	Sets all values to 0 and the desity to 1000.
*/
		BuoyantForce(void);

/*!
	Sets the values of the force.
	\param maxDepth is the value for the depth the object is able to reach.
	\param objVolume is the value for the volume of the object.
	\param liquidHeight is the value for the height of the liquid.
	\param liquidDensity is the value for the desity, with a default of 1000 set.
*/
		BuoyantForce::BuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity=1000.0f);

/*!
	Not implemenated.
*/
		~BuoyantForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*!
	The y value of the position of the object is checked against the max depth. If the object has reached the max depth, then
	it is given a +y force, scaled by the density and volume, until it reaches the height. Untested.
	\param RigidBody2D is the pointer to the object that will have the force affect it. 
*/
		void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D);

/*!
	The y value of the position of the object is checked against the max depth. If the object has reached the max depth, then
	it is given a +y force, scaled by the density and volume, until it reaches the height. Untested.
	\param body is the pointer to the object that will have the force affect it. 
*/
		void v_UpdateForce(shared_ptr<RigidBody3D> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Changes the max depth.
*/
		inline void SetMaxDepth(real depth) 
		{ 
			_maxDepth = depth; 
		}

/*!
	Changes the volume of the objects affect by the force..
*/
		inline void SetObjectVolume(real volume) 
		{ 
			_objectVolume = volume; 
		}

/*!
	Changes the height of the liquid. 
*/
		inline void SetLiquidHeight(real hieght) 
		{ 
			_liquidHeight = hieght; 
		}

/*!
	Changes the density of the liquid. 
*/
		inline void SetLiquidDensity(real density) 
		{ 
			_liquidDensity = density; 
		}
	
	private:
		real _maxDepth;				///< The depth that when reached and object will be pushed up from.
		real _objectVolume;			///< Volume of the object. This should be moved into the object itself.
		real _liquidHeight;			///< Hight of the top of the liquid. This is where the object will be pushed to.
		real _liquidDensity;		///< The thickness of the liquid. Will change how fast the object is pushed.
	};//end BuoyantForce

}//end Namespace