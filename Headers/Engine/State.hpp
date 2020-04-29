#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>

namespace Tempest
{
    template <class GameObjectType>
    class State
    {
    public:
        State(void)
        {  }

        virtual ~State(void)
        {  }

        virtual void v_Enter(GameObjectType* object)=0;

        virtual void v_Execute(GameObjectType* object)=0;

        virtual void v_Exit(GameObjectType* object)=0;
    private:

    };//end Class
}
