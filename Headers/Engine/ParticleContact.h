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
#include <Engine/Particle3D.h>
#include <Engine/Vector2.h>
#include <engine/Vector3.h>
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

		inline void SetContactNormal(KM::Vector2& normal)
		{
			_contactNormal2D = normal;
		}

		inline void SetContactNormal(KM::Vector3& normal)
		{
			_contactNormal3D = normal;
		}

		void SetContacts(shared_ptr<Particle2D> particle1, shared_ptr<Particle2D> particle2=nullptr);

		void SetContacts(shared_ptr<Particle3D> particle1, shared_ptr<Particle3D> particle2=nullptr);

		inline void SetPenetration(real penetration)
		{
			_penetration = penetration;
		}

		inline real GetPenetration(void)
		{
			return _penetration;
		}

		//move to cpp

		inline const shared_ptr<Particle2D> GetParticleOne(void)
		{
			return _particles2D[0];
		}

		inline const shared_ptr<Particle2D> GetParticleTwo(void)
		{
			return _particles2D[1];
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
		shared_ptr<Particle2D>  _particles2D[2];
		shared_ptr<Particle3D>  _particles3D[2];
		shared_ptr<KM::Vector2> _particle2DMovements[2];
		shared_ptr<KM::Vector3> _particle3DMovements[2];
		KM::Vector2			    _contactNormal2D;
		KM::Vector3			    _contactNormal3D;
		real 				    _restitution;
		real				    _penetration;
	};//end ParticleContact


//==========================================================================================================================
//ParticleContactResolver
//==========================================================================================================================	
	class ParticleContactResolver
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ParticleContactResolver(void);

		ParticleContactResolver(U32 iterations);

		~ParticleContactResolver(void);
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
		void ResolveContacts(ParticleContact* contactArray, U32 numContacts);

		//void ResolveContacts(ParticleContact* contactArray, U32 numContacts);

	private:
		U32 _iterations;
		U32 _iterationsUsed;
	};//end ParticleContactResolver

//==========================================================================================================================
//ParticleContactGenerator
// I don't see the point of this class, and the book didn't cover it. I'll skip it for now. 
//==========================================================================================================================	

}//end Namespace
