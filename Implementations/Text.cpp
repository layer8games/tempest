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
_scale(1.0f, 1.0f),
_color(1.0f)
{  }

Text::Text(const Font& font) 
: 
_active(true),
_pos(0.0f),
_text(), 
_font(font), 
_characterList(),  
_scale(1.0f, 1.0f),
_color(1.0f)
{  }

Text::Text(const Font& font, string text) 
:
_active(true),
_pos(0.0f), 
_text(text), 
_font(font), 
_characterList(),  
_scale(1.0f, 1.0f),
_color(1.0f)
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
		for(U32 i = 0; i < _characterList.size(); ++i)
		{
			_characterList[i].v_Render();
		}
	}
}

void Text::AddText(string text)
{
	_text = text;
	_characterList.clear();

	KM::Vector currentPos = _pos;
	F32 size = static_cast<F32>(_font.GetSize());

	for(U32 i = 0; i < _text.size(); ++i)
	{
		Glyph g = _font.GetCharacterGlyph(_text[i]);
		
		CharacterData data = g.GetCharacterData();

		g.SetColor(_color);
		//g.SetColor(1.0f, 0.0f, 0.0f);

		//g.SetPosition(currentPos[0] + data.bearingX, currentPos[1] - (data.height - data.bearingY));
		g.SetPosition(currentPos);

		//std::cout << "for character " << _text[i] << " xAdvance is " << data.xAdvance << " and offset will be " << currentPos[0] << std::endl
		//<< "pos is " << g.GetPosition()[0] << " " << g.GetPosition()[1] << std::endl
		//<< "scale will be " << data.width << " " << data.height << std::endl
		//<< "size is " << size << std::endl;
		//if(_text[i + 1] != ' ')
		//{
			currentPos[0] += data.xAdvance;
		//}
		
		//g.SetScale(static_cast<F32>(data.width), static_cast<F32>(data.height));
		//g.SetScale(size, size);
		g.SetScale(25.0f, 25.0f);

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

void Text::SetUniforms(string name, const KM::Matrix& matrix)
{
	for(auto i : _characterList)
	{
		i.SetUniform(name, matrix);
	}
}