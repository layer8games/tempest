/*========================================================================
Registry to find out which particles need forces. It keeps track of which
objects need specific forces for their development. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

//=====STL includes=====
#include <vector>

namespace KillerPhysics
{

	class ForceRegistry
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		ForceRegistry(void);

		~ForceRegistry(void);

//==========================================================================================================================
//
//ForceRegistry functions
//
//==========================================================================================================================		
		void Add(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen);

		void Add(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen);

		void Remove(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen);

		void Remove(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen);

		void Clear(void);

		void UpdateForces(void);
		
	private:
//==========================================================================================================================
//This struct will keep track of one force generator, and the particle that uses it. 
//==========================================================================================================================		
		struct _ParticleForceRegistration
		{
			shared_ptr<Particle> 	   particle;
			shared_ptr<ForceGenerator> forceGen;

			bool operator ==(_ParticleForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

		//TODO: Implement for RigidBody

		struct _RigidBodyRegistration
		{
			shared_ptr<RigidBody> 	   body;
			shared_ptr<ForceGenerator> forceGen;

			bool operator ==(_RigidBodyRegistration b)
			{
				if(b.body == body && b.forceGen == forceGen)
					return true;
				else
					return false;
			}
		};

		typedef std::vector<_ParticleForceRegistration> ParticleRegistry;
		typedef std::vector<_RigidBodyRegistration> RigidBodyRegistry;
		
		ParticleRegistry _particleRegistrations;
		RigidBodyRegistry _bodyRegistrations;

	};//end class
}//end namespacef