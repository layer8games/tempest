#include <Engine/GameObjectManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
GameObjectManager::GameObjectManager(void)
{  }

GameObjectManager::~GameObjectManager(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
p_GameObjectManager GameObjectManager::_instance = nullptr;

p_GameObjectManager GameObjectManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_GameObjectManager(new GameObjectManager());
	}

	return _instance;
}