#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/ErrorManager.h>

namespace TP = TempestPhysics;

//=====STL includes=====
#include <map>

namespace Tempest 
{ 
	///	A lazy loader for Levels. If there is a need to cache a Level in memory, it can be registered with the LevelManager
	/// and recalled later. This is far more simple then it used to be. For histories sake, at one point this class was used
	/// to control the rendering and updating of objects. 
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
		///	Register a Level with the manager.
		///	\param level is added into the database, with Level::GetID used to index.  
		TEMPEST_API void Add(p_Level level);
		
		///	Removes Level from database. 
		///	\param levelID is the index to delete.  
		TEMPEST_API void Remove(U32 levelID);

		///	Returns a pointer to Level with \param levelID if it exists.
		TEMPEST_API p_Level GetLevel(U32 levelID);

	protected: 
		///	Singleton constructor. 
		LevelManager(void);

	private:
		std::map<U32, p_Level> _levels;			///< Database of Levels that can be activated. 
		static LevelManager*   _instance;		///< Singletone pointer to global version of LevelManager. 

	};
}//End namespace