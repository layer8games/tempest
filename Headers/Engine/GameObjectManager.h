#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/GameObject2D.h>
#include <Engine/ErrorManager.h>
#include <Engine/CollisionDetector.h>

namespace TC = TempestCollisions;

//===== STL includes =====
#include <map>

namespace Tempest
{
    typedef	std::map<U32, p_GameObject2D> ObjectRegistry2D;
    
    class GameObjectManager
    {

    public:
        TEMPEST_API ~GameObjectManager(void);

        TEMPEST_API static shared_ptr<GameObjectManager> Instance(void);

        TEMPEST_API void Shutdown(void);

        TEMPEST_API void AddDynamicObject(p_GameObject2D obj);

        TEMPEST_API void AddStaticObject(p_GameObject2D obj);

        TEMPEST_API void RemoveDynamicObject(U32 id);

        TEMPEST_API void RemoveStaticObject(U32 id);

        TEMPEST_API p_GameObject2D GetDynamicObject(U32 id);

        TEMPEST_API p_GameObject2D GetStaticObject(U32 id);

        TEMPEST_API void UpdateObjects(void);

        TEMPEST_API void CheckCollisions(void);

        TEMPEST_API void RenderObjects(const Camera* camera);

        TEMPEST_API ObjectRegistry2D& GetDynamicObjects(void);

        TEMPEST_API ObjectRegistry2D& GetStaticObjects(void);

        TEMPEST_API U32 GetDynamicObjectCount(void) const;

        TEMPEST_API U32 GetStaticObjectCount(void) const;

    protected:
        TEMPEST_API GameObjectManager(void);

    private:
        static shared_ptr<GameObjectManager> _instance;
        ObjectRegistry2D _dynamicObjects;
        ObjectRegistry2D _staticObjects;

    };//end Class
    typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}