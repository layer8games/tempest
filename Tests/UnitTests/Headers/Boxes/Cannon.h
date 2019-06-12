#pragma once
/*=========================================================================
Physics demo, aka Ballistics. 

This the player texture that will be responsible for firing projectiles in 
this specific level. It does not move, and only fires its projectiles onto
the screen. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#pragma once

//Killer1 Includes
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Controller.h>
#include <Engine/Timer.h>
#include <Engine/Texture.h>
#include <Engine/Vector4.h>
#include <Engine/LevelManager.h>
#include <Engine/GravityForce.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;
namespace KP = KillerPhysics;

//=====std includes=====
#include <vector>

//=====Box inclues=====
#include <Boxes/Projectile.h>

namespace Boxes
{
	class Cannon;
	typedef shared_ptr<Cannon> p_Cannon;

	class Cannon : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Cannon(void);

		~Cannon(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void v_Update(void);

		void Fire(const KM::Vector4& heading, shared_ptr<Projectile> projectile, ProjectileType type);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetMovementSpeed(F32 speed)
		{
			_movementSpeed = speed;
		}

		inline F32 GetMovementSpeed(void) const
		{
			return _movementSpeed;
		}

		inline void SetBottomBoundary(F32 boundary) 
		{
			_bottomBoundary = boundary;
		}

		inline F32 GetBottomBoundary(void) const
		{
			return _bottomBoundary;
		}

		inline void SetTopBoundary(F32 boundary)
		{
			_topBoundary = boundary;
		}

		inline F32 GetTopBoundary(void) const
		{
			return _topBoundary;
		}

		inline void SetUpDirection(const KM::Vector4& direction)
		{
			_upDirection = direction;
		}

		inline const KM::Vector4& GetUpDirection(void) const
		{
			return _upDirection;
		}

		inline void SetDownDirection(const KM::Vector4& direction)
		{
			_downDirection = direction;
		}

		inline const KM::Vector4& GetDownDirection(void) const
		{
			return _downDirection;
		}

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
		F32						  			 _movementSpeed;
		F32						  			 _bottomBoundary;
		F32						  			 _topBoundary;
		KM::Vector4							 _upDirection;
		KM::Vector4							 _downDirection;
	};
}//end namespace