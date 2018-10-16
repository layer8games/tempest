#include <Engine/Text.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
Text::Text(void) 
: 
_pos(0.0f),
_text(), 
_font(), 
_characterList(), 
_width(0), 
_height(0), 
_scale(1.0f, 1.0f)
{  }

Text::Text(const Font& font) 
: 
_pos(0.0f),
_text(), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_scale(1.0f, 1.0f)
{  }

Text::Text(const Font& font, string text) 
:
_pos(0.0f), 
_text(text), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_scale(1.0f, 1.0f)
{
	AddText(_text);
}

Text::Text(const Font& font, string text, const KM::Vector& pos)
:
_pos(pos),
_text(text), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_scale(1.0f, 1.0f)
{
	AddText(_text);
}

Text::~Text(void)
{  }

//==========================================================================================================================
//
//Text Functions
//
//==========================================================================================================================
void Text::AddText(string text)
{
	
}//End AddText

void Text::SetPosition(const KM::Vector& pos)
{
/*
	_pos = pos;;

	F32 currentX = _pos.GetX();
	F32 currentY = _pos.GetY();

	for(shared_ptr<RenderedCharacter> character : _characterList)
	{
		CharacterData data = character->GetSprite().GetCharData();

		character->SetPosition(KM::Vector( currentX + static_cast<F32>(data.xoffset), currentY - static_cast<F32>(data.yoffset) ));

		currentX += static_cast<F32>(data.xadvance);// + static_cast<F32>(data.xoffset);
	}
*/	
}

/*	Not implemented yet in Sprite	
void Text::SetTextColor(Color& col)
{
	for(RenderedCharacter& character : _characterList)
	{
		character.SetColor(col);
	}
}
*/	