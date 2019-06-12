#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace KillerPhysics
{
	class PhysicsFactory
	{
	public:
//==========================================================================================================================
//
//Destructor	 	
//
//==========================================================================================================================
		~PhysicsFactory(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline p_RigidBody2D MakeRigidBody2D(void)
		{
			return p_RigidBody2D(new RigidBody2D());
		}

		inline p_RigidBody3D MakeRigidBody3D(void)
		{
			return p_RigidBody3D(new RigidBody3D());
		}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static shared_ptr<PhysicsFactory> Instance(void);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		PhysicsFactory(void);

	private:
		static shared_ptr<PhysicsFactory> _instance;
		
	};//end Class

	typedef shared_ptr<PhysicsFactory> P_PhysicsFactory;
}//end Namespace
