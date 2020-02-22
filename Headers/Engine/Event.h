#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>

//===== STL includes =====
#include <functional>

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
		Event(void);
		
		Event(string type);

		Event(string type, U32 sender, U32 reciever, F64 dispatchTime);

		~Event(void);

		//==========================================================================================================================
		//
		//Data
		//
		//==========================================================================================================================
		U32 SenderID;
		U32 ReceiverID;
		F64 DispatchTime;
		string Type;

	};//end Class
	typedef shared_ptr<Event> p_Event;
}
