/*========================================================================
Represents the contact between 2 Particle2D objects. A contact is when 
their physics simulations are touching. 

Will hold two pointers, one for each Particle2D involved. All calculation
are made from the perspective of the first paticle. If there is only one,
that implies that we are making a contact with an environmental object. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Particle2D.h>
#include <Engine/Vector2.h>
#include <Engine/Timer.h>

namespace KillerPhysics
{
	class Particle2DContact
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Particle2DContact(void);

		~Particle2DContact(void);
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetRestitution(real restitution)
		{
			_restitution = restitution;
		}

		inline void SetContactNormal(KM::Vector2& normal)
		{
			_contactNormal = normal;
		}
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void Resolve(void);

		real CalculateSeparatingVelocity(void) const;

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		void _ResolveImpulseVelocity(void);

		void _ResolveInterpenetration(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		shared_ptr<Particle2D> _particles[2];
		KM::Vector2			   _contactNormal;
		real 				   _restitution;
	};//end Class
}//end Namespace
