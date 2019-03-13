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

namespace KE = KillerEngine;
namespace KM = KillerMath;

namespace Boxes
{

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
//Virtual functions
//
//==========================================================================================================================		
		void v_Update(void);

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

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		F32  	  				_speed;
		KM::Vector4 			_direction;
	};

}//End namespace
