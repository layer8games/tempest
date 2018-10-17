#include <Engine/Glyph.h>

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
_characterData()
{  }

Glyph::Glyph(char character, const Texture& tex, const CharacterData& characterData)
:
_character(character),
_texture(tex),
_characterData(characterData)
{
	v_InitBuffers();
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
	GameObject::_shader.Use(true);
	GameObject::_shader.SetUniform("model", GameObject::GetModelMatrix());

	_texture.Bind();
	
	GameObject::BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, GameObject::GetNumVertices());

	_texture.UnBind();
	GameObject::_shader.Use(false);
	GameObject::BindVAO(false);
}

void Glyph::v_InitBuffers(void)
{
	KM::Vector topRight(-1.0f, 1.0f, 0.0f);
	KM::Vector topLeft(1.0f, 1.0f, 0.0f);
	KM::Vector bottomRight(-1.0f, -1.0f, 0.0f);
	KM::Vector bottomLeft(1.0f, -1.0f, 0.0);

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

	vertPositions.push_back(bottomLeft[0]);
	vertPositions.push_back(bottomLeft[1]);
	vertPositions.push_back(bottomLeft[2]);
	vertPositions.push_back(bottomLeft[3]);

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

	GameObject::BindVAO(true);

	GameObject::BindVBO(VERTEX_BUFFER, true);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPositions.size()), &vertPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	GameObject::BindVBO(TEX_COORD_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(TEX_COORD_POS);

	GameObject::BindVAO(false);
}