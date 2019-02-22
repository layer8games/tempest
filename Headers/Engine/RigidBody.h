#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>
#include <Engine/Matrix4.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

#include <cassert>

namespace KillerPhysics
{
	class RigidBody : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		RigidBody(void);

		~RigidBody(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void)
		{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
		void Integrate(void);

		void CalculateDerivedData(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== Inertia Tensor =====
		inline const KM::Matrix4& GetInverseInertiaTensor(void) const
		{
			return _inverseInertiaTensor;
		}

		void SetInverseInertiaTensor(const KM::Matrix4& mat)
		{
			_inverseInertiaTensor.SetAsInverse(mat);
		}

//===== Velocity =====		
		inline const KM::Vector4& GetVelocity(void) const
		{
			return _velocity;
		}

		inline void SetVelocity(const KM::Vector4& vec)
		{
			_velocity = vec; 
		}

		inline void SetVelocity(F32 x, F32 y, F32 z)
		{
			_velocity[0] = x;
			_velocity[1] = y;
			_velocity[2] = z;
		}

		inline void AddScaledVelocity(const KM::Vector4& vec, F32 scale)
		{
			_velocity.AddScaledVector4(vec, scale);
		}

//===== Acceleration =====
		inline const KM::Vector4& GetAcceleration(void) const
		{
			return _acceleration;
		}

		inline void SetAcceleration(const KM::Vector4& vec)
		{
			_acceleration = vec;
		}

		inline void SetAcceleration(F32 x, F32 y, F32 z)
		{
			_acceleration[0] = x; 
			_acceleration[1] = y;
			_acceleration[2] = z;
		}

		inline void AddScaledAcceleration(const KM::Vector4& vec, F32 scale)
		{
			_acceleration.AddScaledVector4(vec, scale);
		}

//===== Rotation =====
		inline const KM::Vector4& GetRotation(void) const
		{
			return _rotation;
		}

		inline void SetRotation(const KM::Vector4& vec)
		{
			_rotation = vec;
		}

		inline void SetRotation(F32 x, F32 y, F32 z)
		{
			_rotation[0] = x; 
			_rotation[1] = y;
			_rotation[2] = z;
		}

		inline void AddScaledRotation(const KM::Vector4& vec, F32 scale)
		{
			_rotation.AddScaledVector4(vec, scale);
		}

//===== Forces =====
		inline const KM::Vector4& GetForces(void) const
		{
			return _forceAccum;
		}

		inline void AddForce(const KM::Vector4& force)
		{
			_forceAccum += force;
			_isAwake = true;
		}

		inline const KM::Vector4& GetTorque(void) const
		{
			return _torqueAccum;
		}

		inline void AddTorque(const KM::Vector4& torque)
		{
			_torqueAccum += torque;
		}

		inline void ClearAccumulators(void)
		{
			_forceAccum.Reset();
			_torqueAccum.Reset();
		}

		//Given in world space coordinates
		void AddForceAtPoint(const KM::Vector4& force, const KM::Vector4& point);

		//Force given in world space, point given in local space
		void AddForceAtLocalPoint(const KM::Vector4& force, const KM::Vector4& point);

//===== Mass =====
		inline real GetInverseMass(void) const
		{
			return _inverseMass;
		}

		inline void SetInverseMass(real val)
		{
			_inverseMass = val;
		}

		inline bool HasFiniteMass(void) const
		{
			return _inverseMass >= 0.0f;
		}

		const real GetMass(void);

		inline void SetMass(real mass)
		{
			assert(mass != 0.0f);
			_inverseMass = static_cast<real>(1.0f) / mass;
		}

//===== Linear Damping =====
		inline real GetLinearDamping(void) const
		{
			return _linearDamping;
		}

		inline void SetLinearDamping(real val)
		{
			_linearDamping = val;
		}

//===== Angular Damping =====
		inline real GetAngularDamping(void) const
		{
			return _angularDamping;
		}

		inline void SetAngularDamping(real val)
		{
			_angularDamping = val;
		}

//===== Awake =====
		inline bool GetIsAwake(void)
		{
			return _isAwake;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================


		void _TransformInertiaTensor(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		KM::Matrix4 _inverseInertiaTensor;
		KM::Matrix4 _inverseInertiaTensorInWorld;
		KM::Vector4 _velocity;
		KM::Vector4 _acceleration;
		KM::Vector4 _rotation;
		KM::Vector4 _forceAccum;
		KM::Vector4 _torqueAccum;
		real 	   _inverseMass;
		real 	   _linearDamping;
		real 	   _angularDamping;
		bool 	   _isAwake;	

	};//end Class
}//end Namespace
