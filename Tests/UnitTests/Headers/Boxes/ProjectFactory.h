#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Boxes/Box.h>
#include <Boxes/Cannon.h>
#include <Boxes/Projectile.h>
#include <Boxes/Cube.h>
#include <Boxes/Firework.h>

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
			return p_Projectile(new Projectile());
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
