#include <Engine/GameObject2D.h>

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
_color()
{
	SetID();
}

GameObject2D::GameObject2D(const GameObject2D& obj) 
: 
_ID(obj.GetID()),
_active(obj.GetActive()),
_sprite(obj.GetSprite()),
_position(obj.GetPosition()),
_width(obj.GetWidth()),
_height(obj.GetHeight()),
_color(obj.GetColor())
{  }

GameObject2D::~GameObject2D(void)
{  }

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
const Color& GameObject2D::GetColor(void) const
{
	return _color;
}

void GameObject2D::SetColor(const Color& col)
{
	_color = col;
}

void GameObject2D::SetColor(F32 red, F32 green, F32 blue)
{
	_color.SetRed(red);
	_color.SetGreen(green);
	_color.SetBlue(blue);
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
