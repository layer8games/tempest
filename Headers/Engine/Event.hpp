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
        U32 SenderID;		
        U32 ReceiverID;		
        F64 DispatchTime;	
        string Type;		
        std::any Data;		
        
        Event(void)
            :
            SenderID(0),
            ReceiverID(0),
            DispatchTime(0.0),
            Type(),
            Data()
        {  }

        Event(string type)
            :
            SenderID(0),
            ReceiverID(0),
            DispatchTime(0.0),
            Type(type),
            Data()
        {  }

        Event(string type, U32 sender, U32 reciever, F64 dispatchTime, std::any data)
            :
            SenderID(sender),
            ReceiverID(reciever),
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
                event.ReceiverID == ReceiverID &&
                event.SenderID == SenderID
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
