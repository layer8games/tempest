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
	GameObject::_shader.Use(true);

	GameObject::SetUniform("sprite_color", GameObject::GetColor());
	GameObject::SetUniform("model", GameObject::GetModelMatrix());
	
	GameObject::BindTexture(true);
	GameObject::BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, GameObject::GetNumVertices());

	GameObject::_shader.Use(false);
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

	std::vector<ShaderData> shaderSources;

	ShaderData vs;
	vs.filePath = "../Assets/Shaders/Default/glyph_vertex.glsl";
	vs.type = ShaderType::VERTEX;
	shaderSources.push_back(vs);

	ShaderData fs;
	fs.filePath = "../Assets/Shaders/Default/glyph_fragment.glsl";
	fs.type = ShaderType::FRAGMENT;
	shaderSources.push_back(fs);

	GameObject::LoadShader(shaderSources);
}