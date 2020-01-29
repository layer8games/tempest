#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/GameWindow.h>
#include <Engine/GameObject.h>
#include <Engine/ErrorManager.h>

namespace TP = TempestPhysics;

//=====STL includes=====
#include <map>

namespace Tempest 
{ 
///	The holder and controller of the the Level objects. This will act as both a singleton and a state matching controller, where 
///	each Level will be a state that can be set to active.
///	For now, all of the states that are to be used will be instantiated during the initialization in the main loop, however later, 
///	each Level will only be created once it is called, as part of a loading screen. 
	class LevelManager
	{
	public:
///	No implementation. 
		TEMPEST_API ~LevelManager(void);

///	Singleton fucntion. Returns the global pointer used to access the manager. 
		TEMPEST_API static LevelManager* Instance();

//==========================================================================================================================
//
//Accessors
//
//========================================================================================================================== 
///	Adds a Level into the state machine that can then be set to active to be in use. 
///	\param level is added into the database, with Level::GetID used to index.  
		TEMPEST_API void Add(p_Level level);
		
///	Removes Level from database. 
///	\param levelID is the index to delete.  
		TEMPEST_API void Remove(U32 levelID);

///	Returns a pointer to the active Level state. 
		TEMPEST_API p_Level GetLevel(U32 levelID);

	protected: 
///	Sets active Level state to a nullptr.  
		LevelManager(void);

	private:
		std::map<U32, p_Level> _levels;			///< Database of Levels that can be activated. 
		static LevelManager*   _instance;		///< Singletone pointer to global version of LevelManager. 

	};
}//End namespace