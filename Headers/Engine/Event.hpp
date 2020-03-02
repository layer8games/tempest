#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

//===== STL includes =====
#include <any>

namespace Tempest
{
	struct Event
	{
	public:
		//==========================================================================================================================
		//
		//Data
		//
		//==========================================================================================================================
		U32 SenderID;
		U32 ReceiverID;
		F64 DispatchTime;
		string Type;
		std::any Data;
		
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================
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

		//TEMPEST_API Event(string type, U32 sender, U32 reciever, F64 dispatchTime, void* data);
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
			if(event.DispatchTime == DispatchTime)
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
