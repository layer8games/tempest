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