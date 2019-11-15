#include <Engine/LevelManager.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
LevelManager::LevelManager(void) 
:
_levels(),
_activeLevel(nullptr),
_activeLevelID(UINT_MAX)
{  }

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
void LevelManager::AddLevel(p_Level level) 
{
	_levels.insert({level->GetID(), level});
	
	if(_levels.find(level->GetID()) == _levels.end()) 
	{ 
		ErrorManager::Instance()->SetError(ENGINE, "Unable to AddLevel to LevelManager"); 
	}
}

void LevelManager::RemoveLevel(U32 levelID) 
{
	auto w = _levels.find(levelID);
	_levels.erase(w);
}

//==========================================================================================================================
//
//SetActiveLevel
//
//==========================================================================================================================
void LevelManager::SetActiveLevel(U32 levelID) 
{
	if(_activeLevelID == 0)
	{
		_activeLevel.reset();
	}

	_activeLevelID = levelID;
	auto level = _levels.find(levelID);
	_activeLevel = level->second;
	_activeLevel->ActivateBackgroundColor();
}

void LevelManager::SetActiveLevel(p_Level level)
{
	_activeLevelID = 0;
	level->v_Init();

	_activeLevel = level;
}

//==========================================================================================================================
//
//Update
//
//==========================================================================================================================
void LevelManager::Update(void) 
{
	//Update Physics, then level will update all registered Objects. 
	//finally, the level can update anything custom
	
	if(_activeLevel != nullptr)
	{
		_activeLevel->UpdateLevel();
		_activeLevel->UpdateObjects();
		_activeLevel->v_Update();	
	}
}

//==========================================================================================================================
//
//Render
//
//==========================================================================================================================
void LevelManager::Render(void) 
{
	if(_activeLevel != nullptr)
	{
		_activeLevel->v_Render();
	}
}

//==========================================================================================================================
//
//Add/Remove Objects from Level
//
//This function will add a GameObject to an existing, registered level. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
void LevelManager::AddObjectToLevel(U32 id, const GameObject& obj)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddObjectToLevel(obj); 
	} 
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "LevelManager -> Tried to call the AddObjectToLevel() function for a level that does not exist. ID = " + std::to_string(id));	
	} 
}

void LevelManager::AddObjectToLevel(U32 id, shared_ptr<GameObject> obj)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddObjectToLevel(obj); 
	} 
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "LevelManager -> Tried to call the AddObjectToLevel() function for a level that does not exist. ID = " + std::to_string(id));	
	} 
}

void LevelManager::RemoveObjectFromLevel(U32 levelID, U32 objID)
{
	if(_levels.find(levelID) != _levels.end()) 
	{ 
		_levels[levelID]->RemoveObjectFromLevel(objID); 
	}
}