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
_fontName(), 
_characterData()
{  }

Font::Font(const Font& f)
:
_size(f.GetSize()),
_fontName(f.GetName()),
_characterData(f.GetCharacterData())
{  }

Font::Font(const Font* f)
:
_size(f->GetSize()),
_fontName(f->GetName()),
_characterData(f->GetCharacterData())
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Font::InitFont(string fontName, string filePath)
{

}//InitFont


//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Font& Font::operator=(const Font& font)
{
	_size = font.GetSize();
	_fontName = font.GetName();
	_characterData = font.GetCharacterData();

	return *this;
}

Font& Font::operator=(const Font* font)
{
	_size = font->GetSize();
	_fontName = font->GetName();
	_characterData = font->GetCharacterData();

	return *this;
}