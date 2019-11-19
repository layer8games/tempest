#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Quaternion.h>
#include <Engine/Matrix4.h>
#include <Engine/GameObject.h>

namespace TM = TempestMath;
namespace TE = Tempest;

#include <cassert>

namespace TempestPhysics
{
	class RigidBody3D
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		RigidBody3D(void);

		~RigidBody3D(void);

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
//===== Active =====
		inline void SetActive(bool state)
		{
			_active = state;
		}

		bool GetActive(void) const;

//===== Object Position =====
		const TM::Point& GetPosition(void);

//===== Inertia Tensor =====
		inline const TM::Matrix4& GetInverseInertiaTensor(void) const
		{
			return _inverseInertiaTensor;
		}

		void SetInverseInertiaTensor(const TM::Matrix4& mat)
		{
			_inverseInertiaTensor.SetAsInverse(mat);
		}

//===== Velocity =====		
		inline const TM::Vector4& GetVelocity(void) const
		{
			return _velocity;
		}

		inline void SetVelocity(const TM::Vector4& vec)
		{
			_velocity = vec; 
		}

		inline void SetVelocity(F32 x, F32 y, F32 z)
		{
			_velocity[0] = x;
			_velocity[1] = y;
			_velocity[2] = z;
		}

		inline void AddScaledVelocity(const TM::Vector4& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

//===== Acceleration =====
		inline const TM::Vector4& GetAcceleration(void) const
		{
			return _acceleration;
		}

		inline void SetAcceleration(const TM::Vector4& vec)
		{
			_acceleration = vec;
		}

		inline void SetAcceleration(F32 x, F32 y, F32 z)
		{
			_acceleration[0] = x; 
			_acceleration[1] = y;
			_acceleration[2] = z;
		}

		inline void AddScaledAcceleration(const TM::Vector4& vec, F32 scale)
		{
			_acceleration.AddScaledVector(vec, scale);
		}

//===== Rotation =====
		inline const TM::Vector4& GetRotation(void) const
		{
			return _rotation;
		}

		inline void SetRotation(const TM::Vector4& vec)
		{
			_rotation = vec;
		}

		inline void SetRotation(F32 x, F32 y, F32 z)
		{
			_rotation[0] = x; 
			_rotation[1] = y;
			_rotation[2] = z;
		}

		inline void AddScaledRotation(const TM::Vector4& vec, F32 scale)
		{
			_rotation.AddScaledVector(vec, scale);
		}

//===== Forces =====
		inline const TM::Vector4& GetForces(void) const
		{
			return _forceAccum;
		}

		inline void AddForce(const TM::Vector4& force)
		{
			_forceAccum += force;
			_isAwake = true;
		}

		inline const TM::Vector4& GetTorque(void) const
		{
			return _torqueAccum;
		}

		inline void AddTorque(const TM::Vector4& torque)
		{
			_torqueAccum += torque;
		}

		inline void ClearAccumulators(void)
		{
			_forceAccum.Reset();
			_torqueAccum.Reset();
		}

		//Given in world space coordinates
		void AddForceAtPoint(const TM::Vector4& force, const TM::Vector4& point);

		//Force given in world space, point given in local space
		void AddForceAtLocalPoint(const TM::Vector4& force, const TM::Vector4& point);

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

//===== GameObject =====
		inline void SetObject(TE::GameObject* obj)
		{
			_obj = obj;
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
		bool 		_active;
		bool 	   _isAwake;
		real 	   _inverseMass;
		real 	   _linearDamping;
		real 	   _angularDamping;
		TE::GameObject* _obj;
		TM::Matrix4 _inverseInertiaTensor;
		TM::Matrix4 _inverseInertiaTensorInWorld;
		TM::Vector4 _velocity;
		TM::Vector4 _acceleration;
		TM::Vector4 _rotation;
		TM::Vector4 _forceAccum;
		TM::Vector4 _torqueAccum;
			

	};//end Class
	typedef shared_ptr<RigidBody3D> p_RigidBody3D;
}//end Namespace
