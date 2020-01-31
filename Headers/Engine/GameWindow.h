#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Point.h>
#include <Engine/Camera.h>
#include <Engine/Keys.h>

namespace TM = TempestMath; 

//===== STL Includes =====
#include <sstream>

namespace Tempest 
{
	class Camera;
	typedef shared_ptr<Camera> p_Camera;
 
///	Framework that will open a window in the designated operating system which
///	will be where the renderer will draw what it needs to for the game to be a
///	game. There will be system specific code in this section which will be how
///	the game will run on each system that is supported. 
///	Supported system:
///		Windows	 
	class GameWindow
	{	
	public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
///	No behavior. 
		TEMPEST_API ~GameWindow(void);

//==========================================================================================================================
//
//GameWindow Functions
//
//==========================================================================================================================
///	Singleton function. Returns the global pointer to the program window. 
		TEMPEST_API static shared_ptr<GameWindow> Instance(void);

/// Sets up program window. Makes all calls needed to start up a window. This is a helper function that takes are of all the
///	glfw calls needed.
///	\param width of created window
///	\param height of created window
///	\param wndName title of window
///	\param isFullScreen sets if the system makes the window fullscreen	
		TEMPEST_API void Init(S32 width, S32 height, string wndName, bool isFullScreen, bool initDefaultCam=true);

/// Processes all commands needed to run each frame.
		TEMPEST_API void Update(void);
		
///	Wrapper around glfwPollEvents. This polls any pending events. Used to capture user Input. 
		TEMPEST_API void ProcessEvents(void);

///	Wrapper around glfwSwapBuffers and glClear. Swap buffers will place the back buffer, that has been getting drawn to, 
///	as the active buffer, and glClear will set the background color, setting up the next frame to be drawn. 
		TEMPEST_API void BufferSwap(void);

///	Converts the glfw key codes into a key code that the engine can understand.
///	\param key is the glfw key code to be converted. 
		TEMPEST_API static Keys ConvertKeyCodes(int key);

///	Toggle that allows the frames per second to be displayed in the title of the window. 
		TEMPEST_API void DisplayFPS(void);

///	Toggle that changes the rendering to only use wireframes, drawing the lines the represent edges in a mesh instead of
///	filling in the faces. Used for debugging.  
		TEMPEST_API void ToggleWireFrame(void);

///	Moves the mouse cursor to the center of the program window. 
		TEMPEST_API void ResetMouseCursor(void);

///	Toggles the mouse cursor to be displayed.  
		TEMPEST_API void EnableMouseCursor(void);

///	Toggles the mouse cursor to no longer be displayed. This is true both inside and outside the program window, meaning that if you 
///	call this, your mouse will no longer work, until you either close the program or re-enable it using EnableMouseCursor(). 
		TEMPEST_API void DisableMouseCursor(void);

///	Toggles the mouse cursor to not be displayed in the program window. Outside of the program window it will behave as normal. 
		TEMPEST_API void HideMouseCursor(void);

///	Returns the position of the mouse cursor with the origin in the top left of the program window, ranging from 0 to 1. 
		TEMPEST_API const TM::Point GetMousePos(void);

///	Returns the position of the mouse cursor in pixels with the origin in the center of the program window, randing from the
///	program windows up - down - left - right values. Very important, this is in Screen Space, not world space.
		TEMPEST_API const TM::Point GetMousePosInScreen(void);

///	Wrapper around glfwGetTime. Used to find out how long the program has been running in miliseconds. Used by the KillerMath::Timer. 
		inline F64 GetTime(void)
		{
			return glfwGetTime();
		}

/// Reset to Camera to a default, orthographic projection based Camera object.
		TEMPEST_API void ResetCamera(void);
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Closes down the GameWindow and ends the program. 
		inline void EndRunning(void) 
		{ 
			_running = false;
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}
		
///	Returns the state of the game. True means that it should keep running, false means that it is shutting down. 
		inline bool GetRunning(void) 
		{ 
			return _running;
		}
 
///	Returns the total width of the program window in pixels. 
		inline S32 GetWidth(void)
		{ 
			return _totalWidth; 
		}
 
///	Returns the total heigth of the program window in pixel. 
		inline S32 GetHeight(void)
		{ 
			return _totalHeight; 
		}
		 
///	Returns half the width positive, representing the right most boundary of the program window. 
		inline F32 GetScreenRight(void)
		{ 
			return _right; 
		}
		
///	Returns half the width negative, representing the left most boundary of the program window.
		inline F32 GetScreenLeft(void)
		{ 
			return _left; 
		}
		 
///	Returns half the height positive, representing the top most boundary of the program window.
		inline F32 GetScreenTop(void)
		{ 
			return _top; 
		}
		
///	Returns half the height negative, repsrenting the bottom most boundary of the program window. 
		inline F32 GetScreenBottom(void)
		{ 
			return _bottom; 
		}

///	Sets the camera to a new Camera pointer, allowing you to change the Camera at run time. 
		inline void SetCamera(p_Camera cam)
		{
			_camera = cam;
		}

///	Returns the current Camera.
		inline p_Camera GetCamera(void)
		{
			return _camera;
		}

//==========================================================================================================================
//
//Callback Functions
//
//==========================================================================================================================
///	Callback function for glfw. Controls what happens when a key is pressed.
///	\param window is the pointer to the glfw window instance we are checking. 
///	\param key is the ID for the key that has been pressed. 
///	\param scancode is a platform specific token for each key pressed. 
///	\param action stores if it was a press or release
///	\param mods represents modifier keys; ctrl, shift, alt.
		TEMPEST_API static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

///	Callback function for glfw. Controls what happens when the screen is resized by the user (in the operating system). 
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param width is the new total width of the window. 
///	\param height is the new total height of the window.
		TEMPEST_API static void OnResize(GLFWwindow* window, int width, int height);

///	Callback function for glfw. Controls what happens when a mouse click happens (right, left, middle or any other). Currently, 
///	only right and left clicks are considered.  
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param button is the mouse button being pressed. 
///	\param action is the state, release or press.
///	\param mods represents modifier keys; ctrl, shift, alt.
		TEMPEST_API static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);

///	Callback function for glfw. Controls what happens when the mouse is detected to move. Currently not implemented.  
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param posX stores the x position value
///	\param posY stores the y posiition value. 
		TEMPEST_API static void OnMouseMove(GLFWwindow* window, F64 posX, F64 posY);

