#include <Engine/Controller.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
Controller::Controller(void) 
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
		_curActiveKeys[i] = false;//KeyStates::KEY_RELEASED;
		_pastActiveKeys[i] = false; //KeyStates::KEY_RELEASED;
	}
//	_transform = 
}

Controller::~Controller(void)
{  }

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
shared_ptr<Controller> Controller::_instance = NULL;

shared_ptr<Controller> Controller::Instance(void) 
{
	if (_instance == NULL) 
	{ 
		_instance = shared_ptr<Controller>(new Controller()); 
	}
	return _instance;
}		

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
void Controller::KeyDown(Keys k)
{ 
	_curActiveKeys[k] = true; 

	if(k == LEFT_MOUSE)
	{
		_leftClickCoordinates = Engine::Instance()->GetMousePos();
	}
	else if(k == RIGHT_MOUSE)
	{
		_rightClickCoordinates = Engine::Instance()->GetMousePos();
	}
}

void Controller::KeyUp(Keys k)
{ 
	_curActiveKeys[k] = false; 

}

const TM::Point2 Controller::GetMouseCoord(void)
{
	return Engine::Instance()->GetMousePos();
}

const TM::Point2 Controller::GetMouseCoordInScreen(void)
{
	return Engine::Instance()->GetMousePosInScreen();
}

void Controller::Update(void)
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

//=======================================================================================================
//KeyState Accessors
//=======================================================================================================
bool Controller::GetKeyDown(Keys k)
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

bool Controller::GetKeyHeld(Keys k)
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

bool Controller::GetKeyUp(Keys k)
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

bool Controller::GetKeyReleased(Keys k)
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