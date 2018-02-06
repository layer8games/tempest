/*========================================================================
The Particle represents a point mass that will be used in physics calcula-
tions. It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.

This is the 3D implementation. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef PARTICLE3D_H
#define PARTICLE3D_H
#pragma once

//=====Physics includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>

//=====KillerMath includes=====
#include <Engine/Timer.h>
#include <Engine/Vector3.h>

//=====STL and other includes=====
#include <cassert>

namespace KM = KillerMath;

namespace KillerPhysics 
{
	class Particle3D
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
		KM::Vector3& GetPosition(void) 
		{ 
			return position; 
		}
		
		void  SetPosition(KM::Vector3& pos) 
		{ 
			position = pos; 
		}

		KM::Vector3& GetVelocity(void) 
		{ 
			return velocity; 
		}
		
		void  SetVelocity(KM::Vector3& vel) 
		{ 
			velocity = vel; 
		}

		KM::Vector3& GetAcceleration(void) 
		{ 
			return acceleration; 
		}

		void SetAcceleration(KM::Vector3& acc) 
		{ 
			acceleration = acc; 
		}

		real GetDamping(void) 
		{ 
			return damping; 
		}

		void SetDamping(real damp) 
		{ 
			damping = damp; 
		}

		real GetInverseMass(void) 
		{ 
			return damping; 
		}

		void SetInverseMass(real mass) 
		{ 
			inverseMass = mass; 
		}

		real GetMass(void);

		void SetMass(const real mass);

//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		void Update(void);

	protected:
		KM::Vector3 position;
		KM::Vector3 velocity;
		KM::Vector3 acceleration;
		real damping;
		real inverseMass;
	};
}//End namespace

#endif