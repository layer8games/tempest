/*========================================================================
A sprite based UI character to be rendered at run time. Is a GameObject

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Vector.h>
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

		void SetPosition(const KM::Vector& pos)
		{
			_pos = pos;
		}

		const KM::Vector& GetPosition(void) const
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
		KM::Vector _pos;
		F32 		_width;
		F32			_height;
		Color 		_color;
		
		static U32 _nextId;
	};//end Class
}//end Namespace