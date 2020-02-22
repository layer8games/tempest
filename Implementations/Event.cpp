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
    Type()
{  }

Event::Event(string type)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    Type()
{  }

Event::Event(string type, U32 sender, U32 reciever, F64 dispatchTime)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    Type()
{  }

Event::~Event(void)
{  }
