#include <Engine/LevelManager.h>
#include <iostream>

namespace KillerEngine 
{
	LevelManager::~LevelManager(void)
	{  }


//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Singleton
//==========================================================================================================================
	LevelManager* LevelManager::_instance = NULL;

	LevelManager* LevelManager::Instance(void) 
	{
		if(_instance == NULL) { _instance = new LevelManager; }
		return _instance;
	}

//==========================================================================================================================
//
//Level Accessors
//
//==========================================================================================================================
	void LevelManager::AddLevel(Level* world) 
	{
		_levels.insert(std::map<U32, std::shared_ptr<Level>>::value_type( world->GetID(), std::shared_ptr<Level>(world) ));
		
		if(_levels.find(world->GetID()) == _levels.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddLevel to LevelManager"); 
		}
	}

	void LevelManager::RemoveLevel(U32 worldID) 
	{
		auto w = _levels.find(worldID);
		_levels.erase(w);
	}

//==========================================================================================================================
//
//SetActiveLevel
//
//==========================================================================================================================
	void LevelManager::SetActiveLevel(U32 worldID) 
	{
		_activeLevelID = worldID;
		auto level = _levels.find(worldID);
		_activeLevel = level->second;
		_activeLevel->ActivateBackgroundColor();
	}

//==========================================================================================================================
//
//Update
//
//==========================================================================================================================
	void LevelManager::Update(void) 
	{
		_activeLevel->v_Update();
	}

//==========================================================================================================================
//
//Render
//
//==========================================================================================================================
	void LevelManager::Render(void) 
	{
		_activeLevel->v_Render();
	}

//==========================================================================================================================
//
//Add/Remove Objects from Level
//
//This function will add a GameObject to an existing, registered world. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
	void LevelManager::AddObjectToLevel(U32 id, GameObject2D* obj)
	{
		if(_levels.find(id) != _levels.end()) 
		{ 
			_levels[id]->AddObjectToLevel(obj); 
		} 
		else
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddObjectToLevel() function for a world that does not exist.");	
		} 
	}

	void LevelManager::AddObject3DToLevel(U32 id, GameObject3D* obj)
	{
		if(_levels.find(id) != _levels.end()) 
		{ 
			_levels[id]->AddObject3DToLevel(obj); 
		} 
		else 
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddObjectToLevel() function for a world that does not exist.");
		}
	}

	void LevelManager::Remove2DObjectFromLevel(U32 worldID, U32 objID)
	{
		if(_levels.find(worldID) != _levels.end()) 
		{ 
			_levels[worldID]->Remove2DObjectFromLevel(objID); 
		}
	}

	void LevelManager::Remove3DObjectFromLevel(U32 worldID, U32 objID)
	{
		if(_levels.find(worldID) != _levels.end()) 
		{ 
			_levels[worldID]->Remove3DObjectFromLevel(objID); 
		}
	}

}//End namsepace