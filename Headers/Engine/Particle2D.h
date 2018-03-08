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
	
		virtual ~Particle2D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====Damping=====
		real GetDamping(void) 
		{ 
			return _damping; 
		}

		void SetDamping(real damp) 
		{ 
			_damping = damp; 
		}

//=====Velocity=====
		KM::Vector2& GetVelocity(void);
		
		void SetVelocity(KM::Vector2& v);
		
		void SetVelocity(F32 x, F32 y);

		void AddScaledVelocity(const KM::Vector2& vec, F32 scale);

//=====Acceleration=====
		KM::Vector2& GetAcceleration(void);
		
		void SetAcceleration(KM::Vector2& a);

		void SetAcceleration(F32 x, F32 y);

		void AddScaledAcceleration(const KM::Vector2& vec, F32 scale);
		
//=====Mass=====
		real GetInverseMass(void);

		void SetInverseMass(real inverseMass);

		real GetMass(void);

		void SetMass(const real mass);

		bool HasFiniteMass(void);

//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		virtual void v_Update(void);

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
		real 		_inverseMass;
		real 		_damping;
		KM::Vector2 _forceAccum;
	};
}//End namespace