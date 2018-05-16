#include <Engine/LevelManager.h>
#include <iostream>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
LevelManager::LevelManager(void) 
: 
_running(true) 
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
void LevelManager::AddLevel(shared_ptr<Level> level) 
{
	_levels.insert({level->GetID(), level});
	
	if(_levels.find(level->GetID()) == _levels.end()) 
	{ 
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddLevel to LevelManager"); 
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
	_activeLevelID = levelID;
	auto level = _levels.find(levelID);
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
	//Update Physics, then level will update all registered Objects. 
	//finally, the level can update anything custom
	_activeLevel->v_Integrate();
	_activeLevel->UpdateObjects();
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
//This function will add a GameObject to an existing, registered level. It will check to make sure that the called worled
//in fact is registered with the manager, and will throw and error if it is not. 
//	
//==========================================================================================================================
void LevelManager::AddObjectToLevel(U32 id, const GameObject2D& obj)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddObjectToLevel(obj); 
	} 
	else
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddObjectToLevel() function for a level that does not exist. ID = " + std::to_string(id));	
	} 
}

void LevelManager::AddObjectToLevel(U32 id, shared_ptr<GameObject2D> obj)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddObjectToLevel(obj); 
	} 
	else
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddObjectToLevel() function for a level that does not exist. ID = " + std::to_string(id));	
	} 
}

void LevelManager::AddParticle2DToLevel(U32 id, shared_ptr<KP::Particle2D> particle, shared_ptr<KP::Particle2DForceGenerator> generator)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddParticle2DToLevel(particle, generator); 
	} 
	else
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddParticle2DToLevel() function for a level that does not exist. ID = " + std::to_string(id));	
	} 
}

void LevelManager::AddObject3DToLevel(U32 id, const GameObject3D& obj)
{
	if(_levels.find(id) != _levels.end()) 
	{ 
		_levels[id]->AddObject3DToLevel(obj); 
	} 
	else 
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "LevelManager -> Tried to call the AddObjectToLevel() function for a level that does not exist.");
	}
}

void LevelManager::Remove2DObjectFromLevel(U32 levelID, U32 objID)
{
	if(_levels.find(levelID) != _levels.end()) 
	{ 
		_levels[levelID]->Remove2DObjectFromLevel(objID); 
	}
}

void LevelManager::Remove3DObjectFromLevel(U32 levelID, U32 objID)
{
	if(_levels.find(levelID) != _levels.end()) 
	{ 
		_levels[levelID]->Remove3DObjectFromLevel(objID); 
	}
}