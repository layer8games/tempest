/*========================================================================
Represents the contact between 2 Particle2D objects. A contact is when 
their physics simulations are touching. 

Will hold two pointers, one for each Particle2D involved. All calculation
are made from the perspective of the first paticle. If there is only one,
that implies that we are making a contact with an environmental object. 

ParticleContact Resolver: This holds the code that will resolve the contact
once it is found. 

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
//==========================================================================================================================
//ParticleContact
//==========================================================================================================================
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

		inline void SetPenetration(real penetration)
		{
			_penetration = penetration;
		}

		inline real GetPenetration(void)
		{
			return _penetration;
		}

		inline const shared_ptr<Particle2D> GetParticleOne(void)
		{
			return _particles[0];
		}

		inline const shared_ptr<Particle2D> GetParticleTwo(void)
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
		shared_ptr<Particle2D>  _particles[2];
		shared_ptr<KM::Vector2> _particleMovements[2];
		KM::Vector2			    _contactNormal;
		real 				    _restitution;
		real				    _penetration;
	};//end ParticleContact


//==========================================================================================================================
//ParticleContactResolver
//==========================================================================================================================	
	class Particle2DContactResolver
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2DContactResolver(void);

		Particle2DContactResolver(U32 iterations);

		~Particle2DContactResolver(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline void SetIterations(U32 iterations)
		{
			_iterations = iterations;
		}

// Consider a different data structure here. Maybe a vector<Particl2DContact> instead		
		void ResolveContacts(Particle2DContact* contactArray, U32 numContacts);

	private:
		U32 _iterations;
		U32 _iterationsUsed;
	};//end ParticleContactResolver

//==========================================================================================================================
//ParticleContactGenerator
// I don't see the point of this class, and the book didn't cover it. I'll skip it for now. 
//==========================================================================================================================	

}//end Namespace
