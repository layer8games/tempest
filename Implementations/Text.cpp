#include <Engine/Text.h>

using namespace Tempest;

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

Text::Text(string text) 
:
_active(true),
_totalWidth(0.0f),
_pos(0.0f),
_text(), 
_font(nullptr), 
_characterList(),  
_scale(1.0f, 1.0f),
_color(1.0f)
{
	AddText(text);
}

Text::Text(string text, p_Font font)
:
_active(true),
_totalWidth(0.0f),
_pos(0.0f),
_text(), 
_font(font), 
_characterList(),  
_scale(1.0f, 1.0f),
_color(1.0f)
{
	AddText(text);
}

Text::Text(string text, Font& font)
	:
	_active(true),
	_totalWidth(0.0f),
	_pos(0.0f),
	_text(),
	_font(),
	_characterList(),
	_scale(1.0f, 1.0f),
	_color(1.0f)
{
	_font = p_Font(&font);
	AddText(text);
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
	_CreateCharacterList();

	TM::Point2 currentPos = _pos;

	if(_font != nullptr)
	{
		for(U32 i = 0; i < _text.size(); ++i)
		{
			_UpdateGlyphData(i);
		}
		_UpdatePositions();
	}
		
}//End AddText

void Text::SetFont(p_Font font)
{
	if(!font->GetInitialized())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Text::SetFont cannot set uninitialized font.");
	}

	_font = font;

	if(_text.size() > 0)
	{
		for(U32 i = 0; i < _text.size(); ++i)
		{
			_UpdateGlyphData(i);
		}
		_UpdatePositions();
	}
}

void Text::SetTextColor(const Color& col)
{
	for(auto i : _characterList)
	{
		i->SetColor(col);
	}
}

//void Text::SetUniforms(string name, const TM::Matrix4& mat)
//{
//	for(auto i : _characterList)
//	{
//		i->GetShader()->SetUniform(name, mat);
//	}
//}

void Text::_UpdatePositions(void)
{
	TM::Point2 currentPos = _pos;
	
	if(_font != nullptr)
	{
		U32 size = _font->GetSize();

		for(U32 i = 0; i < _characterList.size(); ++i)
		{
			CharacterData data = _font->GetCharacterData(_characterList[i]->GetCharacter());
			//_characterList[i]->SetPosition(currentPos[0] + data.bearingX, currentPos[1] - (data.height + data.bearingY));
			_characterList[i]->SetPosition(currentPos);
			_characterList[i]->v_Update();

			currentPos.x += data.xAdvance + size;
		}	
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

void Text::_UpdateGlyphData(U32 index)
{
	if(_characterList.size() != _text.size())
	{
		_CreateCharacterList();
	}
	else
	{
		CharacterData data = _font->GetCharacterData(_text[index]);
		_characterList[index]->SetScale(static_cast<F32>(data.width), static_cast<F32>(data.height));
		_characterList[index]->SetColor(_color);
		_characterList[index]->SetTexture(data.texture);
		_characterList[index]->SetCharacter(_text[index], data);
		_totalWidth += data.width;
	}		
}

void Text::_CreateCharacterList(void)
{
	_characterList.clear();

	for(U32 i = 0; i < _text.size(); ++i)
	{
		shared_ptr<Glyph> g(new Glyph());
		g->Init();
		_characterList.push_back(g);
	}
}