#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameWindow.h>

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
		typedef	std::map<U32, p_GameObject> ObjectRegistry; 

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

		/// Add a GameObject to the Manager. 
		/// \param obj calls GameObject::GetID, then attempts to insert GameObject into the map. 
		TEMPEST_API void Add(p_GameObject obj);

		/// Remove the GameObject with \param id from the Manager, if it exists. 
		TEMPEST_API void Remove(U32 id);

		/// Return pointer to GameObject with \param id if it exists.
		TEMPEST_API p_GameObject GetGameObject(U32 id);

		/// Return a count of all the GameObjects that have been registered with the manager.
		inline U32 Count(void)
		{
			return _registry.size();
		}

		/// Loop over all registered GameObjects calling GameObject::v_Update.
		TEMPEST_API void UpdateObjects(void);

		/// Loop over all registered GameObjects calling GameObject::v_Render.
		TEMPEST_API void RenderObjects(void);

	protected:
		/// Protected constructor part of the Singleton pattern. 
		TEMPEST_API GameObjectManager(void);

	private:
		static shared_ptr<GameObjectManager>	_instance;	///< Singleton pattern global instance. 
		ObjectRegistry							_registry;	///< map of all registered GameObjects. 

	};//end Class
	typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}