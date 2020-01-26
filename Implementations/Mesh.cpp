#include <Engine/Mesh.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Mesh::Mesh(void)
	:
	_vao(0),
	_vbo{0}
{  }

Mesh::Mesh(const Mesh& mesh)
	:
	_vao(mesh.GetVAO()),
	_vbo{0}
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
void Mesh::v_Render(U32 count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Mesh::InitOpenGLData(void)
{
	if(_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
	}

	glGenBuffers(NUM_VBO, _vbo);
}

void Mesh::BindVBO(BufferData buffer)
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
		case NORMAL_BUFFER:
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[NORMAL_BUFFER]);
			break;
		default:
			ErrorManager::Instance()->SetError(GAMEOBJECT, "Mesh::BindVBO: No such buffer");
			break;
	}
}