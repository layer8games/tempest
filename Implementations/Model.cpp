#include <Engine/Model.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Model::Model(void) 
: 
_numVertices(0), 
_vertices(),
_shaderProgram(Shader::Instance()->GetModelShader()),
_scale(1.0f, 1.0f, 1.0f)
{  }

Model::Model(const Model& m)
:
_numVertices(m.VertexCount()),
_vertices(m.GetVertices()),
_scale(m.GetScale()),
_shaderProgram(m.GetShader())
{  }

Model::Model(std::vector<Vertex3D> vertices) 
: 
_numVertices(0), 
_vertices(vertices), 
_shaderProgram(Shader::Instance()->GetModelShader())
{  }

Model::~Model(void)
{  }

//==========================================================================================================================
//
//Model Functions
//
//==========================================================================================================================
void Model::AddVertex(const Vertex3D& vert)
{
	_vertices.push_back(vert);
	++_numVertices;
}

void Model::AddVertex(const KM::Vector3& pos, const Color& color)
{
	Vertex3D vert;
	vert.position = pos; 
	vert.color = color;

	_vertices.push_back(vert);
	++_numVertices;
}

/*
void Model::Render(const KM::Vector3& pos)
{	
	if(_shaderProgram == 0)
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Model: NO shader initialized when render was attempted");
		return;
	}

	glUseProgram(_shaderProgram);

	glBindVertexArray(_vertexArrayObject[0]);

	Camera::Instance()->SetPerspective();
	Camera::Instance()->SetUp(_shaderProgram);

	KM::Matrix M { 0.0f };

	M.Translate(pos);

	GLint shaderPosition = glGetUniformLocation(_shaderProgram, "position_mat");

	glUniformMatrix4fv(shaderPosition, 1, GL_FALSE, M.GetElems());

	GLuint buffersLocal[2];
	glGenBuffers(2, buffersLocal);

	glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _vertices.size()), &_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER ,buffersLocal[1]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _colors.size()), &_colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_DEPTH_BUFFER_BIT);
	
	glDrawArrays(GL_TRIANGLES, 0, _numVertices);

	glDisable(GL_DEPTH_TEST);	
}
*/