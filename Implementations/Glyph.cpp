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
void Glyph::v_Render(void)
{
	GameObject::UseShader(true);

	GameObject::SetUniform("sprite_color", GameObject::GetColor());
	GameObject::SetUniform("model", GameObject::GetModelMatrix());
	
	GameObject::BindTexture(true);
	GameObject::BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, GameObject::GetNumVertices());

	GameObject::UseShader(false);
	GameObject::BindTexture(false);
	GameObject::BindVAO(false);
}

void Glyph::Init(void)
{
	GameObject::MakeSprite();

	GameObject::SetShader(ShaderManager::Instance()->GetShader(GLYPH));
}