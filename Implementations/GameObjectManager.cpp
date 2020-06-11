#include "stdafx.h"
#include <Engine/GameObjectManager.h>
#include <iostream>
using namespace Tempest;

p_GameObjectManager GameObjectManager::_instance = nullptr;
GameObjectManager::GameObjectManager(void)
    :
    _dynamicObjects(),
    _staticObjects()
{  }

GameObjectManager::~GameObjectManager(void)
{  }

p_GameObjectManager GameObjectManager::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = p_GameObjectManager(new GameObjectManager());
    }

    return _instance;
}

void GameObjectManager::Shutdown(void)
{
    _dynamicObjects.clear();
    _staticObjects.clear();
}

void GameObjectManager::AddDynamicObject(p_GameObject2D obj)
{	
    if(_dynamicObjects.count(obj->GetID()) == 0)
    {
        _dynamicObjects.insert({obj->GetID(), obj});
        
        if(_dynamicObjects.find(obj->GetID()) == _dynamicObjects.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject2D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetID());
    }
}

void GameObjectManager::AddStaticObject(p_GameObject2D obj)
{
    if(_staticObjects.count(obj->GetID()) == 0)
    {
        obj->UpdateInternals();
        _staticObjects.insert({obj->GetID(), obj});

        if(_staticObjects.find(obj->GetID()) == _staticObjects.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject3D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetID());
    }
}

void GameObjectManager::RemoveDynamicObject(U32 id)
{
    if(_dynamicObjects.count(id) == 1)
    {
        _dynamicObjects.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

void GameObjectManager::RemoveStaticObject(U32 id)
{
    if(_staticObjects.count(id) == 1)
    {
        _staticObjects.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

p_GameObject2D GameObjectManager::GetDynamicObject(U32 id)
{
    if(_dynamicObjects.count(id) == 1)
    {
        return _dynamicObjects[id];
    }
    else
    {
        return nullptr;
    }
}

p_GameObject2D GameObjectManager::GetStaticObject(U32 id)
{
    if(_staticObjects.count(id) == 1)
    {
        return _staticObjects[id];
    }
    else
    {
        return nullptr;
    }
}

void GameObjectManager::UpdateObjects(void)
{
    for(auto obj : _dynamicObjects)
    {
        if(obj.second->GetActiveUpdate())
        {
            obj.second->UpdateInternals();
            obj.second->v_Update();
        }
    }
}

void GameObjectManager::CheckCollisions(void)
{
    for(auto i : _dynamicObjects)
    {
        TC::CollisionDetector::Instance()->CheckVsDynamic(i.second);
        TC::CollisionDetector::Instance()->CheckVsStatic(i.second);
    }
}

// TODO:: Need a better way to get the view matrix
void GameObjectManager::RenderObjects(const Camera& camera)
{
    for(auto obj : _dynamicObjects)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->GetShader()->SetUniform("projection", camera.GetProjectionMatrix4());
            obj.second->GetShader()->SetUniform("view", camera.GetViewMatrix4());
            obj.second->v_Render();
        }
    }

    for(auto obj : _staticObjects)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->GetShader()->SetUniform("projection", camera.GetProjectionMatrix4());
            obj.second->GetShader()->SetUniform("view", camera.GetViewMatrix4());
            obj.second->v_Render();
        }
    }
}

ObjectRegistry2D& GameObjectManager::GetDynamicObjects(void)
{
    return _dynamicObjects;
}

ObjectRegistry2D& GameObjectManager::GetStaticObjects(void)
{
    return _staticObjects;
}

U32 GameObjectManager::GetDynamicObjectCount(void) const
{
    return _dynamicObjects.size();
}

U32 GameObjectManager::GetStaticObjectCount(void) const
{
    return _staticObjects.size();
}