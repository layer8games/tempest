#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>


namespace TE = Tempest;

namespace TempestMath 
{

    class Timer 
    { 
    public:
        TEMPEST_API ~Timer(void);		

        TEMPEST_API static shared_ptr<Timer> Instance(void);
        
        TEMPEST_API void Update (F64 newTime);
        
        TEMPEST_API void SingleStep(void);

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

    protected:		
        Timer(void);

    private:
        static shared_ptr<Timer> _instance;

        bool _clamp;	
        bool _paused;	
        real _deltaTime;
        real _timeScale;
        F64  _totalTime;
        F64  _pastTime;	
        F64  _currentTime;
        
    };// end class
}//end namespace
