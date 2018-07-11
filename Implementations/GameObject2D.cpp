#include <Engine/GameObject2D.h>
#include <iostream>

using namespace KillerEngine;

U32 GameObject2D::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GameObject2D::GameObject2D(void) 
: 
_ID(0), 
_active(true), 
_sprite(), 
_position(0), 
_width(0.0f), 
_height(0.0f),
_shaderProgram(0),
_vao(0),
_vbo{},
_vertexCount(0),
_color()
{
	SetID();

	F32 vertices[] = 
	{
		0.0f, 0.5f, 0.0f, 1.0f, //Top
		0.5f, -0.5f, 0.0f, 1.0f, //Right
		-0.5f, -0.5f, 0.0f, 1.0f //Left
	};

	_vertexCount = 3;
	
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

	_InitColor();
}

GameObject2D::GameObject2D(const GameObject2D& obj) 
: 
_ID(obj.GetID()),
_active(obj.GetActive()),
_sprite(obj.GetSprite()),
_position(obj.GetPosition()),
_width(obj.GetWidth()),
_height(obj.GetHeight())
{  }

GameObject2D::~GameObject2D(void)
{
	glDeleteBuffers(NUM_VBO, _vbo);
	glDeleteProgram(_shaderProgram);
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void GameObject2D::v_Render(void)
{
	//glUseProgram(_sprite.GetShader());
	glUseProgram(_shaderProgram);

	if(_sprite.GetTextureID() != 0)
	{
		TextureManager::Instance()->SetCurrentTextureID(_sprite.GetTextureID());
	}

	//glBindVertexArray(_sprite.GetVAO());
	glBindVertexArray(_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== Dimensions =====	
F32 GameObject2D::GetWidth(void) const
{
	return _width;
}

void GameObject2D::SetWidth(F32 w)
{
	_width = w;
}

F32 GameObject2D::GetHeight(void) const
{
	return _height;
}

void GameObject2D::SetHeight(F32 h)
{
	_height = h; 
}

void GameObject2D::SetDimensions(F32 w, F32 h)
{
	_width = w; 
	_height = h; 
}

//===== Color =====
void GameObject2D::SetColor(const Color& col)
{
	_color = col;
	_InitColor();
}

void GameObject2D::SetColor(F32 red, F32 green, F32 blue, F32 alpha)
{
	_color.SetRed(red);
	_color.SetGreen(green);
	_color.SetBlue(blue);
	_color.SetAlpha(alpha);
	_InitColor();
}

//===== Texture =====
U32 GameObject2D::GetTextureID(void) const
{
	return _sprite.GetTextureID();
}

void GameObject2D::SetTexture(U32 id, const F32 top, const F32 bottom, const F32 right, const F32 left)
{
	_sprite.SetTexture(id, top, bottom, right, left);
}

void GameObject2D::SetTexture(U32 id)
{
	_sprite.SetTexture(id, 0.0f, 1.0f, 0.0f, 1.0f);
}

bool GameObject2D::GetActive(void) const
{ 
	return _active; 
}

void GameObject2D::SetActive(void)   
{ 
	_active = true; 
}

void GameObject2D::SetInactive(void) 
{ 
	_active = false; 
}

//===== Position =====
const KM::Vector2& GameObject2D::GetPosition(void) const
{ 
	return _position; 
}

void GameObject2D::SetPosition(const KM::Vector2& pos) 
{ 
	_position = pos;
}

void GameObject2D::SetPosition(F32 x, F32 y) 
{ 
	_position.SetX(x);
	_position.SetY(y);
}

void GameObject2D::AddScaledPosition(const KM::Vector2& v, F32 scale)
{				
	_position.AddScaledVector(v, scale);
}

void GameObject2D::_InitColor(void)
{
	std::vector<F32> colors;
	
	for(int i = 0; i < _vertexCount; ++i)
	{
		colors.push_back(_color.GetRed());
		colors.push_back(_color.GetGreen());
		colors.push_back(_color.GetBlue());
		colors.push_back(_color.GetAlpha());
	}

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[FRAGMENT_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * colors.size()), &colors[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(FRAGMENT_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(FRAGMENT_POS);
}