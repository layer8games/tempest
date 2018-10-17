#include <Engine/Font.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Font::Font(void) 
:
_numCharacters(128),
_fontName(), 
_characterGlyphs()
{  }

Font::Font(const Font& f)
:
_numCharacters(f.GetNumCharacters()),
_fontName(f.GetName()),
_characterGlyphs(f.GetAllCharacterGlyphs())
{  }

Font::Font(const Font* f)
:
_numCharacters(f->GetNumCharacters()),
_fontName(f->GetName()),
_characterGlyphs(f->GetAllCharacterGlyphs())
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Font::InitFont(string fontName, string filePath, U32 fontSize)
{
 	S32 error;
	FT_Library ft;
	error = FT_Init_FreeType(&ft);
	if(error != 0) 
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Library with Error Code: " + error);
	}

	FT_Face face;
	error = FT_New_Face(ft, filePath.c_str(), 0, &face);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Face with Error Code: " + error);
		std::cout << "Error: " << error << std::endl;
	}

	error = FT_Set_Pixel_Sizes(face, 0, fontSize);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont cannot set pixel sizes with Error Code: " + error);
	}

	std::cout << "num characters is " << _numCharacters << std::endl;

	char c = 0;
	for(int i = 0; i < _numCharacters; ++i)
	{
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if(error != 0)
		{
			ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to load Glyph for " + c);
			continue;
		}
		

		++c;
	}

	error = FT_Done_Face(face);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to release face");
	}

	error = FT_Done_FreeType(ft);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to release FreeType Library");
	}
}//InitFont


//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Font& Font::operator=(const Font& font)
{
	_fontName = font.GetName();
	_characterGlyphs = font.GetAllCharacterGlyphs();

	return *this;
}

Font& Font::operator=(const Font* font)
{
	_fontName = font->GetName();
	_characterGlyphs = font->GetAllCharacterGlyphs();

	return *this;
}