#include <Engine/EventManager.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EventManager::EventManager(void)
    :
    _2DListeners(),
    _3DListeners()
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
}

void EventManager::AddListener(p_GameObject2D obj, string type)
{
    ListenerRegistration2D reg(obj, type);
    _2DListeners.push_back(reg);
}

void EventManager::AddListener(p_GameObject3D obj, string type)
{
    ListenerRegistration3D reg(obj, type);
    _3DListeners.push_back(reg);
}

void EventManager::Dispatch(void)
{
        F64 currentTime = TM::Timer::Instance()->TotalTime();

        while((_priorityQueue.size() > 0) && (_priorityQueue.begin()->DispatchTime < currentTime) && (_priorityQueue.begin()->DispatchTime > 0.0f))
        {            
            for(auto listener : _2DListeners)
            {
                if(std::strcmp(listener.interestType.c_str(), _priorityQueue.begin()->Type.c_str()) == 0)
                {
                    listener.listener->v_OnEvent(*_priorityQueue.begin());
                }
            }
            for(auto listener : _3DListeners)
            {
                if(std::strcmp(listener.interestType.c_str(), _priorityQueue.begin()->Type.c_str()) == 0)
                {
                    listener.listener->v_OnEvent(*_priorityQueue.begin());
                }
            }
            _priorityQueue.erase(_priorityQueue.begin());
        }
}

void EventManager::DispatchNow(Event event)
{
    for(auto listener : _2DListeners)
    {
        if(event.ReceiverID == listener.listener->GetID())
        {
            listener.listener->v_OnEvent(event);
            return;
        }
    }

    for(auto listener : _3DListeners)
    {
        if(event.ReceiverID == listener.listener->GetID())
        {
            listener.listener->v_OnEvent(event);
            return;
        }
    }
}