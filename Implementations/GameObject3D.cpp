#include <Engine/GameObject3D.h>

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
_modelView(1.0f)
{
	SetID();
}

GameObject3D::GameObject3D(const GameObject3D& obj)
: 
_ID(obj.GetID()),
_active(obj.GetActive()),
_model(obj.GetModel()),
_position(obj.GetPosition()),
_width(obj.GetWidth()),
_height(obj.GetHeight()),
_modelView(obj.GetModelView())
{  }

GameObject3D::~GameObject3D(void)
{  }

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
	_position = pos;
	_modelView.Translate(_position);
}

void GameObject3D::SetPosition(F32 x, F32 y, F32 z)
{
	_position = KM::Vector3(x, y, z);
	_modelView.Translate(_position);
}

void GameObject3D::AddScaledPosition(const KM::Vector3& v, F32 scale)
{
	_position.AddScaledVector(v, scale);
	_modelView.Translate(_position);
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

void GameObject3D::SetDimensions(F32 w, F32 h)
{
	_width = w;
	_height = h;
}