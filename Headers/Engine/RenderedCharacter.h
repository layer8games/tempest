/*========================================================================
A sprite based UI character to be rendered at run time. Is a GameObject2D

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Vector2.h>
#include <Engine/Sprite.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	class RenderedCharacter
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		RenderedCharacter(void);

		~RenderedCharacter(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Accessors
//==========================================================================================================================		
		U32 GetID(void)
		{
			return _id;
		}

		void SetPosition(const KM::Vector2& pos)
		{
			_pos = pos;
		}

		const KM::Vector2& GetPosition(void) const
		{
			return _pos;
		}

		void SetWidth(F32 w)
		{
			_width = w;
		}

		F32 GetWidth(void)
		{
			return _width;
		}

		F32 SetPosition(void)
		{
			return _width;
		}

		void SetHeight(F32 h)
		{
			_height = h;
		}

		F32 GetHeight(void)
		{
			return _height;
		}

		void SetDimensions(F32 w, F32 h)
		{
			_width = w;
			_height = h;
		}

		void SetSprite(shared_ptr<Sprite> sprite)
		{
			_sprite = sprite;
		}

		void SetSprite(const Sprite& sprite)
		{
			_sprite = sprite;
		}

		const Sprite& GetSprite(void) const
		{
			return _sprite;
		}

//		Not implemented yet in Sprite		
		void SetColor(const Color& col)
		{
			_color = col;
		}
				
		const Color& GetColor(void) const
		{
			return _color;
		}

	private:
		U32			_id;
		KM::Vector2 _pos;
		F32 		_width;
		F32			_height;
		Sprite 		_sprite;
		Color 		_color;
		
		static U32 _nextId;
	};//end Class
}//end Namespace