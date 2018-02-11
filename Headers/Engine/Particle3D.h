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
	
		~Particle3D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Velocity
//==========================================================================================================================
		KM::Vector3& GetVelocity(void);
		
		void  SetVelocity(KM::Vector3& vel);

		void SetVelocity(F32 x, F32 y, F32 z);

		void AddScaledVelocity(const KM::Vector3 v, F32 scale);

//==========================================================================================================================
//Acceleration
//==========================================================================================================================		
		KM::Vector3& GetAcceleration(void);

		void SetAcceleration(KM::Vector3& acc);

		void SetAcceleration(F32 x, F32 y, F32 z);

		void AddScaledAcceleration(const KM::Vector3& v, F32 scale);

//==========================================================================================================================
//Damping
//==========================================================================================================================		
		real GetDamping(void);

		void SetDamping(real damp);

//==========================================================================================================================
//Mass
//==========================================================================================================================		
		real GetInverseMass(void);

		void SetInverseMass(real mass);

		real GetMass(void);

		void SetMass(const real mass);

		bool HasFiniteMass(void);

//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		virtual void v_Update(void);

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
		real 		_inverseMass;
		real 		_damping;
		KM::Vector3 _forceAccum;
	};
}//End namespace