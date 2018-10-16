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
_size(0),
_numCharacters(128),
_fontName(), 
_characterGlyphs()
{  }

Font::Font(const Font& f)
:
_size(f.GetSize()),
_numCharacters(f.GetNumCharacters()),
_fontName(f.GetName()),
_characterGlyphs(f.GetAllCharacterGlyphs())
{  }

Font::Font(const Font* f)
:
_size(f->GetSize()),
_numCharacters(f->GetNumCharacters()),
_fontName(f->GetName()),
_characterGlyphs(f->GetAllCharacterGlyphs())
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Font::InitFont(string fontName, string filePath)
{
 
/*	
	std::cout << "Normal init font called\n";
	FT_Library ft;
	if(FT_Init_FreeType(&ft)) 
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Library");
	}

	FT_Face face;
	if(FT_New_Face(ft, filePath.c_str(), 0, &face)) 
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Face");
	}

	if(_size == 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to set font size");
	}

	if(FT_Set_Pixel_Sizes(face, 0, 48))
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont cannot set pixel sizes to " + _size);
	}

	for(char c = 0; c < _numCharacters; ++c)
	{
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to load Glyph for " + c);
			continue;
		}
		std::cout << "Loaded glyph for " << c << "\n";
	}

*/	
}//InitFont

void Font::InitFont(string fontName, string filePath, U32 fontSize)
{
	std::cout << "init font called with size\n";
	_size = fontSize;
	InitFont(fontName, filePath);
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Font& Font::operator=(const Font& font)
{
	_size = font.GetSize();
	_fontName = font.GetName();
	_characterGlyphs = font.GetAllCharacterGlyphs();

	return *this;
}

Font& Font::operator=(const Font* font)
{
	_size = font->GetSize();
	_fontName = font->GetName();
	_characterGlyphs = font->GetAllCharacterGlyphs();

	return *this;
}