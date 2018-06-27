/*==========================================================================//!
@file

Framework that will open a window in the designated operating system which
will be where the renderer will draw what it needs to for the game to be a
game. There will be system specific code in this section which will be how
the game will run on each system that is supported. 

Supported system:
	Windows


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
===========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath; 

namespace KillerEngine 
{
	class Controller;
	enum Keys;

	class WinProgram
	{	
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		~WinProgram(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		S32 GetWidth(void)
		{ 
			return _totalWidth; 
		}
		
		S32 GetRight(void)
		{ 
			return _right; 
		}
		
		S32 GetLeft(void)
		{ 
			return _left; 
		}
		
		S32 GetHeight(void)
		{ 
			return _totalHeight; 
		}
		
		S32 GetTop(void)
		{ 
			return _top; 
		}
		
		S32 GetBottom(void)
		{ 
			return _bottom; 
		}

//==========================================================================================================================
//
//WinProgram Functions
//
//==========================================================================================================================
		static shared_ptr<WinProgram> Instance(void);

/*! \brief Sets up Windows Program
	\details Makes all calls needed to start up a window. This is means to abstract away system specific callls
	\param width S32: width of created window
	\param height S32: height of created window
	\param wndName string: title of window
	\param isFullScreen bool: Sets if the system makes the window fullscreen
*/		
		void Init(S32 width, S32 height, string wndName, bool isFullScreen);
		
		void ProcessEvents(void);
		
		void BufferSwap(void);

		void SetBackgroundColor(const Color& c);

	private:
		static shared_ptr<WinProgram> _instance;
		
		bool    _isFullScreen;
		S32     _totalWidth;
		S32     _totalHeight;
		S32     _right;
		S32     _left;
		S32     _top;
		S32     _bottom;
		string  _wndName;
		GLfloat _bgColor[4];
		GLFWwindow* _window;

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		WinProgram(void);

	};	
}//End namespace