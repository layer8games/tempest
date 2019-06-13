#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Glyph.h>
#include <Engine/RigidBody2D.h>
#include <Engine/RigidBody3D.h>

namespace KP = KillerPhysics;

namespace KillerEngine
{
	class EngineFactory
	{
	public:
//==========================================================================================================================
//
//Destructor	 	
//
//==========================================================================================================================
		~EngineFactory(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline p_Glyph MakeGlyph(void)
		{
			return make_shared<Glyph>();
		}

		inline KP::p_RigidBody2D MakeRigidBody2D(void)
		{
			return KP::p_RigidBody2D(new KP::RigidBody2D());
		}

		inline KP::p_RigidBody3D MakeRigidBody3D(void)
		{
			return KP::p_RigidBody3D(new KP::RigidBody3D());
		}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static shared_ptr<EngineFactory> Instance(void);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		EngineFactory(void);

	private:
		static shared_ptr<EngineFactory> _instance;
		
	};//end Class

	typedef shared_ptr<EngineFactory> P_EngineFactory;
}//end Namespace
