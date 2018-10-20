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
	//GameObject::_shader.SetUniform("projection", _projection);
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

/*
	std::vector<F32> vertPositions;
	std::vector<F32> vertTexCoords;

	//tri 1
	vertPositions.push_back(topLeft[0]);
	vertPositions.push_back(topLeft[1]);
	vertPositions.push_back(topLeft[2]);
	vertPositions.push_back(topLeft[3]);
	
	vertTexCoords.push_back(0.0f);
	vertTexCoords.push_back(1.0f);

	vertPositions.push_back(topRight[0]);
	vertPositions.push_back(topRight[1]);
	vertPositions.push_back(topRight[2]);
	vertPositions.push_back(topRight[3]);
	
	vertTexCoords.push_back(1.0f);
	vertTexCoords.push_back(1.0f);

	vertPositions.push_back(bottomRight[0]);
	vertPositions.push_back(bottomRight[1]);
	vertPositions.push_back(bottomRight[2]);
	vertPositions.push_back(bottomRight[3]);

	vertTexCoords.push_back(1.0f);
	vertTexCoords.push_back(0.0f);

	//tri 2
	vertPositions.push_back(topLeft[0]);
	vertPositions.push_back(topLeft[1]);
	vertPositions.push_back(topLeft[2]);
	vertPositions.push_back(topLeft[3]);

	vertTexCoords.push_back(0.0f);
	vertTexCoords.push_back(1.0f);

	vertPositions.push_back(bottomRight[0]);
	vertPositions.push_back(bottomRight[1]);
	vertPositions.push_back(bottomRight[2]);
	vertPositions.push_back(bottomRight[3]);

	vertTexCoords.push_back(1.0f);
	vertTexCoords.push_back(0.0f);

	vertPositions.push_back(bottomLeft[0]);
	vertPositions.push_back(bottomLeft[1]);
	vertPositions.push_back(bottomLeft[2]);
	vertPositions.push_back(bottomLeft[3]);

	vertTexCoords.push_back(0.0f);
	vertTexCoords.push_back(0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	GameObject::BindVAO(true);

	GameObject::BindVBO(VERTEX_BUFFER, true);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPositions.size()), &vertPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	GameObject::BindVBO(TEX_COORD_BUFFER, true);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(TEX_COORD_POS);

	GameObject::BindVAO(false);
*/

	//TODO: Need to store depth in the WinProgram
	_projection.MakeOrthographic(
		static_cast<F32>(WinProgram::Instance()->GetWidth()), 
		static_cast<F32>(WinProgram::Instance()->GetHeight()), 
		200
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