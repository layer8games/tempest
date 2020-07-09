
#include "stdafx.h"
#include <Engine/Input.h>
using namespace Tempest;

Input::Input(void) 
:
_keyStates{},
_pastActiveKeys{},
_curActiveKeys{},
_leftClickCoordinates(0.0f), 
_rightClickCoordinates(0.0f),
_leftClickCoordInScreen(0.0f),
_rightClickCoordInScreen(0.0f)
{
    for(int i = 0; i < TOTAL_KEYS; ++i)
    {
        _curActiveKeys[i] = false;
        _pastActiveKeys[i] = false;
    }
}

Input::~Input(void)
{  }

shared_ptr<Input> Input::_instance = NULL;

shared_ptr<Input> Input::Instance(void) 
{
    if (_instance == NULL) 
    { 
        _instance = shared_ptr<Input>(new Input()); 
    }
    return _instance;
}		

void Input::KeyDown(Keys k)
{ 
    _curActiveKeys[k] = true; 

    if(k == LEFT_MOUSE)
    {
        _leftClickCoordinates = Driver::Instance()->GetMousePos();
    }
    else if(k == RIGHT_MOUSE)
    {
        _rightClickCoordinates = Driver::Instance()->GetMousePos();
    }
}

void Input::KeyUp(Keys k)
{ 
    _curActiveKeys[k] = false; 

}

const TM::Point2 Input::GetMouseCoord(void)
{
    return Driver::Instance()->GetMousePos();
}

const TM::Point2 Input::GetMouseCoordInScreen(void)
{
    return Driver::Instance()->GetMousePosInScreen();
}

void Input::Update(void)
{
    for(int i = 0; i < TOTAL_KEYS; ++i)
    {
        //check if key was just pressed
        if(!_pastActiveKeys[i] && _curActiveKeys[i])
            _keyStates[i] = KeyStates::KEY_DOWN;

        //check if key is being held
        if(_pastActiveKeys[i] && _curActiveKeys[i])
            _keyStates[i] = KeyStates::KEY_HELD;

        //check if key has been release this frame
        if(_pastActiveKeys[i] && !_curActiveKeys[i])
            _keyStates[i] = KeyStates::KEY_UP;

        //check if key is not being pressed
        if(!_pastActiveKeys[i] && !_curActiveKeys[i] )
            _keyStates[i] = KeyStates::KEY_RELEASED;

        //Save current state for next frame
        _pastActiveKeys[i] = _curActiveKeys[i];
    }
}

bool Input::GetKeyDown(Keys k)
{
    if(_keyStates[k] == KeyStates::KEY_DOWN) 
    { 
        return true; 
    }
    else 
    { 
        return false; 
    }
}

bool Input::GetKeyHeld(Keys k)
{
    if(_keyStates[k] == KeyStates::KEY_HELD)
    { 
        return true; 
    }
    else
    { 
        return false; 
    }
}

bool Input::GetKeyUp(Keys k)
{
    if(_keyStates[k] == KeyStates::KEY_UP)
    { 
        return true; 
    }
    else
    { 
        return false; 
    }
}

bool Input::GetKeyReleased(Keys k)
{
    if(_keyStates[k] == KeyStates::KEY_RELEASED)
    { 
        return true; 
    }
    else
    { 
        return false;
    }
}