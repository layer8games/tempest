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
	KM::Vector charPos = _pos;
	
	Texture fontTexture = _font.GetTexture();

	std::vector<ShaderData> shaderData;

	ShaderData vs;
	vs.filePath = "..\\Assets\\Shaders\\sprite_vertex.glsl";
	vs.type = ShaderType::VERTEX;
	shaderData.push_back(vs);

	ShaderData fs;
	fs.filePath = "..\\Assets\\Shaders\\sprite_fragment.glsl";
	vs.type = ShaderType::FRAGMENT;
	shaderData.push_back(fs);

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
		F32 uMax = (charX / fontWidth);
		F32 uMin = uMax + (charWidth / fontWidth);
		
		F32 vMax = charY / fontHeight;
		F32 vMin = vMax + (charHeight / fontHeight);
		
		//std::cout << "offset for " << _text[i] << " => " << xoffset << " " << yoffset << std::endl;

		//Setup Glyph
		//First Triangle
		glyph->AddVertex(Vertex(KM::Vector(-1.0f, 1.0f, 0.0f), uMin, vMax)); //Top Left
		glyph->AddVertex(Vertex(KM::Vector(1.0f, 1.0f, 0.0f), uMax, vMax)); //Top Right
		glyph->AddVertex(Vertex(KM::Vector(1.0f, -1.0f, 0.0f), uMax, vMin)); //Bottom Right

		//Second Triangle
		glyph->AddVertex(Vertex(KM::Vector(-1.0f, 1.0f, 0.0f), uMin, vMax)); //Top Left
		glyph->AddVertex(Vertex(KM::Vector(1.0f, -1.0f, 0.0f), uMax, vMin)); //Bottom Right
		glyph->AddVertex(Vertex(KM::Vector(-1.0f, -1.0f, 0.0f), uMin, vMin)); //Bottom Left
		
		glyph->SetScale(_scale);

		glyph->SetPosition(charPos[0] + xoffset, charPos[1] + yoffset);
		
		charPos[0] += static_cast<F32>(data.xadvance);

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