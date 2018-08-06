#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/ErrorManager.h>
#include <Engine/Matrix.h>
#include <Engine/Vector.h>
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

/*! Keycodes to access specific Key state. Each value is used to represent keys that are pressed by the user.
	These codes represent all possible key inputs. In order to add support for a new key, this enum must be 
	updated */
	enum Keys 
	{
		NO_KEY=0, 				///<Used as a fall through to indicated an error 
		A=1,					///< Alphabetic A key
		B=2,					///< Alphabetic B key
		C=3,					///< Alphabetic C key
		D=4,					///< Alphabetic D key
		E=5,					///< Alphabetic E key		
		F=6,					///< Alphabetic F key
		G=7,					///< Alphabetic G key
		H=8,					///< Alphabetic H key
		I=9,					///< Alphabetic I key
		J=10,					///< Alphabetic J key
		K=11,					///< Alphabetic K key
		L=12,					///< Alphabetic L key
		M=13,					///< Alphabetic M key
		N=14,					///< Alphabetic N key
		O=15,					///< Alphabetic O key
		P=16,					///< Alphabetic P key
		Q=17,					///< Alphabetic Q key
		R=18,					///< Alphabetic R key
		S=19,					///< Alphabetic S key
		T=20,					///< Alphabetic T key
		U=21,					///< Alphabetic U key
		V=22,					///< Alphabetic V key
		W=23,					///< Alphabetic W key
		X=24,					///< Alphabetic X key
		Y=25,					///< Alphabetic Y key
		Z=26,					///< Alphabetic Z key
		UP_ARROW=27,			///< Up Arrow key
		DOWN_ARROW=28,			///< Down Arrow key
		LEFT_ARROW=29,			///< Left Arrow key
		RIGHT_ARROW=30,			///< Right Arrow key
		ZERO=31,				///< 0 key
		ONE=32,					///< 1 key
		TWO=33,					///< 2 key
		THREE=34,				///< 3 key
		FOUR=35,				///< 4 key
		FIVE=36,				///< 5 key
		SIX=37,					///< 6 key
		SEVEN=38,				///< 7 key
		EIGHT=39,				///< 8 key
		NINE=40,				///< 9 key
		MINUS=41,				///< Minus key
		EQUAL=42,				///< Plus key
		SPACE=43,				///< Spacebar
		ESCAPE=44,				///< Escape key
		TAB=45,					///< Tab key
		LSHIFT=46,				///< Left Shift key
		RSHIFT=47,				///< Right Shift key
		ENTER=48,				///< Enter key
		RIGHT_MOUSE=49,			///< Right Mouse click
		LEFT_MOUSE=50,			///< Left Mouse click
		MIDDLE_MOUSE=51,		///< Middle Mouse click
	};
//==========================================================================================================================
//Documentation
//==========================================================================================================================	
/*! Human input device controller. Abstract Keyboard input is received through a system all found in the *Program class. 
	For example, in WinProgram, when windows gets a key input message for a key down even, KeyDown(Keys k) is called.

	Two enums are defined. 

	KeyStates represents all the possible states that a key can have. KEY_RELEASED  means that the key is not pressed. KEY_UP 
	means that the key was released this frame. 

	Keys represents all the supported keys. 

	Update handles the logic of changing they key states, with two KeyState arrays holding the current key states, that is 
	the key states of this frame and the past key states, that is the key states from last frame. */
	class Controller 
	{
	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
/*! Singleton function to get global instance of Controller. */
		static shared_ptr<Controller> Instance();

/*! Destructor. No special functions within it. */
		~Controller(void);

//==========================================================================================================================
//
//Controller Functions
//
//==========================================================================================================================
/*! Sets the new state of each key. */
		void Update(void);

/*! Used by WinProgram to set when a key is pressed down, based on system signals.
	\param k Keys: Keycode for key that has been pressed down. */
		inline void KeyDown(Keys k) 
		{ 
			_curActiveKeys[k] = true; 
		}

/*! Used by WinProgram to set when a key is no longer detected to be held down. 
	\param k Keys: Keycode for key that has been released. */
		inline void KeyUp(Keys k) 
		{ 
			_curActiveKeys[k] = false; 
		}

/*! Used by WinProgram to save the coordinates when a Left Mouse click is detected by the system. 
	\param coord Vector: x,y position on the screen of the click. */
		void LeftMouseClick(const KM::Vector& coord);

/*! Returns the raw coordinates of a Left Click in screen space. */
		const KM::Vector GetLeftMouseCoord(void) const
		{ 
			return _leftClickCoordinates; 
		}

/*! Used by WinProgram to save the coordinates when a Right Mouse click is detected by the system.
	\param coord Vector: x.y position on the screen of the click */
		void RightMouseClick(const KM::Vector& coord) 
		{ 
			_rightClickCoordinates = coord; 
		}

/*! Returns the raw coordinates of a Right click in screen space */		
		const KM::Vector GetRightMouseCoord(void) const
		{ 
			return _rightClickCoordinates; 
		}

/*! Returns true if k has been pressed down this frame.
	\param k Keys: Desired keycode. */
		bool GetKeyDown(Keys k);

/*! Returns true if k has been held down longer than 1 frame.
	\param k Keys: Desired keycode */
		bool GetKeyHeld(Keys k);

/*! Returns true if k has been released this frame.
	\params k Keys: Desired keycode */		
		bool GetKeyUp(Keys k);

/*! Returns true if k is not being pressed during this frame
	\param k Keys: Desired keycode */
		bool GetKeyReleased(Keys k);
		
/*
BUG! This is not copying anything at all. It is only passing the new refalone
		shared_ptr<Controller> operator=(Controller& c) 
		{ 
			return shared_ptr<Controller>(&c); 
		}
*/

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Controller(void);		

	private:
		static shared_ptr<Controller> _instance;		///< Singleton Global instance.
		static const int 			  _totalKeys = 51;	///< Total supported Keys from KeyCode.
		
		KeyStates 		_keyStates[_totalKeys];			///< Array of states for each key, indexed by ID.
		bool 			_pastActiveKeys[_totalKeys];	///< Array of keys in a pressed state as of last frame, indexed by ID.
		bool			_curActiveKeys[_totalKeys];		///< Array of keys in a pressed state as of this frame, indexed by ID.
		KM::Vector 	_leftClickCoordinates;			///< Coordinates of last left click.
		KM::Vector		_rightClickCoordinates;			///< Coordinates of last right click.
	};
}//End namespace