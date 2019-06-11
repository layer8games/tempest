/*=========================================================================
The player controled object in the basic game of boxes. It will inher-
it from the GameObject class, and will define its own update and render.
It will have a controller in time that will allow a player to control 
where the box goes.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#pragma once;

//Killer1 Includes
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Controller.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Color.h>
#include <Engine/AABB.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;
namespace KC = KillerCollisions;

namespace Boxes
{
	class Box;
	typedef shared_ptr<Box> p_Box;

	class Box : public KE::GameObject 
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		

		Box(void);

		Box(const KM::Point& pos, F32 width, F32 height);
		
		Box(const KM::Point& pos, F32 width, F32 height, const KE::Color& col);

		Box(const KM::Point& pos, F32 width, F32 height, const KE::Color& col, shared_ptr<KE::Texture> texture);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
		void v_Update(void);

		inline bool OverlapCheck(const shared_ptr<Box> other)
		{
			return _boundingBox.TestCollision(other->GetBounding());
		}

		void OnCollide(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetSpeed(F32 s) 
		{ 
			_speed = s; 
		}

		inline F32 GetSpeed(void) const
		{
			return _speed;
		}

		inline void SetDirection(const KM::Vector4& dir)
		{
			_direction = dir;
		}

		inline void SetDirection(F32 x, F32 y)
		{
			_direction[0] = x;
			_direction[1] = y;
		}

		inline const KM::Vector4& GetDirection(void) const
		{
			return _direction;
		}

		inline const KC::AABB& GetBounding(void) const
		{
			return _boundingBox;
		}

		void InitBounding(void);

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		F32  	  				_speed;
		KM::Vector4 			_direction;
		KC::AABB				_boundingBox;
	};

}//End namespace
