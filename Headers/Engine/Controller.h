#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/GameWindow.h>
#include <Engine/ErrorManager.h>
#include <Engine/Matrix4.h>
#include <Engine/Point.h>
#include <Engine/Keys.h>

namespace TM = TempestMath;

//=====DirectInput includes=====
//#include <dinput.h>

namespace Tempest 
{
/// States that a key is allowed to be in. 
	enum TEMPEST_API KeyStates
	{
		KEY_DOWN = 1,
		KEY_HELD,
		KEY_UP,
		KEY_RELEASED
	};

//==========================================================================================================================
//Documentation
//==========================================================================================================================	 
/// Human input device controller. Abstract Keyboard input is received through a system all found in the *Program class. 
/// For example, in GameWindow, when windows gets a key input message for a key down even, KeyDown(Keys k) is called.

/// Two enums are defined. 

/// KeyStates represents all the possible states that a key can have. KEY_RELEASED  means that the key is not pressed. KEY_UP 
/// means that the key was released this frame. 

/// Keys represents all the supported keys. 

/// Update handles the logic of changing they key states, with two KeyState arrays holding the current key states, that is 
/// the key states of this frame and the past key states, that is the key states from last frame. 
	class Controller
	{
	public:
//==========================================================================================================================
//
//Singleton Functions
//
//========================================================================================================================== /// 	Singleton function to get global instance of Controller. 
		TEMPEST_API static shared_ptr<Controller> Instance();

/// Destructor. No special functions within it. 
		TEMPEST_API ~Controller(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
/// Sets the new state of each key. 
		TEMPEST_API void Update(void);

/// Used by GameWindow to set when a key is pressed down, based on system signals.
/// \param k Keys: Keycode for key that has been pressed down. 
		TEMPEST_API void KeyDown(Keys k);
 
/// Used by GameWindow to set when a key is no longer detected to be held down. 
/// \param k Keys: Keycode for key that has been released. 
		TEMPEST_API void KeyUp(Keys k);

/// Returns the raw mouse coordinates from the GameWindow. This is with the origin in the top left corner of the screen. 
		TEMPEST_API const TM::Point GetMouseCoord(void);

/// Returns the mouse coordinates in screen space, with the origin in the center of the screen. Wrapper around GameWindow. 
		TEMPEST_API const TM::Point GetMouseCoordInScreen(void);

/// Returns the raw coordinates of a Left Click in screen space. 
		inline const TM::Point GetLeftMouseCoord(void) const
		{ 
			return _leftClickCoordinates; 
		}

/// Returns the raw coordinates of a Right click in screen space 
		inline const TM::Point GetRightMouseCoord(void) const
		{ 
			return _rightClickCoordinates; 
		}

/// Returns true if k has been pressed down this frame.
/// \param k Keys: Desired keycode. 
		TEMPEST_API bool GetKeyDown(Keys k);

/// Returns true if k has been held down longer than 1 frame.
/// \param k Keys: Desired keycode
		TEMPEST_API bool GetKeyHeld(Keys k);

/// Returns true if k has been released this frame.
/// \params k Keys: Desired keycode 
		TEMPEST_API bool GetKeyUp(Keys k);

/// Returns true if k is not being pressed during this frame
/// \param k Keys: Desired keycode
		TEMPEST_API bool GetKeyReleased(Keys k);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Controller(void);		

	private:
		static shared_ptr<Controller> _instance;	///< Singleton Global instance.
		
		KeyStates 	_keyStates[TOTAL_KEYS];			///< Array of states for each key, indexed by ID.
		bool 		_pastActiveKeys[TOTAL_KEYS];	///< Array of keys in a pressed state as of last frame, indexed by ID.
		bool		_curActiveKeys[TOTAL_KEYS];		///< Array of keys in a pressed state as of this frame, indexed by ID.
		TM::Point 	_leftClickCoordinates;			///< Coordinates of last left click. Unused. 
		TM::Point	_rightClickCoordinates;			///< Coordinates of last right click. Unused.
		TM::Point 	_leftClickCoordInScreen;		///< Cached value of last left click in screen space. Unused. 
		TM::Point 	_rightClickCoordInScreen;		///< Cached value of last right click in screen space. Unused. 
	};
	typedef shared_ptr<Controller> p_Controller;
}//End namespace