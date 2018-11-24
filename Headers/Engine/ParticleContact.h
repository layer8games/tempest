/*========================================================================
Represents the contact between 2 Particle objects. A contact is when 
their physics simulations are touching. 

Will hold two pointers, one for each Particle involved. All calculation
are made from the perspective of the first paticle. If there is only one,
that implies that we are making a contact with an environmental object. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Particle.h>
#include <Engine/Vector.h>
#include <Engine/Timer.h>
#include <Engine/ErrorManager.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

namespace KillerPhysics
{
//==========================================================================================================================
//ParticleContact
//==========================================================================================================================
	class ParticleContact
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		ParticleContact(void);

		~ParticleContact(void);
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetRestitution(real restitution)
		{
			_restitution = restitution;
		}

		inline void SetContactNormal(KM::Vector& normal)
		{
			_contactNormal = normal;
		}

		inline void SetContacts(shared_ptr<Particle> particle1, shared_ptr<Particle> particle2=nullptr)
		{
			_particles[0] = particle1;
			_particles[1] = particle2;
		}

		inline void SetPenetration(real penetration)
		{
			_penetration = penetration;
		}

		inline real GetPenetration(void)
		{
			return _penetration;
		}

		//move to cpp

		inline const shared_ptr<Particle> GetParticleOne(void)
		{
			return _particles[0];
		}

		inline const shared_ptr<Particle> GetParticleTwo(void)
		{
			return _particles[1];
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
		shared_ptr<Particle>    _particles[2];
		shared_ptr<KM::Vector>  _particleMovements[2];
		KM::Vector			    _contactNormal;
		real 				    _restitution;
		real				    _penetration;
	};//end ParticleContact
}//end Namespace
