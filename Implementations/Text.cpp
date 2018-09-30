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
	_characterList.clear();

	_text = text;

	F32 fontWidth  = static_cast<F32>(_font.GetWidth());
	F32 fontHeight = static_cast<F32>(_font.GetHeight());
	F32 currentX = _pos[0];
	F32 currentY = _pos[1];
	Texture fontTexture = _font.GetTexture();

	for(U32 i = 0; i < _text.size(); ++i)
	{
		shared_ptr<Glyph> glyph{new Glyph()};

		CharacterData data = _font.GetCharacterData(_text[i]);
		
		F32 charX 	 	  = static_cast<F32>(data.x);
		F32 charY 	 	  = static_cast<F32>(data.y);
		F32 charWidth  	  = static_cast<F32>(data.width);
		F32 charHeight 	  = static_cast<F32>(data.height);
		F32 xoffset		  = static_cast<F32>(data.xoffset);
		F32 yoffset 	  = static_cast<F32>(data.yoffset);

		//Compute UV's for character
		F32 uMaxCoord = (charX / fontWidth);
		F32 uMinCoord = uMaxCoord + (charWidth / fontWidth);
		
		F32 vMaxCoord = charY / fontHeight;
		F32 vMinCoord = vMaxCoord + (charHeight / fontHeight);
		
		//Setup Glyph
		//ToDo::Set vertices for Glyph
		
		glyph->SetScale(_scale);

		KM::Vector charPos{1.0f, 1.0f};
		charPos.Make2D();

		currentX += static_cast<F32>(data.xadvance);

		glyph->SetPosition(charPos);

		glyph->SetTexture(fontTexture);

		_characterList.push_back(glyph);			
	}
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