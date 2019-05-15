#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/ErrorManager.h>
#include <Engine/Matrix4.h>
#include <Engine/Point.h>
namespace KM = KillerMath;

//=====DirectInput includes=====
//#include <dinput.h>

namespace KillerEngine 
{
/// States that a key is allowed to be in. 
	enum KeyStates
	{
		KEY_DOWN = 1,
		KEY_HELD,
		KEY_UP,
		KEY_RELEASED
	};

/*! 
	Keycodes to access specific Key state. Each value is used to represent keys that are pressed by the user.
	These codes represent all possible key inputs. In order to add support for a new key, this enum must be 
	updated 
*/
	enum Keys 
	{
		NO_KEY, 			///<Used as a fall through to indicated an error 
		A,					///< Alphabetic A key
		B,					///< Alphabetic B key
		C,					///< Alphabetic C key
		D,					///< Alphabetic D key
		E,					///< Alphabetic E key		
		F,					///< Alphabetic F key
		G,					///< Alphabetic G key
		H,					///< Alphabetic H key
		I,					///< Alphabetic I key
		J,					///< Alphabetic J key
		K,					///< Alphabetic K key
		L,					///< Alphabetic L key
		M,					///< Alphabetic M key
		N,					///< Alphabetic N key
		O,					///< Alphabetic O key
		P,					///< Alphabetic P key
		Q,					///< Alphabetic Q key
		R,					///< Alphabetic R key
		S,					///< Alphabetic S key
		T,					///< Alphabetic T key
		U,					///< Alphabetic U key
		V,					///< Alphabetic V key
		W,					///< Alphabetic W key
		X,					///< Alphabetic X key
		Y,					///< Alphabetic Y key
		Z,					///< Alphabetic Z key
		UP_ARROW,			///< Up Arrow key
		DOWN_ARROW,			///< Down Arrow key
		LEFT_ARROW,			///< Left Arrow key
		RIGHT_ARROW,		///< Right Arrow key
		ZERO,				///< 0 key
		ONE,				///< 1 key
		TWO,				///< 2 key
		THREE,				///< 3 key
		FOUR,				///< 4 key
		FIVE,				///< 5 key
		SIX,				///< 6 key
		SEVEN,				///< 7 key
		EIGHT,				///< 8 key
		NINE,				///< 9 key
		MINUS,				///< Minus key
		EQUAL,				///< Plus key
		SPACE,				///< Spacebar
		ESCAPE,				///< Escape key
		TAB,				///< Tab key
		LSHIFT,				///< Left Shift key
		RSHIFT,				///< Right Shift key
		ENTER,				///< Enter key
		RIGHT_MOUSE,		///< Right Mouse click
		LEFT_MOUSE,			///< Left Mouse click
		MIDDLE_MOUSE,		///< Middle Mouse click
		F1,					///< F1 key
		F2,					///< F2 key
		F3,					///< F3 key
		F4,					///< F4 key
		F5,					///< F5 key
		F6,					///< F6 key
		F7,					///< F7 Key
		F8,					///< F8 key
		F9,					///< F9 key
		F10,				///< F10 key
		F11,				///< F11 key
		TOTAL_KEYS			///< Total keys available. 
	};
//==========================================================================================================================
//Documentation
//==========================================================================================================================	
/*! 
	Human input device controller. Abstract Keyboard input is received through a system all found in the *Program class. 
	For example, in WinProgram, when windows gets a key input message for a key down even, KeyDown(Keys k) is called.

	Two enums are defined. 

	KeyStates represents all the possible states that a key can have. KEY_RELEASED  means that the key is not pressed. KEY_UP 
	means that the key was released this frame. 

	Keys represents all the supported keys. 

	Update handles the logic of changing they key states, with two KeyState arrays holding the current key states, that is 
	the key states of this frame and the past key states, that is the key states from last frame. 
*/
	class Controller 
	{
	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
/*! 
	Singleton function to get global instance of Controller. 
*/
		static shared_ptr<Controller> Instance();

/*! 
	Destructor. No special functions within it. 
*/
		~Controller(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
/*! 
	Sets the new state of each key. 
*/
		void Update(void);

/*! 
	Used by WinProgram to set when a key is pressed down, based on system signals.
	\param k Keys: Keycode for key that has been pressed down. 
*/
		void KeyDown(Keys k);

/*! 
	Used by WinProgram to set when a key is no longer detected to be held down. 
	\param k Keys: Keycode for key that has been released. 
*/
		void KeyUp(Keys k);


/*! 
	Returns the raw mouse coordinates from the WinProgram. This is with the origin in the top left corner of the screen. 
*/
		const KM::Point GetMouseCoord(void);

/*! 
	Returns the mouse coordinates in screen space, with the origin in the center of the screen. Wrapper around WinProgram. 
*/
		const KM::Point GetMouseCoordInScreen(void);

/*! 
	Returns the raw coordinates of a Left Click in screen space. 
*/
		inline const KM::Point GetLeftMouseCoord(void) const
		{ 
			return _leftClickCoordinates; 
		}

/*! 
	Returns the raw coordinates of a Right click in screen space 
*/		
		inline const KM::Point GetRightMouseCoord(void) const
		{ 
			return _rightClickCoordinates; 
		}

/*! 
	Returns true if k has been pressed down this frame.
	\param k Keys: Desired keycode. 
*/
		bool GetKeyDown(Keys k);

/*! 
	Returns true if k has been held down longer than 1 frame.
	\param k Keys: Desired keycode 
*/
		bool GetKeyHeld(Keys k);

/*! 
	Returns true if k has been released this frame.
	\params k Keys: Desired keycode 
*/		
		bool GetKeyUp(Keys k);

/*! 
	Returns true if k is not being pressed during this frame
	\param k Keys: Desired keycode 
*/
		bool GetKeyReleased(Keys k);

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
		KM::Point 	_leftClickCoordinates;			///< Coordinates of last left click. Unused. 
		KM::Point	_rightClickCoordinates;			///< Coordinates of last right click. Unused.
		KM::Point 	_leftClickCoordInScreen;		///< Cached value of last left click in screen space. Unused. 
		KM::Point 	_rightClickCoordInScreen;		///< Cached value of last right click in screen space. Unused. 
	};
}//End namespace