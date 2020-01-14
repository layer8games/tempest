#include <Engine/Mesh.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Mesh::Mesh(void)
{  }

Mesh::~Mesh(void)
{
	bool clear = false;
	for(S32 i = 0; i < NUM_VBO; ++i)
	{
		if(_vbo[i] > 0)
		{
			clear = true;
		}
	}

	if(clear)
	{
		glDeleteBuffers(NUM_VBO, _vbo);
	}
	if(_vao > 0)
	{
		glDeleteVertexArrays(1, &_vao);
	}
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//if(_isSprite)
//{
//	SetUniform("sprite_color", _color);
//}

void Mesh::v_Render(void)
{
	_shader->Use(true);
	BindVAO(true);

	if(_texture != nullptr)
	{
		_texture->Bind();
		_shader->SetUniform("has_texture", true);
	}

	_shader->SetUniform("model", _gameObject->GetModelMatrix());

	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

	_shader->Use(false);
	BindVAO(false);

	if(_texture != nullptr)
	{
		_texture->UnBind();
		_shader->SetUniform("has_texture", false);
	}
}

void Mesh::BindVBO(BufferData buffer, bool state)
{
	switch(buffer)
	{
		case VERTEX_BUFFER:
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
		break;
		case FRAGMENT_BUFFER:
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[FRAGMENT_BUFFER]);
		break;
		case TEX_COORD_BUFFER:
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
		break;
		default:
		ErrorManager::Instance()->SetError(GAMEOBJECT, "GameObject::BindVBO: No such buffer");
		break;
	}
}