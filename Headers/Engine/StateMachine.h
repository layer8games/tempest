#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/State.h>

namespace Tempest
{
	template <class GameObjectType>
	class StateMachine
	{
	public:
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================
		StateMachine(void);

		~StateMachine(void);

		//==========================================================================================================================
		//
		//Functions
		//
		//==========================================================================================================================
	private:
		shared_ptr<GameObjectType> _owner;
		shared_ptr<State> _currentState;

	};//end Class
}
