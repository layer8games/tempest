#include <Engine/EventManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EventManager::EventManager(void)
{  }

EventManager::~EventManager(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
p_EventManager EventManager::_instance = nullptr;

p_EventManager EventManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_EventManager(new EventManager());
	}
	return _instance;
}