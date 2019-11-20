#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>

namespace TE = Tempest;

namespace TempestMath 
{
///	The high precision timer for the Killer1 Engine. At the time of writting
///	this the timer is windows specific, but cross platform functionality is
///	planned in the future. 

///	It uses the GLFW function glfwGetTime, located in the GameWindow to get
///	the total time that the glfw window has been open. It used to have a 
///	customer frequency timer, but this turned out to be too eratic, and 
///	was removed.  
	class Timer 
	{ 
	public:
///	Default Destructor. Does not do anything. 
		TEMPEST_API ~Timer(void);

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================		

///	Singleton pattern function. Returns a pointer to the globabl version of the timer. This is the only way to use the timer,
///	ensuring that there will only ever be 1 version of it running. 
		TEMPEST_API static shared_ptr<Timer> Instance(void);

//==========================================================================================================================
//
//Timer Functions
//
//==========================================================================================================================		
///	This updates the _totalTime and _deltaTime values. This is where all of the magic happens. Should be called once per frame.
///	It called GameWindow::GetTime().
		TEMPEST_API void Update (void);
		
///	This will attempt to move _deltaTime forward one single frame, at 60 frames per second. Note: Maybe this should be updated
///	to be configurable?
		TEMPEST_API void SingleStep(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Sets the Timer to be clamped.
///	\param state sets the clamp flag.
		inline void SetClamp(bool state)
		{
			_clamp = state;
		}

///	Returns the current state of _clamp.
		inline bool GetClamp(void) const
		{
			return _clamp;
		}

///	Sets the state of the _paused flag.
///	\param paused is the state to set.
		inline void SetPaused(bool paused)
		{
			_paused = paused;
		}

///	Returns the state of the _paused flag.
		inline bool GetPaused(void) const
		{
			return _paused;
		}

///	Sets the _timeScale variable.
///	\param is the new value for _timeScale.
		inline void SetTimeScale(F32 scale)
		{
			_timeScale = scale;
		}

///	Returns the current value for _timeScale.
		inline F32  GetTimeScale(void) const
		{
			return _timeScale;
		}

///	Returns the current _deltaTime.
		inline real DeltaTime(void) const
		{
			return _deltaTime;
		}

///	Returns the total time that the program has been running.
		inline F64 TotalTime(void) const
		{
			return _totalTime;
		}

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
///	Default Constructor, sets _deltaTime and _totalTime to 0, _timeScale to 1, _pastTime to the current time and _currentTime to 
///	_pastTime, and _paused to false.
		Timer(void);

	private:
		static shared_ptr<Timer> _instance; ///< Internal reference to self, used in Singleton Pattern.

/// Wrapper around QueryPerformanceFrequency. This will check the processor for how many cycles have passed, saving it into the 
/// time keeping variables of the instance.
		F64 _QueryCounter(void);

		bool _clamp;		///< If clamped, the timer will be forced to lock the framerate at 60 fps.
		bool _paused;		///< If paused, the Update loop will not run, allowing the timer to stop. 
		real _deltaTime;	///< The time that the last frame took to run. 
		real _timeScale;	///< A scale factor that is applied to the delta time.
		F64  _pcFreq;		///< The frequency of the processor. Used in determining the total time. 
		F64  _totalTime;	///< The total time that the program has been running. 
		F64  _pastTime;		///< The time stamp of the last frame. 
		F64  _currentTime;	///< The time stamp of this frame. 
		S64	 _counterStart; ///< This is the starting point of the counter.
		
	};// end class
}//end namespace
