#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/State.h>
#include <Engine/ErrorManager.h>

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
		StateMachine(GameObjectType* owner)
			:
			_owner(owner),
			_currentState(nullptr),
			_previousState(nullptr),
			_globalState(nullptr)
		{  }

		~StateMachine(void)
		{  }

		//==========================================================================================================================
		//
		//Functions
		//
		//==========================================================================================================================
		void Update(void) const
		{
			if(_globalState)
			{
				_globalState->v_Execute(_owner);
			}
			
			if(_currentState)
			{
				_currentState->v_Execute(_owner);
			}
		}

		void ChangeState(State<GameObjectType>* newState)
		{
			if(newState == nullptr)
			{
				ErrorManager::Instance()->SetError(ENGINE, "StateMachine::ChangeState cannot pass nullptr to ChangeState!");
				return;
			}

			if(_currentState != nullptr)
			{
				_currentState->v_Exit(_owner);

				_previousState = _currentState;
			}
			
			_currentState = newState;

			_currentState->v_Enter(_owner);
		}

		void RevertState(void)
		{
			ChangeState(_previousState);
		}



		//==========================================================================================================================
		//
		//Accessors
		//
		//==========================================================================================================================
		void SetCurrentState(State<GameObjectType>* state)
		{
			_currentState = state;
		}

		State<GameObjectType>* GetCurrentState(void) const
		{
			return _currentState;
		}

		void SetPreviousState(State<GameObjectType>* state)
		{
			_previousState = state;
		}

		State<GameObjectType>* GetPreviousState(void) const
		{
			return _previousState;
		}

		void SetGlobalState(State<GameObjectType>* state)
		{
			_globalState = state;
		}

		State<GameObjectType>* GetGlobalState(void) const
		{
			return _globalState;
		}
	
	private:
		GameObjectType* _owner;
		State<GameObjectType>* _currentState;
		State<GameObjectType>* _previousState;
		State<GameObjectType>* _globalState;

	};//end Class
}
