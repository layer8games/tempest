#include <Boxes/Box.h>

using namespace Boxes;


//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Box::Box(void) 
: 
_speed(200.0f),
_direction(0.0f)
{ 
	_direction.Make2D();
	GameObject::MakeSprite();
	GameObject::SetPosition(0.0f, 0.0f);
	GameObject::SetScale(1.0f, 1.0f);
}

Box::Box(const KM::Point& pos, F32 width, F32 height)
:
_speed(200.0f),
_direction(0.0f)
{
	_direction.Make2D();
	GameObject::MakeSprite();
	GameObject::SetPosition(pos);
	GameObject::SetScale(width, height);
}

Box::Box(const KM::Point& pos, F32 width, F32 height, const KE::Color& col)
: 
_speed(200.0f),
_direction(0.0f)
{ 	
	_direction.Make2D();
	GameObject::MakeSprite();
	GameObject::SetPosition(pos);
	GameObject::SetScale(width, height);
	GameObject::SetColor(col);
}


Box::Box(const KM::Point& pos, F32 width, F32 height, const KE::Color& col, shared_ptr<KE::Texture> texture)
: 
_speed(200.0f),
_direction(0.0f)
{ 
	_direction.Make2D();
	GameObject::MakeSprite();
	GameObject::SetPosition(pos);
	GameObject::SetScale(width, height);
	GameObject::SetColor(col);
	GameObject::SetTexture(texture);
}

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================
//==========================================================================================================================
//Update
//==========================================================================================================================
void Box::v_Update(void) 
{
	GameObject::AddScaledPosition(_direction, KM::Timer::Instance()->DeltaTime() * _speed);
}
