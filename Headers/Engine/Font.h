/*========================================================================
The Font class is used to open a .fnt file, extract the needed character
data, and then save that for text processing later on.

CreateCharacter is a CharSprite Factory. This may be important to know.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/Texture.h>
#include <Engine/Sprite.h>
#include <Engine/CharacterData.h>
#include <Engine/TextureManager.h>

//=====STL includes=====
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <map>
#include <list>
#include <memory>

namespace KillerEngine
{
	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Font(void);

		Font(const Font& f);

		Font(const Font* f);

		explicit Font(U32 tID);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
		void InitFont(string fontName, string fontFile);

		CharacterData GetDataForCharacter(char c);

		inline std::map<U32, CharacterData> GetDataLevel(void) const
		{ 
			return _fontCharData; 
		}

		std::shared_ptr<Sprite> CreateCharacter(char character);

//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================

		Font& operator=(const Font* font)
		{
			_textureID = font->GetTextureID();
			_fontFile = font->GetFile();
			_fontName = font->GetName();
			_fontCharData = font->GetDataLevel();

			return *this;
		}

		Font& operator=(const Font& font)
		{
			_textureID = font.GetTextureID();
			_fontFile = font.GetFile();
			_fontName = font.GetName();
			_fontCharData = font.GetDataLevel();

			return *this;
		}		

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetFile(string fontFile) 	  
		{
		 	_fontFile = fontFile; 
		}

		inline const string GetFile(void) const
		{ 
			return _fontFile; 
		}

		void SetName(string fontName)
		{ 
			_fontName = fontName; 
		}

		inline const string GetName(void) const
		{ 
			return _fontName; 
		}

		void SetTexture(U32 tID)
		{ 
			_textureID = tID; 
		}

		inline const U32 GetTextureID(void) const
		{ 
			return  _textureID; 
		}

	private:
		U32 					 	 _textureID;
		string  					 _fontFile;
		string  					 _fontName;
		U32     					 _headerSize = 26;
		std::map<U32, CharacterData> _fontCharData;

		void _AddNewCharacterData(string id,      string x, 		string y,
							  	  string width,   string height,   string xoffset,
							  	  string yoffset, string xadvance);
	};
}