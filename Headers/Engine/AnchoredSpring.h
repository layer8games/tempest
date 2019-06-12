#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
/*!
	A spring-like force that is anchored to a specific point. This can act like a chain, or a rubber band like force.

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

	To set an Anchored Spring Force Generator, simple give it an object that cannot be moved. This can be enforced in the GameObject 
	using physics or something. May need to be figured out later. 
*/
	class AnchoredSpring : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*!
	Sets all values to 1, with anchor at 0.
*/
		AnchoredSpring(void);

/*!
	Sets up the default values of the spring.
	\param anchor is the location of the anchor point.
	\param springConstant is the "stiffness" of the spring.
	\param restLength is the length of the spring.
*/
		AnchoredSpring(const KM::Point& anchor, real springConstant, real restLength);

/*!
	No implementation.
*/
		~AnchoredSpring(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*!
	Adds a force to a RigidBody2D in relation to the objects position and the anchor point.
	\param RigidBody2D is the object that will recieve the force.
*/
		void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D) final;

/*!
	Adds a force to a RigidBody3D in relation to the objects position and the anchor point.
	\param body is the object that will recieve the force.
*/
		void v_UpdateForce(shared_ptr<RigidBody3D> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Changes the location of the other end of the spring.
	\param end is the new opposite end of the spring.
*/
		inline void SetAnchor(const KM::Point& anchor)
		{
			_anchor = anchor;
		}

/*!
	Changes the "striffness" of the spring.
	\param constant is the new value for the spring constant. 
*/
		inline void SetSpringConstant(real constant)
		{
			_springConstant = constant;
		}

/*!
	Changes the length of the invisible spring.
	\param length is the new value for the rest length.
*/
		inline void SetRestLength(real length)
		{
			_restLength = length;
		}

	private:
		KM::Point	_anchor;			///< The location of the anchor point of the spring.
		real 		_springConstant;	///< Determines the "stiffness" of the spring. The higher this value is, the more force the spring can make.
		real		_restLength;		///< Length of the spring at rest. When an object reaches this length, a force will be acted on it. 
	};//end AnchoredSpring

}//end Namespace