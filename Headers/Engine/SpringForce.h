#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
/*!
	A spring-like force that can be used with the Killer Engine.

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
*/
	class SpringForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*!
	Sets spring constant to 1, rest length to 1, everything else to default or false.
*/
		SpringForce(void);

/*!
	Allows you to set up SpringForce in a single call.
	\param otherEnd is the far end of the spring.
	\param springConstant determines the "stiffness" of the spring.
	\param restLength determines how long before the spring "snaps" back.
*/
		SpringForce(shared_ptr<Particle> otherEnd, real springConstant, real restLength);

/*!
	Not implemented.
*/
		~SpringForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*!
	Calculate the length of the spring, then creates a force to pull the object towards the other end if it is far enough 
	away.
	\param particle is the object that will be acted on by the spring.
*/
		void v_UpdateForce(shared_ptr<Particle> particle) final;

/*!
	Calculate the length of the spring, then creates a force to pull the object towards the other end if it is far enough 
	away. This has been implemented but not tested. 
	\param body is the object that will be acted on by the spring.
*/
		void v_UpdateForce(shared_ptr<RigidBody> body) final;

//==========================================================================================================================
//
//Class Functions
//
//==========================================================================================================================		
/*!
	Sets state to be bungie-like. This means that it will only produce pull forces. If the rest length is not at full, it will
	not product any force.
*/
		void MakeBungie(bool state) 
		{ 
			_isBungie = state; 
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
/*!
	Changes the location of the other end of the spring.
	\param end is the new opposite end of the spring.
*/
		inline void SetOtherEnd(shared_ptr<Particle> end) 
		{ 
			_otherEnd = end; 
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
		shared_ptr<Particle> _otherEnd;			///< Other end of the spring. Consider changing to a GameObject.
		real 				 _springConstant;	///< Determines the "stiffness" of the spring. The higher this value is, the more force the spring can make.
		real 				 _restLength;		///< Length of the spring at rest. When an object reaches this length, a force will be acted on it. 
		bool				 _isBungie;			///< Changes the state of the spring to use only pull forces, allowing the spring to "scrunch" up.
		
	};//end SpringForce	
		
}//end Namespace