#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Driver.h>
#include <Engine/GameObject2D.h>
#include <Engine/StaticGameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/StaticGameObject3D.h>
#include <Engine/ErrorManager.h>
#include <Engine/CollisionDetector.h>
#include <Engine/CameraController.h>

namespace TC = TempestCollisions;

//===== STL includes =====
#include <map>

namespace Tempest
{
    typedef	std::map<string, p_GameObject2D> ObjectRegistry2D;
    typedef	std::map<string, p_GameObject3D> ObjectRegistry3D;
    
    class GameObjectManager
    {

    public:
        TEMPEST_API ~GameObjectManager(void);

        TEMPEST_API static shared_ptr<GameObjectManager> Instance(void);

        TEMPEST_API void Shutdown(void);

        TEMPEST_API void AddDynamicObject2D(p_GameObject2D obj);

        TEMPEST_API void AddDynamicObject3D(p_GameObject3D obj);

        TEMPEST_API void AddStaticObject2D(p_StaticGameObject2D obj);

        TEMPEST_API void AddStaticObject3D(p_StaticGameObject3D obj);

        TEMPEST_API void RemoveDynamicObject(string id);

        TEMPEST_API void RemoveStaticObject(string id);

        TEMPEST_API p_GameObject2D GetDynamicObject(string id);

        TEMPEST_API p_GameObject2D GetStaticObject(string id);

        TEMPEST_API void UpdateObjects(void);

        TEMPEST_API void CheckCollisions(void);

        TEMPEST_API void RenderObjects(void);

        TEMPEST_API ObjectRegistry2D& GetDynamicObjects(void);

        TEMPEST_API ObjectRegistry2D& GetStaticObjects(void);

        TEMPEST_API U32 GetDynamicObjectCount(void) const;

        TEMPEST_API U32 GetStaticObjectCount(void) const;

        template <class T>
        inline void SetDyanmicGameObject2DUniforms(string name, const T& type)
        {
            for(auto i : _dynamicObjects2D)
            {
                i.second->GetShader()->SetUniform(name, type);
            }
        }

        template <class T>
        inline void SetStaticGameObject2DUniforms(string name, const T& type)
        {
            for(auto i : _staticObjects2D)
            {
                i.second->GetShader()->SetUniform(name, type);
            }
        }

        template <class T>
        inline void SetDyanmicGameObject3DUniforms(string name, const T& type)
        {
            for(auto i : _dynamicObjects3D)
            {
                i.second->GetShader()->SetUniform(name, type);
            }
        }

        template <class T>
        inline void SetStaticGameObject3DUniforms(string name, const T& type)
        {
            for(auto i : _staticObjects3D)
            {
                i.second->GetShader()->SetUniform(name, type);
            }
        }

    protected:
        TEMPEST_API GameObjectManager(void);

    private:
        static shared_ptr<GameObjectManager> _instance;
        ObjectRegistry2D _dynamicObjects2D;
        ObjectRegistry2D _staticObjects2D;
        ObjectRegistry3D _dynamicObjects3D;
        ObjectRegistry3D _staticObjects3D;

    };//end Class
    typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}