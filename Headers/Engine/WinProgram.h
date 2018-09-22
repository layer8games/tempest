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
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Vector.h>

namespace KM = KillerMath; 

//===== STL Includes =====
#include <sstream>

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
		inline void EndRunning(void) 
		{ 
			_running = false;
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}
		
		inline bool GetRunning(void) 
		{ 
			return _running;
		}

		inline S32 GetWidth(void)
		{ 
			return _totalWidth; 
		}
		
		inline S32 GetRight(void)
		{ 
			return _right; 
		}
		
		inline S32 GetLeft(void)
		{ 
			return _left; 
		}
		
		inline S32 GetHeight(void)
		{ 
			return _totalHeight; 
		}
		
		inline S32 GetTop(void)
		{ 
			return _top; 
		}
		
		inline S32 GetBottom(void)
		{ 
			return _bottom; 
		}

		inline void SetBackgroundColor(const Color& c)
		{
			_bgColor = c;
			glClearColor(_bgColor[0], _bgColor[1], _bgColor[2], _bgColor[3]);
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

		static Keys ConvertKeyCodes(int key);

		void DisplayFPS(void);

		void ToggleWireFrame(void);

		void ResetMouseCursor(void);

		void EnableMouseCursor(void);

		void DisableMouseCursor(void);

		void HideMouseCursor(void);

		const KM::Vector GetMousePos(void);

//==========================================================================================================================
//
//Callback Functions
//
//==========================================================================================================================
		static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mode);

		static void OnResize(GLFWwindow* window, int width, int height);

		static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);

		static void OnMouseMove(GLFWwindow* window, F64 posX, F64 posY);

	private:
		static shared_ptr<WinProgram> _instance;
		static S32     				  _totalWidth;
		static S32     				  _totalHeight;
		
		bool    _isFullScreen;
		bool 	_running;
		bool 	_wireFrame;
		S32     _right;
		S32     _left;
		S32     _top;
		S32     _bottom;
		string  _wndName;
		Color 	_bgColor;
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