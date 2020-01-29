#include <Engine/GameObjectManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
GameObjectManager::GameObjectManager(void)
	:
	_registry()
{  }

GameObjectManager::~GameObjectManager(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
p_GameObjectManager GameObjectManager::_instance = nullptr;

p_GameObjectManager GameObjectManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_GameObjectManager(new GameObjectManager());
	}

	return _instance;
}

void GameObjectManager::Add(p_GameObject obj)
{	
	if(_registry.count(obj->GetID()) == 0)
	{
		_registry.insert({obj->GetID(), obj});
		
		if(_registry.find(obj->GetID()) == _registry.end())
		{
			ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
		}
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetID());
	}
	
}

void GameObjectManager::Remove(U32 id)
{
	if(_registry.count(id) == 1)
	{
		_registry.erase(id);
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
	}
}

p_GameObject GameObjectManager::GetGameObject(U32 id)
{
	if(_registry.count(id) == 1)
	{
		return _registry[id];
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::GetGameObject: no object found with id= " + id);
		return nullptr;
	}
}

void GameObjectManager::UpdateObjects(void)
{
	for(auto obj : _registry)
	{
		if(obj.second->GetActiveUpdate())
		{
			obj.second->v_Update();
		}
	}
}

void GameObjectManager::RenderObjects(void)
{
	for(auto obj : _registry)
	{
		if(obj.second->GetActiveRender())
		{
			obj.second->GetShader()->SetUniform("view", GameWindow::Instance()->GetCamera()->GetViewMatrix4());
			obj.second->v_Render();
		}
	}
}