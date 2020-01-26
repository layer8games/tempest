#include <Engine/Mesh.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Mesh::Mesh(void)
	:
	_vertices(),
	_indices(),
	_uvList(),
	_vao(0),
	_vbo{0}
{  }

Mesh::Mesh(const Mesh& mesh)
	:
	_vertices(mesh.GetVertices()),
	_indices(mesh.GetIndices()),
	_uvList(mesh.GetUVList()),
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
void Mesh::v_Render(void)
{
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
}

void Mesh::InitOpenGLData(void)
{
	if(_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
	}

	glGenBuffers(NUM_VBO, _vbo);

	std::vector<F32> vertPosition;
	std::vector<F32> vertNormals;
	std::vector<F32> vertTexCoords;

	for(auto i : _vertices)
	{
		vertPosition.push_back(i.position[0]);
		vertPosition.push_back(i.position[1]);
		vertPosition.push_back(i.position[2]);
		vertPosition.push_back(i.position[3]);

		vertNormals.push_back(i.normal[0]);
		vertNormals.push_back(i.normal[1]);
		vertNormals.push_back(i.normal[2]);
		vertNormals.push_back(i.normal[3]);

		vertTexCoords.push_back(i.texCoord.u);
		vertTexCoords.push_back(i.texCoord.v);
	}

	BindVAO(true);

	//glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
	BindVBO(VERTEX_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPosition.size()), &vertPosition[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	if(vertNormals.size() > 0)
	{
		//glBindBuffer(GL_ARRAY_BUFFER, _vbo[NORMAL_BUFFER]);
		BindVBO(NORMAL_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertNormals.size()), &vertNormals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(NORMAL_POS);
	}

	if(vertTexCoords.size() > 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
		BindVBO(TEX_COORD_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(TEX_COORD_POS);
	}

	glBindVertexArray(0);
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