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
_totalWidth(0.0f),
_pos(0.0f),
_text(), 
_font(), 
_characterList(),  
_scale(1.0f, 1.0f),
_color(1.0f)
{  }

Text::~Text(void)
{  }

//==========================================================================================================================
//
//Text Functions
//
//==========================================================================================================================
void Text::AddText(string text)
{
	_text = text;
	_characterList.clear();

	KM::Vector currentPos = _pos;
	F32 size = static_cast<F32>(_font->GetSize());

	for(U32 i = 0; i < _text.size(); ++i)
	{
		CharacterData data = _font->GetCharacterData(_text[i]);
		
		shared_ptr<Glyph> g(new Glyph());
		g->v_InitBuffers();
		g->SetScale(static_cast<F32>(data.width), static_cast<F32>(data.height));
		g->SetColor(_color);
		//g->SetPosition(currentPos[0] + data.bearingX, currentPos[1] - (data.height + data.bearingY));
		g->SetPosition(currentPos);
		g->SetTexture(data.texture);
		g->SetCharacter(_text[i], data);

		currentPos[0] += data.xAdvance + _font->GetSize();
		_totalWidth += data.width;
		
		_characterList.push_back(g);
	}	
}//End AddText

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

void Text::_UpdatePositions(void)
{
	KM::Vector currentPos = _pos;
	U32 size = _font->GetSize();

	for(U32 i = 0; i < _characterList.size(); ++i)
	{
		CharacterData data = _font->GetCharacterData(_characterList[i]->GetCharacter());
		//_characterList[i]->SetPosition(currentPos[0] + data.bearingX, currentPos[1] - (data.height + data.bearingY));
		_characterList[i]->SetPosition(currentPos);

		currentPos[0] += data.xAdvance + size;
	}
}

void Text::_UpdateActive(void)
{
	for(U32 i = 0; i < _characterList.size(); ++i)
	{
		_characterList[i]->SetActive(_active);
	}
}

void Text::_UpdateScales(void)
{
	for(U32 i = 0; i < _characterList.size(); ++i)
	{
		_characterList[i]->SetScale(_scale);
	}
}

void Text::_UpdateColors(void)
{
	for(U32 i = 0; i < _characterList.size(); ++i)
	{
		_characterList[i]->SetColor(_color);
	}
}