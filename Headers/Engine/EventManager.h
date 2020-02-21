#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Event.h>
#include <Engine/GameObjectManager.h>

//===== STL includes =====
#include <set>

namespace Tempest
{
    class EventManager
    {
    public:
        //==========================================================================================================================
        //
        //Constructors	 	
        //
        //==========================================================================================================================
        ~EventManager(void);

        //==========================================================================================================================
        //
        //Functions
        //
        //==========================================================================================================================
        static shared_ptr<EventManager> Instance(void);

    protected:
        EventManager(void);
    
    private:
        static shared_ptr<EventManager> _instance;
        std::set<Event> _priorityQueue;
        
    };//end Class
    typedef shared_ptr<EventManager> p_EventManager;
}
