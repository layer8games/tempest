#include <Engine/GameObject.h>
#include <iostream>

using namespace Tempest;

//==========================================================================================================================
//
//Static Member
//
//==========================================================================================================================
U32 GameObject::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GameObject::GameObject(void)
:
_modelTOWorldCache(),
_position(0.0f),
_scale(1.0f),
_orientation(0.0f),
_color(1.0f),
_boundingBox(),
_activeUpdate(true),
_activeRender(true),
_ID(_nextID)
{
	++_nextID;	
}

GameObject::GameObject(const GameObject& obj)
:
_modelTOWorldCache(obj.GetModelMatrix()),
_position(obj.GetPosition()),
_scale(obj.GetScale()),
_orientation(obj.GetOrientation()),
_color(obj.GetColor()),
_activeUpdate(obj.GetActiveUpdate()),
_activeRender(obj.GetActiveRender()),
_ID(obj.GetID())
{  }

GameObject::~GameObject(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
//==========================================================================================================================
//v_Render
//==========================================================================================================================
void GameObject::v_Render(void)
{
	DefaultRender();
}

void GameObject::DefaultRender(void)
{
	_mesh->v_Render(_modelTOWorldCache);
}

//==========================================================================================================================
//
//Functions
//==========================================================================================================================
void GameObject::UpdateInternals(void)
{
	_CalculateCachedData();
}

//==========================================================================================================================
//Protected
//==========================================================================================================================
void GameObject::DefaultAwake(void)
{
	UpdateInternals();
}

//==========================================================================================================================
//Private
//==========================================================================================================================
void GameObject::_CalculateCachedData(void)
{
	//_modelTOWorldCache =  TM::Matrix4::Translate(_position) * TM::Matrix4::Scale(_scale);

	_modelTOWorldCache.SetOrientationAndPosition(_orientation, _position);
	_modelTOWorldCache = _modelTOWorldCache * TM::Matrix4::Scale(_scale);
}