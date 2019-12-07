#include <Engine/Timer.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
Timer::Timer() 
	: 
	_clamp(false),
	_paused(false),
	_deltaTime(0.0),
	_timeScale(1.0),
	_pcFreq(0.0),
	_totalTime(0.0),
	_pastTime(0.0),
	_currentTime(_pastTime),
	_counterStart(0)
{
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
	{
		TE::ErrorManager::Instance()->SetError(TE::MATH, "Timer::_QueryCounter:: Call to QueryPerformanceFrequency failed. This is a really bad thing!");
	}

	_pcFreq = static_cast<F64>(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	_counterStart = li.QuadPart;

	_pastTime = _QueryCounter();
}

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
		//_currentTime = _QueryCounter();
		_currentTime = TE::GameWindow::Instance()->GetTime();
		_deltaTime = static_cast<real>((_currentTime - _pastTime) * _timeScale);
		_pastTime = _currentTime;

		if(_clamp && _deltaTime < 0.016f || _deltaTime > 1.0f)
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

F64 Timer::_QueryCounter(void)
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return static_cast<F64>(li.QuadPart - _counterStart) / _pcFreq;
}