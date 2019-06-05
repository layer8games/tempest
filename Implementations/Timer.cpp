#include <Engine/Timer.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
Timer::Timer() 
: 
_clamp(false),
_deltaTime(0.0f),
_timeScale(1.0f),
_totalTime(0.0f),
_pastTime(KE::GameWindow::Instance()->GetTime()),
_currentTime(_pastTime),
_paused(false) 
{  }

Timer::~Timer(void)
{  }


//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================	
//===============================================================================
//Instance
//===============================================================================
shared_ptr<Timer> Timer::_instance = NULL;
shared_ptr<Timer> Timer::Instance(void) 
{
	if(_instance == NULL) 
	{ 
		_instance = shared_ptr<Timer>(new Timer()); 
	}
	return _instance;
}

//==========================================================================================================================
//
//Timer Functions
//
//==========================================================================================================================	
//===============================================================================
//Update
//===============================================================================
void Timer::Update(void) 
{
	if(!_paused) 
	{
		_currentTime = KE::GameWindow::Instance()->GetTime();
		_deltaTime = static_cast<real>((_currentTime - _pastTime) * _timeScale);
		_pastTime = _currentTime;

		if(_clamp && _deltaTime < 0.001f || _deltaTime > 1.0f)
		{ 
			_deltaTime = 0.016f; 
		}
		
		_totalTime += static_cast<F64>(_deltaTime);
	}
}

//===============================================================================
//SingleStep
//===============================================================================
void Timer::SingleStep(void) 
{
	if(!_paused) 
	{
		_deltaTime = (1.0f/60.0f) * _timeScale;

		_totalTime += _deltaTime;
	}
}