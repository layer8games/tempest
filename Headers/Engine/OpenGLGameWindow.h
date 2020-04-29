#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameWindow.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Point2.h>
#include <Engine/Camera.h>
#include <Engine/Controller.h>
#include <Engine/Keys.h>

namespace TM = TempestMath; 

//===== STL Includes =====
#include <sstream>

//=====OGL includes=====
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tempest 
{
    class GameWindow;
///	Framework that will open a window in the designated operating system which
///	will be where the renderer will draw what it needs to for the game to be a
///	game. There will be system specific code in this section which will be how
///	the game will run on each system that is supported. 
///	Supported system:
///		Windows	 
    class OpenGLGameWindow : public GameWindow
    {	
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
        OpenGLGameWindow(void);
///	No behavior. 
        TEMPEST_API ~OpenGLGameWindow(void);

//==========================================================================================================================
//
//OpenGLGameWindow Functions
//
//==========================================================================================================================
///	Singleton function. Returns the global pointer to the program window. 
        TEMPEST_API static shared_ptr<OpenGLGameWindow> Instance(void);

/// Sets up program window. Makes all calls needed to start up a window. This is a helper function that takes are of all the
///	glfw calls needed.
///	\param width of created window
///	\param height of created window
///	\param wndName title of window
///	\param isFullScreen sets if the system makes the window fullscreen	
        TEMPEST_API void v_Init(S32 width, S32 height, string wndName, bool isFullScreen) final;
        
///	Wrapper around glfwPollEvents. This polls any pending events. Used to capture user Input. 
        TEMPEST_API void v_ProcessEvents(void) final;

///	Wrapper around glfwSwapBuffers and glClear. Swap buffers will place the back buffer, that has been getting drawn to, 
///	as the active buffer, and glClear will set the background color, setting up the next frame to be drawn. 
        TEMPEST_API void v_BufferSwap(void) final;

///	Toggle that allows the frames per second to be displayed in the title of the window. 
        TEMPEST_API void v_DisplayFPS(void) final;

///	Toggle that changes the rendering to only use wireframes, drawing the lines the represent edges in a mesh instead of
///	filling in the faces. Used for debugging.  
        TEMPEST_API void v_ToggleWireFrame(void) final;

///	Moves the mouse cursor to the center of the program window. 
        TEMPEST_API void v_ResetMouseCursor(void) final;

///	Toggles the mouse cursor to be displayed.  
        TEMPEST_API void v_EnableMouseCursor(void) final;

///	Toggles the mouse cursor to no longer be displayed. This is true both inside and outside the program window, meaning that if you 
///	call this, your mouse will no longer work, until you either close the program or re-enable it using EnableMouseCursor(). 
        TEMPEST_API void v_DisableMouseCursor(void) final;

///	Toggles the mouse cursor to not be displayed in the program window. Outside of the program window it will behave as normal. 
        TEMPEST_API void v_HideMouseCursor(void) final;

///	Returns the position of the mouse cursor with the origin in the top left of the program window, ranging from 0 to 1. 
        TEMPEST_API const TM::Point2 v_GetMousePos(void) final;

///	Returns the position of the mouse cursor in pixels with the origin in the center of the program window, randing from the
///	program windows up - down - left - right values. Very important, this is in Screen Space, not world space.
        TEMPEST_API const TM::Point2 v_GetMousePosInScreen(void) final;

///	Wrapper around glfwGetTime. Used to find out how long the program has been running in miliseconds. Used by the KillerMath::Timer. 
        TEMPEST_API F64 v_GetTime(void) final;
        ///	Closes down the OpenGLGameWindow and ends the program. 
        TEMPEST_API void v_EndRunning(void) final;

        TEMPEST_API void v_SetScreenColor(const Color& col) final;
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
        static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

///	Callback function for glfw. Controls what happens when the screen is resized by the user (in the operating system). 
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param width is the new total width of the window. 
///	\param height is the new total height of the window.
        static void OnResize(GLFWwindow* window, int width, int height);

///	Callback function for glfw. Controls what happens when a mouse click happens (right, left, middle or any other). Currently, 
///	only right and left clicks are considered.  
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param button is the mouse button being pressed. 
///	\param action is the state, release or press.
///	\param mods represents modifier keys; ctrl, shift, alt.
        static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);

///	Callback function for glfw. Controls what happens when the mouse is detected to move. Currently not implemented.  
///	\param window is the pointer to the glfw window instance we are changing. 
///	\param posX stores the x position value
///	\param posY stores the y posiition value. 
        static void OnMouseMove(GLFWwindow* window, F64 posX, F64 posY);

    private:
///	Converts the glfw key codes into a key code that the engine can understand.
///	\param key is the glfw key code to be converted. 
        static Keys _ConvertKeyCodes(int key);
        
        GLFWwindow* _window;
    };
    typedef shared_ptr<OpenGLGameWindow> p_OpenGLGameWindow;
}//End namespace