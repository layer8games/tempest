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
_shaderProgram(Shader::Instance()->GetSpriteShader())
{  }

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

void Sprite::Render(const KM::Vector2& pos, F32 w, F32 h, const Color& col)
{  }