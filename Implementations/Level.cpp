#include <Engine/Level.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Level::Level(void) 
: 
_width(0),
_height(0),
_topBorder(0),
_bottomBorder(0),
_rightBorder(0),
_leftBorder(0),
_depth(0),
_nearBorder(0),
_farBorder(0),
_bgColor(),
_ID(0),
_camera(new Camera()),
_gameObjects(),
_RigidBody2Ds(),
_forceRegistry()
{
	_camera->SetOrthographic();
}

Level::~Level(void)
{
	_camera = nullptr;
	_gameObjects.clear();
	_RigidBody2Ds.clear();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Level::v_Integrate(void)
{
	_forceRegistry.UpdateForces();

	for(auto i : _RigidBody2Ds)
	{
		if(i.second->GetActive())
		{
			i.second->Integrate();
		}
	}
}

void Level::v_Render(void)
{ 
	RenderObjects(); 
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

void Level::UpdateLevel(void)
{
	_camera->v_Update();
}

void Level::AddObjectToLevel(const GameObject& obj)
{
	_gameObjects.insert({ obj.GetID(), shared_ptr<GameObject>(const_cast<GameObject*>(&obj)) });
	_gameObjects[obj.GetID()]->SetUniform("projection", _camera->GetProjectionMatrix4());

	if(_gameObjects.find(obj.GetID()) == _gameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddObjectToLevel(shared_ptr<GameObject> obj)
{
	obj->SetUniform("projection", _camera->GetProjectionMatrix4());

	_gameObjects.insert({obj->GetID(), obj});

	if(_gameObjects.find(obj->GetID()) == _gameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}


void Level::AddRigidBody2DToLevel(const KP::RigidBody2D& RigidBody2D)
{
	_RigidBody2Ds.insert({ RigidBody2D.GetID(), shared_ptr<KP::RigidBody2D>(const_cast<KP::RigidBody2D*>(&RigidBody2D)) });
	_RigidBody2Ds[RigidBody2D.GetID()]->SetUniform("projection", _camera->GetProjectionMatrix4());

	if(_RigidBody2Ds.find(RigidBody2D.GetID()) == _RigidBody2Ds.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddRigidBody2DToLevel Unable to add RigidBody2D to level.");
	}
}

void Level::AddRigidBody2DToLevel(shared_ptr<KP::RigidBody2D> RigidBody2D)
{
	RigidBody2D->SetUniform("projection", _camera->GetProjectionMatrix4());

	_RigidBody2Ds.insert({RigidBody2D->GetID(), RigidBody2D});

	if(_RigidBody2Ds.find(RigidBody2D->GetID()) == _RigidBody2Ds.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddRigidBody2DToLevel Unable to add RigidBody2D to level.");	
	}
}

void Level::AddRigidBody2DToLevel(shared_ptr<KP::RigidBody2D> RigidBody2D, shared_ptr<KP::ForceGenerator> generator)
{
	RigidBody2D->SetUniform("projection", _camera->GetProjectionMatrix4());

	_RigidBody2Ds.insert({RigidBody2D->GetID(), RigidBody2D});

	if(_RigidBody2Ds.find(RigidBody2D->GetID()) == _RigidBody2Ds.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Unable to Add RigidBody2D to Level. Level.h line 80");
	}

	if(generator != nullptr)
	{
		_forceRegistry.Add(RigidBody2D, generator);
	}
}

void Level::AddTextToLevel(const Text& text)
{
	//text->SetUniforms("projection", _camera->GetProjectionMatrix4());

	//_textList.push_back(text);
	std::vector<shared_ptr<Glyph>> v = text.GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

void Level::AddTextToLevel(shared_ptr<Text> text)
{
	std::vector<shared_ptr<Glyph>> v = text->GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

//=============================================================================
//
//RemoveObjectFromLevel
//
//=============================================================================
void Level::RemoveObjectFromLevel(U32 id)
{
	//Assume that if an ID is not a GameObject, then it could be derived type.
	if(_gameObjects.find(id) != _gameObjects.end())
	{
		_gameObjects.erase(id);
	}
	else if(_RigidBody2Ds.find(id) != _RigidBody2Ds.end())
	{
		_RigidBody2Ds.erase(id);
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::RemoveObjectFromLevel, ln 163, no object found with id " + id);
	}
}

//==========================================================================================================================
//
//Update and Render all objects
//
//==========================================================================================================================	
void Level::UpdateObjects(void)
{
	for(auto i : _gameObjects)
	{
		if(i.second->GetActiveUpdate())
		{
			i.second->UpdateInternals();
			i.second->v_Update();
		}
	}

	for(auto i : _RigidBody2Ds)
	{
		if(i.second->GetActiveUpdate())
		{
			i.second->UpdateInternals();
			i.second->v_Update();
		}
	}
}

void Level::RenderObjects(void)
{
//==========================================================================================================================
//Render Sprites
//==========================================================================================================================	
	for(auto i : _gameObjects)
	{
		if(i.second->GetActiveRender())
		{
			i.second->SetUniform("view", _camera->GetViewMatrix4());
			i.second->v_Render();
		}
	}

	for(auto i : _RigidBody2Ds)
	{
		if(i.second->GetActiveRender())
		{
			i.second->SetUniform("view", _camera->GetViewMatrix4());
			i.second->v_Render();
		}
	}	
}

//==========================================================================================================================
//GetObjects
//==========================================================================================================================

shared_ptr<GameObject> Level::GetGameObject(U32 id)
{
	shared_ptr<GameObject> obj = _gameObjects[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}

shared_ptr<KP::RigidBody2D> Level::GetRigidBody2D(U32 id)
{
	shared_ptr<KP::RigidBody2D> obj = _RigidBody2Ds[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}