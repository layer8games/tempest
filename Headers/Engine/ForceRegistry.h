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
/*! 
	Registry to find out which particles need forces. It keeps track of which objects need specific forces for their development. 
	There is also untested functionality to allow for a RigidBody registration. These registrations are called every frame to add
	the accompanying force to the object. 

	It is based on the Cyclone engine design found in "Game Physics Engine Development, second edition" by Ian Millington. 
*/
	class ForceRegistry
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*! 
	Sets everything to 0. 
*/
		ForceRegistry(void);

/*! 
	No implementation. 
*/
		~ForceRegistry(void);

//==========================================================================================================================
//
//ForceRegistry functions
//
//==========================================================================================================================		
/*! 
	 Creates a new _ParticleForceRegistration. Adds the args to the new _ParticleForceRegistration, then saves this into the
	 instance.
	 \param particle is the pointer to be registered and saved. 
	 \param forceGen is the force that will be saved with the object.
*/
		void Add(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen);

/*! 
	Creates a new  _RigidBodyRegistration. Adds the args to the new _RigidBodyRegistration, then saves this into the instance.
	\param body is the pointer to be registered and saved. 
	\param forceGen is the force that will be saved with the object.
*/
		void Add(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen);

/*! 
	Removes the registration matching the pointer args from the instance. This has some cost, since it creates a new registration,
	then uses this to compare with every registration, until the needed registration is found. There is room to optimize here.
	\param particle is the object that needs to be removed. 
	\param forceGen is the matching force that also needs to be removed.  
*/
		void Remove(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen);

/*! 
	Removes the registration matching the pointer args from the instance. This has some cost, since it creates a new registration,
	then uses this to compare with every registration, until the needed registration is found. There is room to optimize here.
	\param body is the object that needs to be removed. 
	\param forceGen is the matching force that also needs to be removed.  	 
*/
		void Remove(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen);

/*! 
	Removed all saved registrations by clearing the list of saved registrations. 
*/
		void Clear(void);

/*! 
	Iterates over all registered objects, adding the force to the accompanying object. This is what will cause a force to act 
	on the object. This is where the magic happens.  
*/
		void UpdateForces(void);
		
	private:
//==========================================================================================================================
//This struct will keep track of one force generator, and the particle that uses it. 
//==========================================================================================================================		
/*! 
	Private struct type that pairs a single Particle with a ForceGenerator.
*/
		struct _ParticleForceRegistration
		{
			shared_ptr<Particle> 	   particle;						///< Pointer to object saved to add force to later.
			shared_ptr<ForceGenerator> forceGen;						///< Pointer to force saved to be added to object later.

/*! 
	Returns true if another registration matches this one. 
	\param p is the registration to be compared against.  
*/
			bool operator ==(_ParticleForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

/*! 
	Private struct type that pairs a single RigidBody with a ForceGenerators.
*/
		struct _RigidBodyRegistration
		{
			shared_ptr<RigidBody> 	   body;							///< Pointer to object saved to add force to later.
			shared_ptr<ForceGenerator> forceGen;						///< Pointer to force saved to be added to object later.

/*! 
	Returns true if another registration matches this one. 
	\param b is the registration to be compared against.  
*/
			bool operator ==(_RigidBodyRegistration b)
			{
				if(b.body == body && b.forceGen == forceGen)
					return true;
				else
					return false;
			}
		};

/*! 
	Alias type for Particle Registration Vector4. 
*/
		typedef std::vector<_ParticleForceRegistration> ParticleRegistry;
/*! 
	Alias type for RigidBody registration Vector4. 
*/
		typedef std::vector<_RigidBodyRegistration> RigidBodyRegistry;
		
		ParticleRegistry _particleRegistrations;					///< Saved list of all Particle objects registered with a ForceGenerator.
		RigidBodyRegistry _bodyRegistrations;						///< Saved list of all RigidBody objects registered with a ForceGenerator.

	};//end class
}//end namespacef