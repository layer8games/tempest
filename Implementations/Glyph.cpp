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
	_mesh.GetShader()->Use(true);

	_mesh.GetShader()->SetUniform("sprite_color", GameObject::GetColor());
	_mesh.GetShader()->SetUniform("model", GameObject::GetModelMatrix());
	
	_mesh.GetTexture()->Bind(true);
	_mesh.BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, _mesh.GetNumVertices());

	_mesh.GetShader()->Use(false);
	_mesh.GetTexture()->Bind(false);
	_mesh.BindVAO(false);
}

void Glyph::Init(void)
{
	// TODO: Need to instatiate a Sprite, with Shader and add it to the GameObject as the Mesh
	//GameObject::MakeSprite();
	//GameObject::SetMeshShader(ShaderManager::Instance()->GetShader(GLYPH));
}