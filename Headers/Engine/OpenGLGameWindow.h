#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameWindow.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Point2.h>
#include <Engine/Input.h>
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
    class OpenGLGameWindow : public GameWindow
    {	
    public:
        OpenGLGameWindow(void);
        
        TEMPEST_API ~OpenGLGameWindow(void);

        TEMPEST_API void v_Init(S32 width, S32 height, string wndName, bool isFullScreen) final;
        
        TEMPEST_API void v_ProcessEvents(void) final;

        TEMPEST_API void v_BufferSwap(void) final;

        TEMPEST_API void v_DisplayFPS(void) final;

        TEMPEST_API void v_ToggleWireFrame(void) final;

        TEMPEST_API void v_ResetMouseCursor(void) final;

        TEMPEST_API void v_EnableMouseCursor(void) final;

        TEMPEST_API void v_DisableMouseCursor(void) final;

        TEMPEST_API void v_HideMouseCursor(void) final;

        TEMPEST_API const TM::Point2 v_GetMousePos(void) final;

        TEMPEST_API const TM::Point2 v_GetMousePosInScreen(void) final;

        TEMPEST_API F64 v_GetTime(void) final;
        TEMPEST_API void v_EndRunning(void) final;

        TEMPEST_API void v_SetScreenColor(const Color& col) final;

        static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void OnResize(GLFWwindow* window, int width, int height);

        static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);

        static void OnMouseMove(GLFWwindow* window, F64 posX, F64 posY);

    private:
        static Keys _ConvertKeyCodes(int key);
        GLFWwindow* _window;
    };
    typedef shared_ptr<OpenGLGameWindow> p_OpenGLGameWindow;
}//End namespace