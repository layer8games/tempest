#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Boxes/Box.h>
#include <Boxes/Projectile.h>
#include <Boxes/Cube.h>

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

		inline p_Projectile MakeProjectile(void)
		{
			return p_Projectile(new Projectile());
		}

		inline p_Cube MakeCube()
		{
			return p_Cube(new Cube());
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
