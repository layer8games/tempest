/*========================================================================
A Particle force for 2D particles which simulates Gravity. In this case, 
down is going to be -y. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ParticleForceGenerator.h>
#include <Engine/Vector2.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class ParticleGravityForce : public ParticleForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		ParticleGravityForce(void);

		ParticleGravityForce(const KM::Vector2& gravity);

		ParticleGravityForce(const KM::Vector3& gravity);

		~ParticleGravityForce(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_UpdateForce(shared_ptr<Particle2D> particle) final;

		void v_UpdateForce(shared_ptr<Particle3D> particle) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		inline void SetGravityAcceleration(KM::Vector2& gravity)
		{
			_gravityAcc2D = gravity;
		}

		inline void SetGravityAcceleration(KM::Vector3& gravity)
		{
			_gravityAcc3D = gravity;
		}

	private:
		KM::Vector2 _gravityAcc2D;
		KM::Vector3 _gravityAcc3D;
	};//end class
}//end namespace