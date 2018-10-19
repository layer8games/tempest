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
_active(true),
_pos(0.0f),
_text(), 
_font(), 
_characterList(),  
_scale(1.0f, 1.0f)
{  }

Text::Text(const Font& font) 
: 
_active(true),
_pos(0.0f),
_text(), 
_font(font), 
_characterList(),  
_scale(1.0f, 1.0f)
{  }

Text::Text(const Font& font, string text) 
:
_active(true),
_pos(0.0f), 
_text(text), 
_font(font), 
_characterList(),  
_scale(1.0f, 1.0f)
{
	AddText(_text);
}

Text::Text(const Font& font, string text, const KM::Vector& pos)
:
_active(true),
_pos(pos),
_text(text), 
_font(font), 
_characterList(), 
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
void Text::Render(void)
{
	if(_active)
	{
		for(auto g : _characterList)
		{
			g.v_Render();
		}
	}
}

void Text::AddText(string text)
{
	_text = text;
	_characterList.clear();

	KM::Vector currentPos = _pos;

	for(U32 i = 0; i < _text.size(); ++i)
	{
		Glyph g = _font.GetCharacterGlyph(_text[i]);

		KM::Vector glyphPos = currentPos;
		glyphPos[0] += g.GetCharacterData().bearingWidth;
		glyphPos[1] -= g.GetCharacterData().bearingHeight;

		g.SetPosition(glyphPos);

		currentPos[0] += g.GetCharacterData().xAdvance;

		_characterList.push_back(g);
	}	
}//End AddText

void Text::SetPosition(const KM::Vector& pos)
{
	_pos = pos;;

	//TODO:: Maybe there should be a private function that just updates the positions. 
	if(_text.size() > 0)
	{
		AddText(_text);	
	}
}

void Text::SetTextColor(const Color& col)
{
	for(auto i : _characterList)
	{
		i.SetColor(col);
	}
}
