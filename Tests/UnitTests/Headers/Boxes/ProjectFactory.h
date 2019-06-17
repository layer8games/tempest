#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/PhysicsFactory.h>

namespace KP = KillerPhysics;

//===== Boxes Includes =====
#include <Boxes/Box.h>
#include <Boxes/Cannon.h>
#include <Boxes/Projectile.h>
#include <Boxes/Cube.h>
#include <Boxes/Firework.h>
#include <Boxes/Payload.h>

namespace Boxes
{
	class ProjectFactory;
	typedef shared_ptr<ProjectFactory> p_ProjectFactory;

	class ProjectFactory
	{
	public:
//==========================================================================================================================
//
//Destructor	 	
//
//==========================================================================================================================
		~ProjectFactory(void);

//==========================================================================================================================
//
//Creator Functions
//
//==========================================================================================================================
		inline p_Box MakeBox(void)
		{
			return p_Box(new Box());
		}

		inline p_Cannon MakeCannon(void)
		{
			return p_Cannon(new Cannon());
		}

		inline p_Projectile MakeProjectile(void)
		{
			p_Projectile p = new Projectile();
			p->SetBody(KP::PhysicsFactory::Instance()->MakeRigidBody2D());
			return p;
		}

		inline p_Cube MakeCube(void)
		{
			return p_Cube(new Cube());
		}

		inline p_Firework MakeFirework(void)
		{
			return p_Firework(new Firework());
		}

		inline p_Payload MakePayload(void)
		{
			return p_Payload(new Payload());
		}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static p_ProjectFactory Instance(void);

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		protected:
		ProjectFactory(void);

	private:
		static p_ProjectFactory _instance;

	};//end Class
}//end Namespace
