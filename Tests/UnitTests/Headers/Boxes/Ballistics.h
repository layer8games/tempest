/*==========================================================================================================================
Physics demo using the Killer Physics Engine. This will test various types of Ballistics, and will eventually turn into a 
king of mini game that lets you shoot down various types of missiles with the correct type of ballistic ammo. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
==========================================================================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/WinProgram.h>
#include <Engine/Level.h>
#include <Engine/Controller.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Vector4.h>
#include <Engine/Color.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

//=====Box includes=====
#include <Boxes/Cannon.h>
#include <Boxes/Projectile.h>

namespace Boxes
{
	class Ballistics : public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Ballistics(void);
		~Ballistics(void);		

//==========================================================================================================================
//
//Virtual Functions 
//
//==========================================================================================================================		
		void v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c);

		void v_Update(void);

	private:
		void _InitPool(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		U32									_poolSize;
		ProjectileType			  			_activeProjectileType;
		KE::Text 							_levelTitle;
		Cannon								_cannon;
		KP::GravityForce					_gravityForce;
		std::vector<shared_ptr<Projectile>> _projectilePool;
		Projectile test;
	};
}//end namespace