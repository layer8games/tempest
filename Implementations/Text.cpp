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
			//std::cout << "trying to render " << _characterList[i].GetCharacter() << std::endl;
			//_characterList[i].v_Render();
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
		//Glyph g = _font.GetCharacterGlyph(_text[i]);
		CharacterData data = _font.GetCharacter(_text[i]);

		//std::cout << "for " << _text[i] << " creating glyph with width " << data.width << " height " << data.height << " texture with handel " << data.texture->GetHandle() << std::endl;

		shared_ptr<Glyph> g(new Glyph());
		g->v_InitBuffers();
		g->SetScale(static_cast<F32>(data.width), static_cast<F32>(data.height));
		//g->SetScale(25.0f, 25.0f);
		g->SetColor(_color);
		//g->SetColor(1.0f, 0.0f, 0.0f);
		g->SetPosition(currentPos[0] + data.bearingX, currentPos[1] - (data.height - data.bearingY));
		//g->SetPosition(currentPos);
		g->SetTexture(data.texture);
		g->SetCharacter(_text[i], data);

		//if(_text[i + 1] != ' ')
		//{
		currentPos[0] += data.xAdvance;
		//}

		std::cout << "xAdvance is " << data.xAdvance << " for " << _text[i] << std::endl;
		
		//g->SetScale(static_cast<F32>(data.width), static_cast<F32>(data.height));
		//g->SetScale(size, size);

		//std::cout << "from glyph " << g->GetCharacter() << std::endl;
		
		_characterList.push_back(g);

		//std::cout << "from char list " << _characterList[i].GetCharacter() << std::endl;
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
		i->SetColor(col);
	}
}

void Text::SetUniforms(string name, const KM::Matrix& matrix)
{
	for(auto i : _characterList)
	{
		i->SetUniform(name, matrix);
	}
}