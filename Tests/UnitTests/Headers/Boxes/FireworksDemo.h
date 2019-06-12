/*========================================================================
A basic level that will demo fireworks that are created procedurally though
the logic of the physics engine. The bulk of this code came from teh book
Game Physics Engine Development by Ian Millington. I have altered the 
code to fit my engine, but this is the example given in chapter 4

This is not free to use, and cannot be used without the express permission
of Layer8 Games.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/Level.h>
#include <Engine/Text.h>
#include <Engine/FontManager.h>
#include <Engine/Controller.h>
#include <Engine/Point.h>

//===== Box Includes =====
#include <Boxes/Firework.h>
#include <Boxes/DataBases.h>
#include <Boxes/ProjectFactory.h>

namespace KE = KillerEngine;

namespace Boxes
{
	typedef std::vector<p_Payload> PayloadPool;

	class FireworksDemo : public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		FireworksDemo(void);

		~FireworksDemo(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Init(void) final;
		
		void v_Update(void) final;
	
	private:
		PayloadPool _pool;
		KE::Text 	_levelTitle;
		p_Firework 	_firework;
		F32			_speed;
		
	};//end Class
}//end Namespace
