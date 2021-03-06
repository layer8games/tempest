#include "stdafx.h"
#include <Engine/CollisionDetector.h>
using namespace TempestCollisions;

shared_ptr<CollisionDetector> CollisionDetector::_instance = nullptr;
CollisionDetector::CollisionDetector(void)
{  }

CollisionDetector::~CollisionDetector(void)
{  }

shared_ptr<CollisionDetector> CollisionDetector::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = shared_ptr<CollisionDetector>(new CollisionDetector());
    }
    return _instance;
}

void CollisionDetector::CheckVsDynamic(TE::p_GameObject2D& object)
{
    //TE::ObjectRegistry2D& dynamicObjects = TE::GameObjectManager::Instance()->GetDynamicObjects();

    for(auto i : TE::GameObjectManager::Instance()->GetDynamicObjects())
    {
        if(i.second->GetName() != object->GetName())
        {
            if(object->OverlapCheck(i.second))
            {
                object->v_OnCollide(i.second->GetName());
            }
        }
    }
}

void CollisionDetector::CheckVsStatic(TE::p_GameObject2D& object)
{
    TE::ObjectRegistry2D& staticObjects = TE::GameObjectManager::Instance()->GetStaticObjects();

    for(auto i : staticObjects)
    {
        if(i.second->GetName() != object->GetName())
        {
            if(object->OverlapCheck(i.second))
            {
                object->v_OnCollide(i.second->GetName());
            }
        }
    }
}