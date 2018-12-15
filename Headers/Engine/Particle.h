#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/Vector.h>

//===== Standard includes =====
#include <cassert>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class Particle : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle(void);

		Particle(const Particle* particle);

		Particle(const Particle& particle);

		virtual ~Particle(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		virtual void v_Update();

		void Integrate(void);

		void ClearAccumulator(void);

		void AddForce(const KM::Vector force);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== Velocity =====
		inline const KM::Vector& GetVelocity(void) const
		{
			return _velocity;
		}

		inline void SetVelocity(const KM::Vector& vel)
		{
			_velocity = vel;
		}

		inline void SetVelocity(F32 x, F32 y)
		{
			_velocity[0] = x;
			_velocity[1] = y;
		}

		inline void SetVelocity(F32 x, F32 y, F32 z)
		{
			_velocity[0] = x;
			_velocity[1] = y;
			_velocity[2] = z;
		}

		inline void AddScaledVelocity(const KM::Vector& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

//===== Accleration =====
		inline const KM::Vector& GetAcceleration(void) const
		{
			return _acceleration;
		}

		inline void SetAcceleration(const KM::Vector& acc)
		{
			_acceleration = acc;
		}

		inline void SetAcceleration(F32 x, F32 y)
		{
			_acceleration[0] = x;
			_acceleration[1] = y;
		}

		inline void SetAcceleration(F32 x, F32 y, F32 z)
		{
			_acceleration[0] = x;
			_acceleration[1] = y;
			_acceleration[2] = z;
		}

		inline void AddScaledAcceleration(const KM::Vector& acc, F32 scale)
		{
			_acceleration.AddScaledVector(acc, scale);
		}

//===== Froces =====
		inline const KM::Vector& GetForces(void) const
		{
			return _forceAccum;
		}

//===== Gravity =====
		inline const KM::Vector& GetGravityForce(void) const
		{
			return _gravityForce;
		}

		inline void SetGravityForce(const KM::Vector& grav)
		{
			_gravityForce = grav;
		}

//===== Mass =====
		inline const real GetInverseMass(void) const
		{
			return _inverseMass;
		}

		inline void SetInverseMass(real inverseMass)
		{
			_inverseMass = inverseMass;
		}

		inline bool HasFiniteMass(void)
		{
			return _inverseMass >= 0.0f;
		}

		const real GetMass(void);

		inline void SetMass(real mass)
		{
			assert(mass != 0.0f);
			_inverseMass = static_cast<real>(1.0f) / mass;
		}

//===== Damping =====
		inline const real GetDamping(void) const
		{
			return _damping;
		}

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
		KM::Vector _velocity;
		KM::Vector _acceleration;
		KM::Vector _forceAccum;
		KM::Vector _gravityForce;
		real 	   _inverseMass;
		real 	   _damping;
	};
}