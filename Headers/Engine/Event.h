#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>

//===== STL includes =====
#include <any>

namespace Tempest
{
	struct Event
	{
	public:
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================
		TEMPEST_API Event(void);
		
		TEMPEST_API Event(string type);

		//TEMPEST_API Event(string type, U32 sender, U32 reciever, F64 dispatchTime, void* data);
		TEMPEST_API Event(string type, U32 sender, U32 reciever, F64 dispatchTime, std::any data);

		TEMPEST_API ~Event(void);

		//==========================================================================================================================
		//
		//Data
		//
		//==========================================================================================================================
		U32 SenderID;
		U32 ReceiverID;
		F64 DispatchTime;
		string Type;
		//void* Data;
		std::any Data;

	};//end Class
	typedef shared_ptr<Event> p_Event;
}
