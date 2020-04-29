#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/ErrorManager.h>

//===== STL includes =====
#include <map>

namespace Tempest
{
    /// A general manager class for all GameObject that are created. In the past, there have been a lot of issues with the way that
    /// GameObjects are stored. In the past, this was done in the Level, but this creates issues with persistence and ownership. 
    /// The purpose of this manager is to simplify this by registering all GameObjects in the GameObjectManager, using their ID 
    /// as their lookup key. The Level will then store just the ID of the GameObjects that it cares about, or that it registered, 
    /// and will look these up for rendering and updating. Only persisten, multilevel objects should be registered in this way. 
    class GameObjectManager
    {
        typedef	std::map<U32, p_GameObject2D> ObjectRegistry2D;
        typedef	std::map<U32, p_GameObject3D> ObjectRegistry3D;

    public:
    //==========================================================================================================================
    //
    //Constructors	 	
    //
    //==========================================================================================================================
        /// No implementation. 
        TEMPEST_API ~GameObjectManager(void);

    //==========================================================================================================================
    //
    //Functions
    //
    //==========================================================================================================================
        /// Singleton pattern used for Global nature of the Manager.
        TEMPEST_API static shared_ptr<GameObjectManager> Instance(void);

        /// Add a GameObject2D to the Manager. 
        /// \param obj calls GameObject2D::GetID, then attempts to insert GameObject2D into the map. 
        TEMPEST_API void Add(p_GameObject2D obj);

         /// Add a GameObject3D to the Manager. 
        /// \param obj calls GameObject2D::GetID, then attempts to insert GameObject2D into the map. 
        TEMPEST_API void Add(p_GameObject3D obj);

        /// Remove the GameObject2D with \param id from the Manager, if it exists. 
        TEMPEST_API void Remove2D(U32 id);

        /// Remove the GameObject3D with \param id from the Manager, if it exists. 
        TEMPEST_API void Remove3D(U32 id);

        /// Return pointer to GameObject2D with \param id if it exists.
        TEMPEST_API p_GameObject2D GetGameObject2D(U32 id);

        /// Return pointer to GameObject3D with \param id if it exists.
        TEMPEST_API p_GameObject3D GetGameObject3D(U32 id);

        /// Return a count of all the GameObjects2D that have been registered with the manager.
        inline U32 Count2D(void)
        {
            return _registry2D.size();
        }

        /// Return a count of all the GameObjects3D that have been registered with the manager.
        inline U32 Count3D(void)
        {
            return _registry3D.size();
        }

        /// Loop over all registered GameObjects2D calling GameObject::v_Update.
        TEMPEST_API void UpdateObjects(void);

        /// Loop over all registered GameObjects2D calling GameObject::v_Render.
        // TODO:: Need a better way to do this. Can't get the view matrix this way any more. 
        // Maybe the Level should call GetAllObjects and render them one by one from its update
        //TEMPEST_API void RenderObjects(void);

    protected:
        /// Protected constructor part of the Singleton pattern. 
        TEMPEST_API GameObjectManager(void);

    private:
        static shared_ptr<GameObjectManager>	_instance;	    ///< Singleton pattern global instance. 
        ObjectRegistry2D						_registry2D;	///< map of all registered GameObjects2D.
        ObjectRegistry3D						_registry3D;	///< map of all registered GameObjects2D.

    };//end Class
    typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}