#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ForceGenerator.h>
#include <Engine/Vector4.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace TM = TempestMath;
namespace TE = Tempest;

namespace TempestPhysics
{
/*!
	A Drag or friction simulator. It takes in a physics object, then will reduce its overall velocity by an ammount each
	frame to simulate the affect of drag or friction.

	The equation used for this is:

	f = v * -d

	where f is the force added to the object, v is the normalized velocity of the object and d is this equation: 

	d' = d * m + s * m^2

	where m is the magnitude of the velocity of the object, and s is d * d, and is the coefficient set in the instance.

	It is based on the Cyclone engine design found in "Game Physics Engine Development, second edition" by Ian Millington.
*/
	class DragForce : public ForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*!
	Sets all values to 0.
*/
		DragForce(void);

/*!
	Sets starting values for the DragForce.
	\param drag is the starting values for the drag cooefficient. Drag squared is set to drag * drag.
*/
		DragForce(real drag);

/*!
	Default Destructor. Not implemented.
*/
		~DragForce(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================		
/*!
	Adds a force to the object based on the drag coefficient and the velocity of the object. For details, see the class 
	description. 
	\param RigidBody2D is the pointer to the object that will have the forced added to it, and will be used to determine what the force is.
*/
		void v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D) final;

/*!
	Adds a force to the object based on the drag coefficient and the velocity of the object. For details, see the class 
	description. 
	\param body is the pointer to the object that will have the forced added to it, and will be used to determine what the force is.
*/
		void v_UpdateForce(shared_ptr<RigidBody3D> body) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Changes the drag coefficient.
	\param d is the new coefficient. Drag squared is set to d * d. 
*/
		inline void SetDrag(real d)
		{
			_drag = d;
			_dragSqr = _drag * _drag;
		}

/*!
	Returns the current drag coefficient.
*/
		inline real GetDrag(void)
		{
			return _drag;
		}

	private:
		real _drag;		///< Drag coefficent used to determine how much velocity should be removed.
		real _dragSqr;	///< Simply the drag coefficient squared. Cached to save on some operations. 
	};//end class
}//end namespace