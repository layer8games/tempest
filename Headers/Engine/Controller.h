#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/ErrorManager.h>
#include <Engine/Matrix.h>
#include <Engine/Vector2.h>
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

/// Keycodes to access specific Key state
	enum Keys 
	{
		NO_KEY=0,
		A=1,
		B=2,
		C=3,
		D=4,
		E=5,
		F=6,
		G=7,
		H=8,
		I=9,
		J=10,
		K=11,
		L=12,
		M=13,
		N=14,
		O=15,
		P=16,
		Q=17,
		R=18,
		S=19,
		T=20,
		U=21,
		V=22,
		W=23,
		X=24,
		Y=25,
		Z=26,
		UP_ARROW=27,
		DOWN_ARROW=28,
		LEFT_ARROW=29,
		RIGHT_ARROW=30,
		ZERO=31,
		ONE=32,
		TWO=33,
		THREE=34,
		FOUR=35,
		FIVE=36,
		SIX=37,
		SEVEN=38,
		EIGHT=39,
		NINE=40,
		MINUS=41,
		PLUS=42,
		SPACE=43,
		ESCAPE=44,
		TAB=45,
		LSHIFT=46,
		RSHIFT=47,
		ENTER=48,
		RIGHT_MOUSE=49,
		LEFT_MOUSE=50,
		MIDDLE_MOUSE=51,
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
/*! Singleton function to get global instance of Controller.
	\param none */
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
	\param coord Vector2: x,y position on the screen of the click. */
		void LeftMouseClick(const KM::Vector2& coord);

/*! Returns the raw coordinates of a Left Click in screen space. */
		const KM::Vector2 GetLeftMouseCoord(void) const
		{ 
			return _leftClickCoordinates; 
		}

/*! Used by WinProgram to save the coordinates when a Right Mouse click is detected by the system.
	\param coord Vector2: x.y position on the screen of the click */
		void RightMouseClick(const KM::Vector2& coord) 
		{ 
			_rightClickCoordinates = coord; 
		}

/*! Returns the raw coordinates of a Right click in screen space */		
		const KM::Vector2 GetRightMouseCoord(void) const
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
		static shared_ptr<Controller> _instance;
		static const int 			  _totalKeys = 51;
		
		KeyStates 		_keyStates[_totalKeys];
		bool 			_pastActiveKeys[_totalKeys];
		bool			_curActiveKeys[_totalKeys];
		KM::Vector2 	_leftClickCoordinates;
		KM::Vector2		_rightClickCoordinates;
	};
}//End namespace