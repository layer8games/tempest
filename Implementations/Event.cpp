#include <Engine/Event.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Event::Event(void)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    Type(),
    Data()
{  }

Event::Event(string type)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    Type(type),
    Data()
{  }

//Event::Event(string type, U32 sender, U32 reciever, F64 dispatchTime, void* data)
Event::Event(string type, U32 sender, U32 reciever, F64 dispatchTime, std::any data)
    :
    SenderID(sender),
    ReceiverID(reciever),
    DispatchTime(dispatchTime),
    Type(type),
    Data(data)
{  }

Event::~Event(void)
{  }
