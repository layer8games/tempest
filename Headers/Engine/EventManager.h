#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Event.hpp>
#include <Engine/GameObjectManager.h>
#include <Engine/GameObject.h>

//===== STL includes =====
#include <set>
#include <functional>

#include <list>

namespace Tempest
{
    /// A general Event dispatcher and manager. An object will register its interests (defined as an event type), and when an event
    /// is added to the manager, if the GameObject has that type's interest, it will call GameObject::v_OnEvent, sending the found 
    /// Event along. This is true for sending an event at a future time (AddEvent) or sending an event now (DispatchNow). This class
    /// is a singleton.
    class EventManager
    {
    public:
        //==========================================================================================================================
        //
        //Constructors	 	
        //
        //==========================================================================================================================
        /// No implementation
        TEMPEST_API ~EventManager(void);

        //==========================================================================================================================
        //
        //Functions
        //
        //==========================================================================================================================
        /// Returns the singleton instance of the class.
        TEMPEST_API static shared_ptr<EventManager> Instance(void);

        /// Adds and Event to the priority queue. If Event::DispatchTime is set to 0, the Event will be dispatched on the next 
        /// Dispatch call. It's basically the same as calling DispatchNow, but with more steps. 
        /// \param event is dispatched at Event::DispatchTime
        TEMPEST_API void AddEvent(Event event);
        
        /// Register a GameObject with an interest type. 
        /// \param obj is registered
        /// \param type is the interest of obj.
        TEMPEST_API void AddListener(p_GameObject obj, string type);

        /// Checks the priority queue for the next Event to dispatch. If the dispatch time is equal to the Current Time (total time)
        /// then then we check for any registered listeners. If any listeners are found, they v_OnEvent is called and the event is sent.
        /// The Event is then removed from the queue. 
        TEMPEST_API void Dispatch(void);
         
        /// Checks if there are any listeners registered with ReceiverID. If one is found, the Event is sent to them. 
        /// \param event is sent to the reciever. 
        TEMPEST_API void DispatchNow(Event event);

    protected:
        /// No major implemenation notes. 
        TEMPEST_API EventManager(void);
    
    private:
        /// Helper struct to keep track of which GameObjects are interested in what types of Events. 
        struct ListenerRegistration
        {
            string interestType;    ///< Type of Event to recieve. 
            p_GameObject listener;  ///< GameObject to receive the type of Event.

            /// Basic constructor.
            ListenerRegistration(p_GameObject l, string t) : interestType(t), listener(l)
            {  }
        };
        
        static shared_ptr<EventManager>      _instance;         ///< Singleton instance of EventManager.
        std::set<Event, std::greater<Event>> _priorityQueue;    ///< Set of Events acting as a queue. Set to decending order.
        std::list<ListenerRegistration>      _listeners;        ///< List of registered listeners. 
        
    };//end Class
    typedef shared_ptr<EventManager> p_EventManager;
}