	private:
		static shared_ptr<GameWindow> _instance;		///< Singleton instance. Global pointer, allows only one GameWindow to be active.
		TEMPEST_API static S32     				  _totalWidth;		///< Total width of the window in pixels.
		TEMPEST_API static S32     				  _totalHeight;		///< Total height of the window in pixels.
		
		bool    _isFullScreen;							///< Fullscreen state of the window. True means full screen, false means not full screen.
		bool 	_running;								///< Running state of the window. True means its running, false means its time for shutdown. 
		bool 	_wireFrame;								///< State of wireframe based rendering. True means render in wireframe mode, false means normal rendering.
		F32     _right;									///< Right boundary of window in pixels with origin in the center of the window.
		F32     _left;									///< Left boundary of window in pixels with origin in the center of the window.
		F32     _top;									///< Top boundary of window in pixels with origin in the center of the window.
		F32     _bottom;								///< Bottom boundary of the window in pixels with origin in the center of the window.
		string  _wndName;								///< Title used for the window.
		GLFWwindow* _window;							///< Pointer to the glfw window instance.
		p_Camera _camera;


	protected:
//==========================================================================================================================
//
//Constructor
//
//========================================================================================================================== 
///	By default, sets all numeric values to 0, all bools to false, the _wndName to "Killer Engine" and _window to a null pointer.  
		GameWindow(void);

	};
	typedef shared_ptr<GameWindow> p_GameWindow;
}//End namespace