#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>

namespace Tempest
{
    /// A State is used in a StateMachine to define behavior at run time. This is based on the pattern that is well established as 
    /// a good way to control what an object is going, given a certain context. These States should be used to express how a GameObject
    /// should behave, given a certain context. This is an abstract class. It is also templated. This is so that any type of object
    /// can have states added to it, and any of their functions can be called. Without this, only the functions located in the 
    /// GameObject base could be called, and this would not do. This class also uses what is called an alias declaration template.
    /// This allowed me to declare a shared_ptr to the template State. Very useful.
    template <class GameObjectType>
    class State
    {
    public:
        //==========================================================================================================================
        //
        //Constructors	 	
        //
        //==========================================================================================================================
        /// No implementation.
        State(void)
        {  }

        /// No implementation.
        virtual ~State(void)
        {  }

        //==========================================================================================================================
        //
        //Functions
        //
        //==========================================================================================================================
        /// Called when the State is made active by the StateMachine. Abstract, but be implemented for use.
        /// \param object type is a defined GameObject which functions can and probably should be called on.
        virtual void v_Enter(GameObjectType* object)=0;

        /// Called when the State is executed during the Update loop, by the StateMachine.
        /// \param object type is a defined GameObject which functions can and probably should be called on.
        virtual void v_Execute(GameObjectType* object)=0;

        /// Called when the State is finished. This could define what the next state is. 
        /// \param object type is a defined GameObject which functions can and probably should be called on.
        virtual void v_Exit(GameObjectType* object)=0;
    private:

    };//end Class
}
