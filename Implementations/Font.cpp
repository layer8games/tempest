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
void Font::InitFont(string fontName, string filePath)
{
	if(filePath.find(".fnt") == string::npos)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "Font::InitFont => Wrong file type: " + filePath);
		return;
	}

	std::ifstream file(filePath);

	if(!file)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "Font::InitFont => unable to open file: " + filePath);
		return;
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	file.close();

	rapidxml::xml_document<char> doc;
	doc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* node = doc.first_node("font")->first_node("chars");

	U32 totalChars = static_cast<U32>(std::stoi(node->first_attribute("count")->value()));
	
	node = node->first_node("char");

	for(U32 i = 0; i < totalChars; ++i)
	{
		CharacterData data;
		data.id = static_cast<S32>(std::stoi(node->first_attribute("id")->value()));
		data.x = static_cast<S32>(std::stoi(node->first_attribute("x")->value()));
		data.y = static_cast<S32>(std::stoi(node->first_attribute("y")->value()));
		data.width = static_cast<S32>(std::stoi(node->first_attribute("width")->value()));
		data.height = static_cast<S32>(std::stoi(node->first_attribute("height")->value()));
		data.xoffset = static_cast<S32>(std::stoi(node->first_attribute("xoffset")->value()));
		data.yoffset = static_cast<S32>(std::stoi(node->first_attribute("yoffset")->value()));
		data.xadvance = static_cast<S32>(std::stoi(node->first_attribute("xadvance")->value()));

		_characterData.insert({data.id, data});

		node = node->next_sibling("char");
	}
}//InitFont

/*
old version for reference

std::shared_ptr<Sprite> Font::CreateCharacter(char character)
{
//		std::cout << "FONT:: character=" << character << "\ntexture id =" << _textureID << "\nfont name=" << _fontName << "\n"; 

	U32 id = static_cast<U32>(character);

	shared_ptr<Texture> texture = TextureManager::Instance()->GetTexture(_textureID);

	CharacterData data = _fontCharData[id];

	shared_ptr<Sprite> sprite{new Sprite()};

	F32 charWidth  	  = static_cast<F32>(data.width);
	F32 charHeight 	  = static_cast<F32>(data.height);
	F32 charX 	 	  = static_cast<F32>(data.x);
	F32 charY 	 	  = static_cast<F32>(data.y);
	F32 textureWidth  = static_cast<F32>(texture->GetWidth());
	F32 textureHeight = static_cast<F32>(texture->GetHeight());

	F32 rightCoord   = (charX / textureWidth);
	F32 topCoord    = charY / textureHeight;
	F32 leftCoord  = rightCoord + charWidth / textureWidth;
	F32 bottomCoord = topCoord + charHeight / textureHeight;

	sprite->SetTexture(_textureID, topCoord, bottomCoord, rightCoord, leftCoord);

	sprite->SetCharData(data);
	
	return sprite;	 		
}


*/

CharacterData Font::GetCharacterData(char c)
{
	U32 id = U32(c);

	return _characterData[id];
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