#include <Engine/Glyph.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//Static Init
//==========================================================================================================================
	static U32 _nextID = 1;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Glyph::Glyph(void) 
:
_character(),
_texture(),
_characterData(),
_color(1.0f, 1.0f, 1.0f),
_projection(1.0f)
{
	v_InitBuffers();
}

Glyph::Glyph(const Glyph& glyph)
:
_character(glyph.GetCharacter()),
_texture(glyph.GetTexture()),
_characterData(glyph.GetCharacterData()),
_color(glyph.GetColor()),
_projection(1.0f)
{
	//std::cout << "At the time of copy, char is " << glyph.GetCharacter() << "\n";
	v_InitBuffers();
	GameObject::SetPosition(glyph.GetPosition());
}

Glyph::~Glyph(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Glyph::v_Render(void)
{
	//std::cout << "char is " << _character << "\n";

	GameObject::_shader.Use(true);
	GameObject::_shader.SetUniform("text_offset", GameObject::GetPosition());
	GameObject::_shader.SetUniform("projection", _projection);
	GameObject::_shader.SetUniform("text_color", _color);

	_texture.Bind();
	
	GameObject::BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, GameObject::GetNumVertices());

	_texture.UnBind();
	GameObject::_shader.Use(false);
	GameObject::BindVAO(false);
}

void Glyph::v_InitBuffers(void)
{
	KM::Vector topRight(0.25f, 0.25f, 0.0f);
	KM::Vector topLeft(-0.25f, 0.25f, 0.0f);
	KM::Vector bottomRight(0.25f, -0.25f, 0.0f);
	KM::Vector bottomLeft(-0.25f, -0.25f, 0.0);

	GameObject::AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	GameObject::AddVertex(Vertex(topRight, 1.0f, 0.0f));
	GameObject::AddVertex(Vertex(bottomRight, 1.0f, 1.0f));

	GameObject::AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	GameObject::AddVertex(Vertex(bottomRight, 1.0f, 1.0f));
	GameObject::AddVertex(Vertex(bottomLeft, 0.0f, 1.0f));

	GameObject::v_InitBuffers();

	//TODO: Need to store depth in the WinProgram
	_projection.MakeOrthographic(
		static_cast<F32>(WinProgram::Instance()->GetWidth()), 
		static_cast<F32>(WinProgram::Instance()->GetHeight()), 
		200.0f
	);


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