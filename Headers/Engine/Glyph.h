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
#include <Engine/Texture.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	class Glyph : public GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Glyph(void);

		~Glyph(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void)
		{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		inline void SetTexture(const Texture& tex)
		{
			_texture = tex;
		}

		const Texture& GetTexture(void)
		{
			return _texture;
		}

	private:
		Texture _texture;

	};//end Class
}//end Namespace