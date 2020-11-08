#include "stdafx.h"
#include <Engine/GameObjectManager.h>
using namespace Tempest;

p_GameObjectManager GameObjectManager::_instance = nullptr;
GameObjectManager::GameObjectManager(void)
    :
    _dynamicObjects2D(),
    _staticObjects2D()
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
    _dynamicObjects2D.clear();
    _staticObjects2D.clear();
}

void GameObjectManager::AddDynamicObject2D(p_GameObject2D obj)
{	
    if(_dynamicObjects2D.count(obj->GetName()) == 0)
    {
        _dynamicObjects2D.insert({obj->GetName(), obj});
        
        if(_dynamicObjects2D.find(obj->GetName()) == _dynamicObjects2D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject2D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetName());
    }
}

void GameObjectManager::AddDynamicObject3D(p_GameObject3D obj)
{	
    if(_dynamicObjects3D.count(obj->GetName()) == 0)
    {
        _dynamicObjects3D.insert({obj->GetName(), obj});
        
        if(_dynamicObjects3D.find(obj->GetName()) == _dynamicObjects3D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject2D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetName());
    }
}

void GameObjectManager::AddStaticObject2D(p_StaticGameObject2D obj)
{
    if(_staticObjects2D.count(obj->GetName()) == 0)
    {
        obj->UpdateInternals();
        _staticObjects2D.insert({obj->GetName(), obj});

        if(_staticObjects2D.find(obj->GetName()) == _staticObjects2D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject3D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetName());
    }
}

void GameObjectManager::AddStaticObject3D(p_StaticGameObject3D obj)
{
    if(_staticObjects3D.count(obj->GetName()) == 0)
    {
        obj->UpdateInternals();
        _staticObjects3D.insert({obj->GetName(), obj});

        if(_staticObjects3D.find(obj->GetName()) == _staticObjects3D.end())
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject3D to level.");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Add attempted to add ID that already exists. ID = " + obj->GetName());
    }
}

void GameObjectManager::RemoveDynamicObject(string id)
{
    if(_dynamicObjects2D.count(id) == 1)
    {
        _dynamicObjects2D.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

void GameObjectManager::RemoveStaticObject(string id)
{
    if(_staticObjects2D.count(id) == 1)
    {
        _staticObjects2D.erase(id);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "GameObjectManager::Remove: no object found with id= " + id);
    }
}

p_GameObject2D GameObjectManager::GetDynamicObject(string id)
{
    if(_dynamicObjects2D.count(id) == 1)
    {
        return _dynamicObjects2D[id];
    }
    else
    {
        return nullptr;
    }
}

p_GameObject2D GameObjectManager::GetStaticObject(string id)
{
    if(_staticObjects2D.count(id) == 1)
    {
        return _staticObjects2D[id];
    }
    else
    {
        return nullptr;
    }
}

void GameObjectManager::UpdateObjects(void)
{
    for(auto obj : _dynamicObjects2D)
    {
        if(obj.second->GetActiveUpdate())
        {
            obj.second->v_Update();
            obj.second->UpdateInternals();
        }
    }
    
    for(auto obj : _dynamicObjects3D)
    {
        if(obj.second->GetActiveUpdate())
        {
            obj.second->v_Update();
            obj.second->UpdateInternals();
        }
    }
}

void GameObjectManager::CheckCollisions(void)
{
    for(auto i : _dynamicObjects2D)
    {
        TC::CollisionDetector::Instance()->CheckVsDynamic(i.second);
        TC::CollisionDetector::Instance()->CheckVsStatic(i.second);
    }
}

void GameObjectManager::RenderObjects(void)
{
    for(auto obj : _dynamicObjects2D)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->GetShader()->SetUniform("projection", CameraController::Instance()->GetProjectionMatrix());
            obj.second->GetShader()->SetUniform("view", CameraController::Instance()->GetViewMatrix());
            obj.second->v_Render();
        }
    }

    for(auto obj : _staticObjects2D)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->GetShader()->SetUniform("projection", CameraController::Instance()->GetProjectionMatrix());
            obj.second->GetShader()->SetUniform("view", CameraController::Instance()->GetViewMatrix());
            obj.second->v_Render();
        }
    }

    for(auto obj : _dynamicObjects3D)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->GetShader()->SetUniform("projection", CameraController::Instance()->GetProjectionMatrix());
            obj.second->GetShader()->SetUniform("view", CameraController::Instance()->GetViewMatrix());
            obj.second->v_Render();
        }
    }

    for(auto obj : _staticObjects3D)
    {
        if(obj.second->GetActiveRender())
        {
            obj.second->UpdateInternals();
            obj.second->v_Render();
        }
    }
}

ObjectRegistry2D& GameObjectManager::GetDynamicObjects(void)
{
    return _dynamicObjects2D;
}

ObjectRegistry2D& GameObjectManager::GetStaticObjects(void)
{
    return _staticObjects2D;
}

U32 GameObjectManager::GetDynamicObjectCount(void) const
{
    return _dynamicObjects2D.size();
}

U32 GameObjectManager::GetStaticObjectCount(void) const
{
    return _staticObjects2D.size();
}