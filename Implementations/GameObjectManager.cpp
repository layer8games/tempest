#include "stdafx.h"
#include <Engine/GameObjectManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
GameObjectManager::GameObjectManager(void)
    :
    _registry2D(),
    _registry3D()
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

void GameObjectManager::Add(p_GameObject2D obj)
{	
    if(_registry2D.count(obj->GetID()) == 0)
    {
        _registry2D.insert({obj->GetID(), obj});
        
        if(_registry2D.find(obj->GetID()) == _registry2D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject2D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetID());
    }
}

void GameObjectManager::Add(p_GameObject3D obj)
{
    if(_registry3D.count(obj->GetID()) == 0)
    {
        _registry3D.insert({obj->GetID(), obj});

        if(_registry3D.find(obj->GetID()) == _registry3D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject3D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetID());
    }
}

void GameObjectManager::Remove2D(U32 id)
{
    if(_registry2D.count(id) == 1)
    {
        _registry2D.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

void GameObjectManager::Remove3D(U32 id)
{
    if(_registry3D.count(id) == 1)
    {
        _registry3D.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

p_GameObject2D GameObjectManager::GetGameObject2D(U32 id)
{
    if(_registry2D.count(id) == 1)
    {
        return _registry2D[id];
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::GetGameObject: no object found with id= " + id);
        return nullptr;
    }
}

p_GameObject3D GameObjectManager::GetGameObject3D(U32 id)
{
    if(_registry3D.count(id) == 1)
    {
        return _registry3D[id];
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::GetGameObject: no object found with id= " + id);
        return nullptr;
    }
}

void GameObjectManager::UpdateObjects(void)
{
    for(auto obj : _registry2D)
    {
        if(obj.second->GetActiveUpdate())
        {
            obj.second->v_Update();
        }
    }

    for(auto obj : _registry3D)
    {
        if(obj.second->GetActiveUpdate())
        {
            obj.second->v_Update();
        }
    }
}

// TODO:: Need a better way to get the view matrix
//void GameObjectManager::RenderObjects(void)
//{
//    for(auto obj : _registry2D)
//    {
//        if(obj.second->GetActiveRender())
//        {
//            obj.second->GetShader()->SetUniform("view", Engine::Instance()->GetCamera()->GetViewMatrix4());
//            obj.second->v_Render();
//        }
//    }
//
//    for(auto obj : _registry3D)
//    {
//        if(obj.second->GetActiveRender())
//        {
//            obj.second->GetShader()->SetUniform("view", Engine::Instance()->GetCamera()->GetViewMatrix4());
//            obj.second->v_Render();
//        }
//    }
//}