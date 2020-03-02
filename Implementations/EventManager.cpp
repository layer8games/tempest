#include <Engine/EventManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EventManager::EventManager(void)
{  }

EventManager::~EventManager(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
p_EventManager EventManager::_instance = nullptr;

p_EventManager EventManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_EventManager(new EventManager());
	}
	return _instance;
}

void EventManager::AddEvent(Event event)
{
	if(event.DispatchTime == 0.0)
	{
		DispatchNow(event);
		return;
	}

	_priorityQueue.insert(event);
	//_priorityQueue.push(event);
}

void EventManager::AddListener(p_GameObject obj, string type)
{
	ListenerRegistration reg(obj, type);
	_listeners.push_back(reg);
}

void EventManager::Dispatch(void)
{
	F32 currentTime = TM::Timer::Instance()->TotalTime();
	
	while((_priorityQueue.begin()->DispatchTime < currentTime) && (_priorityQueue.begin()->DispatchTime > 0.0f) )
	{
		for(auto listener : _listeners)
		{
			if(std::strcmp(listener.interestType.c_str(), _priorityQueue.begin()->Type.c_str()))
			{
				listener.listener->v_OnEvent(*_priorityQueue.begin());
			}
		}
		_priorityQueue.erase(_priorityQueue.begin());
	}
}

void EventManager::DispatchNow(Event event)
{
	for(auto listener : _listeners)
	{
		if(event.ReceiverID == listener.listener->GetID())
		{
			listener.listener->v_OnEvent(event);
			return;
		}
	}
}