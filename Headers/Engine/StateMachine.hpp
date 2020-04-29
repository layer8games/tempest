#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/State.hpp>
#include <Engine/ErrorManager.h>

namespace Tempest
{
    /// This is a general purpose state Machine. It will facilitate the changes between states that have been added to it. States 
    /// can control when they are switched, of they can be switched manually. This is created as a template, meaning that each 
    /// class should have its own version of the StateMachine so that it can control its own States. 
    template <class GameObjectType>
    class StateMachine
    {
    public:
        //==========================================================================================================================
        //
        //Constructors	 	
        //
        //==========================================================================================================================
        /// No major change. Sets all states to nullptr. 
        StateMachine(GameObjectType* owner)
            :
            _owner(owner),
            _currentState(nullptr),
            _previousState(nullptr),
            _globalState(nullptr)
        {  }

        /// Not implemented. 
        ~StateMachine(void)
        {  }

        //==========================================================================================================================
        //
        //Functions
        //
        //==========================================================================================================================
        /// Calls State::v_Execute on the global and current state. 
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

        /// Changes the State to the new state. Calls State::v_Exit and State::v_Enter as expected on the old and new State.
        /// \param newState is the next state for the Machine. 
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

        /// The previous State is remembered. This changes back to that State, calling ChangeState so its logic gets used. 
        void RevertState(void)
        {
            ChangeState(_previousState);
        }



        //==========================================================================================================================
        //
        //Accessors
        //
        //==========================================================================================================================
        /// Set the current State bypassing the ChangeState logic. 
        /// \param state is the new current state. 
        void SetCurrentState(State<GameObjectType>* state)
        {
            _currentState = state;
        }

        /// Return an accessible pointer to the current state. 
        State<GameObjectType>* GetCurrentState(void) const
        {
            return _currentState;
        }

        /// Set the previous state, by passing the ChangeState logic. 
        /// \param state
        void SetPreviousState(State<GameObjectType>* state)
        {
            _previousState = state;
        }

        /// Return the previous state pointer
        State<GameObjectType>* GetPreviousState(void) const
        {
            return _previousState;
        }

        /// Set the global state, bypassing the ChangeState logic. 
        /// \param state
        void SetGlobalState(State<GameObjectType>* state)
        {
            _globalState = state;
        }

        /// Return the global state. 
        State<GameObjectType>* GetGlobalState(void) const
        {
            return _globalState;
        }
    
    private:
        GameObjectType* _owner;						/// Pointer to the owner of the StateMachine. This allows State functions to be called on the owner. 
        State<GameObjectType>* _currentState;       /// Pointer to the current state. 
        State<GameObjectType>* _previousState;      /// Pointer to the previous state.
        State<GameObjectType>* _globalState;        /// Pointer to a global, world state.

    };//end Class
}
