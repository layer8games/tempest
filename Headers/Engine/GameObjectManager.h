#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/ErrorManager.h>
#include <Engine/CollisionDetector.h>

namespace TC = TempestCollisions;

//===== STL includes =====
#include <map>

namespace Tempest
{
    typedef	std::map<U32, p_GameObject2D> ObjectRegistry2D;
    typedef	std::map<U32, p_GameObject3D> ObjectRegistry3D;
    
    class GameObjectManager
    {

    public:
        TEMPEST_API ~GameObjectManager(void);

        TEMPEST_API static shared_ptr<GameObjectManager> Instance(void);

        TEMPEST_API void Shutdown(void);

        TEMPEST_API void Add(p_GameObject2D obj);

        TEMPEST_API void Add(p_GameObject3D obj);

        TEMPEST_API void Remove2D(U32 id);

        TEMPEST_API void Remove3D(U32 id);

        TEMPEST_API p_GameObject2D GetGameObject2D(U32 id);

        TEMPEST_API p_GameObject3D GetGameObject3D(U32 id);

        TEMPEST_API U32 Count2D(void);

        TEMPEST_API U32 Count3D(void);

        TEMPEST_API void UpdateObjects(void);

        TEMPEST_API void CheckCollisions(void);

        // TODO:: Need a better way to do this. Can't get the view matrix this way any more. 
        // Maybe the Level should call GetAllObjects and render them one by one from its update
        TEMPEST_API void RenderObjects(const Camera& camera);

        TEMPEST_API ObjectRegistry2D& Get2DObjects(void);

    protected:
        TEMPEST_API GameObjectManager(void);

    private:
        static shared_ptr<GameObjectManager>	_instance;	   
        ObjectRegistry2D _registry2D;
        ObjectRegistry3D _registry3D;

    };//end Class
    typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}