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
		StateMachine(shared_ptr<GameObjectType> owner)
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

		void ChangeState(p_State<GameObjectType> newState)
		{
			if(newState == nullptr)
			{
				ErrorManager::Instance()->SetError(ENGINE, "StateMachine::ChangeState cannot pass nullptr to ChangeState!");
				return;
			}

			_previousState = _currentState;

			_currentState->v_Exit(_owner);

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
		void SetCurrentState(p_State<GameObjectType> state)
		{
			_currentState = state;
		}

		p_State<GameObjectType> GetCurrentState(void) const
		{
			return _currentState;
		}

		void SetPreviousState(p_State<GameObjectType> state)
		{
			_previousState = state;
		}

		p_State<GameObjectType> GetPreviousState(void) const
		{
			return _previousState;
		}

		void SetGlobalState(p_State<GameObjectType> state)
		{
			_globalState = state;
		}

		p_State<GameObjectType> GetGlobalState(void) const
		{
			return _globalState;
		}
	
	private:
		shared_ptr<GameObjectType> _owner;
		p_State<GameObjectType> _currentState;
		p_State<GameObjectType> _previousState;
		p_State<GameObjectType> _globalState;

	};//end Class
	template <class GameObjectType>
	using p_StateMachine = shared_ptr<StateMachine<GameObjectType>>;
}
