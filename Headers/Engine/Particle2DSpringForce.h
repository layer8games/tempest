/*========================================================================
A collection of spring-like forces that can be used with the Killer Engine.

It uses Hooks law to generate the amount of force based on the distance
that the spring is extended. 

The base equation is:

f = -k * delta * l

Where delta is the distance that the spring has been moved and k is what is
known as the "spring constant", a value that represents the "stiffness" of 
the spring. For our terms, the equation will look like this:

f = -k(l - l^0)

Where l is the location of the end of the spring, and l^0 is the reseting 
position of the spring.

Since this is a vector force, the vector version of the law looks like this:

f = -l(|d| - l^0)^d

Where |d| is the magnitude or length of d, which is distance away from l^0
our spring now is, and ^d is a unit vector version of d. Also:

d = xA - xB

Where xA is the position of the spring attached to our object, and xB is 
the end of the spring. 

Usage:

The force generator cannot be re-used. For each unique spring-like force
we need to have its own Spring like force. Each spring-like force is 
created with a pointer to the object at the other end of the spring, the
length of the spring, and the spring constant. This then must be registered
with a ParticleForceRegistry*. 

To set an Anchored Spring Force Generator, simple give it an object that cannot
be moved. This can be enforced in the GameObject using physics or something. 
May need to be figured out later. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Particle2DForceGenerator.h>
#include <Engine/Vector2.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
	class Particle2DSpringForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Particle2DSpringForce(void);

		Particle2DSpringForce(shared_ptr<Particle2D> otherEnd, real springConstant, real restLength);

		~Particle2DSpringForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(shared_ptr<Particle2D> particle) final;

//==========================================================================================================================
//
//Class Functions
//
//==========================================================================================================================		
		void MakeBungie(bool state) 
		{ 
			_isBungie = state; 
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		inline void SetOtherEnd(shared_ptr<Particle2D> end) 
		{ 
			_otherEnd = end; 
		}

		inline void SetSpringConstant(real constant) 
		{ 
			_springConstant = constant; 
		}

		inline void SetRestLength(real length) 
		{ 
			_restLength = length; 
		}
	
	private:
		//Consider using a GameObject2D here instead of a Particle2D
		//This would allow for it to be more generic, and to be used
		//With any kind of object that is rendered in the Level.
		shared_ptr<Particle2D> _otherEnd;
		real 				   _springConstant;
		real 				   _restLength;
		bool				   _isBungie;
		
	};//end SpringForce Class

	class Particle2DAnchoredSpring : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Particle2DAnchoredSpring(void);

		Particle2DAnchoredSpring(KM::Vector2 anchor, real springConstant, real restLength);

		~Particle2DAnchoredSpring(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(shared_ptr<Particle2D> particle) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetAnchor(KM::Vector2& anchor)
		{
			_anchor = anchor;
		}

		inline void SetSpringConstant(real constant)
		{
			_springConstant = constant;
		}

		inline void SetRestLength(real length)
		{
			_restLength = length;
		}

	private:
		KM::Vector2	_anchor;
		real 		_springConstant;
		real		_restLength;
	};
}//end Namespace