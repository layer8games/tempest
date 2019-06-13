/*========================================================================
The holder and controller of the the level objects. This will act as 
both a singleton and a state maching controller, where each level will
be a state that can be set to active. 

For now, all of the states that are to be used will be instantiated 
during the initialization in the main loop, however later, each level
will only be created once it is called, as part of a loading screen.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/GameWindow.h>
#include <Engine/GameObject.h>
#include <Engine/ErrorManager.h>

namespace KP = KillerPhysics;

//=====STL includes=====
#include <map>

namespace KillerEngine 
{
/*! 
	The holder and controller of the the Level objects. This will act as both a singleton and a state matching controller, where 
	each Level will be a state that can be set to active. 

	For now, all of the states that are to be used will be instantiated during the initialization in the main loop, however later, 
	each Level will only be created once it is called, as part of a loading screen. 
*/
	class LevelManager
	{
	public:
/*! 
	No implementation. 
*/
		~LevelManager(void);

/*! 
	Singleton fucntion. Returns the global pointer used to access the manager. 
*/
		static LevelManager* Instance();

/*! 
	Helper function that deletes the instance from global memory.  
*/
		void ShutDown(void)
		{
			delete _instance;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*! 
	Adds a Level into the state machine that can then be set to active to be in use. 
	\param level is added into the database, with Level::GetID used to index.  
*/
		void AddLevel(shared_ptr<Level> level);
		
/*! 
	Removes Level from database. 
	\param levelID is the index to delete.  
*/
		void RemoveLevel(U32 levelID);
		
/*! 
	Changes the state to have a different active Level.
	\param levelID is the index to set to active.  
*/
		void SetActiveLevel(U32 levelID);

/*! 
	Changes the active level to be a new level. This level is NOT stored in the levels data base and will be deleted when
	the active level is changed again. This allows for levels to be lazy loaded, for quick switching, or to not be loaded 
	into memory until they are set to active. Level::v_Init is called before it is set to active.
	\param level is the new Level that will be set to active.
*/
		void SetActiveLevel(shared_ptr<Level> level);
		
/*! 
	Returns the ID of the active Level state.  
*/
		U32 GetActiveLevelID(void) 
		{ 
			return _activeLevelID; 
		}

/*! 
	Returns a pointer to the active Level state. 
*/
		inline shared_ptr<Level> GetActiveLevel(void)
		{
			return _activeLevel;
		}

/*! 
	Starts the process to shut down the game. Wrapper around GameWindow::EndRunning. 
*/
		void EndGame(void)
		{
			GameWindow::Instance()->EndRunning();
		}

/*! 
	 Allows object to be added to level. Wrapper around Level::AddObjectToLevel.
	 \param id is the key for the Level that the object will be added to. 
	 \param obj is the object to add.
*/
		void AddObjectToLevel(U32 id, const GameObject& obj);

/*! 
	 Allows object to be added to level. Wrapper around Level::AddObjectToLevel.
	 \param id is the key for the Level that the object will be added to. 
	 \param obj is the object pointer to add.
*/
		void AddObjectToLevel(U32 id, shared_ptr<GameObject> obj);
		
/*! 
	Removes an object from a Level. Wrapper around Level::RemoveObjectFromLevel. This assumes that ID are unique for all GameObject. 
	I don't know if this is true, so be careful. 
	\param levelID is the key for the Level that the object will be removed from. 
	\param objID is the GameObject ID to remove. 
*/
		void RemoveObjectFromLevel(U32 levelID, U32 objID);

//==========================================================================================================================
//
//Integrators
//
//==========================================================================================================================
/*! 
	Calls all functions on the active Level state needed to update that state. This includes Level::v_Integrate, Level::UpdateLevel,
	Level::UpdateObjects and Level::v_Update. 
*/
		void Update(void);
		
/*! 
	Calls all of the functions on the active Level state needed to render the state. Calls Level::v_Render. 
*/
		void Render(void);

	protected:
/*! 
	Sets active Level state to a nullptr.  
*/
		LevelManager(void);

	private:
		std::map<U32, shared_ptr<Level>> _levels;			///< Database of Levels that can be activated. 
		shared_ptr<Level> 				 _activeLevel;		///< Pointer to active Level from database. 
		U32 				   			_activeLevelID;		///< The ID of the active Level. 
		static LevelManager*     		_instance;			///< Singletone pointer to global version of LevelManager. 

	};

}//End namespace