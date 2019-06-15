#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/GameObject.h>

//===== Standard includes =====
#include <cassert>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
/*!
	The RigidBody2D class reprsents a point mass. This means that we pretend that it has no area, that it is a single point 
	in space, but that it has a mass. It can be acted on by forces, and most of this magic happens in the Integrate. 

	Most of the math and ideas were taken from Game Physics Programming by Ian Millington, but have been tweeked by me
	as I have experiemented with what works in the framework of the KillerEngine. 

	It inherits from the GameObject, but it is not an abstract class itself. It can be inherited from, but this should
	be done sparingly. I attempted to make this a class that would use componsition to work, but it needed to have direct
	access to the position of GameObject, while the GameObject can handle all of the rendering logic. It was was simplier 
	to go with this inheritance schema. 
*/
	class RigidBody2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*!
	Default Constructor. All data values are set to 0, except for _inverseMass, which is set to 1, and _damping, which is set
	to 0.999f.
*/
		RigidBody2D(void);

/*!
	Pointer Copy Constructor. This is here because of some errors that were being thrown at one point. It is a full copy. 
*/
		RigidBody2D(const RigidBody2D* RigidBody2D);

/*!
	Reference Copy Constructor. This was the perfered method of copy, I don't even know if this will be used any more.
*/
		RigidBody2D(const RigidBody2D& RigidBody2D);

