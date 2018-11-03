/*========================================================================
The high precision timer for the Killer1 Engine. At the time of writting
this the timer is windows specific, but cross platform functionality is
planned in the future. 

It uses the GLFW function glfwGetTime, located in the WinProgram to get
the total time that the glfw window has been open. It used to have a 
customer frequency timer, but this turned out to be too eratic, and 
was removed.  

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>

namespace KE = KillerEngine;

namespace KillerMath 
{

	class Timer 
	{ 
	public:
		~Timer(void);

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================		
		static shared_ptr<Timer> Instance(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetClamp(bool state)
		{
			_clamp = state;
		}

		inline bool GetClamp(void) const
		{
			return _clamp;
		}

		inline void SetPaused(bool paused)
		{ 
			_paused = paused; 
		}
		
		inline bool GetPaused(void) const
		{ 
			return _paused; 
		}

		inline void SetTimeScale(F32 scale)
		{ 
			_timeScale = scale; 
		}
		
		inline F32  GetTimeScale(void) const
		{ 
			return _timeScale; 
		}

		inline real DeltaTime(void) const
		{ 
			return _deltaTime;
		}
		
		inline F64 TotalTime(void) const
		{ 
			return _totalTime; 
		}

//==========================================================================================================================
//
//Timer Functions
//
//==========================================================================================================================		
		void Update (void);
		
		void SingleStep(void);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		explicit Timer(void);

	private:
		static shared_ptr<Timer> _instance;

		bool _clamp;
		real  _deltaTime;
		real  _timeScale;
		F64  _totalTime;
		F64  _pastTime;
		F64  _currentTime;
		bool _paused;
	};

}//End namespace
