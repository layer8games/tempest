#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/ErrorManager.h>
#include <Engine/Matrix4.h>
#include <Engine/Point2.h>
#include <Engine/Keys.h>

namespace TM = TempestMath;

namespace Tempest 
{
    enum TEMPEST_API KeyStates
    {
        KEY_DOWN = 1,
        KEY_HELD,
        KEY_UP,
        KEY_RELEASED
    };

    class Controller
    {
    public:
        TEMPEST_API static shared_ptr<Controller> Instance();

        TEMPEST_API ~Controller(void);

        TEMPEST_API void Update(void);

        TEMPEST_API void KeyDown(Keys k);

        TEMPEST_API void KeyUp(Keys k);

        TEMPEST_API const TM::Point2 GetMouseCoord(void);

        TEMPEST_API const TM::Point2 GetMouseCoordInScreen(void);

        inline const TM::Point2 GetLeftMouseCoord(void) const
        { 
            return _leftClickCoordinates; 
        }

        inline const TM::Point2 GetRightMouseCoord(void) const
        { 
            return _rightClickCoordinates; 
        }

        TEMPEST_API bool GetKeyDown(Keys k);

        TEMPEST_API bool GetKeyHeld(Keys k);

        TEMPEST_API bool GetKeyUp(Keys k);

        TEMPEST_API bool GetKeyReleased(Keys k);

    protected:
        Controller(void);		

    private:
        static shared_ptr<Controller> _instance;	
        KeyStates _keyStates[TOTAL_KEYS];			
        bool _pastActiveKeys[TOTAL_KEYS];	
        bool _curActiveKeys[TOTAL_KEYS];		
        TM::Point2 _leftClickCoordinates;			
        TM::Point2 _rightClickCoordinates;			
        TM::Point2 _leftClickCoordInScreen;		
        TM::Point2 _rightClickCoordInScreen;		
    };
    typedef shared_ptr<Controller> p_Controller;
}//End namespace