/*!
	Default destructor. Virtual because this class is a child of the GameObject. It performs no function.
*/
		virtual ~RigidBody2D(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
/*!
	Integrate is where the physical poperties of a point mass are simulated. An algorithm is used to update the velocity 
	based off the acceleration, and the position based off the velocity. Forces that are applied to this RigidBody2D are taken
	into account for this update. All forces are cleared at the end of the integration step.
*/
		void Integrate(void);

/*!
	Removed all forces that have been applied to the RigidBody2D this frame.
*/
		void ClearAccumulator(void);

/*!
	Adds a force that will act upon this RigidBody2D. This is done by adding the combined forces into the acceleration of the RigidBody2D.
*/
		void AddForce(const KM::Vector4 force);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetActive(bool state)
		{
			_active = state;
		}

		bool GetActive(void) const;

		inline void SetObject(KE::GameObject* obj)
		{
			_obj = obj;
		}

		const KM::Point& GetPosition(void) const;

//===== Velocity =====
/*!
	Returns the current velocity of the RigidBody2D.
*/
		inline const KM::Vector4& GetVelocity(void) const
		{
			return _velocity;
		}

/*!
	 Directly sets the velocity of the RigidBody2D, ignoring acceleration and physics. This can be viewed as an impulse, but permanent.
	 \param vel is the value set for the velocity. Disregards what the velocity was. 
*/
		inline void SetVelocity(const KM::Vector4& vel)
		{
			_velocity = vel;
		}

/*!
	 Directly sets the velocity of the RigidBody2D, ignoring acceleration and physics. This can be viewed as an impulse, but permanent. 
	 Does not change the z value of the velocity.
	 \param x is the value for the x part of the velocity.
	 \param y is the value for the y part of the velocity.
*/		
		inline void SetVelocity(F32 x, F32 y)
		{
			_velocity[0] = x;
			_velocity[1] = y;
		}

/*!
	 Directly sets the velocity of the RigidBody2D, ignoring acceleration and physics. This can be viewed as an impulse, but permanent. 
	 \param x is the value for the x part of the velocity.
	 \param y is the value for the y part of the velocity.
	 \parar z is the value for the z part of the velocity.
*/
		inline void SetVelocity(F32 x, F32 y, F32 z)
		{
			_velocity[0] = x;
			_velocity[1] = y;
			_velocity[2] = z;
		}

/*!
	Directly add a scaled Vector4y into the current velocity. 
	\param vec is the Vector4 to be added. 
	\param scale is the F32 that vec will be scaled by before it is added into the velocity. 
*/
		inline void AddScaledVelocity(const KM::Vector4& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

//===== Accleration =====
/*!
	Returns the current acceleration of the RigidBody2D. 
*/
		inline const KM::Vector4& GetAcceleration(void) const
		{
			return _acceleration;
		}

/*!
	Directly set the acceleration of the RigidBody2D without regards to physics or the current value of the acceleration. 
	\param acc is the new value of the acceleration.
*/
		inline void SetAcceleration(const KM::Vector4& acc)
		{
			_acceleration = acc;
		}

/*!
	Directly set the acceleration of the RigidBody2D without regards to physics or the current value of the acceleration.
	The z value is not affected.
	\param x is the value for the x element of the acceleration.
	\param y is the value for the y element of the acceleration.
*/
		inline void SetAcceleration(F32 x, F32 y)
		{
			_acceleration[0] = x;
			_acceleration[1] = y;
		}

/*!
	Directly set the acceleration of the RigidBody2D without regards to physics or the current value of the acceleration.
	\param x is the value for the x element of the acceleration.
	\param y is the value for the y element of the acceleration.
	\param z is the value for teh z element of the acceleration.
*/
		inline void SetAcceleration(F32 x, F32 y, F32 z)
		{
			_acceleration[0] = x;
			_acceleration[1] = y;
			_acceleration[2] = z;
		}

/*!
	Directly add a scaled Vector4y into the current acceleration. 
	\param vec is the Vector4 to be added. 
	\param scale is the F32 that vec will be scaled by before it is added into the acceleration. 
*/		
		inline void AddScaledAcceleration(const KM::Vector4& acc, F32 scale)
		{
			_acceleration.AddScaledVector(acc, scale);
		}

//===== Froces =====
/*!
	Returns the total amount of all the forces applied to this RigidBody2D for this frame added together.
*/
		inline const KM::Vector4& GetForces(void) const
		{
			return _forceAccum;
		}

//===== Gravity =====
/*!
	Returns the value cached to represent the force of gravity on this RigidBody2D.
*/
		inline const KM::Vector4& GetGravityForce(void) const
		{
			return _gravityForce;
		}

/*!
	Sets the cached value that represents the force of gravity on this RigidBody2D.
	\param grav is the value that the gravity force will be set to.
*/
		inline void SetGravityForce(const KM::Vector4& grav)
		{
			_gravityForce = grav;
		}

//===== Mass =====
/*!
	Returns the Inverse Mass of this RigidBody2D.
*/
		inline const real GetInverseMass(void) const
		{
			return _inverseMass;
		}

/*!
	Sets the Inverse Mass of this RigidBody2D.
	\param inverseMass is the new value for the inverse mass.
*/
		inline void SetInverseMass(real inverseMass)
		{
			_inverseMass = inverseMass;
		}

/*!
	As a convention, if the inverse mass is less than 0.0f, then the mass of this RigidBody2D is thought of as being
	infinate, that is, it is an immovable object. This returns the current state of the mass relation to this logic.
*/
		inline bool HasFiniteMass(void)
		{
			return _inverseMass >= 0.0f;
		}

/*!
	Returns the actual Mass of the RigidBody2D object.
*/
		const real GetMass(void);

/*!
	Sets the actual Mass of the RigidBody2D object. Because Mass is stored as the inverse, that is 1/mass, this involves
	some math to set up the inverse.
	\param mass is the value that will be transformed into the inverse mass. Cannot be set to 0. 
*/
		inline void SetMass(real mass)
		{
			assert(mass != 0.0f);
			_inverseMass = static_cast<real>(1.0f) / mass;
		}

//===== Damping =====
/*!
	Returns the current damping for the RigidBody2D.
*/
		inline const real GetDamping(void) const
		{
			return _damping;
		}

/*!
	Sets the damping value for the RigidBody2D. 
	\param damp is the new value for damping.
*/
		inline void SetDamping(real damp)
		{
			_damping = damp;
		}

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool 	   				 _active;
		real 	   				 _inverseMass;	///< The inverse mass of the object, written like 1/mass. This is an optimization to avoid uneeded operations. 
		real 	   				 _damping;		///< Damping is a substitute for friction. It represents the rate of acceleration decay. 0.0f means heavy friction, close to 1 means almost none. Do not set to 1. A good value for no decay is 0.999f.
		KE::GameObject* _obj;
		KM::Vector4 			 _velocity;		///< Represents the rate of change, otherwise known as the first differential of the position.
		KM::Vector4 			 _acceleration;	///< Reprsent the rate of change of the velocity, otherwise known as the second differential of the position.
		KM::Vector4 			 _forceAccum;		///< Using D'Lambert's principal, this reprsents the combined forces that will as on this RigidBody2D for exactly 1 frame.
		KM::Vector4 			 _gravityForce;	///< An optimization, gravity does not have to be treated like other forces, it can permanately be cached. 

	};
	typedef shared_ptr<RigidBody2D> p_RigidBody2D;
}