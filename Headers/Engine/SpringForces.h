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
with a ForceRegistry*. 

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
#include <Engine/ForceGenerator.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
	class SpringForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		SpringForce(void);

		SpringForce(shared_ptr<Particle> otherEnd, real springConstant, real restLength);

		~SpringForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(shared_ptr<Particle> particle) final;

		void v_UpdateForce(shared_ptr<RigidBody> body) final;

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
		inline void SetOtherEnd(shared_ptr<Particle> end) 
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
		//Consider using a GameObject2D here instead of a Particle
		//This would allow for it to be more generic, and to be used
		//With any kind of object that is rendered in the Level.
		shared_ptr<Particle> _otherEnd;
		real 				 _springConstant;
		real 				 _restLength;
		bool				 _isBungie;
		
	};//end SpringForce

//==========================================================================================================================
//Anchored Spring
//==========================================================================================================================
	class AnchoredSpring : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		AnchoredSpring(void);

		AnchoredSpring(KM::Vector anchor, real springConstant, real restLength);

		~AnchoredSpring(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(shared_ptr<Particle> particle) final;

		void v_UpdateForce(shared_ptr<RigidBody> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetAnchor(KM::Vector& anchor)
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
		KM::Vector	_anchor;
		real 		_springConstant;
		real		_restLength;
	};//end AnchoredSpring

//==========================================================================================================================
//Buoyant Force
//==========================================================================================================================
	class BuoyantForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		BuoyantForce(void);

		BuoyantForce::BuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity=1000.0f);

		~BuoyantForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(shared_ptr<Particle> particle);

		void v_UpdateForce(shared_ptr<RigidBody> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetMaxDepth(real depth) 
		{ 
			_maxDepth = depth; 
		}

		inline void SetObjectVolume(real volume) 
		{ 
			_objectVolume = volume; 
		}

		inline void SetLiquidHeight(real hieght) 
		{ 
			_liquidHeight = hieght; 
		}

		inline void SetLiquidDensity(real density) 
		{ 
			_liquidDensity = density; 
		}
	
	private:
		real _maxDepth;
		real _objectVolume;
		real _liquidHeight;
		real _liquidDensity;
	};//end BuoyantForce
		
}//end Namespace