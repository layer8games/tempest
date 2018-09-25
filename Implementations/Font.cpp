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

	rapidxml::xml_node<>* root_node = doc.first_node("font")->first_node("chars");

	U32 totalChars = static_cast<U32>(std::stoi(root_node->first_attribute("count")->value()));

	std::cout << "total chars = " << totalChars << "\n";

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