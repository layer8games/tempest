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

GameObject2D::GameObject2D(GameObject2D& obj) 
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
const F32 GameObject2D::GetWidth(void)
{
	return _width;
}

void GameObject2D::SetWidth(F32 w)
{
	_width = w;
}

const F32 GameObject2D::GetHeight(void)
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
const Color& GameObject2D::GetColor(void)
{
	return _color;
}

void GameObject2D::SetColor(Color& col)
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
const U32 GameObject2D::GetTextureID(void)
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

const bool GameObject2D::GetActive(void) 
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
KM::Vector2& GameObject2D::GetPosition(void) 
{ 
	return _position; 
}

void GameObject2D::SetPosition(KM::Vector2& pos) 
{ 
	_position = pos;
}

void GameObject2D::SetPosition(F32 x, F32 y) 
{ 
	_position = KM::Vector2(x, y);
}

void GameObject2D::AddScaledPosition(const KM::Vector2& v, F32 scale)
{				
	_position.AddScaledVector(v, scale);
}
/*
//=====Velocity=====
KM::Vector2& GameObject2D::GetVelocity(void) 
{ 
	return _velocity; 
}

void GameObject2D::SetVelocity(KM::Vector2& v) 
{ 
	_velocity = v; 
}

void GameObject2D::ScaleVelocity(const KM::Vector2& vec, F32 scale)
{
	_velocity.AddScaledVector(vec, scale);
}

void GameObject2D::SetVelocity(F32 x, F32 y) 
{ 
	_velocity = KM::Vector2(x, y); 
}

//=====Acceleration=====
KM::Vector2& GameObject2D::GetAcceleration(void) 
{ 
	return _acceleration; 
}

void GameObject2D::SetAcceleration(KM::Vector2& a) 
{ 
	_acceleration = a; 
}

void GameObject2D::ScaleAcceleration(const KM::Vector2& vec, F32 scale)
{
	_acceleration.AddScaledVector(vec, scale);
}

void GameObject2D::SetAcceleration(F32 x, F32 y) 
{
 	_acceleration = KM::Vector2(x, y); 
}
*/
