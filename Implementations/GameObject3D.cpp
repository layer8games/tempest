#include <Engine/GameObject3D.h>
#include <iostream>

using namespace KillerEngine;

U32 GameObject3D::_nextID = 1; 

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
GameObject3D::GameObject3D(void) 
: 
_ID(0), 
_active(true),
_model(),
_position(KM::Vector3(0.0f)),
_width(0.0f),
_height(0.0f),
_depth(0.0f),
_modelView(),
_shader(),
_vao(0),
_vbo{}
{
	SetID();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(NUM_VBO, _vbo);
}

GameObject3D::GameObject3D(const GameObject3D& obj)
: 
_ID(obj.GetID()),
_active(obj.GetActive()),
_model(obj.GetModel()),
_position(obj.GetPosition()),
_width(obj.GetWidth()),
_height(obj.GetHeight()),
_depth(obj.GetDepth()),
_modelView(obj.GetModelView()),
_shader(obj.GetShader()),
_vao(obj.GetVAO()),
_vbo{}
{  }

GameObject3D::~GameObject3D(void)
{
	glDeleteBuffers(NUM_VBO, _vbo);
	glDeleteVertexArrays(1, &_vao);
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

void GameObject3D::v_Render(void)
{
	S32 count = _model.VertexCount();

	std::cout << "I found " << count << " vertices to render\n";

	UseShader();
	BindVAO();

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void GameObject3D::InitRenderingData(void)
{
	std::vector<Vertex3D> vertices = _model.GetVertices();

	std::vector<U32> indices = _model.GetIndices();

	if(vertices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject3D::InitRenderingData -> No vertices added to model yet!");
	}
	else if(indices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject3D::InitRenderingData -> No indices added to model yet!");
	}

	std::vector<F32> vertPositions;
	std::vector<F32> vertColors;
	std::vector<F32> vertTexCoords;

	for(auto i : vertices)
	{
		vertPositions.push_back(i.position.GetX());
		vertPositions.push_back(i.position.GetY());
		vertPositions.push_back(i.position.GetZ());
		vertPositions.push_back(i.position.GetW());

		vertColors.push_back(i.color.GetRed());
		vertColors.push_back(i.color.GetGreen());
		vertColors.push_back(i.color.GetBlue());
		vertColors.push_back(i.color.GetAlpha());

		vertTexCoords.push_back(i.texCoord.GetX());
		vertTexCoords.push_back(i.texCoord.GetY());
	}

	BindVAO();

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPositions.size()), &vertPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[COLOR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertColors.size()), &vertColors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(COLOR_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(COLOR_POS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(F32) * indices.size()), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void GameObject3D::LoadShader(std::vector<ShaderData> shaderData)
{
	_shader.LoadShader(shaderData);
}

void GameObject3D::UseShader(void)
{
	_shader.Use();
}

void GameObject3D::BindVAO(void)
{
	glBindVertexArray(_vao);
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Active
//==========================================================================================================================	
bool GameObject3D::GetActive(void) const
{
	return _active;
}

void GameObject3D::SetActive(void)
{
	_active = true;
}

void GameObject3D::SetInactive(void)
{
	_active = false;
}

//==========================================================================================================================
//Position
//==========================================================================================================================
const KM::Vector3& GameObject3D::GetPosition(void) const
{
	return _position;
}

void GameObject3D::SetPosition(const KM::Vector3& pos)
{
	//_position = pos;
	//_modelView.Translate(_position);
}

void GameObject3D::SetPosition(F32 x, F32 y, F32 z)
{
	_position.SetX(x);
	_position.SetY(y);
	_position.SetZ(z);
	//_modelView.Translate(_position);
}

void GameObject3D::AddScaledPosition(const KM::Vector3& v, F32 scale)
{
	//_position.AddScaledVector(v, scale);
	//_modelView.Translate(_position);
}
//==========================================================================================================================
//Dimensions
//==========================================================================================================================
F32 GameObject3D::GetWidth(void) const
{
	return _width;
}

void GameObject3D::SetWidth(F32 w)
{
	_width = w;
}

F32 GameObject3D::GetHeight(void) const
{
	return _height;
}

void GameObject3D::SetHeight(F32 h)
{
	_height = h;
}

F32 GameObject3D::GetDepth(void) const
{
	return _depth;
}

void GameObject3D::SetDepth(F32 d)
{
	_depth = d;
}

void GameObject3D::SetDimensions(F32 w, F32 h, F32 d)
{
	_width = w;
	_height = h;
	_depth = d;
}