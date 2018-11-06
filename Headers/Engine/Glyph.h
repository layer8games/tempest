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
#include <Engine/CharacterData.h>
#include <Engine/Color.h>
#include <Engine/Matrix.h>
#include <Engine/WinProgram.h>

#include <iostream>

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

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetCharacter(char character, const CharacterData& characterData)
		{
			_character = character;
			_characterData = characterData;
		}

		inline char GetCharacter(void) const
		{
			return _character;
		}

		inline const CharacterData& GetCharacterData(void) const
		{
			return _characterData;
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================


	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		char 		  _character;
		CharacterData _characterData;
	};//end Class
}//end Namespace
