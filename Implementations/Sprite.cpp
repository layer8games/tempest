#include <Engine/Sprite.h>

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
_shaderProgram(Shader::Instance()->GetSpriteShader()),
_vao(),
_vbo()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(NUM_BUFFERS, _vbo);

	F32 vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, //Top
		0.5f, -0.5f, 0.0f, 1.0f, //Right
		-0.5f, -0.5f, 0.0f, 1.0f //Left
	};

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	const F32* colors = _color.Get();

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	
}

Sprite::~Sprite(void)
{  }																	     

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
void Sprite::SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left)
{
	_textureID = tID;
	_bottomTop = KM::Vector2(bottom, top);
	_leftRight  = KM::Vector2(left, right);
}

//void Sprite::Render(const KM::Vector2& pos, F32 w, F32 h, const Color& col)
//{  }