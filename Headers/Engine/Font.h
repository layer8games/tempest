#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/Texture.h>
#include <Engine/CharacterData.h>
#include <Engine/Glyph.h>
#include <Engine/ErrorManager.h>

//===== External =====
#include <ft2build.h>
#include FT_FREETYPE_H

//=====STL includes=====
#include <vector>
#include <map>
#include <list>

typedef std::map<char, KillerEngine::CharacterData> CharacterDataMap;

namespace KillerEngine
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The Font class is used to open a .fnt file, extract the needed character data, and then save that for text processing 
	later on.
	
	CreateCharacter is a CharSprite Factory. This may be important to know. */
	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! Default Constructor. No special actions taken. */
		Font(void);

/*! Copy Constructor. Calls GetTextureID(), GetFile() and GetName(). 
	\param f Font&: Font to be copied.*/
		Font(const Font& f);

/*! Copy Constructor. Calls GetTextureID(), GetFile() and GetName(). 
	\param f Font*: Font to be copied.*/
		Font(const Font* f);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
	void Init(string fontName, string filePath, U32 fontSize);

//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
/*! Copies Font pointer. Calls GetTextureID(), GetFile(), GetName() and GetCharacterData(). */
		Font& operator=(const Font* font);

/*! Copies Font reference. Calls GetTextureID(), GetFile(), GetName() and GetCharacterData(). */
		Font& operator=(const Font& font);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline bool GetInitialized(void) const
		{
			return _initialized;
		}

//===== Num Characters =====
// 128 for ACCII, 256 for UTF8
		inline void SetNumCharacters(S32 num)
		{
			_numCharacters = num;
		}

		inline S32 GetNumCharacters(void) const
		{
			return _numCharacters;
		}

		inline void SetSize(U32 size)
		{
			_fontSize = size;
		}

		inline U32 GetSize(void) const
		{
			return _fontSize;
		}

/*! Set's the name of font. Not used actively in any major way.
	\param fontName string: New name of the font. */
		inline void SetName(string fontName)
		{
			_fontName = fontName; 
		}

/*! Returns the current name of the font. Not used in any major way. */		
		inline const string GetName(void) const
		{
			return _fontName; 
		}

/*! Returns the map containing all data for all characters found in the loaded font. The ID of each character is found in 
	the .fnt file and is the ASCII int value of a char */
		CharacterDataMap GetAllCharacterGlyphs(void) const
		{ 
			return _characterGlyphs; 
		}

		inline CharacterData GetCharacterData(char c)
		{
			return _characterGlyphs[c];
		}

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================	
		bool 	 _initialized;
		S32 	 _numCharacters;
		U32 	 _fontSize;
		string   _fontName;
		CharacterDataMap _characterGlyphs; ///< All data from .fnt file stored in a RenderText can use for placement.
	};
}