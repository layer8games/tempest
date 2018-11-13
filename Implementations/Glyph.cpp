#include <Engine/Glyph.h>
#include <iostream>

using namespace KillerEngine;

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

void Glyph::v_InitBuffers(void)
{
	KM::Vector topRight(1.0f, 1.0f, 0.0f);
	KM::Vector topLeft(-1.0f, 1.0f, 0.0f);
	KM::Vector bottomRight(1.0f, -1.0f, 0.0f);
	KM::Vector bottomLeft(-1.0f, -1.0f, 0.0);

	GameObject::AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	GameObject::AddVertex(Vertex(topRight, 1.0f, 0.0f));
	GameObject::AddVertex(Vertex(bottomRight, 1.0f, 1.0f));

	GameObject::AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	GameObject::AddVertex(Vertex(bottomRight, 1.0f, 1.0f));
	GameObject::AddVertex(Vertex(bottomLeft, 0.0f, 1.0f));

	GameObject::v_InitBuffers();

	GameObject::SetShader(ShaderManager::Instance()->GetShader(GLYPH));
}