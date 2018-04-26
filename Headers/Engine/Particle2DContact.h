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

namespace KM = KillerMath;

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

		inline void SetContacts(shared_ptr<Particle2D> particle1, shared_ptr<Particle2D> particle2 = nullptr)
		{
			_particles[0] = particle1;
			_particles[1] = particle2;
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
		shared_ptr<Particle2D>  _particles[2];
		shared_ptr<KM::Vector2> _particleMovements[2];
		KM::Vector2			    _contactNormal;
		real 				    _restitution;
		real				    _penetration;
	};//end Class
}//end Namespace
