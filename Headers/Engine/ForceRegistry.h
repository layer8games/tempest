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
	Registry to find out which RigidBody2Ds need forces. It keeps track of which objects need specific forces for their development. 
	There is also untested functionality to allow for a RigidBody3D registration. These registrations are called every frame to add
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
	 Creates a new _RigidBody2DForceRegistration. Adds the args to the new _RigidBody2DForceRegistration, then saves this into the
	 instance.
	 \param RigidBody2D is the pointer to be registered and saved. 
	 \param forceGen is the force that will be saved with the object.
*/
		void Add(p_RigidBody2D RigidBody2D, p_ForceGenerator forceGen);

/*! 
	Creates a new  _RigidBody3DRegistration. Adds the args to the new _RigidBody3DRegistration, then saves this into the instance.
	\param body is the pointer to be registered and saved. 
	\param forceGen is the force that will be saved with the object.
*/
		void Add(p_RigidBody3D body, p_ForceGenerator forceGen);

/*! 
	Removes the registration matching the pointer args from the instance. This has some cost, since it creates a new registration,
	then uses this to compare with every registration, until the needed registration is found. There is room to optimize here.
	\param RigidBody2D is the object that needs to be removed. 
	\param forceGen is the matching force that also needs to be removed.  
*/
		void Remove(p_RigidBody2D RigidBody2D, p_ForceGenerator forceGen);

/*! 
	Removes the registration matching the pointer args from the instance. This has some cost, since it creates a new registration,
	then uses this to compare with every registration, until the needed registration is found. There is room to optimize here.
	\param body is the object that needs to be removed. 
	\param forceGen is the matching force that also needs to be removed.  	 
*/
		void Remove(p_RigidBody3D body, p_ForceGenerator forceGen);

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
//This struct will keep track of one force generator, and the RigidBody2D that uses it. 
//==========================================================================================================================		
/*! 
	Private struct type that pairs a single RigidBody2D with a ForceGenerator.
*/
		struct _RigidBody2DForceRegistration
		{
			p_RigidBody2D 	   		   RigidBody2D;						///< Pointer to object saved to add force to later.
			p_ForceGenerator forceGen;						///< Pointer to force saved to be added to object later.

/*! 
	Returns true if another registration matches this one. 
	\param p is the registration to be compared against.  
*/
			bool operator ==(_RigidBody2DForceRegistration p)
			{
				if(p.RigidBody2D == RigidBody2D && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

/*! 
	Private struct type that pairs a single RigidBody3D with a ForceGenerators.
*/
		struct _RigidBody3DRegistration
		{
			p_RigidBody3D 	   body;							///< Pointer to object saved to add force to later.
			p_ForceGenerator forceGen;						///< Pointer to force saved to be added to object later.

/*! 
	Returns true if another registration matches this one. 
	\param b is the registration to be compared against.  
*/
			bool operator ==(_RigidBody3DRegistration b)
			{
				if(b.body == body && b.forceGen == forceGen)
					return true;
				else
					return false;
			}
		};

/*! 
	Alias type for RigidBody2D Registration Vector4. 
*/
		typedef std::vector<_RigidBody2DForceRegistration> RigidBody2DRegistry;
/*! 
	Alias type for RigidBody3D registration Vector4. 
*/
		typedef std::vector<_RigidBody3DRegistration> RigidBody3DRegistry;
		
		RigidBody2DRegistry _body2DRegistrations;					///< Saved list of all RigidBody2D objects registered with a ForceGenerator.
		RigidBody3DRegistry _body3DRegistrations;						///< Saved list of all RigidBody3D objects registered with a ForceGenerator.

	};//end class
}//end namespacef