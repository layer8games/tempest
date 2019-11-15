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

namespace Tempest
{

typedef std::map<char, CharacterData> CharacterDataMap;

//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	The Font class is used to open a .fnt file, extract the needed character data, and then save that for text processing 
	later on.
	
	CreateCharacter is a CharSprite Factory. This may be important to know.
*/
	class Font
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*!
 	Default Constructor. No special actions taken. 
*/
		Font(void);

/*! 
	Copy Constructor. Calls GetTextureID(), GetFile() and GetName(). 
	\param f Font&: Font to be copied.
*/
		Font(const Font& f);

/*! 
	Copy Constructor. Calls GetTextureID(), GetFile() and GetName(). 
	\param f Font*: Font to be copied.
*/
		Font(const Font* f);

//==========================================================================================================================
//
//Font Functions
//
//==========================================================================================================================
/*!
	Initializes the Font based on the file path and size. This holds most of the FreeType code that creates everything that
	is needed for the font. 
	\param fontName is the name of the font. 
	\param filePath is the relative path to the font file. Should be a ttf file. 
	\param fontSize is weight of the font. This should match what you'd find in a text editor, ie: 12, 18, 24. etc.
*/
	void Init(string fontName, string filePath, U32 fontSize);

//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
/*! 
	Copies Font pointer. Calls GetTextureID(), GetFile(), GetName() and GetCharacterData(). 
*/
		Font& operator=(const Font* font);

/*! 
	Copies Font reference. Calls GetTextureID(), GetFile(), GetName() and GetCharacterData(). 
*/
		Font& operator=(const Font& font);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns if the Font has been initialized yet. This allows for temporary Fonts that have not been fully created yet. 
*/
		inline bool GetInitialized(void) const
		{
			return _initialized;
		}

//===== Num Characters =====
/*!
	Sets the number of characters that the font contains. 
	\param num is the number of characters. Set 128 for ACCII, 256 for UTF8
*/
		inline void SetNumCharacters(S32 num)
		{
			_numCharacters = num;
		}

/*!
	Returns the number of characters found in the font. 128 for ACCII, 256 for UTF8.
*/
		inline S32 GetNumCharacters(void) const
		{
			return _numCharacters;
		}

/*!
	Sets the weight of the Font. Does not re-intialize. 
*/
		inline void SetSize(U32 size)
		{
			_fontSize = size;
		}

/*!
	Returns the current weight of the font.
*/
		inline U32 GetSize(void) const
		{
			return _fontSize;
		}

/*! 
	Set's the name of font. Not used actively in any major way.
	\param fontName string: New name of the font. 
*/
		inline void SetName(string fontName)
		{
			_fontName = fontName; 
		}

/*! 
	Returns the current name of the font. Not used in any major way. 
*/		
		inline const string GetName(void) const
		{
			return _fontName; 
		}

/*! 
	Returns the map containing all data for all characters found in the loaded font. The ID of each character is found in 
	the .fnt file and is the ASCII int value of a char 
*/
		inline CharacterDataMap GetAllCharacterGlyphs(void) const
		{ 
			return _characterGlyphs; 
		}

/*!
	Returns data for a single character. 
	\param c is the desired data character. 
*/
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
		bool 	 		 _initialized;		///< Initialization state of the Font. 
		S32 	 		 _numCharacters;	///< Number of characters found in the Font. 128 for ACCII, 256 for UTF8
		U32 	 		 _fontSize;			///< Size of the Font. Should be used like a text font for weight. 
		string   		 _fontName;			///< Name of the font. Not used for anything really. 
		CharacterDataMap _characterGlyphs; 	///< All data from .fnt file stored in a RenderText can use for placement.
	};//End Font
	typedef shared_ptr<Font> p_Font;
}//End namespace