#include <Engine/ModelRenderer.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ModelRenderer::ModelRenderer(void)
:
_maxBatchSize(1000),
_currentBatchSize(0),
_vertices()
{
	glGenVertexArrays(_NUM_VOA, _VOA);
	glBindVertexArray(_VOA[0]);
}

ModelRenderer::~ModelRenderer(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
shared_ptr<ModelRenderer> ModelRenderer::_instance = nullptr;

shared_ptr<ModelRenderer> ModelRenderer::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = shared_ptr<ModelRenderer>(new ModelRenderer());
	}

	return _instance;
}

void ModelRenderer::SetShader(GLuint shader)
{
	_shader = shader;

	glUseProgram(_shader);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//Camera::Instance()->SetOrthographic();
	Camera::Instance()->SetPerspective();
	//Camera::Instance()->SetDefaultMatrix();
	Camera::Instance()->SetUp(_shader);
}

void ModelRenderer::AddToBatch(const Model& m)
{

}

void ModelRenderer::Draw(void)
{

}

void ModelRenderer::DrawNow(const Model& m, const KM::Matrix& modelView)
{
	std::vector<Vertex3D> vertices = m.GetVertices();
	std::vector<F32> vertexPositions;
	std::vector<F32> vertexColors;
	std::vector<U32>  indices = m.GetIndices();

	int vertextCount = 0;

	for(auto i : vertices)
	{
		vertexPositions.push_back(i.position.GetX());
		vertexPositions.push_back(i.position.GetY());
		vertexPositions.push_back(i.position.GetZ());
		vertexPositions.push_back(i.position.GetW());

		vertexColors.push_back(i.color.GetRed());
		vertexColors.push_back(i.color.GetGreen());
		vertexColors.push_back(i.color.GetBlue());
		vertexColors.push_back(i.color.GetAlpha());

		++vertextCount;
	}

	glBindVertexArray(_VOA[0]);

	GLuint buffers[3];
	glGenBuffers(3, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertexPositions.size()), &vertexPositions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertexColors.size()), &vertexColors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]),
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U16) * indices.size(), &indices[0], GL_STATIC_DRAW);

	GLint transform1 = glGetUniformLocation(_shader, "modelView_mat");
	//glUniformMatrix4fv(transform1, 1, GL_FALSE, modelView.GetElems());

	GLint viewportLoc = glGetUniformLocation(_shader, "viewport_mat");
	//glUniformMatrix4fv(viewportLoc, 1, GL_FALSE, Camera::Instance()->GetViewMatrix().GetElems());

	glDrawElements(GL_TRIANGLES, m.VertexCount(), GL_UNSIGNED_SHORT, 0);

}