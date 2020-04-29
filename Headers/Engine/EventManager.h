#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Event.hpp>
#include <Engine/GameObjectManager.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObject3D.h>

//===== STL includes =====
#include <set>
#include <functional>

#include <list>

namespace Tempest
{
    class EventManager
    {
    public:
        TEMPEST_API ~EventManager(void);

        TEMPEST_API static shared_ptr<EventManager> Instance(void);

        TEMPEST_API void AddEvent(Event event);
        
        TEMPEST_API void AddListener(p_GameObject2D obj, string type);

        TEMPEST_API void AddListener(p_GameObject3D obj, string type);

        TEMPEST_API void Dispatch(void);
         
        TEMPEST_API void DispatchNow(Event event);

    protected:
        TEMPEST_API EventManager(void);
    
    private:
        struct ListenerRegistration2D
        {
            string interestType;    
            p_GameObject2D listener;  

            ListenerRegistration2D(p_GameObject2D l, string t) : interestType(t), listener(l)
            {  }
        };

        struct ListenerRegistration3D
        {
            string interestType;    
            p_GameObject3D listener;  

            ListenerRegistration3D(p_GameObject3D l, string t) : interestType(t), listener(l)
            {  }
        };
        
        static shared_ptr<EventManager> _instance;     
        std::set<Event, std::greater<Event>> _priorityQueue;
        std::list<ListenerRegistration2D> _2DListeners;  
        std::list<ListenerRegistration3D> _3DListeners;  
        
    };//end Class
    typedef shared_ptr<EventManager> p_EventManager;
}
