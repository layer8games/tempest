#include <Engine/Sprite.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//Static members
//==========================================================================================================================
	//GLuint Sprite::_shaderProgram = NULL;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Sprite::Sprite(void) 
:  
_bottomTop(0),
_leftRight(0),
_textureID(0),
_color(),
_shaderProgram(0),
_vao(),
_vertexCount(0)
{
	std::cout << "Sprite Default constructor called\n";

	Shader::Instance();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	GLuint vbo = 0;

	glGenBuffers(1, &vbo);

	F32 vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, //Top
		0.5f, -0.5f, 0.0f, 1.0f, //Right
		-0.5f, -0.5f, 0.0f, 1.0f //Left
	};

	_vertexCount = 3;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glDeleteBuffers(1, &vbo);
}

Sprite::~Sprite(void)
{
	glDeleteVertexArrays(1, &_vao);
}																	     

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void Sprite::SetCharData(CharacterData data)
{
	_characterData = data;
}

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
Sprite& Sprite::operator=(const Sprite& S)
{
	_bottomTop = S.GetUVBottomTop();
	_leftRight = S. GetUVLeftRight();
	_textureID = S.GetTextureID();
	_characterData = S.GetCharData();
	_shaderProgram = S.GetShader();

	return *this;
}

Sprite& Sprite::operator=(const Sprite* S)
{
	_bottomTop = S->GetUVBottomTop();
	_leftRight = S-> GetUVLeftRight();
	_textureID = S->GetTextureID();
	_characterData = S->GetCharData();
	_shaderProgram = S->GetShader();

	return *this;
}

Sprite& Sprite::operator=(shared_ptr<Sprite> S)
{
	_bottomTop = S->GetUVBottomTop();
	_leftRight = S-> GetUVLeftRight();
	_textureID = S->GetTextureID();
	_characterData = S->GetCharData();
	_shaderProgram = S->GetShader();

	return *this;	
}

//==========================================================================================================================
//
//Sprite Fucntions
//
//==========================================================================================================================
void Sprite::SetColor(const Color& col)
{
	std::cout << "sprite set color calle\n";

	_color = col;

	const F32* colorData = _color.Get();

	GLuint vbo = 0;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glDeleteBuffers(1, &vbo);
}

void Sprite::SetColor(F32 red, F32 green, F32 blue, F32 alpha)
{
	std::cout << "sprite set color calle\n";

	_color.SetRed(red);
	_color.SetGreen(green);
	_color.SetBlue(blue);
	_color.SetAlpha(alpha);

	const F32* colorData = _color.Get();

	GLuint vbo = 0;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glDeleteBuffers(1, &vbo);
}

void Sprite::SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left)
{
	_textureID = tID;
	_bottomTop = KM::Vector2(bottom, top);
	_leftRight  = KM::Vector2(left, right);
}

//void Sprite::Render(const KM::Vector2& pos, F32 w, F32 h, const Color& col)
//{  }