/*========================================================================
The Particle represents a point mass that will be used in physics calcula-
tions. It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====KillerMath includes=====
#include <Engine/Timer.h>
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Vector2.h>

//=====STL and other includes=====
#include <cassert>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics 
{
	class Particle2D : public KE::GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2D(void);

		Particle2D(const Particle2D* particle);

		Particle2D(const Particle2D& particle);
	
		virtual ~Particle2D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====Damping=====
		inline const real GetDamping(void) const
		{ 
			return _damping; 
		}

		inline void SetDamping(real damp) 
		{ 
			_damping = damp; 
		}

//=====Velocity=====
		inline const KM::Vector2& GetVelocity(void) const
		{
			return _velocity;
		}
		
		inline void SetVelocity(const KM::Vector2& v)
		{
			_velocity = v;
		}
		
		inline void SetVelocity(F32 x, F32 y)
		{
			_velocity = KM::Vector2(x, y);
		}

		inline void AddScaledVelocity(const KM::Vector2& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

//=====Acceleration=====
		inline const KM::Vector2& GetAcceleration(void) const
		{
			return _acceleration;
		}
		
		inline void SetAcceleration(const KM::Vector2& a)
		{
			_acceleration = a;
		}

		inline void SetAcceleration(F32 x, F32 y)
		{
			_acceleration = KM::Vector2(x, y);
		}

		inline void AddScaledAcceleration(const KM::Vector2& vec, F32 scale)
		{
			_acceleration.AddScaledVector(vec, scale);
		}
		
//=====Mass=====
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

		inline bool HasFiniteMass(void)
		{
			return _inverseMass >= 0.0f;
		}

//=====Forces=====
		inline const KM::Vector2& GetForces(void) const
		{
			return _forceAccum;
		}

//=====Gravity=====
		inline const KM::Vector2& GetGravityForce(void) const
		{
			return _gravityForce;
		}

		inline void SetGravityForce(const KM::Vector2 gravity)
		{
			_gravityForce = gravity;
		}

//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		virtual void v_Update(void);

		void Integrate();

		void ClearAccumulator(void);

		void AddForce(const KM::Vector2& force);

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
		KM::Vector2 _velocity;
		KM::Vector2 _acceleration;
		KM::Vector2 _forceAccum;
		KM::Vector2 _gravityForce;
		real 		_inverseMass;
		real 		_damping;
	};
}//End namespace