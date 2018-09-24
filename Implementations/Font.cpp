#include <Engine/Font.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Font::Font(void) 
: 
_texture(),
_fontName(), 
_characterData()
{  }

Font::Font(const Font& f)
:
_texture(f.GetTexture()),
_fontName(f.GetName()),
_characterData(f.GetCharacterData())
{  }

Font::Font(const Font* f)
:
_texture(f->GetTexture()),
_fontName(f->GetName()),
_characterData(f->GetCharacterData())
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Font::InitFont(string fontName, string fontFile)
{
	
		
}//InitFont

CharacterData Font::GetCharacterData(char c)
{
	U32 id = U32(c);

	return _characterData[id];

}

void Font::_AddNewCharacterData(string id,      string x, 		string y,
						    	string width,   string height,  string xoffset,
						    	string yoffset, string xadvance)
{
	//CharacterData data;
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Font& Font::operator=(const Font& font)
{
	_texture = font.GetTexture();
	_fontName = font.GetName();
	_characterData = font.GetCharacterData();

	return *this;
}

Font& Font::operator=(const Font* font)
{
	_texture = font->GetTexture();
	_fontName = font->GetName();
	_characterData = font->GetCharacterData();

	return *this;
}