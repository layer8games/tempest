#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/Vector.h>
#include <Engine/Quaternion.h>
#include <Engine/Matrix.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

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
		void v_Update(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		KM::Vector _velocity;
		KM::Vector _acceleration;
		KM::Vector _rotation;
		KM::Vector _forceAccum;
		KM::Matrix _transformMatrix;
		real 	   _inverseMass;
		real 	   _linearDamping;		

	};//end Class
}//end Namespace
