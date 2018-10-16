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

		void v_Render(void);

		void v_InitBuffers(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
		void InitShader(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		inline void SetCharacter(char character, const Texture& tex, const CharacterData& characterData)
		{
			_character = character;
			_texture = tex;
			_characterData = characterData;

			v_InitBuffers();
		}

		inline void SetCharacter(char character, const CharacterData& characterData)
		{
			_character = character;
			_characterData = characterData;
		}

		inline void SetTexture(const Texture& tex)
		{
			_texture = tex;
		}

		const Texture& GetTexture(void)
		{
			return _texture;
		}

		const CharacterData& GetCharacterData(void) const
		{
			return _characterData;
		}

	private:
		char 		  _character;
		Texture 	  _texture;
		CharacterData _characterData;

	};//end Class
}//end Namespace