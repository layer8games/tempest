#include <Engine/StateMachine.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
StateMachine::StateMachine(void)
{  }

StateMachine::~StateMachine(void)
{  }

p_StateMachine StateMachine::_instance = nullptr;

p_StateMachine StateMachine::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_StateMachine(new StateMachine);
	}

	return _instance;
}