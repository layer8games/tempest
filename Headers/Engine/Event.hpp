#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>

//===== STL includes =====
#include <any>

namespace Tempest
{
    struct Event
    {
    public:
        string Sender;
        string Receiver;
        F64 DispatchTime;
        string Type;
        std::any Data;
        
        Event(void)
            :
            Sender(),
            Receiver(),
            DispatchTime(0.0),
            Type(),
            Data()
        {  }

        Event(string type)
            :
            Sender(),
            Receiver(),
            DispatchTime(0.0),
            Type(type),
            Data()
        {  }

        Event(string type, string sender, string reciever, F64 dispatchTime, std::any data)
            :
            Sender(sender),
            Receiver(reciever),
            DispatchTime(dispatchTime),
            Type(type),
            Data(data)
        {  }

        ~Event(void)
        {  }

        inline bool operator<(const Event& event) const
        {
            if(event.DispatchTime < DispatchTime)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        inline bool operator>(const Event& event) const
        {
            if(event.DispatchTime > DispatchTime)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        inline bool operator==(const Event& event) const
        {
            if( std::strcmp(event.Type.c_str(), Type.c_str()) == 0 && 
                event.DispatchTime == DispatchTime &&
                event.Receiver == Receiver &&
                event.Sender == Sender
               )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };//end Class
    typedef shared_ptr<Event> p_Event;
}
