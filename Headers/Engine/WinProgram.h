/*==========================================================================
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
#ifndef WIN_PROGRAM_H
#define WIN_PROGRAM_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath; 


//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

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
		WinProgram(void);
		
		~WinProgram(void);

		void ShutDown(void)
		{
			delete _instance;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		HINSTANCE GetHINSTANCE(void) 	
		{ 
			return _wndClass.hInstance; 
		}

		HWND GetHWND(void)
		{
			return _hwnd; 
		}
		
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
		static WinProgram* Instance(void);

		void Init(S32 width, S32 height, string wndName, bool isFullScreen);
		
		void ProcessWndEvents(void);

		Keys ConvertKeyCodes(WPARAM wParam);
		
		void BufferSwap(void);

		void SetBackgroundColor(Color& c) 
		{
			_bgColor[0] = c.GetRed();
			_bgColor[1] = c.GetGreen();
			_bgColor[2] = c.GetBlue();
			_bgColor[3] = c.GetAlpha();
		}
		
//==========================================================================================================================
//
//System Windows Functions
//
//==========================================================================================================================	
		static LRESULT CALLBACK StaticWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		static WinProgram* _instance;
		bool    _isFullScreen;
		S32     _totalWidth;
		S32     _totalHeight;
		S32     _right;
		S32     _left;
		S32     _top;
		S32     _bottom;
		string  _wndName;
		GLfloat _bgColor[4];

		//=====Windows Variables=====
		HWND _hwnd;
		HDC _hdc;
		HGLRC _hglrc;
		WNDCLASSEX _wndClass;

//==========================================================================================================================
//
//Private WinProgram Functions
//
//==========================================================================================================================
		void _SetTempPixelFormat(void);
		
		void _SetPixelFormat(void);

	};	
}//End namespace

#endif