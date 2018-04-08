/*========================================================================
The Particle2DForceGenerator provides the interface for forces to be generated 
and then accumulated by anything that uses forces for physics calculations.

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>
#include <Engine/Particle2D.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
//==========================================================================================================================
//Force Generator
//==========================================================================================================================	
	class Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2DForceGenerator(void);

		virtual ~Particle2DForceGenerator(void);


//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
		virtual void v_UpdateForce(shared_ptr<Particle2D> particle)=0;
	private:

	};//end class

/*
//==========================================================================================================================
//Force Registry
//==========================================================================================================================

	class Particle2DForceRegistry
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Particle2DForceRegistry(void);

		~Particle2DForceRegistry(void);

//==========================================================================================================================
//
//ParticleForceRegistry functions
//
//==========================================================================================================================		
		void Add(shared_ptr<Particle2D> particle, shared_ptr<Particle2DForceGenerator> forceGen);

		void Remove(shared_ptr<Particle2D> particle, shared_ptr<Particle2DForceGenerator> forceGen);

		void Clear(void);

		void UpdateForces(void);
		
	private:
//==========================================================================================================================
//This struct will keep track of one force generator, and the particle that uses it. 
//==========================================================================================================================		
		struct ParticleForceRegistration
		{
			shared_ptr<Particle2D> 			  	 particle;
			shared_ptr<Particle2DForceGenerator> forceGen;

			bool operator ==(ParticleForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

		typedef std::vector<ParticleForceRegistration> Registry;
		Registry _registrations;
	};//end class
*/
}//end namespace
