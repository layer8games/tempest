#include <Engine/GameObject.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Static Member
//
//==========================================================================================================================
U32 GameObject::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GameObject::GameObject(void)
:
_ID(_nextID),
_active(true),
_position(0.0f),
_shader(),
_texture(),
_vertices(),
_indices(),
_vao(0),
_vbo{0}
{
	++_nextID;

	glGenVertexArrays(1, &_vao);
	glGenBuffers(NUM_VBO, _vbo);
}

GameObject::GameObject(const GameObject& obj)
:
_ID(obj.GetID()),
_active(obj.GetActive()),
_position(obj.GetPosition()),
_shader(obj.GetShader()),
_texture(obj.GetTexture()),
_vertices(obj.GetVertices()),
_indices(obj.GetIndices()),
_vao(obj.GetVAO())
{
	glGenBuffers(NUM_VBO, _vbo);
}

GameObject::~GameObject(void)
{
	glDeleteBuffers(NUM_VBO, _vbo);
	glDeleteVertexArrays(1, &_vao);
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
//==========================================================================================================================
//v_Render
//==========================================================================================================================
void GameObject::v_Render(void)
{
	_shader.Use();
	BindVAO();

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//==========================================================================================================================
//v_InitVertexData
//==========================================================================================================================
void GameObject::v_InitVertexData(void)
{
	if(_vertices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::v_InitVertexData. No Vertices added to GameObject before init was called.");
	}
	else if(_indices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::v_InitVertexData. No indices added to GameObject before init was called.");
	}

	std::vector<F32> vertPosition;
	std::vector<F32> vertTexCoords;

	for(auto i : _vertices)
	{
		vertPosition.push_back(i.position[0]);
		vertPosition.push_back(i.position[1]);
		vertPosition.push_back(i.position[2]);
		vertPosition.push_back(i.position[3]);

		vertTexCoords.push_back(i.uCoord);
		vertTexCoords.push_back(i.vCoord);
	}

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPosition.size()), &vertPosition[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(U32) * _indices.size()), &_indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0 , NULL);
	glEnableVertexAttribArray(TEX_COORD_POS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(U32) * _indices.size()), &_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}