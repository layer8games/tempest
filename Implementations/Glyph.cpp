#include <Engine/Glyph.h>
#include <iostream>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Glyph::Glyph(void) 
:
_character(),
_characterData()
{  }

Glyph::Glyph(const Glyph& glyph)
:
GameObject(glyph),
_character(glyph.GetCharacter()),
_characterData(glyph.GetCharacterData())
{  }

Glyph::~Glyph(void)
{  }

/*
Glyph& Glyph::operator=(const Glyph& glyph)
{
	GameObject = glyph;
	_character = glyph.GetCharacter(),
	_characterDatar = glyph.GetCharacterData();
}
*/

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Glyph::Init(void)
{
	GameObject::MakeSprite();

	GameObject::SetShader(ShaderManager::Instance()->GetShader(GLYPH));
}