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
    _type(0),
    _hasher()
{  }

Event::Event(string type)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    _type(0),
    _hasher()
{
    SetType(type);
}

Event::Event(string type, U32 sender, U32 reciever, F64 dispatchTime)
    :
    SenderID(0),
    ReceiverID(0),
    DispatchTime(0.0),
    _type(0),
    _hasher()
{
    SetType(type);
}

Event::~Event(void)
{  }

void Event::SetType(string type)
{
    _type = _hasher(type);
}