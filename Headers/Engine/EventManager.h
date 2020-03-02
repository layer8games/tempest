#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Event.hpp>
#include <Engine/GameObjectManager.h>
#include <Engine/GameObject.h>

//===== STL includes =====
#include <set>
//#include <queue>
#include <list>

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
        TEMPEST_API ~EventManager(void);

        //==========================================================================================================================
        //
        //Functions
        //
        //==========================================================================================================================
        TEMPEST_API static shared_ptr<EventManager> Instance(void);

        TEMPEST_API void AddEvent(Event event);
        
        TEMPEST_API void AddListener(p_GameObject obj, string type);

        TEMPEST_API void Dispatch(void);
         
        TEMPEST_API void DispatchNow(Event event);

    protected:
        TEMPEST_API EventManager(void);
    
    private:
        struct ListenerRegistration
        {
            string interestType;
            p_GameObject listener;

            ListenerRegistration(p_GameObject l, string t) : interestType(t), listener(l)
            {  }
        };
        
        static shared_ptr<EventManager> _instance;
        std::set<Event>                 _priorityQueue;
        //std::priority_queue<Event>        _priorityQueue;
        std::list<ListenerRegistration> _listeners;
        
    };//end Class
    typedef shared_ptr<EventManager> p_EventManager;
}
