#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

//===== STL includes =====
#include <any>

namespace Tempest
{
	/// Message or Command that can be sent to a GameObject by Event Type or by ID. In order for an Event to be dispatched to an 
	/// object, the object must be registered with the EventManager. Type is defined as a string. There is no data base of valid
	/// Event types, so be careful! Anything goes. This was carefully thought over. In the end, I opted to let each defined object
	/// decide what to do with the Events as they are sent to it. This allows for the flexibilty I am looking for. In the future
	/// a data base of event types could be a very good thing. std::strcmp should be used to see if the type matches. Test carefully
	/// since the compiler isn't going to help out as much as it probably should. I just couldn't find a better way than this. 
	struct Event
	{
	public:
		//==========================================================================================================================
		//
		//Data
		//
		//==========================================================================================================================
		U32 SenderID;		///< ID of the sender of the Event.
		U32 ReceiverID;		///< ID of the receiver of the Event.
		F64 DispatchTime;	///< The total or current time when the Event should be sent. Should be in the future.
		string Type;		///< Event Type. Used to let the object know what to do with the event. 
		std::any Data;		///< Random data to be sent with the Event. The object must use std::any_cast to use this, so it has to know the type to expect.
		
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================
		/// No implemenation change.
		Event(void)
			:
			SenderID(0),
			ReceiverID(0),
			DispatchTime(0.0),
			Type(),
			Data()
		{  }
		
		/// Set just the type of the Event. 
		Event(string type)
			:
			SenderID(0),
			ReceiverID(0),
			DispatchTime(0.0),
			Type(type),
			Data()
		{  }

		/// Fully construct an Event inline. 
		Event(string type, U32 sender, U32 reciever, F64 dispatchTime, std::any data)
			:
			SenderID(sender),
			ReceiverID(reciever),
			DispatchTime(dispatchTime),
			Type(type),
			Data(data)
		{  }

		/// Not implemented. 
		~Event(void)
		{  }

		/// Overloaded so that the set can order the events correctly. Only matches on DispatchTime.
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

		/// Overloaded so that the set can order the events correctly. Only matches on DispatchTime.
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
		
		/// Overloaded so that the set can order the events correctly. Matches on everything but Data. 
		/// This means that if the DispatchTime, SenderID, ReceiverID and Type are all the same, it 
		/// will not be added to the event queue, since it will be seen as a duplicate. 
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
