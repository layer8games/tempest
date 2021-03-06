#include "stdafx.h"
#include <Engine/Timer.h>
using namespace TempestMath;


shared_ptr<Timer> Timer::_instance = nullptr;
Timer::Timer() 
    : 
    _clamp(false),
    _paused(false),
    _deltaTime(0.0),
    _timeScale(1.0),
    _totalTime(0.0),
    _pastTime(0.0),
    _currentTime(_pastTime)
{  }

Timer::~Timer(void)
{  }


shared_ptr<Timer> Timer::Instance(void) 
{
    if(_instance == nullptr) 
    { 
        _instance = shared_ptr<Timer>(new Timer()); 
    }
    return _instance;
}

void Timer::Update(F64 newTime) 
{
    if(!_paused) 
    {
        _currentTime = newTime;
        _deltaTime = static_cast<real>((_currentTime - _pastTime) * _timeScale);
        _pastTime = _currentTime;

        if(_clamp && _deltaTime < 0.016f || _deltaTime > 1.0f)
        { 
            _deltaTime = 0.016f; 
        }
        
        _totalTime += static_cast<F64>(_deltaTime);
    }
}

void Timer::SingleStep(void) 
{
    if(!_paused) 
    {
        _deltaTime = (1.0f/60.0f) * _timeScale;

        _totalTime += _deltaTime;
    }
}