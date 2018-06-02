/*========================================================================
The Particle represents a point mass that will be used in physics calcula-
tions. It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.

This is the 3D implementation. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Physics includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject3D.h>
#include <Engine/Vector3.h>

//=====KillerMath includes=====
#include <Engine/Timer.h>
#include <Engine/Vector3.h>

//=====STL and other includes=====
#include <cassert>

namespace KE = KillerEngine;
namespace KM = KillerMath;

namespace KillerPhysics 
{
	class Particle3D : public KE::GameObject3D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle3D(void);

		Particle3D(const Particle3D* particle);

		Particle3D(const Particle3D& particle);
	
		virtual ~Particle3D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Velocity
//==========================================================================================================================
		inline const KM::Vector3& GetVelocity(void) const
		{
			return _velocity;
		}

		inline void SetVelocity(const KM::Vector3& vel)
		{
			_velocity = vel;
		}

		inline void SetVelocity(F32 x, F32 y, F32 z)
		{
			_velocity = KM::Vector3(x, y, z);
		}

		inline void AddScaledVelocity(const KM::Vector3 v, F32 scale)
		{
			_velocity.AddScaledVector(v, scale);
		}

//==========================================================================================================================
//Acceleration
//==========================================================================================================================		
		inline const KM::Vector3& GetAcceleration(void) const
		{
			return _acceleration;
		}

		inline void SetAcceleration(const KM::Vector3& acc)
		{
			_acceleration = acc;
		}

		inline void SetAcceleration(F32 x, F32 y, F32 z)
		{
			_acceleration = KM::Vector3(x, y, z);
		}

		inline void AddScaledAcceleration(const KM::Vector3& v, F32 scale)
		{
			_acceleration.AddScaledVector(v, scale);
		}
	
//==========================================================================================================================
//Damping
//==========================================================================================================================
		inline const real GetDamping(void) const
		{
			return _damping;
		}

		inline void SetDamping(real damp)
		{
			_damping = damp;
		}
//==========================================================================================================================
//Mass
//==========================================================================================================================		
		inline const real GetInverseMass(void) const
		{
			return _inverseMass;
		}

		inline void SetInverseMass(real inverseMass)
		{
			_inverseMass = inverseMass;
		}

		const real GetMass(void) const;

		void SetMass(const real mass);

		inline bool Particle3D::HasFiniteMass(void)
		{
			return _inverseMass >= 0.0f;
		}

//==========================================================================================================================
//Forces
//==========================================================================================================================		
//===== Accumulated Forces =====
		inline const KM::Vector3& GetForces(void) const
		{
			return _forceAccum;
		}

//===== Gravity =====
		inline const KM::Vector3& GetGravityForce(void) const
		{
			return _gravityForce;
		}

		inline void SetGravityForce(const KM::Vector3& gravity)
		{
			_gravityForce = gravity;
		}
//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		virtual void v_Update(void);

		void Integrate(void);

		inline void ClearAccumulator(void)
		{
			_forceAccum.Reset();
		}

		void AddForce(const KM::Vector3& force)
		{
			_forceAccum += force;
		}

	private:
//==========================================================================================================================
//Descriptions
//
//Mass stored over 1 in order to take advantage of the equation -> 
// a = 1/m * f
//which is a transformed version of -> 
// f = m * a
//where f is a force applied to the particle.
//m is the mass
//a is the accerelation applied to the mass
//==========================================================================================================================
		KM::Vector3 _velocity;
		KM::Vector3 _acceleration;
		KM::Vector3 _forceAccum;
		KM::Vector3 _gravityForce;
		real 		_inverseMass;
		real 		_damping;
	};
}//End namespace