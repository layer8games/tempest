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
#include <Engine/ParticleForceGenerator.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

//=====STL includes=====
#include <vector>

namespace KillerPhysics
{

	class ParticleForceRegistry
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		ParticleForceRegistry(void);

		~ParticleForceRegistry(void);

//==========================================================================================================================
//
//ParticleForceRegistry functions
//
//==========================================================================================================================		
		void Add(shared_ptr<Particle2D> particle, shared_ptr<ParticleForceGenerator> forceGen);

		void Add(shared_ptr<Particle3D> particle, shared_ptr<ParticleForceGenerator> forceGen);

		void Remove(shared_ptr<Particle2D> particle, shared_ptr<ParticleForceGenerator> forceGen);

		void Remove(shared_ptr<Particle3D> particle, shared_ptr<ParticleForceGenerator> forceGen);

		void Clear(void);

		void UpdateForces(void);
		
	private:
//==========================================================================================================================
//This struct will keep track of one force generator, and the particle that uses it. 
//==========================================================================================================================		
		struct _Particle2DForceRegistration
		{
			shared_ptr<Particle2D> 			   particle;
			shared_ptr<ParticleForceGenerator> forceGen;

			bool operator ==(_Particle2DForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

		struct _Particle3DForceRegistration
		{
			shared_ptr<Particle3D> 			   particle;
			shared_ptr<ParticleForceGenerator> forceGen;

			bool operator ==(_Particle3DForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

		typedef std::vector<_Particle2DForceRegistration> Registry2D;
		typedef std::vector<_Particle3DForceRegistration> Registry3D;
		
		Registry2D _registrations2D;
		Registry3D _registrations3D;
	};//end class
}//end namespacef