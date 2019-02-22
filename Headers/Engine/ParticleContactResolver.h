/*========================================================================
ParticleContact Resolver: This holds the code that will resolve the contact
once it is found. This is most useful when decideing which contact to resolve
and what order to resolve contacts in. 

Iterations is used to tell the system how many times to resolve the contacts.
The array of contacts that is passed in will represent all of the different
contacts that Particle has. For example, if a particle has contacted with
another Particle, and is touching a wall, the array would have 2 contacts 
in it. ResolveContacts will then iterate over the contacts and resolve 
the one with the most negative value first, then go through again and resolve
the next most negative value. 

Written by Maxwell Miller
========================================================================*/

#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ParticleContact.h>

namespace KillerPhysics
{	
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

// Consider a different data structure here. Maybe a Vector4<Particl2DContact> instead		
		void ResolveContacts(ParticleContact* contactArray, U32 numContacts);

	private:
		U32 _iterations;
		U32 _iterationsUsed;
	};//end ParticleContactResolver	
}//end Namespace
